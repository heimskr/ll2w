#pragma once

#include <memory>
#include <set>
#include <vector>

#include "allocator/Allocator.h"

namespace LL2W {
	struct Interval;

	using IntervalPtr = std::shared_ptr<Interval>;

	struct LinearScanEndCompare {
		bool operator()(const IntervalPtr &, const IntervalPtr &) const;
	};

	/** Assigns registers using the linear scan algorithm. */
	class LinearScanAllocator: public Allocator {
		public:
			using Allocator::Allocator;

			Result attempt() override;

		private:
			std::set<IntervalPtr, LinearScanEndCompare> active;
			size_t activeRegisterCount;
			std::set<int> freeRegisters;

			void resetFreeRegisters();
			std::vector<IntervalPtr> getIntervals() const;
			void expireOldIntervals(const IntervalPtr &);
			bool spillAtInterval(const IntervalPtr &);
			void afterSpill();
	};
}
