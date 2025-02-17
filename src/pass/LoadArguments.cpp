#include <variant>

#include "compiler/Function.h"
#include "compiler/Immediate.h"
#include "instruction/AddIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LoadArguments.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void loadArguments(Function &function) {
		Timer timer{"LoadArguments"};
		CallingConvention cconv = function.getCallingConvention();

		if (cconv == CallingConvention::Reg16 || cconv == CallingConvention::StackOnly) {
			const int arity = function.getArity();
			const int min = cconv == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			if (arity <= min) {
				return;
			}

			BasicBlockPtr entry = function.getEntry();
			std::shared_ptr<LoadRInstruction> first_load;

			for (int arg = arity - 1; min <= arg; --arg) {
				const FunctionArgument &fn_arg = function.arguments->at(arg - min);
				assert(fn_arg.name != nullptr);
				VariablePtr arg_var = function.getVariable(fn_arg.name, fn_arg.type, entry);
				VariablePtr m0 = function.mx(0, entry);
				VariablePtr sp = function.sp(entry);

				// The stack frame looks like [ argN-1 | ... | arg16 | $rt | $fp | var1 | var2 | ... ] (if Reg16)
				//                         or [ argN-1 | ... | arg0  | $rt | $fp | var1 | var2 | ... ] (if StackOnly).
				// The stack pointer will be pointing right after where the frame pointer was pushed.
				// We need to skip over the arguments after this one, in addition to the return address and frame
				// pointer.
				int to_skip{}; // in bytes
				if (cconv == CallingConvention::Reg16) {
					// With Reg16, arguments are pushed with spacious (8-byte) stack pushes.
					to_skip = 8 * (arg - min + 1);
				} else {
					// With StackOnly, arguments are also pushed with spacious stack pushes.
					for (int i = 0; i < arg; ++i) {
						to_skip += Util::upalign(function.arguments->at(i).type->width() / 8, 8);
					}
				}

				auto add = std::make_shared<AddIInstruction> (sp, to_skip, m0);
				add->meta.insert(InstructionMeta::LoadArgumentsSkip);
				auto load = std::make_shared<LoadRInstruction>(m0, arg_var, static_cast<WASMSize>(arg_var->type->width() / 8));
				if (!first_load) {
					first_load = load;
				}

				std::string comment = std::format("LoadArguments: $sp + to_skip (originally {}) -> %temp", to_skip);
				function.insertBefore(entry->instructions.front(), add, std::move(comment), false);
				function.insertAfter(add, load, false);
				function.comment(load, "LoadArguments: [%temp] -> %var", false);
			}

			function.reindexInstructions();
			function.splitBlock(entry, first_load);
			function.removeUselessBranch(entry);
		} else {
			throw std::invalid_argument("Invalid calling convention: " + std::to_string(static_cast<int>(cconv)));
		}
	}

	void loadArgumentsReadjust(Function &function) {
		Timer timer{"LoadArgumentsReadjust"};
		const auto addend = function.initialPushedBytes.value();

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (instruction->meta.contains(InstructionMeta::LoadArgumentsSkip)) {
				if (auto itype = std::dynamic_pointer_cast<IType>(instruction)) {
					if (std::holds_alternative<int>(itype->imm)) {
						std::get<int>(itype->imm) += addend;
					}
				}
				function.comment(instruction, "Augmented by " + std::to_string(addend) + " bytes");
			}
		}
	}
}
