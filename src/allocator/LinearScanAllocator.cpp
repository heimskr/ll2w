#include "allocator/LinearScanAllocator.h"
#include "compiler/Function.h"
#include "compiler/Interval.h"

#include <cassert>

namespace LL2W {
	bool LinearScanEndCompare::operator()(const IntervalPtr &left, const IntervalPtr &right) const {
		return left->endpoint() < right->endpoint();
	}

	Allocator::Result LinearScanAllocator::attempt() {
		assert(function != nullptr);
		resetFreeRegisters();

		for (const IntervalPtr &interval: getIntervals()) {
			
		}
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
		std::vector<IntervalPtr> out;
		out.reserve(function->variableStore.size());
		for (const auto &[id, variable]: function->variableStore)
			out.emplace_back(std::make_shared<Interval>(variable));
		std::sort(out.begin(), out.end(), [](const IntervalPtr &left, const IntervalPtr &right) {
			return left->startpoint() < right->startpoint();
		});
		return out;
	}

	void LinearScanAllocator::expireOldIntervals(const IntervalPtr &interval) {
		std::vector<IntervalPtr> to_erase;

		for (const IntervalPtr &j: active) {
			if (interval->startpoint() <= j->endpoint())
				break;
			to_erase.push_back(j);
			for (const int reg: j->registers)
				freeRegisters.insert(reg);
		}

		for (const IntervalPtr &j: to_erase)
			active.erase(j);
	}
}
