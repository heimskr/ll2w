#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/LowerFreeze.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t lowerFreeze(Function &function) {
		Timer timer("LowerFreeze");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Freeze)
				continue;
			FreezeNode *sw = dynamic_cast<FreezeNode *>(llvm->node);

			if (!sw->value->isLocal())
				throw std::runtime_error("Expected the operand of a freeze instruction to be a pvar");

			function.insertBefore(instruction, std::make_shared<MoveInstruction>(dynamic_cast<LocalValue *>(
				sw->value.get())->getVariable(function), sw->variable), false)->setDebug(llvm)->extract();
			to_remove.push_back(instruction);
		}

		if (!to_remove.empty())
			function.reindexInstructions();

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
