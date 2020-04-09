#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/CompareIInstruction.h"
#include "instruction/CompareRInstruction.h"
#include "instruction/SelectInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LowerSelect.h"

namespace LL2W::Passes {
	int lowerSelect(Function &function) {
		std::list<InstructionPtr> to_remove;

		VariablePtr m0 = function.m0(function.getEntry());

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Select)
				continue;
			SelectNode *select = dynamic_cast<SelectNode *>(llvm->node);

			VariablePtr left_var, right_var;

			// If the true-condition is an integer-like constant, we need to put it in a register.
			if (select->firstValue->isIntLike()) {
				left_var = function.newVariable(select->firstType, instruction->parent.lock());
				auto set = std::make_shared<SetInstruction>(left_var, select->firstValue->intValue());
				function.insertBefore(instruction, set);
				set->extract();
			} else if (select->firstValue->isLocal()) {
				left_var = dynamic_cast<LocalValue *>(select->firstValue.get())->variable;
			} else {
				throw std::runtime_error("Invalid true-value in select instruction: " +
					std::string(*select->firstValue));
			}

			// If the false-condition is an integer-like constant, we need to put it in a register.
			if (select->secondValue->isIntLike()) {
				right_var = function.newVariable(select->firstType, instruction->parent.lock());
				auto set = std::make_shared<SetInstruction>(right_var, select->secondValue->intValue());
				function.insertBefore(instruction, set);
				set->extract();
			} else if (select->secondValue->isLocal()) {
				right_var = dynamic_cast<LocalValue *>(select->secondValue.get())->variable;
			} else {
				throw std::runtime_error("Invalid false-value in select instruction: " +
					std::string(*select->secondValue));
			}

			// Next, we need to compare the i1 value with zero.
			std::shared_ptr<CompareIInstruction> comp;
			if (select->conditionValue->isIntLike()) {
				VariablePtr zero = function.makePrecoloredVariable(WhyInfo::zeroOffset, instruction->parent.lock());
				// We can compare backwards because the select instruction following the comparison isn't checking for
				// greater-than or less-than conditions; it's checking for inequality.
				comp = std::make_shared<CompareIInstruction>(zero, select->conditionValue->intValue());
			} else if (select->conditionValue->isLocal()) {
				VariablePtr cond_var = dynamic_cast<LocalValue *>(select->conditionValue.get())->variable;
				comp = std::make_shared<CompareIInstruction>(cond_var, 0);
			} else {
				throw std::runtime_error("Invalid condition-value in select instruction: " +
					std::string(*select->conditionValue));
			}

			function.insertBefore(instruction, comp);
			comp->extract();

			auto sel = std::make_shared<SelectInstruction>(left_var, right_var, select->variable, Condition::Nonzero);
			function.insertBefore(instruction, sel);
			sel->extract();

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
