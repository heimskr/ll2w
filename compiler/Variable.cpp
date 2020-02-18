#include "compiler/BasicBlock.h"
#include "compiler/Variable.h"

namespace LL2W {
	int Variable::weight() const {
		int sum = 0;
		for (BasicBlock *use: usingBlocks)
			sum += use->estimatedExecutions;
		return sum;
	}
}