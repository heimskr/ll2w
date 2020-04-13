#include "compiler/Function.h"
#include "instruction/AddIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "pass/LoadArguments.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void loadArguments(Function &function) {
		CallingConvention cconv = function.getCallingConvention();
		if (cconv == CallingConvention::StackOnly) {
			error() << "LoadArguments failed for \e[1m" << *function.name << "\e[22m.\n";
			throw std::runtime_error("loadArguments is currently unimplemented for StackOnly functions.");
		} else if (cconv == CallingConvention::Reg16) {
			const int arity = function.getArity();
			if (arity <= WhyInfo::argumentCount)
				return;

			BasicBlockPtr entry = function.getEntry();
			std::shared_ptr<LoadRInstruction> first_load;
			for (int arg = arity - 1; WhyInfo::argumentCount <= arg; --arg) {
				const FunctionArgument &fn_arg = function.arguments->at(arg - WhyInfo::argumentCount);
				VariablePtr arg_var = function.getVariable(arg, fn_arg.type, entry);
				VariablePtr temp_var = function.makeAssemblerVariable(0, entry);
				VariablePtr sp = function.makePrecoloredVariable(WhyInfo::stackPointerOffset, entry);

				// The stack frame looks like [ argN-1 | ... | arg16 | $rt | $fp | var1 | var2 | ... ].
				// The stack pointer will be pointing right after where the frame pointer was pushed.
				// We need to skip over the arguments after this one, in addition to the return address and frame
				// pointer.
				const int to_skip = 16 + 8 * (arg - WhyInfo::argumentCount + 1); // in bytes

				auto add  = std::make_shared<AddIInstruction> (sp, to_skip, temp_var);
				auto load = std::make_shared<LoadRInstruction>(temp_var, arg_var, arg_var->type->width() / 8);
				if (!first_load)
					first_load = load;

				function.insertBefore(entry->instructions.front(), add, "LoadArguments: $sp + to_skip -> %temp", false);
				function.insertAfter(add, load, false);
				function.comment(load, "LoadArguments: [%temp] -> %var", false);
			}

			function.reindexInstructions();
			function.splitBlock(entry, first_load);
			function.removeUselessBranch(entry);
		} else throw std::invalid_argument("Invalid calling convention: " + std::to_string(static_cast<int>(cconv)));
	}
}
