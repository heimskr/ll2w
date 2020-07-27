#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
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
		const int size = getLoadStoreSize(node->constant);
		const ValueType value_type = node->constant->value->valueType();

		if (value_type == ValueType::Local) {
			LocalValue *local = dynamic_cast<LocalValue *>(node->constant->value.get());
			auto load = std::make_shared<LoadRInstruction>(local->variable, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [" + local->variable->plainString() + "] -> "
				+ node->variable->plainString());
			load->extract();
		} else if (value_type == ValueType::Global) {
			GlobalValue *global = dynamic_cast<GlobalValue *>(node->constant->value.get());
			auto load = std::make_shared<LoadSymbolInstruction>(*global->name, node->variable, size);
			function.insertBefore(instruction, load, "LowerMemory(load): [global] -> %var");
			load->extract();
		} else throw std::runtime_error("Unexpected ValueType in load instruction: " + value_map.at(value_type));
	}

	void lowerStore(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		StoreNode *node = dynamic_cast<StoreNode *>(llvm.node);

		LocalValue *local = dynamic_cast<LocalValue *>(node->constant->value.get());
		GlobalValue *global = local? nullptr : dynamic_cast<GlobalValue *>(node->constant->value.get());
		if (!local && !global)
			throw std::runtime_error("Expected a LocalValue or GlobalValue in the constant of a store instruction");

		const int size = getLoadStoreSize(node->constant);
		const ValueType value_type = node->value->valueType();

		if (value_type == ValueType::Int || value_type == ValueType::Null) {
			int int_value = 0;
			if (value_type == ValueType::Int)
				int_value = dynamic_cast<IntValue *>(node->value.get())->value;
			if (local) {
				auto m1 = function.mx(1, instruction);
				// Because there's no single instruction of the form imm -> [$reg], we have to use a set+store pair.
				// imm -> $m1
				auto set = std::make_shared<SetInstruction>(m1, int_value);
				// $m1 -> [%var]
				auto store = std::make_shared<StoreRInstruction>(m1, local->variable, size);
				function.insertBefore(instruction, set,   "LowerMemory: imm -> $m1");
				function.insertBefore(instruction, store, "LowerMemory: $m1 -> [" + local->variable->plainString() +
					"]");
				set->extract();
				store->extract();
			} else {
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
			}
		} else if (value_type == ValueType::Local) {
			LocalValue *source = dynamic_cast<LocalValue *>(node->value.get());
			if (local) {
				// %src -> [%dest]
				auto store = std::make_shared<StoreRInstruction>(source->variable, local->variable, size);
				function.insertBefore(instruction, store, "LowerMemory: " + source->variable->plainString() + " -> [" +
					local->variable->plainString() + "]");
				store->extract();
			} else {
				// %src -> [global]
				auto store = std::make_shared<StoreSymbolInstruction>(source->variable, *global->name,
					function.parent->symbolSize("@" + *global->name) / 8);
				function.insertBefore(instruction, store, "LowerMemory: " + source->variable->plainString() +
					" -> [global]");
				store->extract();
			}
		} else throw std::runtime_error("Unexpected ValueType in store instruction: " + value_map.at(value_type));
	}

	int getLoadStoreSize(ConstantPtr &constant) {
		PointerType *constant_ptr = dynamic_cast<PointerType *>(constant->type.get());
		if (!constant_ptr)
			throw std::runtime_error("Expected a PointerType in the constant of a load/store instruction");

		Type *subtype = constant_ptr->subtype.get();
		if (IntType *constant_int = dynamic_cast<IntType *>(subtype)) {
			return constant_int->width() / 8;
		} else if (dynamic_cast<PointerType *>(subtype) || dynamic_cast<FunctionType *>(subtype)) {
			return WhyInfo::pointerWidth;
		} else {
			throw std::runtime_error("Unexpected pointer subtype in load/store instruction: "
				+ std::string(*constant_ptr->subtype));
		}
	}
}
