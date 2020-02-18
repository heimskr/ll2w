#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <set>

namespace LL2W {
	class Node;
	class BasicBlock;
	class Instruction;

	struct Variable {
		int id;
		std::set<BasicBlock *> usingBlocks;
		std::set<Instruction *> uses;
		BasicBlock *definingBlock;
		Instruction *definition = nullptr, *lastUse = nullptr;

		Variable(int id_, BasicBlock *definingBlock_ = nullptr, const std::set<BasicBlock *> &uses_ = {}):
			id(id_), usingBlocks(uses_), definingBlock(definingBlock_) {}


		/** Calculates the sum of each use's estimated execution count. */
		int weight() const;

		/** Calculates the variable's spill cost. */
		int spillCost() const;
	};
}

#endif
