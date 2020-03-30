#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/StoreSymbolInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "parser/Enums.h"
#include "pass/ReplaceMemory.h"

namespace LL2W::Passes {
	int replaceMemory(Function &function) {
		int replaced_count = 0;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || (llvm->node->nodeType() != NodeType::Load && llvm->node->nodeType() != NodeType::Store))
				continue;
			
			if (llvm->node->nodeType() == NodeType::Load)
				replaceLoad(function, instruction, *llvm);
			else if (llvm->node->nodeType() == NodeType::Store) {
				to_remove.push_back(instruction);
				replaceStore(function, instruction, *llvm);
			} else continue;

			++replaced_count;
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return replaced_count;
	}

	void replaceLoad(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		LoadNode *load = dynamic_cast<LoadNode *>(llvm.node);
		std::cout << "L: " << load->debugExtra() << "\n";
		std::cout << "  Constant: " << *load->constant << "\n";
	}

	void replaceStore(Function &function, InstructionPtr &instruction, LLVMInstruction &llvm) {
		StoreNode *store = dynamic_cast<StoreNode *>(llvm.node);

		LocalValue *local = dynamic_cast<LocalValue *>(store->constant->value.get());
		GlobalValue *global = local? nullptr : dynamic_cast<GlobalValue *>(store->constant->value.get());
		if (!local && !global)
			throw std::runtime_error("Expected a LocalValue or GlobalValue in the constant of a store instruction");
		
		PointerType *constant_ptr = dynamic_cast<PointerType *>(store->constant->type.get());
		if (!constant_ptr)
			throw std::runtime_error("Expected a PointerType in the constant of a store instruction");

		int size;
		if (IntType *constant_int = dynamic_cast<IntType *>(constant_ptr->subtype.get())) {
			size = constant_int->width() / 8;
		} else if (PointerType *subpointer = dynamic_cast<PointerType *>(constant_ptr->subtype.get())) {
			size = WhyInfo::pointerWidth;
		} else {
			throw std::runtime_error("Unexpected pointer subtype in store instruction: "
				+ std::string(*constant_ptr->subtype));
		}

		const ValueType value_type = store->value->valueType();
		if (value_type == ValueType::Int || value_type == ValueType::Null) {
			int int_value = 0;
			if (value_type == ValueType::Int)
				int_value = dynamic_cast<IntValue *>(store->value.get())->value;
			if (local) {
				// imm -> %var
				auto store = std::make_shared<StoreIInstruction>(local->variable, int_value, size);
				function.insertBefore(instruction, store);
				store->extract();
			} else {
				auto m0 = function.makeAssemblerVariable(0, instruction->parent.lock());
				// imm -> $m0
				auto set = std::make_shared<SetInstruction>(m0, int_value);
				// $m0 -> [global]
				auto store = std::make_shared<StoreSymbolInstruction>(m0, *global->name,
					function.parent->symbolSize("@" + *global->name) / 8);
				function.insertBefore(instruction, set);
				function.insertBefore(instruction, store);
				set->extract();
				store->extract();
			}
		} else if (value_type == ValueType::Local) {
			LocalValue *source = dynamic_cast<LocalValue *>(store->value.get());
			if (local) {
				// %src -> [%dest]
				auto store = std::make_shared<StoreRInstruction>(source->variable, local->variable, size);
				function.insertBefore(instruction, store);
				store->extract();
			} else {
				// %src -> [global]
				auto store = std::make_shared<StoreSymbolInstruction>(source->variable, *global->name,
					function.parent->symbolSize("@" + *global->name) / 8);
				function.insertBefore(instruction, store);
				store->extract();
			}
		} else throw std::runtime_error("Unexpected ValueType in store instruction: " + value_map.at(value_type));
	}
}
