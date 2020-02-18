#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	int Variable::weight() const {
		int sum = 0;
		for (BasicBlock *use: usingBlocks)
			sum += use->estimatedExecutions;
		return sum;
	}

	int Variable::spillCost() const {
		// If a variable has only one use and that use is right after its definition, it has an (effectively) infinite
		// spill cost.
		if (uses.size() == 1 && (*uses.begin())->index == definition->index + 1)
			return INT_MAX;
		return weight();
	}
}