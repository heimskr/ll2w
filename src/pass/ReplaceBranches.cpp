#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/JumpSymbolInstruction.h"
#include "pass/ReplaceBranches.h"

namespace LL2W::Passes {
	int replaceBranches(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			const LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;
			const NodeType node_type = llvm->node->nodeType();
			if (node_type == NodeType::BrCond)
				replaceBranch(function, instruction, dynamic_cast<BrCondNode *>(llvm->node));
			else if (node_type == NodeType::BrUncond)
				replaceBranch(function, instruction, dynamic_cast<BrUncondNode *>(llvm->node));
			else
				continue;

			// to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void replaceBranch(Function &function, InstructionPtr &instruction, BrCondNode *br) {

	}

	void replaceBranch(Function &function, InstructionPtr &instruction, BrUncondNode *br) {
		function.insertBefore(instruction, std::make_shared<JumpSymbolInstruction>(function.transformLabel(*br->destination), false));
	}
}
