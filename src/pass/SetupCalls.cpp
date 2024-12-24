#include <ranges>
#include <span>
#include <tuple>

#include "compiler/BasicType.h"
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
#include "instruction/SextRInstruction.h"
#include "instruction/StackPopInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "instruction/SubRInstruction.h"
#include "instruction/TypedPopInstruction.h"
#include "instruction/TypedPushInstruction.h"
#include "pass/LowerIcmp.h"
#include "pass/MakeCFG.h"
#include "pass/SetupCalls.h"
#include "util/Timer.h"
#include "util/Util.h"

// #define PUSH_ARGUMENT_REGISTERS

namespace LL2W::Passes {
	static void extractInfo(const std::string *global, Function &function, CallNode *call,
	                        CallingConvention &convention, bool &ellipsis,
	                        std::vector<TypePtr> *argument_types = nullptr, TypePtr *return_type = nullptr) {
		Timer timer{"ExtractInfo"};

		TypePtr ret;

		for (;;) {
			// First, we check the call node itself—it sometimes contains the signature of the function.
			if (call->argumentsExplicit) {
				if (argument_types != nullptr) {
					*argument_types = Type::copyMany(call->argumentTypes);
				}
				ret = call->returnType;
				ellipsis = call->argumentEllipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
				break;
			}

			if (function.parent.functions.count(*global) != 0) {
				// When the arguments aren't explicit, we check the parent program's map of functions.
				Function &func = *function.parent.functions.at(*global);
				ellipsis = func.isVariadic();
				convention = func.getCallingConvention();
				if (argument_types != nullptr) {
					argument_types->reserve(func.arguments->size());
					for (const FunctionArgument &argument: *func.arguments) {
						argument_types->push_back(argument.type->copy());
					}
				}
				ret = func.returnType;
				break;
			}

			if (function.parent.declarations.count(*global) != 0) {
				// We can also check the map of declarations.
				FunctionHeader *header = function.parent.declarations.at(*global);
				ellipsis = header->arguments->ellipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
				if (argument_types != nullptr) {
					argument_types->reserve(header->arguments->arguments.size());
					for (const FunctionArgument &argument: header->arguments->arguments) {
						argument_types->push_back(argument.type->copy());
					}
				}
				ret = header->returnType;
				break;
			}

			if (function.parent.aliases.count(StringSet::intern(*global)) != 0) {
				// In rare cases, there may be an alias.
				AliasDef *alias = function.parent.aliases.at(StringSet::intern(*global));
				global = alias->aliasTo->front() == '@'? StringSet::intern(alias->aliasTo->substr(1)) : alias->aliasTo;
				continue;
			}

			throw std::runtime_error("Couldn't find signature for function " + *global);
		}

		if (return_type != nullptr) {
			*return_type = ret;
		}

		if (argument_types != nullptr) {
			if (function.debugIndex == -1) {
				// warn() << "Couldn't find debug index for function " << *global << '\n';
				return;
			}

			Program &program = function.parent;

			int debug_index = -1;

			if (auto iter = program.declarations.find(*global); iter != program.declarations.end()) {
				debug_index = iter->second->debugIndex;
			} else if (auto iter = program.functions.find(*global); iter != program.functions.end()) {
				debug_index = iter->second->debugIndex;
			} else {
				warn() << "Couldn't find declaration for function " << *global << '\n';
				return;
			}

			auto subprogram_iter = program.subprograms.find(debug_index);

			if (subprogram_iter == program.subprograms.end()) {
				// warn() << "Couldn't find subprogram for function " << *global << " (debug index " << debug_index << ")\n";
				return;
			}

			Subprogram &subprogram = subprogram_iter->second;

			if (!program.subroutineTypes.contains(subprogram.type)) {
				warn() << "Couldn't find subroutine types for function " << *function.name << '\n';
				return;
			}

			try {
				const auto subroutine_type = program.subroutineTypes.at(subprogram.type);
				size_t i = 0;
				std::span span(program.basicTypeLists.at(subroutine_type));
				if (!ret->isVoid() || (!span.empty() && !span.front())) {
					// Skip the return type.
					span = span.subspan(1);
				}

				for (size_t s = 0, end = std::min(span.size(), argument_types->size()); s < end; ++s) {
					if (auto int_type = std::dynamic_pointer_cast<IntType>(argument_types->at(i++))) {
						int_type->setSignedness(span[s]->getSignedness(&function.parent));
					}
				}
			} catch (const std::out_of_range &) {
				info() << "List indices:";
				for (const auto &[key, val]: program.basicTypeLists) std::cerr << ' ' << key;
				std::cerr << '\n';
			}
		}
	}

	void setupCalls(Function &function) {
		auto lock = function.parent.getLock();
		Timer timer{"SetupCalls"};
		int i{};
		std::list<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			// Look for a call instruction.
			auto llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->getNodeType() != NodeType::Call) {
				continue;
			}

			CallNode *call = dynamic_cast<CallNode *>(llvm->getNode());
			BasicBlockPtr block = instruction->parent.lock();

			VariableValue *name_value = dynamic_cast<VariableValue *>(call->name.get());
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(name_value);
			std::unique_ptr<GlobalValue> global_uptr;

			if (global_name) {
				global_uptr = std::make_unique<GlobalValue>(*global_name);
				const std::string &name = *global_name->name;

				if (function.parent.uselessFunctions.count(name) != 0) {
					to_remove.push_back(instruction);
					continue;
				}

				if (function.parent.simpleFunctions.count(name) != 0) {
					CallingConvention convention;
					bool ellipsis;
					const long simple_index = function.parent.simpleFunctions.at(name);
					extractInfo(global_uptr->name, function, call, convention, ellipsis, nullptr);
					// TODO: Instructions inserted here won't be touched by SplitResultMoves. This might be an issue.
					if (!call->result) {
						warn() << "Call to simple function " << name << " has no result.\n";
					} else if (convention != CallingConvention::Reg16) {
						warn() << "Call to simple function " << name << " isn't Reg16.\n";
					} else {
						auto out = setupCallValue(function, call->variable, instruction, call->constants[simple_index]);
						if (out) {
							function.comment(out, "SetupCallValue: simple function elision for " + name);
						} else {
							function.comment(instruction, "SetupCallValue: simple function elision for " + name + " somewhere around here");
						}
						to_remove.push_back(instruction);
						continue;
					}
				}
			}

			// Now we need to find out about the function's arguments because we need to know how to call it.
			CallingConvention convention;
			std::vector<TypePtr> argument_types;
			bool ellipsis;
			TypePtr return_type;

			if (global_uptr) {
				extractInfo(global_uptr->name, function, call, convention, ellipsis, &argument_types, &return_type);
			} else {
				return_type = call->returnType;
				for (ConstantPtr &ptr: call->constants) {
					argument_types.push_back(ptr->type);
				}
				ellipsis = false;
				convention = CallingConvention::Reg16;
			}

			int reg_max = convention == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			int arg_count = argument_types.size();

#ifdef PUSH_ARGUMENT_REGISTERS
			// First, push the current values of the argument registers to the stack.
			if (convention == CallingConvention::Reg16) {
				for (i = 0; i < arg_count && i < WhyInfo::argumentCount; ++i) {
					VariablePtr arg_variable = function.makePrecoloredVariable(WhyInfo::argumentOffset + i, block);
					function.insertBefore(instruction, std::make_shared<TypedPushInstruction>(arg_variable), false)->setDebug(*llvm)->extract();
				}
			}
#endif

			// Clobber caller-saved registers as necessary.
			std::vector<std::shared_ptr<Clobber>> clobbers;
			ClobberMap clobbers_by_reg;
			for (int offset = 0; offset < WhyInfo::temporaryCount; ++offset) {
				const int reg = WhyInfo::temporaryOffset + offset;
				auto clobber = function.clobber(instruction, reg);
				clobbers.push_back(clobber);
				clobbers_by_reg.emplace(reg, clobber);
			}

			// Next, if applicable, we account for the situation where the jump is to an argument register. Because it
			// may be overwritten right before the jump, we'd need to copy it to a temporary variable and jump to that.
			VariablePtr jump_var;
			if (!global_uptr) {
				jump_var = dynamic_cast<LocalValue *>(name_value)->variable;
				if (jump_var->isLess(arg_count)) {
					VariablePtr new_var = function.newVariable(jump_var->type);
					auto move = std::make_shared<MoveInstruction>(jump_var, new_var);
					function.insertBefore(instruction, move, "jump_var -> new_var")->setDebug(*llvm)->extract();
					jump_var = new_var;
				}
			}

			// Next, move variables into the argument registers.
			for (i = 0; i < reg_max && i < arg_count; ++i) {
				VariablePtr precolored = function.makePrecoloredVariable(WhyInfo::argumentOffset + i, instruction->parent.lock());
				// precolored->type = call->constants[i]->type;
				precolored->type = argument_types.at(i);
				setupCallValue(function, precolored, instruction, call->constants[i]);
			}

			// Push variables onto the stack, right to left.
			int bytes_pushed = 0;
			if (ellipsis) {
				for (i = call->constants.size() - 1; 0 <= i; --i) {
					bytes_pushed += pushCallValue(function, instruction, call->constants[i]);
				}
			} else {
				for (i = arg_count - 1; reg_max <= i; --i) {
					bytes_pushed += pushCallValue(function, instruction, call->constants[i]);
				}
			}

			VariablePtr m2;

			if (function.isVariadic()) {
				m2 = function.mx(2, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<StackPushInstruction>(m2))->setDebug(*llvm)->extract();
			}

			// Once we're done putting the arguments in the proper place, remove the variables from the call
			// instruction's set of read variables so the register allocator doesn't try to insert any spills/loads.
			llvm->read.clear();

			// At this point, we're ready to insert the jump.
			if (global_uptr) {
				function.insertBefore(instruction, std::make_shared<JumpInstruction>(global_uptr->name, true))->setDebug(*llvm)->extract();
			} else {
				auto jump = std::make_shared<JumpRegisterInstruction>(jump_var, true);
				function.insertBefore(instruction, jump, "SetupCalls: jump to function pointer " + jump_var->plainString(), false)->setDebug(*llvm)->extract();
			}

			// Move the stack pointer up past the variables that were pushed onto the stack with pushCallValue.
			if (0 < bytes_pushed) {
				VariablePtr sp = function.sp(block);
				auto add = std::make_shared<AddIInstruction>(sp, bytes_pushed, sp);
				function.insertBefore(instruction, add, "SetupCalls: readjust stack pointer", false)->setDebug(*llvm)->extract();
			}

			if (function.isVariadic()) {
				function.insertBefore(instruction, std::make_shared<StackPopInstruction>(m2), false);
			}

#ifdef PUSH_ARGUMENT_REGISTERS
			// TODO: Verify. Previously, this was done regardless of calling convention.
			if (convention == CallingConvention::Reg16) {
				// Pop the argument registers from the stack.
				for (i = std::min(15, arg_count - 1); 0 <= i; --i) {
					VariablePtr arg_variable = function.makePrecoloredVariable(WhyInfo::argumentOffset + i, block);
					function.insertBefore(instruction, std::make_shared<TypedPopInstruction>(arg_variable), false)
						->setDebug(*llvm)->extract();
				}
			}
#endif

			// If the call specified a result variable, move $r0 into that variable.
			if (call->result) {
				auto r0 = function.makePrecoloredVariable(WhyInfo::returnValueOffset, block);
				r0->type = return_type;
				auto move = std::make_shared<MoveInstruction>(r0, function.getVariable(*call->result));
				function.insertBefore(instruction, move, "SetupCalls: move result from $r0", false)->setDebug(*llvm)->extract();
				function.categories["SetupCalls:MoveFromResult"].insert(move);
			}

			// Unclobber the temporary registers we clobbered earlier.
			for (auto iter = clobbers.rbegin(), end = clobbers.rend(); iter != end; ++iter) {
				function.unclobber(instruction, *iter);
			}

			to_remove.push_back(instruction);
			function.reindexInstructions();
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		function.extractVariables();
	}

	int pushCallValue(Function &function, InstructionPtr instruction, ConstantPtr constant) {
		// I produce LLVM IR from C code for the mips64el-linux-gnu target, as it's seemingly the most similar to Why.
		// Stack parameters are passed on a 64-bit boundary (https://gcc.gnu.org/projects/mipso64-abi.html), and this
		// function has to adhere to that requirement to satisfy the assumptions that LLVM makes.

		const int size = 8;
		ValueType value_type = constant->value->valueType();
		int signext = constant->parattrs.signext? constant->type->width() : 0;
		signext = signext == 64? 0 : signext;

		auto make_signext = [&](const VariablePtr &source, const VariablePtr &destination) -> InstructionPtr {
			InstructionPtr out;
			switch (signext) {
				case  0:
				case 64:
					return out;
				case  1:
					// If we're sign extending an i1, we can take advantage of the fact that 0 - 1 = all ones
					// and 0 - 0 = all zeroes.
					out = std::make_shared<SubRInstruction>(function.zero(instruction), source, destination);
					break;
				case  8:
				case 16:
				case 32:
					// TODO(typed): verify. Do we need to set the destination's type?
					out = std::make_shared<SextRInstruction>(source, destination);
					break;
				default:
					std::cerr << instruction->debugExtra() << '\n';
					throw std::runtime_error("Invalid sign extension in pushCallValue: " + std::to_string(signext));
			}
			out->setDebug(*instruction)->extract();
			return out;
		};

		if (value_type == ValueType::Local) {
			// Local variables
			std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			VariablePtr var = signext? function.newVariable(constant->type) : local->variable;
			if (signext) {
				function.insertBefore(instruction, make_signext(local->variable, var));
			}
			// TODO: verify
			function.insertBefore(instruction, std::make_shared<StackPushInstruction>(var, -1))->setDebug(*instruction)->extract();
			return size;
		}

		if (value_type == ValueType::Global) {
			// Global variables
			std::shared_ptr<GlobalValue> global = std::dynamic_pointer_cast<GlobalValue>(constant->value);
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, global->name);
			if (signext) {
				function.insertBefore(instruction, make_signext(new_var, new_var));
			}
			// TODO: verify
			auto spush = std::make_shared<StackPushInstruction>(new_var);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, spush)->setDebug(*instruction)->extract();
			return size;
		}

		if (value_type == ValueType::Int) {
			// Integer-like values
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, constant->value->intValue(false));
			set->setOriginalValue(constant->value);
			// TODO: verify
			auto spush = std::make_shared<StackPushInstruction>(new_var);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext(new_var, new_var));
			}
			function.insertBefore(instruction, spush)->setDebug(*instruction)->extract();
			return size;
		}

		if (value_type == ValueType::Bool) {
			// Booleans
			std::shared_ptr<BoolValue> bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, bval->value? 1 : 0);
			// TODO: verify
			auto spush = std::make_shared<StackPushInstruction>(new_var);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext(new_var, new_var));
			}
			function.insertBefore(instruction, spush)->setDebug(*instruction)->extract();
			return size;
		}

		if (value_type == ValueType::Null || value_type == ValueType::Undef) {
			// Null and undef values
			VariablePtr new_var = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(new_var, 0);
			// TODO: verify
			auto spush = std::make_shared<StackPushInstruction>(new_var);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, spush)->setDebug(*instruction)->extract();
			return size;
		}

		if (value_type == ValueType::Getelementptr) {
			// Getelementptr expressions
			std::shared_ptr<GetelementptrValue> gep = std::dynamic_pointer_cast<GetelementptrValue>(constant->value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
			if (!gep_global) {
				warn() << "Not sure what to do when the argument of getelementptr isn't a global.\n";
				function.insertBefore(instruction, InvalidInstruction::make());
				return 0;
			}

			const std::list<long> indices = Getelementptr::getLongIndices(*gep);
			const long offset = Util::updiv(Getelementptr::compute(gep->ptrType, indices), 8l);
			if (Util::outOfRange(offset)) {
				warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
			}
			VariablePtr new_var = function.newVariable(constant->type);
			auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
			function.insertBefore(instruction, setsym)->setDebug(*instruction)->extract();
			if (offset != 0) {
				auto addi = std::make_shared<AddIInstruction>(new_var, int(offset), new_var);
				function.insertAfter(setsym, addi)->setDebug(*instruction)->extract();
			}
			if (signext) {
				function.insertBefore(instruction, make_signext(new_var, new_var));
			}
			// TODO: verify
			auto spush = std::make_shared<StackPushInstruction>(new_var);
			function.insertBefore(instruction, spush)->setDebug(*instruction)->extract();
			return size;
		}

		if (constant->conversionSource) {
			return pushCallValue(function, instruction, constant->conversionSource);
		}

		warn() << "Not sure what to do with " << *constant << " (" << getName(value_type) << ") at " << __FILE__ << ':' << __LINE__ << '\n';
		function.insertBefore(instruction, InvalidInstruction::make());
		return 0;
	}

	InstructionPtr
	setupCallValue(Function &function, VariablePtr new_var, InstructionPtr instruction, ConstantPtr constant) {
		if (constant->conversionSource) {
			setupCallValue(function, new_var, instruction, constant->conversionSource);
			return nullptr;
		}

		int signext = constant->parattrs.signext? constant->type->width() : 0;
		signext = signext == 64? 0 : signext;

		auto make_signext = [&]() -> InstructionPtr {
			InstructionPtr out;
			switch (signext) {
				case  0:
				case 64: return out;
				case  1: out = std::make_shared<SubRInstruction>(function.zero(instruction), new_var, new_var); break;
				case  8:
				case 16:
				case 32: {
					VariablePtr new_var_alias = function.newVariable(IntType::make(64, true),
						instruction->parent.lock());
					new_var_alias->typeOverride = true;
					new_var_alias->makeAliasOf(new_var);
					out = std::make_shared<SextRInstruction>(new_var, new_var_alias);
					break;
				}
				default:
					std::cerr << instruction->debugExtra() << '\n';
					throw std::runtime_error("Invalid sign extension in setupCallValue: " + std::to_string(signext));
			}
			out->setDebug(*instruction)->extract();
			return out;
		};

		ValueType value_type = constant->value->valueType();

		if (value_type == ValueType::Local) {
			// If it's a variable, move it into the argument register.
			auto local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			auto move = std::make_shared<MoveInstruction>(local->variable, new_var);
			auto out = function.insertBefore(instruction, move);
			out->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext());
			}
			return out;
		}

		if (value_type == ValueType::Int) {
			// If it's an integer constant, set the argument register to it.
			auto set = std::make_shared<SetInstruction>(new_var, constant->value->intValue(false));
			set->setOriginalValue(constant->value);
			auto out = function.insertBefore(instruction, set);
			out->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext());
			}
			return out;
		}

		if (value_type == ValueType::Bool) {
			// If it's a boolean constant, convert it to an integer and do the same.
			auto bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			auto set = std::make_shared<SetInstruction>(new_var, bval->value? 1 : 0);
			auto out = function.insertBefore(instruction, set);
			out->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext());
			}
			return out;
		}

		if (value_type == ValueType::Null || value_type == ValueType::Undef) {
			// If it's a null or undef constant, just use zero. No need to sign extend.
			auto set = std::make_shared<SetInstruction>(new_var, 0);
			auto out = function.insertBefore(instruction, set);
			out->setDebug(*instruction)->extract();
			return out;
		}

		if (value_type == ValueType::Getelementptr) {
			// If it's a getelementptr expression, things are a little more difficult.
			GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(constant->value.get());
			GlobalValue *gep_global = dynamic_cast<GlobalValue *>(gep->variable.get());

			// TODO, maybe: reduce duplication
			if (!gep_global) {
				std::shared_ptr<LocalValue> local;

				if (LocalValue *gep_local = dynamic_cast<LocalValue *>(gep->variable.get())) {
					local = std::make_shared<LocalValue>(gep_local->getVariable(function));
				} else if (auto subgep = std::dynamic_pointer_cast<GetelementptrValue>(gep->variable)) {
					local = function.replaceGetelementptrValue(subgep, instruction);
				} else {
					warn() << "Not sure what to do when the argument of getelementptr isn't a global or getelementptr.\n    " << *gep->variable << '\n';
					return function.insertBefore(instruction, InvalidInstruction::make());
				}

				std::list<long> indices = Getelementptr::getLongIndices(*gep);

				const auto offset = Util::updiv(Getelementptr::compute(gep->ptrType, std::move(indices)), 8);
				if (Util::outOfRange(offset)) {
					warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
				}

				InstructionPtr out;

				if (offset == 0) {
					auto move = std::make_shared<MoveInstruction>(local->getVariable(function), new_var);
					function.insertBefore(instruction, move)->setDebug(*instruction)->extract();
					out = move;
				} else {
					auto addi = std::make_shared<AddIInstruction>(local->getVariable(function), int(offset), new_var);
					function.insertBefore(instruction, addi)->setDebug(*instruction)->extract();
					out = addi;
				}

				if (signext) {
					function.insertBefore(instruction, make_signext());
				}

				return out;
			}

			std::list<long> indices = Getelementptr::getLongIndices(*gep);

			const int64_t offset = Util::updiv(Getelementptr::compute(gep->ptrType, std::move(indices)), 8);
			if (Util::outOfRange(offset)) {
				warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
			}

			auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
			auto out = function.insertBefore(instruction, setsym);
			out->setDebug(*instruction)->extract();

			if (offset != 0) {
				function.insertAfter(setsym, std::make_shared<AddIInstruction>(new_var, int(offset), new_var))->setDebug(*instruction)->extract();
			}

			if (signext) {
				function.insertBefore(instruction, make_signext());
			}

			return out;
		}

		if (value_type == ValueType::Global) {
			auto *global = dynamic_cast<GlobalValue *>(constant->value.get());
			auto out = function.insertBefore(instruction, std::make_shared<SetInstruction>(new_var, global->name));
			out->setDebug(*instruction)->extract();
			if (signext) {
				function.insertBefore(instruction, make_signext());
			}
			return out;
		}

		if (value_type == ValueType::Icmp) {
			auto *icmp = dynamic_cast<IcmpValue *>(constant->value.get());
			auto node = IcmpNode::make(new_var, icmp->cond, icmp->left, icmp->right);
			Passes::lowerIcmp(function, instruction, node.get());
			if (signext) {
				function.insertBefore(instruction, make_signext());
			}
			return nullptr; // Whatever.
		}

		warn() << "Not sure what to do with " << *constant << " (" << getName(value_type) << ") at " << __FILE__ << ":" << __LINE__ << '\n';
		return function.insertBefore(instruction, InvalidInstruction::make());
	}
}
