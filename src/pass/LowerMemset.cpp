#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/Variable.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/MemsetInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/LowerMemset.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	size_t lowerMemset(Function &function) {
		Timer timer{"LowerMemset"};
		size_t replaced = 0;
		auto &linear = function.linearInstructions;
		std::vector<InstructionPtr> to_remove;

		for (auto iter = linear.begin(), end = linear.end(); iter != end;) {
			const InstructionPtr &instruction = *iter;
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Call) {
				++iter;
				continue;
			}

			CallNode *call = dynamic_cast<CallNode *>(llvm->getNode());
			if (!call->name->isGlobal()) {
				++iter;
				continue;
			}

			BasicBlockPtr block = instruction->parent.lock();
			GlobalValue *global = dynamic_cast<GlobalValue *>(call->name.get());
			std::string_view name(*global->name);

			if (!name.starts_with("llvm.memset.")) {
				++iter;
				continue;
			}

			if (name == "llvm.memset.p0i8.i64") {
				try {
					VariablePtr count_arg, value_arg, dest_arg;
					setupMemsetValue(function, call->constants[0]->convert(), instruction, dest_arg,  false);
					setupMemsetValue(function, call->constants[1]->convert(), instruction, value_arg, true);
					setupMemsetValue(function, call->constants[2]->convert(), instruction, count_arg, true);
					auto memset = std::make_shared<MemsetInstruction>(count_arg, value_arg, dest_arg);
					function.insertBefore(instruction, memset)->setDebug(llvm)->extract();
					to_remove.push_back(instruction);
					++iter;
					continue;
				} catch (const std::exception &err) {
					error() << "Failed to replace memset.p0i8.i64 intrinsic: " << err.what() << '\n';
				}
			} else {
				throw std::runtime_error("Unhandled memset intrinsic: " + std::string(name));
			}

			++iter;
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return replaced;
	}

	void setupMemsetValue(Function &function, const ConstantPtr &constant, const InstructionPtr &instruction, VariablePtr &variable, bool shouldLoad) {
		ValuePtr value = constant->value;
		if (value->isIntLike()) {
			variable = function.newVariable(constant->type);
			auto set = std::make_shared<SetInstruction>(variable, value->intValue(false));
			set->setOriginalValue(value);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			return;
		}

		if (value->isLocal()) {
			variable = dynamic_cast<LocalValue *>(value.get())->getVariable(function);
			return;
		}

		if (value->isGlobal()) {
			GlobalValue &global = *dynamic_cast<GlobalValue *>(value.get());
			variable = function.newVariable(constant->type);
			if (shouldLoad) {
				auto lock = function.parent.getLock();
				auto load = std::make_shared<LoadIInstruction>(global.name, variable, static_cast<WASMSize>(function.parent.symbolSize(*global.name) / 8));
				function.insertBefore(instruction, load)->setDebug(*instruction)->extract();
			} else {
				function.insertBefore(instruction, std::make_shared<SetInstruction>(variable, global.name))->setDebug(*instruction)->extract();
			}
			return;
		}

		if (value->isGetelementptr()) {
			if (shouldLoad) {
				throw std::runtime_error("shouldLoad not expected for a getelementptr value");
			}
			GetelementptrValue &gep = dynamic_cast<GetelementptrValue &>(*value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep.variable);
			if (!gep_global) {
				warn() << "Not sure what to do when the argument of getelementptr isn't a global in setupMemsetValue.\n" << gep << '\n';
				function.insertBefore(instruction, std::make_shared<InvalidInstruction>())->setDebug(*instruction)->extract();
				return;
			}
			TypePtr out_type;
			const int offset = Getelementptr::compute(&gep, &out_type);
			TypePtr ptr_type = std::make_shared<PointerType>(out_type);
			VariablePtr new_var = function.newVariable(ptr_type, instruction->parent.lock());
			function.comment(instruction, "Getelementptr in LowerMemset");
			function.insertBefore(instruction, std::make_shared<SetInstruction>(new_var, gep_global->name))->setDebug(*instruction)->extract();
			if (offset == 0) {
				variable = new_var;
			} else {
				variable = function.newVariable(ptr_type, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<AddIInstruction>(new_var, offset, variable))->setDebug(*instruction)->extract();
			}
			return;
		}

		throw std::runtime_error("Unhandled value in LowerMemset: " + std::string(*value));
	}
}
