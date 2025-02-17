#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "parser/Nodes.h"
#include "pass/LowerVarargs.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void lowerVarargsFirst(Function &function) {
		Timer timer{"LowerVarargsFirst"};
		VariablePtr m2 = function.mx(2, function.getEntry());
		bool any_changed = false;
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) {
				if (auto *call = dynamic_cast<CallNode *>(llvm->getNode())) {
					if (!call->name->isGlobal()) {
						continue;
					}

					GlobalValue *global = dynamic_cast<GlobalValue *>(call->name.get());

					if (*global->name == "@llvm.va_start") {
						function.comment(instruction, "llvm.va_start removed.");

						if (call->constants.size() != 1) {
							throw std::runtime_error("Expected one argument for llvm.va_start");
						}

						if (!call->constants[0]->value->isLocal()) {
							// Surely no one would be silly enough to use a global variable with va_start, right?
							throw std::runtime_error("Expected argument of llvm.va_start to be a local variable");
						}

						VariablePtr var = dynamic_cast<LocalValue *>(call->constants[0]->value.get())->variable;
						auto store = std::make_shared<StoreRInstruction>(m2, var, static_cast<WASMSize>(var->type->width() / 8));
						function.insertBefore(instruction, std::move(store), "m2 -> [var]")->setDebug(llvm)->extract();
						any_changed = true;
						to_remove.push_back(instruction);
						continue;
					}

					if (*global->name == "@llvm.va_end") {
						to_remove.push_back(instruction);
					}
				}
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		if (!any_changed) {
			function.variableStore.erase(m2->id);
		}
	}

	void lowerVarargsSecond(Function &function) {
		Timer timer{"LowerVarargsSecond"};
		if (!function.isVariadic()) {
			return;
		}

		// At the beginning of each function, copy the stack pointer plus the combined size of all the non-variadic
		// arguments into $m2.
		InstructionPtr first = function.firstInstruction(true);
		BasicBlockPtr entry = function.getEntry();
		auto sp = function.sp(entry);
		auto m2 = function.mx(2, entry);
		int skip = 0;
		for (const FunctionArgument &argument: *function.arguments) {
			skip += Util::upalign(argument.type->width() / 8, 8); // Stack parameters are aligned to 8-byte boundaries.
		}
		function.insertBefore(first, std::make_shared<AddIInstruction>(sp, skip, m2));
	}
}
