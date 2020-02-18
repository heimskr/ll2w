#include <iostream>

#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	Variable::Variable(int id_, Type *type_, BasicBlockPtr defining_block, const std::set<BasicBlockPtr> &using_blocks):
		id(id_), type(type_), definingBlock(defining_block), usingBlocks(using_blocks) {}

	Variable::~Variable() {
		if (type)
			delete type;
	}

	int Variable::weight() const {
		int sum = 0;
		for (BasicBlockPtr use: usingBlocks)
			sum += use->estimatedExecutions;
		return sum;
	}

	int Variable::spillCost() const {
		// If a variable is never used, it has a negative spill cost.
		if (uses.empty())
			return -1;
		// If a variable has only one use and that use is right after its definition, it has an (effectively) infinite
		// spill cost.
		if (definition && uses.size() == 1 && (*uses.begin())->index == definition->index + 1)
			return INT_MAX;
		return weight();
	}

	bool Variable::operator==(const Variable &other) const {
		return id == other.id && *type == *other.type;
	}
}
