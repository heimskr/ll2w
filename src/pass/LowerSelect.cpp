#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/SelectInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LowerSelect.h"

namespace LL2W::Passes {
	int lowerSelect(Function &function) {
		std::list<InstructionPtr> to_remove;

		VariablePtr m0 = function.m0(function.getEntry());

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Select)
				continue;
			SelectNode *select = dynamic_cast<SelectNode *>(llvm->node);



			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
