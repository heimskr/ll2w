#include <iostream>

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

			VariablePtr fp = function.fp(block);
			VariablePtr sp = function.sp(block);
			VariablePtr rt = function.makePrecoloredVariable(WhyInfo::returnAddressOffset, block);
			VariablePtr r0 = function.makePrecoloredVariable(WhyInfo::returnValueOffset, block);

			// $fp -> $sp
			function.insertBefore(instruction, std::make_shared<MoveInstruction>(fp, sp), false)
				->setDebug(llvm)->extract();

			// Put the return value into $r0.
			if (ret->value->isIntLike()) {
				function.insertBefore(instruction, std::make_shared<SetInstruction>(r0, ret->value->intValue()), false)
					->setDebug(llvm)->extract();
			} else if (ret->value->isLocal()) {
				VariablePtr var = dynamic_cast<LocalValue *>(ret->value.get())->variable;
				function.extraVariables.emplace(var->id, var);
				if (var->multireg()) {
					if (WhyInfo::returnValueCount < var->registers.size())
						throw std::runtime_error("Too many registers for " + var->plainString() + " in LowerRet");
					auto iter = var->registers.begin();
					for (size_t i = 0; i < var->registers.size(); ++i) {
						auto subvar = function.makePrecoloredVariable(*iter++, block);
						auto retreg = function.makePrecoloredVariable(WhyInfo::returnValueOffset + i, block);
						function.insertBefore(instruction, std::make_shared<MoveInstruction>(subvar, retreg), false)
							->setDebug(llvm)->extract();
					}
				} else {
					function.insertBefore(instruction, std::make_shared<MoveInstruction>(var, r0), false)
						->setDebug(llvm)->extract();
				}
			}

			// Pop all the general-purpose registers that were saved in the prologue.
			for (auto begin = function.savedRegisters.rbegin(), iter = begin, end = function.savedRegisters.rend();
			     iter != end; ++iter) {
				VariablePtr variable = function.makePrecoloredVariable(*iter, block);
				function.insertBefore(instruction, std::make_shared<StackPopInstruction>(variable), false)
					->setDebug(llvm)->extract();
			}

			// Insert the epilogue (minus the jump).
			function.insertBefore(instruction, std::make_shared<StackPopInstruction>(fp), false)
				->setDebug(llvm)->extract(); // ] $fp
			function.insertBefore(instruction, std::make_shared<StackPopInstruction>(rt), false)
				->setDebug(llvm)->extract(); // ] $rt

			// Jump to the return address.
			function.insertBefore(instruction, std::make_shared<JumpRegisterInstruction>(rt, false), false)
				->setDebug(llvm)->extract();
			to_remove.push_back(instruction);
		}

		function.reindexInstructions();

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
