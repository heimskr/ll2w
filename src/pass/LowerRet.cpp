#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpRegisterInstruction.h"
#include "instruction/Label.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackPopInstruction.h"
#include "pass/LowerRet.h"

namespace LL2W::Passes {
	int lowerRet(Function &function) {
		std::list<InstructionPtr> to_remove;
		
		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;
			if (llvm->node->nodeType() == NodeType::Unreachable)
				to_remove.push_back(instruction);
			if (llvm->node->nodeType() != NodeType::Ret)
				continue;

			RetNode *ret = dynamic_cast<RetNode *>(llvm->node);

			BasicBlockPtr block = instruction->parent.lock();
			if (!block)
				throw std::runtime_error("Couldn't lock instruction parent in LowerRet");

			VariablePtr fp = function.makePrecoloredVariable(WhyInfo::framePointerOffset, block);
			VariablePtr sp = function.makePrecoloredVariable(WhyInfo::stackPointerOffset, block);
			VariablePtr rt = function.makePrecoloredVariable(WhyInfo::returnAddressOffset, block);
			VariablePtr r0 = function.makePrecoloredVariable(WhyInfo::returnValueOffset, block);

			// Insert the epilogue (minus the jump).
			function.insertBefore(instruction, std::make_shared<MoveInstruction>(fp, sp)); // $fp -> $sp
			function.insertBefore(instruction, std::make_shared<StackPopInstruction>(fp)); // ] $fp
			function.insertBefore(instruction, std::make_shared<StackPopInstruction>(rt)); // ] $rt

			// Put the return value into $r0.
			if (ret->value->isIntLike()) {
				function.insertBefore(instruction, std::make_shared<SetInstruction>(r0, ret->value->intValue()));
			} else if (ret->value->isLocal()) {
				VariablePtr var = dynamic_cast<LocalValue *>(ret->value.get())->variable;
				function.insertBefore(instruction, std::make_shared<MoveInstruction>(var, r0));
			}

			// Jump to the return address.
			function.insertBefore(instruction, std::make_shared<JumpRegisterInstruction>(rt, false));
			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
