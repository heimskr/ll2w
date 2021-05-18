#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "parser/Nodes.h"
#include "pass/LowerVarargs.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void lowerVarargsFirst(Function &function) {
		auto m2 = function.makeAssemblerVariable(2, function.getEntry());
		bool any_changed = false;
		std::list<InstructionPtr> to_remove;
		for (InstructionPtr &instruction: function.linearInstructions) {
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
							std::make_shared<StoreRInstruction>(m2, var, var->type->width() / 8))
							->setDebug(llvm)->extract();
						any_changed = true;
						to_remove.push_back(instruction);
						continue;
					} else if (*global->name == "llvm.va_end") {
						to_remove.push_back(instruction);
					}
				}
			}
		}

		for (auto &instruction: to_remove)
			function.remove(instruction);

		if (!any_changed)
			function.variableStore.erase(m2->id);
	}

	void lowerVarargsSecond(Function &function) {
		if (!function.isVariadic())
			return;
		// At the beginning of each function, copy the stack pointer plus the combined size of all the non-variadic
		// arguments into $m2.
		InstructionPtr first = function.firstInstruction(true);
		BasicBlockPtr entry = function.getEntry();
		auto sp = function.sp(entry);
		auto m2 = function.makeAssemblerVariable(2, entry);
		int skip = 0;
		for (FunctionArgument &argument: *function.arguments)
			skip += Util::upalign(argument.type->width() / 8, 8); // Stack parameters are aligned to 8-byte boundaries.
		function.insertBefore(first, std::make_shared<AddIInstruction>(sp, skip, m2));
	}
}
