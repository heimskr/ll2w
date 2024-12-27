#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/JumpConditionalInstruction.h"
#include "pass/LowerBranches.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t lowerBranches(Function &function) {
		Timer timer{"LowerBranches"};
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			const auto *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm) {
				continue;
			}

			switch (llvm->getNodeType()) {
				case NodeType::BrCond:
					lowerBranch(function, instruction, dynamic_cast<BrCondNode *>(llvm->getNode()));
					break;
				case NodeType::BrUncond:
					lowerBranch(function, instruction, dynamic_cast<BrUncondNode *>(llvm->getNode()));
					break;
				default:
					continue;
			}

			to_remove.push_back(instruction);
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}

	void lowerBranch(Function &function, const InstructionPtr &instruction, BrCondNode *br) {
		const ValueType condition_type = br->condition->value->valueType();
		if (condition_type == ValueType::Bool) {
			const BoolValue *boolval = dynamic_cast<BoolValue *>(br->condition->value.get());
			auto jump = std::make_shared<JumpInstruction>(StringSet::unquote(boolval->value? br->ifTrue : br->ifFalse), false);
			function.insertBefore(instruction, jump)->setDebug(*br)->extract();
		} else if (condition_type != ValueType::Local) {
			br->debug();
			throw std::runtime_error("Expected a pvar for the condition of a conditional jump, got " + getName(condition_type));
		} else {
			const auto &variable = dynamic_cast<LocalValue *>(br->condition->value.get())->variable;
			auto conditional = std::make_shared<JumpConditionalInstruction>(variable, StringSet::unquote(br->ifTrue), false);
			conditional->needsTransformation = true;
			function.insertBefore(instruction, conditional)->setDebug(*br)->extract();
			auto unconditional = std::make_shared<JumpInstruction>(StringSet::unquote(br->ifFalse), false);
			unconditional->needsTransformation = true;
			function.insertBefore(instruction, unconditional)->setDebug(*br)->extract();
		}
	}

	void lowerBranch(Function &function, const InstructionPtr &instruction, BrUncondNode *br) {
		auto jump = std::make_shared<JumpInstruction>(StringSet::unquote(br->destination), false);
		jump->needsTransformation = true;
		function.insertBefore(instruction, jump)->setDebug(*br)->extract();
	}
}
