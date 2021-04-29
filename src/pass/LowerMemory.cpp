#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/LoadSymbolInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/StoreSymbolInstruction.h"
#include "instruction/SubRInstruction.h"
#include "parser/Enums.h"
#include "pass/LowerMemory.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int lowerMemory(Function &function) {
		int replaced_count = 0;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || (llvm->node->nodeType() != NodeType::Load && llvm->node->nodeType() != NodeType::Store))
				continue;
			
			if (llvm->node->nodeType() == NodeType::Load)
				lowerLoad(function, instruction, *llvm);
			else if (llvm->node->nodeType() == NodeType::Store) {
				lowerStore(function, instruction, *llvm);
			} else continue;

			to_remove.push_back(instruction);
			++replaced_count;
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return replaced_count;
	}

	void lowerLoad(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		LoadNode *node = dynamic_cast<LoadNode *>(llvm.node);
		ConstantPtr converted = node->constant->convert();
		if (!converted->value)
			throw std::runtime_error("Constant lacks value in lowerLoad: " + std::string(*converted));
		int size;
		try {
			size = getLoadStoreSize(converted);
		} catch (std::exception &) {
			node->debug();
			throw;
		}
		const ValueType value_type = converted->value->valueType();

		if (value_type == ValueType::Local) {
			LocalValue *local = dynamic_cast<LocalValue *>(converted->value.get());
			VariablePtr localvar = local->getVariable(function);
			auto load = std::make_shared<LoadRInstruction>(localvar, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [" + localvar->plainString() + "] -> "
				+ node->variable->plainString());
			load->extract();
		} else if (value_type == ValueType::Global) {
			GlobalValue *global = dynamic_cast<GlobalValue *>(converted->value.get());
			auto load = std::make_shared<LoadSymbolInstruction>(*global->name, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [global] -> %var");
			load->extract();
		} else if (value_type == ValueType::Null) { // In case you're feeling silly.
			auto load = std::make_shared<LoadIInstruction>(0, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [null] -> %var");
			load->extract();
		} else if (value_type == ValueType::Int) {
			IntValue *intval = dynamic_cast<IntValue *>(converted->value.get());
			auto load = std::make_shared<LoadIInstruction>(intval->value, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [int " + std::to_string(intval->value) +
				"] -> %var");
			load->extract();
		} else if (value_type == ValueType::Bool) {
			BoolValue *boolval = dynamic_cast<BoolValue *>(converted->value.get());
			auto load = std::make_shared<LoadIInstruction>(boolval->value? 1 : 0, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [bool " + std::to_string(boolval->value? 1 : 0)
				+ "] -> %var");
			load->extract();
		} else throw std::runtime_error("Unexpected ValueType in load instruction: " + value_map.at(value_type));
	}

	void lowerStore(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		StoreNode *node = dynamic_cast<StoreNode *>(llvm.node);

		ConstantPtr converted = node->destination->convert();
		if (!converted->value)
			throw std::runtime_error("Constant lacks value in lowerStore: " + std::string(*converted));

		LocalValue *local = dynamic_cast<LocalValue *>(converted->value.get());
		GlobalValue *global = local? nullptr : dynamic_cast<GlobalValue *>(converted->value.get());
		if (!local && !global && !converted->value->isIntLike()) {
			error() << std::string(*node->destination) << "\n";
			throw std::runtime_error("Expected a LocalValue, GlobalValue or intlike in the constant of a store "
				"instruction");
		}

		int size;
		try {
			size = getLoadStoreSize(converted);
		} catch (std::exception &) {
			node->debug();
			throw;
		}
		ValuePtr source_value = node->source->convert()->value;
		const ValueType value_type = source_value->valueType();

		if (value_type == ValueType::Int || value_type == ValueType::Null || value_type == ValueType::Bool) {
			int int_value = 0;
			if (value_type == ValueType::Int || value_type == ValueType::Bool)
				int_value = source_value->intValue();
			if (local) {
				auto m1 = function.mx(1, instruction);
				auto lvar = local->getVariable(function);
				// Because there's no single instruction of the form imm -> [$reg], we have to use a set+store pair.
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				// $m1 -> [%var]
				auto store = std::make_shared<StoreRInstruction>(m1, lvar, size);
				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1");
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [" + lvar->plainString() + "]");
				set->extract();
				store->extract();
			} else if (global) {
				auto m1 = function.mx(1, instruction->parent.lock());
				// In this case, it would be impossible for there to be a single instruction for what we're trying to do
				// because there are two immediate values. As such, we use two instructions by necessity.
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				// $m1 -> [global]
				std::shared_ptr<StoreSymbolInstruction> store;
				try {
					store = std::make_shared<StoreSymbolInstruction>(m1, *global->name,
						function.parent->symbolSize("@" + *global->name) / 8);
				} catch (const std::out_of_range &) {
					throw std::runtime_error("Couldn't find global variable @" + *global->name);
				}

				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1");
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [global]");
				set->extract();
				store->extract();
			} else if (converted->value->isIntLike()) {
				auto m1 = function.mx(1, instruction->parent.lock());
				const int intptr = converted->value->intValue();
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				// $m1 -> [intptr]
				auto store = std::make_shared<StoreIInstruction>(m1, intptr, size);
				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1");
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [" + std::to_string(intptr) + "]");
				set->extract();
				store->extract();
			}
		} else if (value_type == ValueType::Local) {
			LocalValue *source = dynamic_cast<LocalValue *>(source_value.get());
			auto svar = source->getVariable(function);
			if (local) {
				auto lvar = local->getVariable(function);
				// %src -> [%dest]
				auto store = std::make_shared<StoreRInstruction>(svar, lvar, size);
				function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [" +
					lvar->plainString() + "]");
				store->extract();
			} else if (global) {
				// %src -> [global]
				int symsize = function.parent->symbolSize("@" + *global->name);
				symsize = symsize / 8 + (symsize % 8? 1 : 0);
				auto store = std::make_shared<StoreSymbolInstruction>(svar, *global->name, symsize);
				function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [global]");
				store->extract();
			} else if (converted->value->isIntLike()) {
				const int intptr = converted->value->intValue();
				// %src -> [intptr]
				auto store = std::make_shared<StoreIInstruction>(svar, intptr, size);
				function.insertBefore(instruction, store, "LowerMemory: " + svar->plainString() + " -> [" +
					std::to_string(intptr) + "]");
				store->extract();
			} else
				throw std::runtime_error("Unexpected destination ValueType in store instruction: " +
					value_map.at(converted->value->valueType()));
		} else
			throw std::runtime_error("Unexpected source ValueType in store instruction: " + value_map.at(value_type));
	}

	int getLoadStoreSize(ConstantPtr &constant) {
		PointerType *constant_ptr = dynamic_cast<PointerType *>(constant->type.get());
		if (!constant_ptr)
			throw std::runtime_error("Expected a PointerType in the constant of a load/store instruction");

		Type *subtype = constant_ptr->subtype.get();
		if (IntType *constant_int = dynamic_cast<IntType *>(subtype)) {
			const int width = constant_int->width();
			if (width < 8)
				return 1;
			return constant_int->width() / 8;
		} else if (dynamic_cast<PointerType *>(subtype) || dynamic_cast<FunctionType *>(subtype)) {
			return WhyInfo::pointerWidth;
		} else {
			// warn() << "getLoadStoreSize: Unexpected pointer subtype: " + std::string(*constant_ptr->subtype) << "\n";
			return constant_ptr->subtype->width() / 8;
			// return -1;
		}
	}
}
