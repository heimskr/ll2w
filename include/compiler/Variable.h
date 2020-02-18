#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <memory>
#include <set>

#include "parser/Types.h"

namespace LL2W {
	class Node;
	class BasicBlock;
	class Instruction;

	class Variable {
		private:
			std::list<Instruction *> useOrder;

		public:
			int id;
			Type *type = nullptr;
			BasicBlock *definingBlock;
			Instruction *definition = nullptr, *lastUse = nullptr;
			std::set<BasicBlock *> usingBlocks;
			std::set<Instruction *> uses;

			Variable *spilledFrom = nullptr; // Tentative.
			std::list<Variable *> spilledTo; // Also tentative.

			Variable(int id_, Type *type_ = nullptr, BasicBlock *definingBlock_ = nullptr,
				const std::set<BasicBlock *> &uses_ = {});

			~Variable();

			/** Calculates the sum of each use's estimated execution count. */
			int weight() const;

			/** Calculates the variable's spill cost. */
			int spillCost() const;
	};

	using VariablePtr = std::shared_ptr<Variable>;
}

#endif
