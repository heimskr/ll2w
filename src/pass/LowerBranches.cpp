#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/JumpConditionalInstruction.h"
#include "pass/LowerBranches.h"

namespace LL2W::Passes {
	int lowerBranches(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			const LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;
			const NodeType node_type = llvm->node->nodeType();
			if (node_type == NodeType::BrCond)
				lowerBranch(function, instruction, dynamic_cast<BrCondNode *>(llvm->node));
			else if (node_type == NodeType::BrUncond)
				lowerBranch(function, instruction, dynamic_cast<BrUncondNode *>(llvm->node));
			else
				continue;

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void lowerBranch(Function &function, InstructionPtr &instruction, BrCondNode *br) {
		const ValueType condition_type = br->condition->valueType();
		if (condition_type == ValueType::Bool) {
			const BoolValue *boolval = dynamic_cast<BoolValue *>(br->condition.get());
			function.insertBefore(instruction, std::make_shared<JumpInstruction>(
				StringSet::intern(function.transformLabel(boolval->value? *br->ifTrue : *br->ifFalse)), false));
		} else if (condition_type != ValueType::Local) {
			br->debug();
			throw std::runtime_error("Expected a pvar for the condition of a conditional jump, got " +
				getName(condition_type));
		} else {
			function.insertBefore(instruction, std::make_shared<JumpConditionalInstruction>(
				dynamic_cast<LocalValue *>(br->condition.get())->variable,
				StringSet::intern(function.transformLabel(*br->ifTrue)), false));
			function.insertBefore(instruction,
				std::make_shared<JumpInstruction>(StringSet::intern(function.transformLabel(*br->ifFalse)), false));
		}
	}

	void lowerBranch(Function &function, InstructionPtr &instruction, BrUncondNode *br) {
		function.insertBefore(instruction,
			std::make_shared<JumpInstruction>(StringSet::intern(function.transformLabel(*br->destination)), false));
	}
}
