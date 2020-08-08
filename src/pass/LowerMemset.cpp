#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/Variable.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/LoadSymbolInstruction.h"
#include "instruction/MemsetInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SetSymbolInstruction.h"
#include "pass/LowerMemset.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int lowerMemset(Function &function) {
		int replaced = 0;

		std::list<InstructionPtr> &linear = function.linearInstructions;
		for (auto iter = linear.begin(), end = linear.end(); iter != end;) {
			InstructionPtr &instruction = *iter;
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Call) {
				++iter;
				continue;
			}
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			if (!call->name->isGlobal()) {
				++iter;
				continue;
			}
			BasicBlockPtr block = instruction->parent.lock();
			GlobalValue *global = dynamic_cast<GlobalValue *>(call->name.get());
			const std::string &name = *global->name;
			if (name.substr(0, sizeof("llvm.memset.") - 1) != "llvm.memset.") {
				++iter;
				continue;
			}

			if (name == "llvm.memset.p0i8.i64") {
				try {
					VariablePtr count_arg, value_arg, dest_arg;
					setupMemsetValue(function, *call->constants[0]->value, instruction, dest_arg,  false, 0);
					setupMemsetValue(function, *call->constants[1]->value, instruction, value_arg, true,  1);
					setupMemsetValue(function, *call->constants[2]->value, instruction, count_arg, true,  2);
					auto memset = std::make_shared<MemsetInstruction>(count_arg, value_arg, dest_arg);
					function.insertBefore(instruction, memset);
					++iter;
					function.remove(instruction);
					continue;
				} catch (const std::exception &err) {
					error() << "Failed to replace memset.p0i8.i64 intrinsic: " << err.what() << "\n";
				}
			} else throw std::runtime_error("Unhandled memset intrinsic: " + name);
			++iter;
		}

		return replaced;
	}

	void setupMemsetValue(Function &function, Value &value, std::shared_ptr<Instruction> &instruction,
	std::shared_ptr<Variable> &variable, bool shouldLoad, int assemblerIndex) {
		if (value.isIntLike()) {
			int intval;
			if (value.isInt())
				intval = dynamic_cast<IntValue &>(value).value;
			else if (value.isBool())
				intval = dynamic_cast<BoolValue &>(value).value? 1 : 0;
			else if (value.isNull())
				intval = 0;
			else throw std::runtime_error("Unknown int-like value in LowerMemset: " + std::string(value));
			variable = function.mx(assemblerIndex, instruction->parent.lock());
			function.insertBefore(instruction, std::make_shared<SetInstruction>(variable, intval));
		} else if (value.isLocal()) {
			LocalValue &local = dynamic_cast<LocalValue &>(value);
			variable = local.variable;
		} else if (value.isGlobal()) {
			GlobalValue &global = dynamic_cast<GlobalValue &>(value);
			variable = function.mx(assemblerIndex, instruction->parent.lock());
			if (shouldLoad) {
				auto load = std::make_shared<LoadSymbolInstruction>(*global.name, variable,
					function.parent->symbolSize("@" + *global.name) / 8);
				function.insertBefore(instruction, load);
			} else {
				function.insertBefore(instruction, std::make_shared<SetSymbolInstruction>(variable, *global.name));
			}
		} else if (value.isGetelementptr()) {
			if (shouldLoad)
				throw std::runtime_error("shouldLoad not expected for a getelementptr value");
			GetelementptrValue &gep = dynamic_cast<GetelementptrValue &>(value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep.variable);
			if (!gep_global) {
				warn() << "Not sure what to do when the argument of getelementptr isn't a global.\n";
				function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
				return;
			}
			TypePtr out_type;
			const int offset = Getelementptr::compute(&gep, &out_type);
			TypePtr ptr_type = std::make_shared<PointerType>(out_type);
			VariablePtr new_var = function.newVariable(ptr_type, instruction->parent.lock());
			function.comment(instruction, "Getelementptr in LowerMemset");
			function.insertBefore(instruction, std::make_shared<SetSymbolInstruction>(new_var, *gep_global->name));
			if (offset == 0) {
				variable = new_var;
			} else {
				variable = function.newVariable(ptr_type, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<AddIInstruction>(new_var, offset, variable));
			}
		} else throw std::runtime_error("Unhandled value in LowerMemset: " + std::string(value));
	}
}
