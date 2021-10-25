#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Program.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/JumpRegisterInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SizedStackPushInstruction.h"
#include "instruction/StackPopInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "pass/MakeCFG.h"
#include "pass/SetupCalls.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void setupCalls(Function &function) {
		int i;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			// Look for a call instruction.
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			BasicBlockPtr block = instruction->parent.lock();

			VariableValue *name_value = dynamic_cast<VariableValue *>(call->name.get());
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(name_value);
			std::unique_ptr<GlobalValue> global_uptr;
			if (global_name)
				global_uptr = std::make_unique<GlobalValue>(*global_name);

			// Now we need to find out about the function's arguments because we need to know how to call it.
			CallingConvention convention;
			std::vector<TypePtr> argument_types;
			bool ellipsis;

			if (global_uptr) {
				do {
					// First, we check the call node itself—it sometimes contains the signature of the function.
					if (call->argumentsExplicit) {
						argument_types = call->argumentTypes;
						ellipsis = call->argumentEllipsis;
						convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
						break;
					} else if (function.parent->functions.count("@" + *global_uptr->name) != 0) {
						// When the arguments aren't explicit, we check the parent program's map of functions.
						Function &func = *function.parent->functions.at("@" + *global_uptr->name);
						ellipsis = func.isVariadic();
						convention = func.getCallingConvention();
						argument_types.reserve(func.arguments->size());
						for (FunctionArgument &argument: *func.arguments)
							argument_types.push_back(argument.type);
						break;
					} else if (function.parent->declarations.count(*global_uptr->name) != 0) {
						// We can also check the map of declarations.
						FunctionHeader *header = function.parent->declarations.at(*global_uptr->name);
						ellipsis = header->arguments->ellipsis;
						convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
						argument_types.reserve(header->arguments->arguments.size());
						for (FunctionArgument &argument: header->arguments->arguments)
							argument_types.push_back(argument.type);
						break;
					} else if (function.parent->aliases.count(StringSet::intern("@" + *global_uptr->name)) != 0) {
						// In rare cases, there may be an alias.
						AliasDef *alias = function.parent->aliases.at(StringSet::intern("@" + *global_uptr->name));
						const std::string *alias_to = alias->aliasTo->front() == '@'?
							StringSet::intern(alias->aliasTo->substr(1)) : alias->aliasTo;
						global_uptr = std::make_unique<GlobalValue>(alias_to);
					} else throw std::runtime_error("Couldn't find signature for function " + *global_uptr->name);
				} while (true);
			} else {
				for (ConstantPtr &ptr: call->constants)
					argument_types.push_back(ptr->type);
				ellipsis = false;
				convention = CallingConvention::Reg16;
			}

			int reg_max = convention == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			int arg_count = argument_types.size();

			// First, push the current values of the argument registers to the stack.
			if (convention == CallingConvention::Reg16) {
				for (i = 0; i < arg_count && i < WhyInfo::argumentCount; ++i) {
					VariablePtr arg_variable = function.makePrecoloredVariable(WhyInfo::argumentOffset + i, block);
					function.insertBefore(instruction, std::make_shared<StackPushInstruction>(arg_variable), false)
						->setDebug(*llvm)->extract();
				}
			}

			// Next, if applicable, we account for the situation where the jump is to an argument register. Because it
			// may be overwritten right before the jump, we'd need to copy it to a temporary variable and jump to that.
			VariablePtr jump_var;
			if (!global_uptr) {
				jump_var = dynamic_cast<LocalValue *>(name_value)->variable;
				if (jump_var->id < arg_count) {
					VariablePtr new_var = function.newVariable(jump_var->type);
					auto move = std::make_shared<MoveInstruction>(jump_var, new_var);
					function.insertBefore(instruction, move, "jump_var -> new_var")->setDebug(*llvm)->extract();
					jump_var = new_var;
				}
			}

			// Next, move variables into the argument registers.
			for (i = 0; i < reg_max && i < arg_count; ++i) {
				// Make a precolored dummy variable.
				VariablePtr new_var = function.newVariable(argument_types[i]);
				new_var->registers = {WhyInfo::argumentOffset + i};
				setupCallValue(function, new_var, instruction, call->constants[i]);
			}

			// Push variables onto the stack, right to left.
			int bytes_pushed = 0;
			if (ellipsis)
				for (i = call->constants.size() - 1; 0 <= i; --i)
					bytes_pushed += pushCallValue(function, instruction, call->constants[i]);
			else
				for (i = arg_count - 1; reg_max <= i; --i)
					bytes_pushed += pushCallValue(function, instruction, call->constants[i]);

			VariablePtr m2;

			if (function.isVariadic()) {
				m2 = function.mx(2, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<StackPushInstruction>(m2))
					->setDebug(*llvm)->extract();
			}

			// Once we're done putting the arguments in the proper place, remove the variables from the call
			// instruction's set of read variables so the register allocator doesn't try to insert any spills/loads.
			llvm->read.clear();

			// At this point, we're ready to insert the jump.
			if (global_uptr) {
				function.insertBefore(instruction, std::make_shared<JumpInstruction>(global_uptr->name, true))
					->setDebug(*llvm)->extract();
			} else {
				auto jump = std::make_shared<JumpRegisterInstruction>(jump_var, true);
				function.insertBefore(instruction, jump, "SetupCalls: jump to function pointer")
					->setDebug(*llvm)->extract();
			}

			// Move the stack pointer up past the variables that were pushed onto the stack with pushCallValue.
			if (0 < bytes_pushed) {
				VariablePtr sp = function.sp(block);
				auto sub = std::make_shared<AddIInstruction>(sp, bytes_pushed, sp);
				function.insertBefore(instruction, sub, "SetupCalls: readjust stack pointer", false)
					->setDebug(*llvm)->extract();
			}

			if (function.isVariadic())
				function.insertBefore(instruction, std::make_shared<StackPopInstruction>(m2), false);

			// TODO: Verify. Previously, this was done regardless of calling convention.
			if (convention == CallingConvention::Reg16) {
				// Pop the argument registers from the stack.
				for (i = std::min(15, arg_count - 1); 0 <= i; --i) {
					VariablePtr arg_variable = function.makePrecoloredVariable(WhyInfo::argumentOffset + i, block);
					function.insertBefore(instruction, std::make_shared<StackPopInstruction>(arg_variable), false)
						->setDebug(*llvm)->extract();
				}
			}

			// If the call specified a result variable, move $r0 into that variable.
			if (call->result) {
				auto move =
					std::make_shared<MoveInstruction>(function.makePrecoloredVariable(WhyInfo::returnValueOffset,
						block), function.getVariable(*call->result));
				function.insertBefore(instruction, move, "SetupCalls: move result from $r0", false)
					->setDebug(*llvm)->extract();
				function.categories["SetupCalls:MoveFromResult"].push_back(move);
			}

			to_remove.push_back(instruction);
			function.reindexInstructions();
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		function.extractVariables();
	}

	int pushCallValue(Function &function, InstructionPtr instruction, ConstantPtr constant) {
		// I produce LLVM IR from C code for the mips64el-linux-gnu target, as it's seemingly the most similar to WhySA.
		// Stack parameters are passed on a 64-bit boundary (https://gcc.gnu.org/projects/mipso64-abi.html), and this
		// function has to adhere to that requirement to satisfy the assumptions that LLVM makes.

		const int size = 8;
		ValueType value_type = constant->value->valueType();

		if (value_type == ValueType::Local) {
			// Local variables
			std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			function.insertBefore(instruction, std::make_shared<SizedStackPushInstruction>(local->variable, size, -1))
				->setDebug(*instruction)->extract();
			return size;
		} else if (value_type == ValueType::Global) {
			std::shared_ptr<GlobalValue> global = std::dynamic_pointer_cast<GlobalValue>(constant->value);
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, global->name);
			auto sspush = std::make_shared<SizedStackPushInstruction>(new_var, size, -1);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, sspush)->setDebug(*instruction)->extract();
			return size;
		} else if (value_type == ValueType::Int) {
			// Integer-like values
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, constant->value->intValue(false));
			set->setOriginalValue(constant->value);
			auto sspush = std::make_shared<SizedStackPushInstruction>(new_var, size, -1);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, sspush)->setDebug(*instruction)->extract();
			return size;
		} else if (value_type == ValueType::Bool) {
			// Booleans
			std::shared_ptr<BoolValue> bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, bval->value? 1 : 0);
			auto sspush = std::make_shared<SizedStackPushInstruction>(new_var, size, -1);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, sspush)->setDebug(*instruction)->extract();
			return size;
		} else if (value_type == ValueType::Null) {
			// Null values
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, 0);
			auto sspush = std::make_shared<SizedStackPushInstruction>(new_var, size, -1);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, sspush)->setDebug(*instruction)->extract();
			return size;
		} else if (value_type == ValueType::Getelementptr) {
			// Getelementptr expressions
			std::shared_ptr<GetelementptrValue> gep = std::dynamic_pointer_cast<GetelementptrValue>(constant->value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
			if (!gep_global) {
				warn() << "Not sure what to do when the argument of getelementptr isn't a global.\n";
				function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
				return 0;
			} else {
				std::list<int> indices;
				for (const std::pair<int, long> &decimal_pair: gep->decimals)
					indices.push_back(decimal_pair.second);
				const int offset = Util::updiv(Getelementptr::compute(gep->ptrType, indices), 8);
				VariablePtr new_var = function.newVariable(constant->type);
				auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
				function.insertBefore(instruction, setsym)->setDebug(*instruction)->extract();
				if (offset != 0) {
					auto addi = std::make_shared<AddIInstruction>(new_var, offset, new_var);
					function.insertAfter(setsym, addi)->setDebug(*instruction)->extract();
				}
				auto sspush = std::make_shared<SizedStackPushInstruction>(new_var, size, -1);
				function.insertBefore(instruction, sspush)->setDebug(*instruction)->extract();
				return size;
			}
		} else if (constant->conversionSource) {
			return pushCallValue(function, instruction, constant->conversionSource);
		} else {
			warn() << "Not sure what to do with " << *constant << " (" << getName(value_type) << ")\n";
			function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
			return 0;
		}
	}

	void setupCallValue(Function &function, VariablePtr new_var, InstructionPtr instruction, ConstantPtr constant) {
		if (constant->conversionSource) {
			setupCallValue(function, new_var, instruction, constant->conversionSource);
			return;
		}

		ValueType value_type = constant->value->valueType();
		if (value_type == ValueType::Local) {
			// If it's a variable, move it into the argument register.
			std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			auto move = std::make_shared<MoveInstruction>(local->variable, new_var);
			function.insertBefore(instruction, move)->setDebug(*instruction)->extract();
		} else if (value_type == ValueType::Int) {
			// If it's an integer constant, set the argument register to it.
			auto set = std::make_shared<SetInstruction>(new_var, constant->value->intValue(false));
			set->setOriginalValue(constant->value);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
		} else if (value_type == ValueType::Bool) {
			// If it's a boolean constant, convert it to an integer and do the same.
			std::shared_ptr<BoolValue> bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			auto set = std::make_shared<SetInstruction>(new_var, bval->value + 0);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
		} else if (value_type == ValueType::Null || value_type == ValueType::Undef) {
			// If it's a null or undef constant, just use zero.
			auto set = std::make_shared<SetInstruction>(new_var, 0);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
		} else if (value_type == ValueType::Getelementptr) {
			// If it's a getelementptr expression, things are a little more difficult.
			GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(constant->value.get());
			GlobalValue *gep_global = dynamic_cast<GlobalValue *>(gep->variable.get());
			// TODO, maybe: reduce duplication
			if (!gep_global) {
				std::shared_ptr<LocalValue> local;
				if (LocalValue *gep_local = dynamic_cast<LocalValue *>(gep->variable.get()))
					local = std::make_shared<LocalValue>(gep_local->getVariable(function));
				else if (auto subgep = std::dynamic_pointer_cast<GetelementptrValue>(gep->variable))
					local = function.replaceGetelementptrValue(subgep, instruction);
				else {
					warn() << "Not sure what to do when the argument of getelementptr isn't a global or getelementptr."
					       << "\n    " << std::string(*gep->variable);
					if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get()))
						std::cerr << " (" << llvm->node->location << ")";
					std::cerr << "\n";
					function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
					return;
				}

				std::list<int> indices;
				for (const std::pair<int, long> &decimal_pair: gep->decimals)
					indices.push_back(decimal_pair.second);
				const int offset = Util::updiv(Getelementptr::compute(gep->ptrType, indices), 8);
				if (offset == 0) {
					auto move = std::make_shared<MoveInstruction>(local->getVariable(function), new_var);
					function.insertBefore(instruction, move)->setDebug(*instruction)->extract();
				} else {
					auto addi = std::make_shared<AddIInstruction>(local->getVariable(function), offset, new_var);
					function.insertBefore(instruction, addi)->setDebug(*instruction)->extract();
				}
			} else {
				std::list<int> indices;
				for (const std::pair<int, long> &decimal_pair: gep->decimals)
					indices.push_back(decimal_pair.second);
				const int offset = Util::updiv(Getelementptr::compute(gep->ptrType, indices), 8);
				auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
				function.insertBefore(instruction, setsym)->setDebug(*instruction)->extract();
				if (offset != 0)
					function.insertAfter(setsym, std::make_shared<AddIInstruction>(new_var, offset, new_var))
						->setDebug(*instruction)->extract();
			}
		} else if (value_type == ValueType::Global) {
			GlobalValue *global = dynamic_cast<GlobalValue *>(constant->value.get());
			function.insertBefore(instruction, std::make_shared<SetInstruction>(new_var, global->name))
				->setDebug(*instruction)->extract();
		} else {
			warn() << "Not sure what to do with " << *constant << " (" << getName(value_type) << ")\n";
			function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
		}
	}
}
