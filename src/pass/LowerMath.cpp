#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/MultRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "pass/LowerMath.h"

namespace LL2W::Passes {
	int lowerMath(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;

			if (llvm->node->nodeType() == NodeType::BasicMath)
				lowerMath(function, instruction, dynamic_cast<BasicMathNode *>(llvm->node));
			else if (llvm->node->nodeType() == NodeType::Logic)
				lowerLogic(function, instruction, dynamic_cast<LogicNode *>(llvm->node));
			else
				continue;

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void lowerMath(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		if (*node->oper == "add") {
			lowerAdd(function, instruction, node);
		} else if (*node->oper == "sub") {
			lowerSub(function, instruction, node);
		} else if (*node->oper == "mul") {
			std::cout << "[mul]\n";
		} else {
			throw std::runtime_error("Unknown math operation: " + *node->oper);
		}

		std::cout << instruction->debugExtra() << "\n";
	}

	void lowerAdd(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (!left->isLocal()) {
			if (right->isLocal()) {
				// Addition is commutative, so we can get away with this.
				std::swap(left, right);
			} else {
				std::cerr << instruction->debugExtra() << "\n";
				throw std::runtime_error("Left value of add instruction expected to be a local value");
			}
		}

		VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
		if (right->isLocal()) {
			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			auto add = std::make_shared<AddRInstruction>(left_var, right_var, node->variable);
			function.insertBefore(instruction, add);
			add->extract();
		} else if (right->isIntLike()) {
			auto add = std::make_shared<AddIInstruction>(left_var, right->intValue(), node->variable);
			function.insertBefore(instruction, add);
			add->extract();
		} else {
			throw std::runtime_error("Unexpected value type in add instruction: " +
				value_map.at(right->valueType()));
		}
	}

	void lowerSub(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (left->isLocal()) {
			// If the LHS is a pvar, we can lower the instruction into one Why instruction.
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto sub = std::make_shared<SubRInstruction>(left_var, right_var, node->variable);
				function.insertBefore(instruction, sub);
				sub->extract();
			} else if (right->isIntLike()) {
				auto sub = std::make_shared<SubIInstruction>(left_var, right->intValue(), node->variable);
				function.insertBefore(instruction, sub);
				sub->extract();
			} else {
				throw std::runtime_error("Unexpected value type in sub instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (right->isLocal()) {
			// If the LHS is intlike, we can't usually lower the instruction directly into one Why instruction because
			// there are no subtraction instructions that support immediate values in the LHS. 
			if (!left->isIntLike()) {
				throw std::runtime_error("Unexpected value type in sub instruction: " +
					value_map.at(left->valueType()));
			}

			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			VariablePtr zero = function.makePrecoloredVariable(WhyInfo::zeroOffset, instruction->parent.lock());
			if (left->intValue() == 0) {
				// In cases where the LHS is zero, we can use the convenient zero register and use just one instruction.
				auto sub = std::make_shared<SubRInstruction>(zero, right_var, node->variable);
				function.insertBefore(instruction, sub);
				sub->extract();
			} else {
				// If the LHS is a non-zero integer, we need to use the property a-b = -(b-a) and then subtract the
				// result from the zero register to fix the sign.
				auto m0 = function.makeAssemblerVariable(0, instruction->parent.lock());
				auto reverse = std::make_shared<SubIInstruction>(right_var, left->intValue(), m0);
				auto fix = std::make_shared<SubRInstruction>(zero, m0, node->variable);
				function.insertBefore(instruction, reverse);
				function.insertBefore(instruction, fix);
				reverse->extract();
				fix->extract();
			}
		} else throw std::runtime_error("At least one operand of sub instruction expected to be a local variable");
	}

	void lowerMul(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		(void) function;
		(void) instruction;
		(void) node;
	}

	void lowerLogic(Function &function, InstructionPtr &instruction, LogicNode *node) {
		(void) function;
		(void) instruction;
		(void) node;
	}
}
