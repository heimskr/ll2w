#pragma once

#include <memory>
#include <unordered_set>

namespace LL2W {
	class Variable;

	using VariablePtr = std::shared_ptr<Variable>;

	/** Represents a point where variables can be live-in/live-out. This used to be basic blocks, but now it's instructions. */
	class LivePoint {
		public:
			using SetPtr = std::unordered_set<VariablePtr> LivePoint::*;

		private:
			std::unordered_set<VariablePtr> liveIn, liveOut;
			/** Contains everything in liveIn and liveOut. */
			std::unordered_set<VariablePtr> allLive;

		public:
			LivePoint() = default;

			bool isLiveIn(const VariablePtr &) const;
			bool isLiveOut(const VariablePtr &) const;
			void clearLive();
			void eraseLive(const VariablePtr &);

			static inline SetPtr liveInPtr = &LivePoint::liveIn;
			static inline SetPtr liveOutPtr = &LivePoint::liveOut;

			inline const auto & getLiveIn() const { return liveIn; }
			inline const auto & getLiveOut() const { return liveOut; }
			inline const auto & getAllLive() const { return allLive; }

			inline void setLiveIn(auto &&value) { liveIn = std::move(value); }
			inline void setLiveOut(auto &&value) { liveOut = std::move(value); }
			inline void setAllLive(auto &&value) { allLive = std::move(value); }

			virtual std::unordered_set<VariablePtr> & getRead() = 0;
			virtual std::unordered_set<VariablePtr> & getWritten() = 0;
			virtual int getIndex() const = 0;
	};

	using LivePointPtr = std::shared_ptr<LivePoint>;
}