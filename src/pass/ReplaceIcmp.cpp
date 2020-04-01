#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/ReplaceIcmp.h"

namespace LL2W::Passes {
	int replaceIcmp(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Icmp)
				continue;
			replaceIcmp(function, instruction, dynamic_cast<IcmpNode *>(llvm->node));
			to_remove.push_back(instruction);
		}

		// for (InstructionPtr &instruction: to_remove)
		// 	function.remove(instruction);

		return to_remove.size();
	}

	void replaceIcmp(Function &function, InstructionPtr &instruction, IcmpNode *node) {
		if (node->type->typeType() == TypeType::Vector)
			throw std::runtime_error("Vectors are unsupported in icmp instructions");
		
	}
}
