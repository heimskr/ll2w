#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/OrRInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SubRInstruction.h"
#include "parser/Enums.h"
#include "pass/LowerMemory.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	size_t lowerMemory(Function &function) {
		Timer timer{"LowerMemory"};
		size_t replaced_count = 0;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || (llvm->getNodeType() != NodeType::Load && llvm->getNodeType() != NodeType::Store)) {
				continue;
			}

			if (llvm->getNodeType() == NodeType::Load) {
				lowerLoad(function, instruction, *llvm);
			} else if (llvm->getNodeType() == NodeType::Store) {
				lowerStore(function, instruction, *llvm);
			} else {
				continue;
			}

			to_remove.push_back(instruction);
			++replaced_count;
		}

		for (InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return replaced_count;
	}

	void lowerLoad(Function &function, const InstructionPtr &instruction, LLVMInstruction &llvm) {
		auto *node = dynamic_cast<LoadNode *>(llvm.getNode());

		ConstantPtr converted = node->constant->convert();
		if (!converted->value) {
			throw std::runtime_error("Constant lacks value in lowerLoad: " + std::string(*converted));
		}

		const auto size = static_cast<WASMSize>(Util::updiv(node->type->width(), 8));
		const ValueType value_type = converted->value->valueType();

		std::string prefix = "LowerMemory(load @ " + std::string(node->location) + "): ";

		if (value_type == ValueType::Local) {
			LocalValue *local = dynamic_cast<LocalValue *>(converted->value.get());
			VariablePtr localvar = local->getVariable(function);
			auto load = std::make_shared<LoadRInstruction>(localvar, node->variable, size);
			function.insertBefore(instruction, load, prefix + "[" + localvar->plainString() + "] -> " + node->variable->plainString())->setDebug(llvm)->extract();
			return;
		}

		if (value_type == ValueType::Global) {
			GlobalValue *global = dynamic_cast<GlobalValue *>(converted->value.get());
			auto load = std::make_shared<LoadIInstruction>(global->name, node->variable, size);
			function.insertBefore(instruction, load, prefix + "[global] -> %var")->setDebug(llvm)->extract();
			return;
		}

		if (value_type == ValueType::Null) { // In case you're feeling silly.
			auto load = std::make_shared<LoadIInstruction>(0, node->variable, size);
			function.insertBefore(instruction, load, prefix + "[null] -> %var")->setDebug(llvm)->extract();
			return;
		}

		if (value_type == ValueType::Int) {
			int intval = converted->value->intValue();
			auto load = std::make_shared<LoadIInstruction>(intval, node->variable, size);
			load->setOriginalValue(converted->value);
			function.insertBefore(instruction, load, prefix + "[int " + std::to_string(intval) + "] -> %var");
			load->setDebug(llvm)->extract();
			return;
		}

		if (value_type == ValueType::Bool) {
			BoolValue *boolval = dynamic_cast<BoolValue *>(converted->value.get());
			auto load = std::make_shared<LoadIInstruction>(boolval->value? 1 : 0, node->variable, size);
			function.insertBefore(instruction, load, prefix + "[bool " + std::to_string(boolval->value? 1 : 0) + "] -> %var")->setDebug(llvm)->extract();
			return;
		}

		throw std::runtime_error("Unexpected ValueType in load instruction: " + value_map.at(value_type));
	}

	void lowerStore(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		auto lock = function.parent.getLock();
		auto *node = dynamic_cast<StoreNode *>(llvm.getNode());

		ConstantPtr converted = node->destination->convert();
		if (!converted->value) {
			throw std::runtime_error("Constant lacks value in lowerStore: " + std::string(*converted));
		}

		std::shared_ptr<LocalValue> local;
		GlobalValue *global;

		if (converted->value->isGetelementptr()) {
			local = function.replaceGetelementptrValue(std::dynamic_pointer_cast<GetelementptrValue>(converted->value), instruction);
		} else {
			local = std::dynamic_pointer_cast<LocalValue>(converted->value);
			global = local? nullptr : dynamic_cast<GlobalValue *>(converted->value.get());
			if (!local && !global && !converted->value->isIntLike()) {
				node->debug();
				throw std::runtime_error("Expected a pvar, gvar or intlike in the constant of a store instruction");
			}
		}

		ConstantPtr source_constant = node->source->convert();
		ValuePtr source_value = source_constant->value;
		TypePtr source_type = source_constant->type;
		const auto size = static_cast<WASMSize>(Util::updiv(source_type->width(), 8));
		const ValueType value_type = source_value->valueType();

		if (source_value->isIntLike()) {
			int int_value = 0;
			ValuePtr value;
			if (value_type == ValueType::Int || value_type == ValueType::Bool) {
				int_value = source_value->intValue(false);
				value = source_value;
			}
			if (local) {
				VariablePtr m1 = function.mx(1, instruction);
				auto lvar = local->getVariable(function);
				// Because there's no single instruction of the form imm -> [$reg], we have to use a set+store pair.
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				set->setOriginalValue(value);
				// $m1 -> [%var]
				auto store = std::make_shared<StoreRInstruction>(m1, lvar, size);
				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1")->setDebug(&llvm)->extract();
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [" + lvar->plainString() + "]")->setDebug(&llvm)->extract();
			} else if (global) {
				VariablePtr m1 = function.mx(1, instruction);
				// In this case, it would be impossible for there to be a single instruction for what we're trying to do
				// because there are two immediate values. As such, we use two instructions by necessity.
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				set->setOriginalValue(value);
				function.insertBefore(instruction, set, "LowerMemory: imm -> $m1")->setDebug(&llvm)->extract();

				const int symsize = Util::updiv(function.parent.symbolSize(*global->name), 8);

				// $m1 -> [global]
				if (symsize == 1 || symsize == 8) {
					InstructionPtr store;
					try {
						store = std::make_shared<StoreIInstruction>(m1, global->name, static_cast<WASMSize>(symsize));
					} catch (const std::out_of_range &) {
						throw std::runtime_error("Couldn't find global variable @" + *global->name);
					}

					function.insertBefore(instruction, store, "LowerMemory: $m1 -> [global]")->setDebug(&llvm)->extract();
				} else if (symsize == 2 || symsize == 4) {
					VariablePtr new_var = function.newVariable(node->destination->type, instruction->parent.lock());
					function.insertBefore(instruction, std::make_shared<SetInstruction>(new_var, global->name), "LowerMemory: global -> temp")->setDebug(&llvm)->extract();
					function.insertBefore(instruction, std::make_shared<StoreRInstruction>(m1, new_var, static_cast<WASMSize>(symsize)), "LowerMemory: $m1 -> [temp]")->setDebug(&llvm)->extract();
				} else {
					throw std::runtime_error("$m1 -> [global] failed: invalid symbol size: " + std::to_string(symsize));
				}
			} else if (converted->value->isIntLike()) {
				VariablePtr m1 = function.mx(1, instruction);
				const int intptr = converted->value->intValue();
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				set->setOriginalValue(value);
				// $m1 -> [intptr]
				auto store = std::make_shared<StoreIInstruction>(m1, intptr, size);
				store->setOriginalValue(converted->value);
				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1")->setDebug(&llvm)->extract();
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [" + std::to_string(intptr) + "]")->setDebug(&llvm)->extract();
			}
		} else if (value_type == ValueType::Local || value_type == ValueType::Global) {
			VariablePtr svar;
			if (value_type == ValueType::Global) {
				svar = function.newVariable(node->source->type);
				auto set = std::make_shared<SetInstruction>(svar, dynamic_cast<GlobalValue *>(source_value.get())->name);
				function.insertBefore(instruction, set, "LowerMemory: load global")->setDebug(&llvm)->extract();
			} else {
				svar = dynamic_cast<LocalValue *>(source_value.get())->getVariable(function);
			}

			if (local) {
				auto lvar = local->getVariable(function);
				// %src -> [%dest]
				auto store = std::make_shared<StoreRInstruction>(svar, lvar, size);
				function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [" + lvar->plainString() + "]")->setDebug(&llvm)->extract();
			} else if (global) {
				// %src -> [global]
				// int symsize = Util::updiv(function.parent.symbolSize(*global->name), 8);
				int symsize = Util::updiv(node->source->type->width(), 8);
				if (symsize == 2 || symsize == 4) {
					// No ssi or shi instructions exist.
					VariablePtr new_var = function.newVariable(node->destination->type, instruction->parent.lock());
					auto set = std::make_shared<SetInstruction>(new_var, global->name);
					function.insertBefore(instruction, set, "LowerMemory: " + svar->plainString() + " -> [global]")->setDebug(&llvm)->extract();
					set->setOriginalValue(converted->value);
					function.insertBefore(instruction, std::make_shared<StoreRInstruction>(svar, new_var, static_cast<WASMSize>(symsize)))->setDebug(&llvm)->extract();
				} else {
					auto store = std::make_shared<StoreIInstruction>(svar, global->name, static_cast<WASMSize>(symsize));
					function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [global]")->setDebug(&llvm)->extract();
				}
			} else if (converted->value->isIntLike()) {
				const int intptr = converted->value->intValue();
				// %src -> [intptr]
				auto store = std::make_shared<StoreIInstruction>(svar, intptr, size);
				store->setOriginalValue(converted->value);
				function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [" + std::to_string(intptr) + "]");
				store->setDebug(&llvm)->extract();
			} else {
				throw std::runtime_error("Unexpected destination ValueType in store instruction: " + value_map.at(converted->value->valueType()));
			}
		} else {
			node->debug();
			throw std::runtime_error("Unexpected source ValueType in store instruction: " + value_map.at(value_type));
		}
	}
}
