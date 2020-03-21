#include <iostream>

#include "compiler/Function.h"
#include "compiler/Program.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpSymbolInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/SetupCalls.h"

namespace LL2W::Passes {
	void setupCalls(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			// Look for a call instruction.
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);

			// Right now, calls to function pointers are unsupported. This might change once I come across an example.
			VariableValue *name_value = std::dynamic_pointer_cast<VariableValue>(call->name).get();
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(name_value);
			if (!global_name)
				throw std::runtime_error("Calls to function pointers are currently unsupported");

			// Now we need to find out about the function's arguments because we need to know how to call it.
			CallingConvention convention;
			std::vector<TypePtr> argument_types;
			bool ellipsis;

			// First, we check the call node itself—it sometimes contains the signature of the function.
			if (call->argumentsExplicit) {
				argument_types = call->argumentTypes;
				ellipsis = call->argumentEllipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
			} else if (function.parent->functions.count("@" + *global_name->name) != 0) {
				// When the arguments aren't explicit, we check the parent program's map of functions.
				Function &func = function.parent->functions.at("@" + *global_name->name);
				ellipsis = func.isVariadic();
				convention = func.getCallingConvention();
				argument_types.reserve(func.arguments->size());
				for (FunctionArgument &argument: *func.arguments)
					argument_types.push_back(argument.type);
			} else if (function.parent->declarations.count(*global_name->name) != 0) {
				// We can also check the map of declarations.
				FunctionHeader *header = function.parent->declarations.at(*global_name->name);
				ellipsis = header->arguments->ellipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
				argument_types.reserve(header->arguments->arguments.size());
				for (FunctionArgument &argument: header->arguments->arguments)
					argument_types.push_back(argument.type);
			} else throw std::runtime_error("Couldn't find signature for function " + *global_name->name);

			int reg_max = convention == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			int arg_count = argument_types.size();

			// First, move variables into the argument registers.
			for (int i = 0; i < reg_max && i < arg_count; ++i) {
				// Make a precolored dummy variable.
				VariablePtr new_var = function.newVariable(argument_types[i]);
				new_var->reg = WhyInfo::argumentOffset + i;
				function.setupCallValue(new_var, instruction, call->constants[i]);
			}

			// Next, push variables onto the stack, right to left.
			for (int i = arg_count - 1; reg_max <= i; --i)
				function.pushCallValue(instruction, call->constants[i]);

			// Once we're done putting the arguments in the proper place, remove the variables from the call
			// instruction's set of read variables so the register allocator doesn't try to insert any spills/loads.
			llvm->read.clear();

			function.insertBefore(instruction, std::make_shared<JumpSymbolInstruction>(*global_name->name, true));
			if (call->result) {
				auto move =
					std::make_shared<MoveInstruction>(function.makePrecoloredVariable(WhyInfo::returnValueOffset,
					instruction->parent.lock()), function.getVariable(*call->result));
				function.insertBefore(instruction, move);
				move->extract();
			}

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		function.extractVariables();
	}
}
