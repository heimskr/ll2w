#include "util/CompilerUtil.h"
#include "compiler/LLVMInstruction.h"
#include "parser/Nodes.h"

namespace LL2W::CompilerUtil {
	BrUncondNode * brUncondCast(InstructionPtr instruction) {
		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) {
			if (llvm->node->nodeType() == NodeType::BrUncond)
				return dynamic_cast<BrUncondNode *>(llvm);
		}

		return nullptr;
	}

	BrCondNode * brCondCast(InstructionPtr instruction) {
		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) {
			if (llvm->node->nodeType() == NodeType::BrCond)
				return dynamic_cast<BrCondNode *>(llvm);
		}

		return nullptr;
	}
}
