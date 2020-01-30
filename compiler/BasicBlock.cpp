#include "compiler/BasicBlock.h"

namespace LL2W {
	BasicBlock::BasicBlock(int label_, const std::vector<int> &preds_,
	                       const std::vector<const InstructionNode *> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {}
}