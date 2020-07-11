#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "pass/LinearScan.h"
#include "options.h"

#define DEBUG_INTERVALS
// #define DEBUG_STACK
// #define DEBUG_LINEAR_SCAN

namespace LL2W::Passes {
	int linearScan(Function &function) {
#ifdef DEBUG_LINEAR_SCAN
		std::cerr << "\e[2mScanning \e[0;1m" << *function.name << "\e[0;2m {\e[0m\n";
		function.debugStack();
#endif

		std::list<Interval> intervals = function.sortedIntervals();
		std::list<Interval *> active;
		std::set<int> pool = WhyInfo::makeRegisterPool();
		int spill_count = 0;

		std::function<void(Interval &)> addToActive = [&](Interval &interval) {
			// std::cout << "\e[31mAddToActive\e[39;2m(\e[22m" << interval << "\e[2m)\e[22m\n";
			const int endpoint = interval.endpoint();
			for (auto iter = active.begin(), end = active.end(); iter != end; ++iter) {
#ifdef DEBUG_LINEAR_SCAN
				std::cerr << "E " << interval << " < E " << **iter << "?\n";
#endif
				if (endpoint < (*iter)->endpoint()) {
					active.insert(iter, &interval);
					return;
				}
			}
			active.push_back(&interval);
		};

		std::function<void(Interval &)> addLocation = [&](Interval &interval) {
			// std::cerr << "\e[31mAddLocation\e[39;2m(\e[22m" << interval << "\e[2m)\e[22m\n";
			function.addToStack(interval.variable.lock(), StackLocation::Purpose::Spill);
			// std::cerr << "\e[31m::\e[39m\n";
			if (function.spill(interval.variable.lock()))
				++spill_count;
			// std::cerr << "\e[31m//AddLocation\e[39m\n";
		};

		std::function<void(Interval &)> expireOldIntervals = [&](Interval &interval) {
			std::cerr << "\e[31mExpireOldIntervals\e[39;2m(\e[22m" << interval << "\e[2m)\e[22m\n";
			for (auto iter = active.begin(); iter != active.end();) {
				Interval &jnterval = **iter;
#ifdef DEBUG_LINEAR_SCAN
				std::cerr << "S " << interval << " <= E " << jnterval << "?\n";
				std::cerr << "  " << function.cfg[interval.startpoint()].label() << "\n";
				std::cerr << "  " << function.cfg[jnterval.endpoint()].label() << "\n";
#endif
				// if (function.cfg[interval.startpoint()].canReach(function.cfg[jnterval.endpoint()])) {
				// if ((function.cfg[interval.startpoint()].canReach(function.cfg[jnterval.endpoint()])
				// 	 && function.cfg[jnterval.endpoint()].canReach(function.cfg[interval.startpoint()]))
				//     || interval.startpoint() == jnterval.endpoint()) {
				// if (function.cfg[jnterval.endpoint()].canReach(function.cfg[interval.startpoint()]) || interval.startpoint() == jnterval.endpoint()) {
				if (interval.startpoint() <= jnterval.endpoint()) {
					// std::cerr << "Bye\n";
					return;
				}
#ifdef DEBUG_LINEAR_SCAN
				std::cerr << "Inserting to pool: " << jnterval.reg << " (" << WhyInfo::registerName(jnterval.reg)
				          << ") from " << jnterval << "\n";
#endif
				pool.insert(jnterval.reg);
				iter = active.erase(iter);
			}
		};

		std::function<bool(Interval &)> maySpill = [&](Interval &interval) {
			VariablePtr variable = interval.variable.lock();
#ifdef DEBUG_LINEAR_SCAN
			std::cerr << "[maySpill(" << *variable << "): "
			          << (variable->definitions.size() != 1 || variable->onlyDefinition()->maySpill()? "true" : "false")
			          << "]";
			if (variable->definitions.size() == 1)
				std::cerr << " \e[2m//\e[0m " << variable->onlyDefinition()->debugExtra();
			std::cerr << "\n";
#endif
			return variable->definitions.size() != 1 || variable->onlyDefinition()->maySpill();
		};

		std::function<void(Interval &)> spillAtInterval = [&](Interval &interval) {
			// std::cerr << "\e[31mSpillAtInterval\e[39;2m(\e[22m" << interval << "\e[2m)\e[22m\n";
#ifdef DEBUG_LINEAR_SCAN
			std::cerr << "Active:"; for (Interval *ivl: active) std::cerr << " " << *ivl->variable; std::cerr << "\n";
#endif
			auto iter = active.end(), prebegin = active.begin();
			--prebegin;
			for (--iter; iter != prebegin && !maySpill(**iter); --iter);
#ifdef DEBUG_LINEAR_SCAN
			if (iter == prebegin)
				std::cerr << "iter == prebegin. This is not good.\n";
#endif
			Interval &spill = iter == prebegin? *active.back() : **iter;
#ifdef DEBUG_LINEAR_SCAN
			std::cerr << "Chose spill: " << *spill.variable << "\n";
#endif
			if (interval.endpoint() < spill.endpoint() || !maySpill(interval)) {
			// if (interval.endpoint() < spill.endpoint()) {
				interval.setRegister(spill.reg);
				addLocation(spill);
				active.remove(&spill);
				addToActive(interval);
			} else {
#ifdef DEBUG_LINEAR_SCAN
				std::cerr << "Spilling " << *interval.variable << " instead.";
				if (interval.variable->definitions.size() == 1)
					std::cerr << " \e[2m//\e[0m " << interval.variable->onlyDefinition()->debugExtra();
				std::cerr << "\n";
#endif
				addLocation(interval);
			}
		};

		function.precolorArguments(intervals);

		for (Interval &interval: intervals) {
			if (WhyInfo::isSpecialPurpose(interval.reg))
				continue;
			expireOldIntervals(interval);
			if (active.size() == static_cast<size_t>(WhyInfo::allocatableRegisters)) {
				spillAtInterval(interval);
			} else {
				pool.erase(interval.setRegister(*pool.begin()));
				addToActive(interval);
			}
		}
#ifdef DEBUG_LINEAR_SCAN
		std::cerr << "\e[2m}\e[0m\n\n";
#endif
#ifdef DEBUG_INTERVALS
		std::cerr << "\e[1;4m" << *function.name << "(" << function.getArity() << ")\e[0m [spills: " << spill_count
		          << "]\n";
		for (Interval &interval: intervals) {
			std::cerr << "    Interval for variable %" << interval.variable.lock()->id << ": [%"
			          << *interval.firstDefinition.lock()->label << ", %" << *interval.lastUse.lock()->label
			          << "]; reg = $" << WhyInfo::registerName(interval.reg) << " (" << interval.reg << ")\n";
		}
#endif
#ifdef DEBUG_STACK
		if (!function.stack.empty()) {
			std::cerr << "Stack for \e[1m" << *function.name << "\e[0m (" << function.stack.size() << "):\n";
			for (const std::pair<const int, StackLocation> &pair: function.stack) {
				std::cerr << "    " << pair.first << ": " << pair.second.getName()
				          << " (" << pair.second.width << "): "
				          << (pair.second.purpose == StackLocation::Purpose::Spill? "Spill" : "Alloca") << "\n";
			}
		}
		std::cerr << "\n";
#endif

		return spill_count;
	}
}
