#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"

namespace LL2W {
	BasicBlock::BasicBlock(int label_, const std::vector<int> &preds_,
	                       const std::vector<std::shared_ptr<Instruction>> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {}
}
