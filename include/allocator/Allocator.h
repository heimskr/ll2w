#pragma once

#include <memory>
#include <string>
#include <unordered_set>

namespace LL2W {
	class Function;
	class Variable;

	class Allocator {
		protected:
			Function *function = nullptr;
			int spillCount = 0;
			int attempts = 0;
			std::unordered_set<const std::string *> triedIDs;
			std::unordered_set<std::string> triedLabels;

		public:
			enum class Result {Invalid = 0, Spilled, NotSpilled, Success};

			std::shared_ptr<Variable> lastSpill, lastSpillAttempt;

			Allocator(Function &function_): function(&function_) {}
			virtual ~Allocator() = default;

			virtual bool needsCFG() const { return false; }
			virtual Result attempt() = 0;
			int getAttempts() const { return attempts; }
			int getSpillCount() const { return spillCount; }

			/** Selects the variable with the lowest spill cost. */
			std::shared_ptr<Variable> selectLowestSpillCost() const;
			std::shared_ptr<Variable> selectMostLive(int *liveness_out = nullptr) const;

			static std::string stringify(Result result) {
				return result == Result::Spilled? "Spilled" : (result == Result::NotSpilled? "NotSpilled" :
					(result == Result::Success? "Success" : "?"));
			}

			const decltype(triedIDs)    & getTriedIDs()    const { return triedIDs;    }
			const decltype(triedLabels) & getTriedLabels() const { return triedLabels; }
	};
}
