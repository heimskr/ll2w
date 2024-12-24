#include "allocator/LinearScanAllocator.h"
#include "compiler/Function.h"
#include "compiler/Interval.h"
#include "util/Timer.h"

#include <cassert>

namespace LL2W {
	bool LinearScanEndCompare::operator()(const IntervalPtr &left, const IntervalPtr &right) const {
		return left->getEndpoint() < right->getEndpoint();
	}

	Allocator::Result LinearScanAllocator::firstAttempt() {
		return attempt();
	}

	Allocator::Result LinearScanAllocator::attempt() {
		assert(function != nullptr);
		Timer timer("LinearScanAllocator::attempt");
		++attempts;
		resetFreeRegisters();
		active.clear();

		const auto intervals = getIntervals();
		auto result = Result::Success;

		constexpr auto R = WhyInfo::temporaryCount + WhyInfo::savedCount;

		for (const IntervalPtr &i: intervals) {
			expireOldIntervals(i);
			const auto required = i->registersRequired();
			if (R < activeRegisterCount + required) {
				spillAtInterval(i);
				result = Result::Spilled;
				// if (!spillAtInterval(i)) {
					// warn() << "Not spilling " << *i << '\n';
					// result = Result::NotSpilled;
					// break;
				// }
			} else {
				assert(i->registers.empty());
				i->registers.clear();

				for (size_t j = 0; j < required; ++j) {
					const auto iter = freeRegisters.begin();
					assert(iter != freeRegisters.end());
					i->registers.insert(*iter);
					// info() << "Inserting " << *iter << " into " << *i << " (new size " << i->registers.size() << ", empty = " << std::boolalpha << i->registers.empty() << ")\n";
					freeRegisters.erase(iter);
				}

				active.insert(i);
				activeRegisterCount += required;
			}
		}

		for (const IntervalPtr &i: intervals) {
			// if (i->registers.empty())
			// 	warn() << "No registers were allocated for interval " << *i << " in function " << *function->name
			// 	       << '\n';
			// info() << *i << " empty -> " << std::boolalpha << i->registers.empty() << '\n';
			if (i->registers.empty())
				error(std::cerr, false) << *i << " in \e[1m" << *function->name << "\e[22m\n";
			else
				// success() << *i << " in \e[1m" << *function->name << "\e[22m\n"
				;
			i->applyRegisters();
		}

		return result;
	}

	void LinearScanAllocator::resetFreeRegisters() {
		// No need to clear first because we're assuming no garbage ends up in freeRegisters.

		for (int t = 0; t < WhyInfo::temporaryCount; ++t)
			freeRegisters.insert(WhyInfo::temporaryOffset + t);

		for (int s = 0; s < WhyInfo::savedCount; ++s)
			freeRegisters.insert(WhyInfo::savedOffset + s);
	}

	std::vector<IntervalPtr> LinearScanAllocator::getIntervals() const {
		assert(function != nullptr);
		Timer timer("GetIntervals");
		std::vector<IntervalPtr> out;
		out.reserve(function->variableStore.size());
		std::unordered_set<VariablePtr> inserted;
		for (const auto &[id, variable]: function->variableStore)
			if (!variable->isAlias() && !variable->allRegistersSpecial() && !inserted.contains(variable)) {
				variable->setRegisters({});
				auto interval = std::make_shared<Interval>(*function, variable);
				if (*interval) {
					inserted.insert(variable);
					out.emplace_back(interval);
				}
			}
		std::sort(out.begin(), out.end(), [](const IntervalPtr &left, const IntervalPtr &right) {
			return left->getStartpoint() < right->getStartpoint();
		});
		return out;
	}

	void LinearScanAllocator::expireOldIntervals(const IntervalPtr &i) {
		std::vector<IntervalPtr> to_erase;

		for (const IntervalPtr &j: active) {
			if (i->getStartpoint() <= j->getEndpoint())
				break;
			to_erase.push_back(j);
			freeRegisters.insert(j->registers.cbegin(), j->registers.cend());
			activeRegisterCount -= j->registers.size();
			// TODO(typed): verify
			// j->registers.clear();
		}

		for (const IntervalPtr &j: to_erase) {
			active.erase(j);
		}
	}

	bool LinearScanAllocator::spillAtInterval(const IntervalPtr &i) {
		assert(!active.empty());
		assert(function != nullptr);

		auto iter = active.end();
		auto spill = *--iter;

		if (i->getEndpoint() < spill->getEndpoint()) {
			i->registers = spill->registers;
			spill->registers.clear();
			auto locked = spill->variable.lock();
			assert(locked);
			const bool spilled = function->spill(locked);
			if (!spilled) {
				warn() << "Couldn't spill interval " << *spill << " in LinearScanAllocator::spillAtInterval(line " << (__LINE__ - 2) << ")\n";
			}
			active.erase(spill);
			active.insert(i);
			return spilled;
		}

		auto locked = i->variable.lock();
		assert(locked);
		const bool spilled = function->spill(locked);
		if (!spilled) {
			warn() << "Couldn't spill interval " << *i << " in LinearScanAllocator::spillAtInterval(line " << (__LINE__ - 2) << ")\n";
		}

		return spilled;
	}

	void LinearScanAllocator::afterSpill(VariablePtr, std::span<VariablePtr>) {
		++spillCount;
		assert(function);
		function->forceLiveness();
	}
}
