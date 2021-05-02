// Sorry for all the repetition.

#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/AndRInstruction.h"
#include "instruction/DiviIInstruction.h"
#include "instruction/DivIInstruction.h"
#include "instruction/DivRInstruction.h"
#include "instruction/DivuiIInstruction.h"
#include "instruction/DivuIInstruction.h"
#include "instruction/DivuRInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/ModRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/MultRInstruction.h"
#include "instruction/OrIInstruction.h"
#include "instruction/OrRInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "instruction/ShiftLeftLogicalInverseIInstruction.h"
#include "instruction/ShiftLeftLogicalRInstruction.h"
#include "instruction/ShiftRightArithmeticIInstruction.h"
#include "instruction/ShiftRightArithmeticInverseIInstruction.h"
#include "instruction/ShiftRightArithmeticRInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/ShiftRightLogicalInverseIInstruction.h"
#include "instruction/ShiftRightLogicalRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "instruction/XorIInstruction.h"
#include "instruction/XorRInstruction.h"
#include "pass/LowerMath.h"

namespace LL2W::Passes {
	template <typename R, typename I, typename Inv>
	void lowerDiv(Function &function, InstructionPtr &instruction, DivNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto div = std::make_shared<R>(left_var, right_var, node->variable);
				function.insertBefore(instruction, div);
				div->extract();
			} else if (right->isIntLike()) {
				auto div = std::make_shared<I>(left_var, right->intValue(), node->variable);
				function.insertBefore(instruction, div);
				div->extract();
			} else {
				throw std::runtime_error("Unexpected RHS value type in division instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto divi = std::make_shared<Inv>(right_var, left->intValue(), node->variable);
				function.insertBefore(instruction, divi);
				divi->extract();
			} else {
				throw std::runtime_error("Invalid RHS value type with constant LHS in division instruction: " +
					std::string(*right));
			}
		} else throw std::runtime_error("Unrecognized LHS value type in division instruction: " + std::string(*left));
	}

	std::string getName(BasicMathNode *node) {
		return *node->oper;
	}

	std::string getName(LogicNode *node) {
		switch (node->logicType) {
			case LogicNode::LogicType::And: return "and";
			case LogicNode::LogicType::Or:  return "or";
			case LogicNode::LogicType::Xor: return "xor";
			default: return std::to_string(static_cast<int>(node->logicType));
		}
	}

	std::string getName(ShrNode *node) {
		switch (node->shrType) {
			case ShrNode::ShrType::Ashr: return "ashr";
			case ShrNode::ShrType::Lshr: return "lshr";
			default: return "invalid";
		}
	}

	template <typename R, typename I, typename N>
	void lowerCommutative(Function &function, InstructionPtr &instruction, N *node) {
		ValuePtr left = node->left, right = node->right;

		if (!left->isLocal()) {
			if (right->isLocal()) {
				// The operation is commutative, so we can get away with this.
				std::swap(left, right);
			} else {
				std::cerr << instruction->debugExtra() << "\n";
				throw std::runtime_error("Left value of " + getName(node) + " instruction expected to be a pvar");
			}
		}

		VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
		if (right->isLocal()) {
			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
			function.insertBefore(instruction, new_instruction);
			new_instruction->extract();
		} else if (right->isIntLike()) {
			auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
			function.insertBefore(instruction, new_instruction);
			new_instruction->extract();
		} else {
			throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " +
				value_map.at(right->valueType()));
		}
	}

	template <typename R, typename I, typename N>
	void lowerNoncommutative(Function &function, InstructionPtr &instruction, N *node) {
		ValuePtr left = node->left, right = node->right;
		if (!left->isLocal()) {
			node->debug();
			throw std::runtime_error("Intlikes are unsupported on the LHS of a " + getName(node) + " instruction");
		}

		VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
		if (right->isLocal()) {
			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
			function.insertBefore(instruction, new_instruction);
			new_instruction->extract();
		} else if (right->isIntLike()) {
			auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
			function.insertBefore(instruction, new_instruction);
			new_instruction->extract();
		} else {
			throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " +
				value_map.at(right->valueType()));
		}
	}

	template <typename R, typename I, typename II, typename N>
	void lowerNoncommutativeOrInverse(Function &function, InstructionPtr &instruction, N *node) {
		ValuePtr left = node->left, right = node->right;
		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
				function.insertBefore(instruction, new_instruction);
				new_instruction->extract();
			} else if (right->isIntLike()) {
				auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
				function.insertBefore(instruction, new_instruction);
				new_instruction->extract();
			} else {
				throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (!right->isLocal())
				throw std::runtime_error("RHS must be a pvar when the LHS is intlike in a " + getName(node) +
					" instruction.");
			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			auto new_instruction = std::make_shared<II>(right_var, left->intValue(), node->variable);
			function.insertBefore(instruction, new_instruction);
			new_instruction->extract();
		} else {
			node->debug();
			throw std::runtime_error("Only pvars and intlikes are unsupported on the LHS of a " + getName(node) +
				" instruction");
		}
	}

	void lowerMath(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		if (*node->oper == "add") {
			lowerCommutative<AddRInstruction, AddIInstruction>(function, instruction, node);
		} else if (*node->oper == "sub") {
			lowerSub(function, instruction, node);
		} else if (*node->oper == "mul") {
			lowerMult(function, instruction, node);
		} else if (*node->oper == "shl") {
			lowerNoncommutativeOrInverse<ShiftLeftLogicalRInstruction, ShiftLeftLogicalIInstruction,
				ShiftLeftLogicalInverseIInstruction>(function, instruction, node);
		} else {
			throw std::runtime_error("Unknown math operation: " + *node->oper);
		}
	}

	void lowerMult(Function &function, InstructionPtr &instruction, BasicMathNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (!left->isLocal()) {
			if (right->isLocal()) {
				// The operation is commutative, so we can get away with this.
				std::swap(left, right);
			} else {
				std::cerr << instruction->debugExtra() << "\n";
				throw std::runtime_error("Left value of mult instruction expected to be a pvar");
			}
		}

		VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
		VariablePtr lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
		if (right->isLocal()) {
			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			auto new_instruction = std::make_shared<MultRInstruction>(left_var, right_var);
			auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
			function.insertBefore(instruction, new_instruction);
			function.insertBefore(instruction, movelo);
			new_instruction->extract();
			movelo->extract();
		} else if (right->isIntLike()) {
			auto new_instruction = std::make_shared<MultIInstruction>(left_var, right->intValue());
			auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
			function.insertBefore(instruction, new_instruction);
			function.insertBefore(instruction, movelo);
			new_instruction->extract();
			movelo->extract();
		} else {
			throw std::runtime_error("Unexpected value type in mult instruction: " +
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
			} else if (right->isGlobal()) {
				VariablePtr right_var = function.newVariable(node->type);
				auto set = std::make_shared<SetInstruction>(right_var, dynamic_cast<GlobalValue *>(right.get())->name);
				function.insertBefore(instruction, set);
				auto sub = std::make_shared<SubRInstruction>(left_var, right_var, node->variable);
				function.insertBefore(instruction, sub);
				set->extract();
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
			if (left->longValue() == 0) {
				// In cases where the LHS is zero, we can use the convenient zero register and use just one instruction.
				auto sub = std::make_shared<SubRInstruction>(zero, right_var, node->variable);
				function.insertBefore(instruction, sub);
				sub->extract();
			} else {
				// If the LHS is a non-zero integer, we need to use the property a-b = -(b-a) and then subtract the
				// result from the zero register to fix the sign.
				auto m0 = function.m0(instruction);
				auto reverse = std::make_shared<SubIInstruction>(right_var, left->intValue(), m0);
				auto fix = std::make_shared<SubRInstruction>(zero, m0, node->variable);
				function.insertBefore(instruction, reverse);
				function.insertBefore(instruction, fix);
				reverse->extract();
				fix->extract();
			}
		} else throw std::runtime_error("At least one operand of sub instruction expected to be a local variable");
	}

	void lowerLogic(Function &function, InstructionPtr &instruction, LogicNode *node) {
		switch (node->logicType) {
			case LogicNode::LogicType::And:
				lowerCommutative<AndRInstruction, AndIInstruction>(function, instruction, node);
				break;
			case LogicNode::LogicType::Or:
				lowerCommutative<OrRInstruction, OrIInstruction>(function, instruction, node);
				break;
			case LogicNode::LogicType::Xor:
				lowerCommutative<XorRInstruction, XorIInstruction>(function, instruction, node);
				break;
			default:
				throw std::runtime_error("Unknown logic type: " + std::to_string(static_cast<int>(node->logicType)));
		}
	}

	void lowerRem(Function &function, InstructionPtr &instruction, RemNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto mod = std::make_shared<ModRInstruction>(left_var, right_var, node->variable);
				function.insertBefore(instruction, mod);
				mod->extract();
			} else if (right->isIntLike()) {
				auto mod = std::make_shared<ModIInstruction>(left_var, right->intValue(), node->variable);
				function.insertBefore(instruction, mod);
				mod->extract();
			} else {
				throw std::runtime_error("Unexpected RHS value type in division instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				// Instead of making a backwards immediate modulo instruction, we can just put the immediate value into
				// $m0 and use the R-type modulo instruction.
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				VariablePtr m0 = function.m0(instruction);
				auto set = std::make_shared<SetInstruction>(m0, left->intValue());
				auto mod = std::make_shared<ModRInstruction>(m0, right_var, node->variable);
				function.insertBefore(instruction, set);
				function.insertBefore(instruction, mod);
				set->extract();
				mod->extract();
			} else {
				throw std::runtime_error("Invalid RHS value type with constant LHS in division instruction: " +
					std::string(*right));
			}
		} else throw std::runtime_error("Unrecognized LHS value type in division instruction: " + std::string(*left));
	}

	int lowerMath(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;

			const NodeType type = llvm->node->nodeType();
			if (type == NodeType::BasicMath) {
				lowerMath(function, instruction, dynamic_cast<BasicMathNode *>(llvm->node));
			} else if (type == NodeType::Logic) {
				lowerLogic(function, instruction, dynamic_cast<LogicNode *>(llvm->node));
			} else if (type == NodeType::Div) {
				DivNode *div = dynamic_cast<DivNode *>(llvm->node);
				if (div->divType == DivNode::DivType::Udiv) {
					lowerDiv<DivuRInstruction, DivuIInstruction, DivuiIInstruction>(function, instruction, div);
				} else if (div->divType == DivNode::DivType::Sdiv) {
					lowerDiv<DivRInstruction, DivIInstruction, DiviIInstruction>(function, instruction, div);
				}
			} else if (type == NodeType::Rem) {
				// TODO: differentiate between signed and unsigned remainder
				lowerRem(function, instruction, dynamic_cast<RemNode *>(llvm->node));
			} else if (type == NodeType::Shr) {
				ShrNode *shr = dynamic_cast<ShrNode *>(llvm->node);
				if (shr->shrType == ShrNode::ShrType::Ashr) {
					lowerNoncommutativeOrInverse<ShiftRightLogicalRInstruction, ShiftRightLogicalIInstruction,
						ShiftRightLogicalInverseIInstruction>(function, instruction, shr);
				} else {
					lowerNoncommutativeOrInverse<ShiftRightLogicalRInstruction, ShiftRightLogicalIInstruction,
						ShiftRightLogicalInverseIInstruction>(function, instruction, shr);
				}
			} else {
				continue;
			}

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
