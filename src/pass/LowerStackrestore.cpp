#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/LowerStackrestore.h"

namespace LL2W::Passes {
	void lowerStackrestore(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			if (!call->name->isGlobal())
				continue;
			if (*dynamic_cast<GlobalValue *>(call->name.get())->name == "llvm.stackrestore") {
				auto move = std::make_shared<MoveInstruction>(
					dynamic_cast<LocalValue *>(call->constants[0]->value.get())->variable,
					function.sp(instruction->parent.lock()));
				function.insertBefore(instruction, move)->setDebug(llvm)->extract();
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
