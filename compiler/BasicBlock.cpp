#include "compiler/BasicBlock.h"

namespace LL2W {
	BasicBlock::BasicBlock(int index_, const std::vector<int> &preds_,
	                       const std::vector<const InstructionNode *> &instructions_):
		index(index_), preds(preds_), instructions(instructions_) {}
}