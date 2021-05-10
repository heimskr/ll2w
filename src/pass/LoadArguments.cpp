#include <variant>

#include "compiler/Function.h"
#include "compiler/Immediate.h"
#include "instruction/AddIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LoadArguments.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void loadArguments(Function &function) {
		CallingConvention cconv = function.getCallingConvention();

		if (cconv == CallingConvention::Reg16 || cconv == CallingConvention::StackOnly) {
			const int arity = function.getArity();
			const int min = cconv == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			if (arity <= min)
				return;

			BasicBlockPtr entry = function.getEntry();
			std::shared_ptr<LoadRInstruction> first_load;
			for (int arg = arity - 1; min <= arg; --arg) {
				const FunctionArgument &fn_arg = function.arguments->at(arg - min);
				VariablePtr arg_var = function.getVariable(arg, fn_arg.type, entry);
				VariablePtr m0 = function.makeAssemblerVariable(0, entry);
				VariablePtr sp = function.sp(entry);

				// The stack frame looks like [ argN-1 | ... | arg16 | $rt | $fp | var1 | var2 | ... ] (if Reg16)
				//                         or [ argN-1 | ... | arg0  | $rt | $fp | var1 | var2 | ... ] (if StackOnly).
				// The stack pointer will be pointing right after where the frame pointer was pushed.
				// We need to skip over the arguments after this one, in addition to the return address and frame
				// pointer.
				int to_skip; // in bytes
				if (cconv == CallingConvention::Reg16) {
					// With Reg16, arguments are pushed with spacious (8-byte) stack pushes.
					to_skip = 8 * (arg - min + 1);
				} else {
					// With StackOnly, arguments are pushed with packed (variable-width) stack pushes.
					to_skip = 0;
					for (int i = 0; i < arg; ++i)
						to_skip += function.arguments->at(i).type->width() / 8;
				}

				auto sub  = std::make_shared<SubIInstruction> (sp, to_skip, m0);
				sub->meta.insert(InstructionMeta::LoadArgumentsSkip);
				auto load = std::make_shared<LoadRInstruction>(m0, arg_var, arg_var->type->width() / 8);
				if (!first_load)
					first_load = load;

				function.insertBefore(entry->instructions.front(), sub, "LoadArguments: $sp - to_skip -> %temp", false);
				function.insertAfter(sub, load, false);
				function.comment(load, "LoadArguments: [%temp] -> %var", false);
			}

			function.reindexInstructions();
			function.splitBlock(entry, first_load);
			function.removeUselessBranch(entry);
		} else throw std::invalid_argument("Invalid calling convention: " + std::to_string(static_cast<int>(cconv)));
	}

	void loadArgumentsReadjust(Function &function) {
		for (InstructionPtr &instruction: function.linearInstructions) {
			// TODO: should this be == 0?
			if (instruction->meta.count(InstructionMeta::LoadArgumentsSkip) != 0) {
				if (IType<int> *itype = dynamic_cast<IType<int> *>(instruction.get()))
					itype->imm += function.initialPushedBytes;
				else if (auto *itype = dynamic_cast<IType<Immediate> *>(instruction.get()))
					if (std::holds_alternative<int>(itype->imm))
						std::get<int>(itype->imm) += function.initialPushedBytes;
				function.comment(instruction, "Increased by " + std::to_string(function.initialPushedBytes) + " bytes");
			}
		}
	}
}
