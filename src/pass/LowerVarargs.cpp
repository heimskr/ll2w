#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "parser/Nodes.h"
#include "pass/LowerVarargs.h"

namespace LL2W::Passes {
	void lowerVarargsFirst(Function &function) {
		const std::list<InstructionPtr> &linearInstructions = function.linearInstructions;
		auto m2 = function.makeAssemblerVariable(2, function.getEntry());
		bool any_changed = false;
		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end;) {
		// for (InstructionPtr &instruction: function.linearInstructions) {
			InstructionPtr instruction = *iter;
			if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) {
				if (CallNode *call = dynamic_cast<CallNode *>(llvm->node)) {
					if (!call->name->isGlobal())
						continue;
					GlobalValue *global = dynamic_cast<GlobalValue *>(call->name.get());
					if (*global->name == "llvm.va_start") {
						function.comment(instruction, "llvm.va_start removed.");
						if (call->constants.size() != 1)
							throw std::runtime_error("Expected one argument for llvm.va_start");
						if (!call->constants[0]->value->isLocal())
							// Surely no one would be silly enough to use a global variable with va_start, right?
							throw std::runtime_error("Expected argument of llvm.va_start to be a local variable");
						VariablePtr var = dynamic_cast<LocalValue *>(call->constants[0]->value.get())->variable;
						// function.insertBefore(instruction, std::make_shared<MoveInstruction>(m2, var));
						function.insertBefore(instruction,
							std::make_shared<StoreRInstruction>(m2, var, var->type->width() / 8));
						any_changed = true;
						iter = ++iter;
						function.remove(instruction);
						continue;
					} else if (*global->name == "llvm.va_end") {
						iter = ++iter;
						function.remove(instruction);
					}
				}
			}

			++iter;
		}

		if (!any_changed)
			function.variableStore.erase(m2->id);
	}

	void lowerVarargsSecond(Function &function) {
		if (!function.isVariadic())
			return;
		//At the beginning of each function, copy $sp into $m2.
		InstructionPtr first = function.firstInstruction(true);
		auto m2 = function.makeAssemblerVariable(2, function.getEntry());
		function.insertBefore(first, std::make_shared<MoveInstruction>(function.sp(function.getEntry()), m2));
	}
}
