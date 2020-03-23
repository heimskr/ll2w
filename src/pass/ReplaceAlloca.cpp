#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/ReplaceAlloca.h"

namespace LL2W::Passes {
	void replaceAlloca(Function &function) {
		std::list<InstructionPtr> to_remove;

		// Loop over all instructions, ignoring everything except allocas.
		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Alloca)
				continue;
			AllocaNode *alloca = dynamic_cast<AllocaNode *>(llvm->node);

			// First, mark the alloca instruction for removal.
			to_remove.push_back(instruction);

			// Move the "stack pointer" (actually the size of the stack so far) down to get the alignment right.
			if (0 < alloca->align)
				function.stackSize += function.stackSize % alloca->align;

			// Compute the number of elements requested.
			int num_elements = 1;
			if (alloca->numelementsValue) {
				IntValue *int_value = dynamic_cast<IntValue *>(alloca->numelementsValue.get());
				if (!int_value)
					throw std::runtime_error("numelements for alloca must be an IntValue");
				num_elements = int_value->value;
			}

			// Compute the width of the type if one is present (which should always be the case).
			const int width = alloca->type? alloca->type->width() : -1;

			// Finally, register the allocation in the function.
			function.addToStack(alloca->variable, StackLocation::Purpose::Alloca, width);
		}

		// Remove the alloca instructions to complete their replacement.
		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
