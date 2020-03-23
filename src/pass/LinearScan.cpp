#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "pass/LinearScan.h"
#include "options.h"

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
			int endpoint = interval.endpoint();
			for (auto iter = active.begin(), end = active.end(); iter != end; ++iter) {
				if (endpoint < (*iter)->endpoint()) {
					active.insert(iter, &interval);
					return;
				}
			}
			active.push_back(&interval);
		};

		std::function<void(Interval &)> addLocation = [&](Interval &interval) {
			function.addToStack(interval.variable, StackLocation::Purpose::Spill);
			if (function.spill(interval.variable))
				++spill_count;
		};

		std::function<void(Interval &)> expireOldIntervals = [&](Interval &interval) {
			for (auto iter = active.begin(); iter != active.end();) {
				Interval &jnterval = **iter;
				if (interval.startpoint() <= jnterval.endpoint())
					return;
				pool.insert(jnterval.reg);
				iter = active.erase(iter);
			}
		};

		std::function<bool(Interval &)> maySpill = [&](Interval &interval) {
			VariablePtr variable = interval.variable;
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
		std::cout << "\e[1;4m" << *name << "(" << getArity() << ")\e[0m [spills: " << spill_count << "]\n";
		for (Interval &interval: intervals) {
			std::cout << "    Interval for variable %" << interval.variable->id << ": [%"
			          << interval.firstDefinition->label << ", %" << interval.lastUse->label << "]; reg = $"
			          << WhyInfo::registerName(interval.reg) << " (" << interval.reg << ")\n";
		}
#endif
#ifdef DEBUG_STACK
		if (!function.stack.empty()) {
			std::cout << "Stack for \e[1m" << *function.name << "\e[0m (" << function.stack.size() << "):\n";
			for (const std::pair<const int, StackLocation> &pair: function.stack) {
				std::cout << "    " << pair.first << ": " << pair.second.getName()
				          << " (" << pair.second.width << ")\n";
			}
		}
		std::cout << "\n";
#endif

		return spill_count;
	}
}
