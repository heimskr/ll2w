#pragma once

#include "compiler/BasicBlock.h"

#include <memory>
#include <ostream>
#include <set>

namespace LL2W {
	class BasicBlock;
	class Function;
	class Variable;

	struct Interval {
		// std::weak_ptr<BasicBlock> firstDefinition, lastUse;
		std::weak_ptr<Variable> variable;
		std::set<int> registers;

		Interval(const std::shared_ptr<Variable> &);
		int getStartpoint() const;
		int getEndpoint() const;

		std::set<int> & setRegisters(const std::set<int> &);
		void applyRegisters();
		size_t registersRequired() const;

		operator std::string() const;

		private:
			int startpoint = -1;
			int endpoint = -1;

			using BlockLivePtr = std::unordered_set<VariablePtr> BasicBlock::*;
			int getFirst(Function &, const std::shared_ptr<Variable> &, BlockLivePtr) const;
			int guess() const;
			int calculatePoint(Function &, BlockLivePtr) const;
			int calculateStartpoint(Function &) const;
			int calculateEndpoint(Function &) const;
	};

	std::ostream & operator<<(std::ostream &, const Interval &);
}
