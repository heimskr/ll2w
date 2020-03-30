#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
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
			else if (llvm->node->nodeType() == NodeType::Store)
				replaceStore(function, instruction, *llvm);
			else continue;

			to_remove.push_back(instruction);
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

		std::cout << "S: " << store->debugExtra() << "\n";
		std::cout << "  Value: " << *store->value << "\n";
		std::cout << "  Constant: " << *store->constant << "\n";

		LocalValue *local = dynamic_cast<LocalValue *>(store->constant->value.get());
		if (!local)
			throw std::runtime_error("Expected a LocalValue in the constant of a store instruction");
		
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
		if (value_type == ValueType::Int) {
			IntValue *int_value = dynamic_cast<IntValue *>(store->value.get());
			auto store = std::make_shared<StoreIInstruction>(local->variable, int_value->value, size);
			function.insertBefore(instruction, store);
		} else if (value_type == ValueType::Local) {
			LocalValue *source = dynamic_cast<LocalValue *>(store->value.get());
			auto store = std::make_shared<StoreRInstruction>(source->variable, local->variable, size);
		} else {
			throw std::runtime_error("Unexpected ValueType in store instruction: "
				+ std::to_string(static_cast<int>(value_type)));
		}

	}
}
