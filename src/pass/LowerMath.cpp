// Sorry for all the repetition.

#include <climits>
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
#include "instruction/LuiInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/ModRInstruction.h"
#include "instruction/ModuIInstruction.h"
#include "instruction/ModuRInstruction.h"
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
#include "util/Timer.h"

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
				div->setDebug(node)->extract();
			} else if (right->isIntLike()) {
				std::shared_ptr<WhyInstruction> div;
				if (right->overflows()) {
					VariablePtr overflow_var = function.get64(instruction, right->longValue());
					div = std::make_shared<R>(left_var, overflow_var, node->variable);
				} else {
					auto idiv = std::make_shared<I>(left_var, right->intValue(), node->variable);
					idiv->setOriginalValue(right);
					div = std::move(idiv);
				}
				function.insertBefore(instruction, div);
				div->setDebug(node)->extract();
			} else {
				throw std::runtime_error("Unexpected RHS value type in division instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto divi = std::make_shared<Inv>(right_var, left->intValue(), node->variable);
				divi->setOriginalValue(left);
				function.insertBefore(instruction, divi);
				divi->setDebug(node)->extract();
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
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
		} else if (right->isIntLike()) {
			auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
			new_instruction->setOriginalValue(right);
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
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
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
		} else if (right->isIntLike()) {
			auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
			new_instruction->setOriginalValue(right);
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
		} else {
			throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " +
				value_map.at(right->valueType()));
		}
	}

	static void insertCarefully(Function &function, InstructionPtr &instruction, VariablePtr &variable, long value) {
		if (value < 0 || INT_MAX < value) {
			const int low = ((unsigned long) value) & 0xffffffff;
			const int high = (((unsigned long) value) >> 32) & 0xffffffff;
			auto set = std::make_shared<SetInstruction>(variable, low);
			auto lui = std::make_shared<LuiInstruction>(variable, high);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, lui)->setDebug(*instruction)->extract();
		} else {
			auto set = std::make_shared<SetInstruction>(variable, int(value));
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
		}
	}

	static void lowerNoncommutativeOrInverseBothIntlike(Function &function, InstructionPtr &instruction,
	                                                    ShrNode *node) {
		const long left = node->left->longValue(), right = node->right->longValue();

		long shifted;
		if (node->shrType == ShrNode::ShrType::Ashr)
			shifted = left >> right;
		else
			shifted = (unsigned long) left >> (unsigned long) right;

		insertCarefully(function, instruction, node->variable, shifted);
	}

	static void lowerNoncommutativeOrInverseBothIntlike(Function &function, InstructionPtr &instruction,
	                                                    BasicMathNode *node) {
		const long left = node->left->longValue(), right = node->right->longValue();
		long computed;

		switch (node->operSymbol) {
			case LLVMTOK_SHL:
				computed = left << right;
				break;
			default:
				throw std::runtime_error("lowerNoncommutativeOrInverseBothIntlike not implemented for " + *node->oper +
					".");
		}

		insertCarefully(function, instruction, node->variable, computed);
	}

	template <typename R, typename I, typename II, typename N>
	void lowerNoncommutativeOrInverse(Function &function, InstructionPtr &instruction, N *node) {
		ValuePtr left = node->left, right = node->right;
		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
			} else if (right->isIntLike()) {
				auto new_instruction = std::make_shared<I>(left_var, right->intValue(), node->variable);
				new_instruction->setOriginalValue(right);
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
			} else {
				throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto new_instruction = std::make_shared<II>(right_var, left->intValue(), node->variable);
				new_instruction->setOriginalValue(left);
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
			} else if (right->isIntLike()) {
				lowerNoncommutativeOrInverseBothIntlike(function, instruction, node);
			} else {
				node->debug();
				throw std::runtime_error("RHS must be a pvar or intlike when the LHS is intlike in a " + getName(node) +
					" instruction.");
			}
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
			auto mult = std::make_shared<MultRInstruction>(left_var, right_var);
			auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
			function.insertBefore(instruction, mult)->setDebug(node)->extract();
			function.insertBefore(instruction, movelo)->setDebug(node)->extract();
		} else if (right->isIntLike()) {
			std::shared_ptr<WhyInstruction> mult;
			if (right->overflows()) {
				mult = std::make_shared<MultRInstruction>(left_var, function.get64(instruction, right->longValue()));
			} else {
				auto imult = std::make_shared<MultIInstruction>(left_var, right->intValue());
				imult->setOriginalValue(right);
				mult = imult;
			}

			auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
			function.insertBefore(instruction, mult)->setDebug(node)->extract();
			function.insertBefore(instruction, movelo)->setDebug(node)->extract();
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
				function.insertBefore(instruction, sub)->setDebug(node)->extract();
			} else if (right->isIntLike()) {
				std::shared_ptr<WhyInstruction> sub;
				if (right->overflows()) {
					VariablePtr overflow_var = function.get64(instruction, right->longValue());
					sub = std::make_shared<SubRInstruction>(left_var, overflow_var, node->variable);
				} else {
					auto isub = std::make_shared<SubIInstruction>(left_var, right->intValue(), node->variable);
					isub->setOriginalValue(right);
					sub = std::move(isub);
				}
				function.insertBefore(instruction, sub)->setDebug(node)->extract();
			} else if (right->isGlobal()) {
				VariablePtr right_var = function.newVariable(node->type);
				auto set = std::make_shared<SetInstruction>(right_var, dynamic_cast<GlobalValue *>(right.get())->name);
				function.insertBefore(instruction, set)->setDebug(node)->extract();
				auto sub = std::make_shared<SubRInstruction>(left_var, right_var, node->variable);
				function.insertBefore(instruction, sub)->setDebug(node)->extract();
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
				function.insertBefore(instruction, sub)->setDebug(node)->extract();
			} else {
				// If the LHS is a non-zero integer, we need to use the property a-b = -(b-a) and then subtract the
				// result from the zero register to fix the sign.
				auto m0 = function.m0(instruction);
				auto reverse = std::make_shared<SubIInstruction>(right_var, left->intValue(), m0);
				reverse->setOriginalValue(left);
				auto fix = std::make_shared<SubRInstruction>(zero, m0, node->variable);
				function.insertBefore(instruction, reverse)->setDebug(node)->extract();
				function.insertBefore(instruction, fix)->setDebug(node)->extract();
			}
		} else if (left->isIntLike() && right->isIntLike()) {
			// Sometimes I've seen things like
			//     %13 = sub i64 23, 1
			// after running mem2reg.
			insertCarefully(function, instruction, node->variable, left->longValue() - right->longValue());
		} else {
			std::cerr << instruction->debugExtra() << '\n';
			throw std::runtime_error("At least one operand of sub instruction expected to be a local variable");
		}
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

	template <typename R, typename I>
	void lowerRem(Function &function, InstructionPtr &instruction, RemNode *node) {
		ValuePtr left = node->left, right = node->right;

		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto mod = std::make_shared<R>(left_var, right_var, node->variable);
				function.insertBefore(instruction, mod)->setDebug(node)->extract();
			} else if (right->isIntLike()) {
				std::shared_ptr<WhyInstruction> mod;
				if (right->overflows()) {
					VariablePtr overflow_var = function.get64(instruction, right->longValue(), false);
					mod = std::make_shared<R>(left_var, overflow_var, node->variable);
				} else {
					auto imod = std::make_shared<I>(left_var, right->intValue(), node->variable);
					imod->setOriginalValue(right);
					mod = std::move(imod);
				}
				function.insertBefore(instruction, mod)->setDebug(node)->extract();
			} else {
				throw std::runtime_error("Unexpected RHS value type in remainder instruction: " +
					value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				// Instead of making a backwards immediate modulo instruction, we can just put the immediate value into
				// $m0 and use the R-type modulo instruction.
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				VariablePtr m0 = function.m0(instruction);
				auto set = std::make_shared<SetInstruction>(m0, left->intValue(false));
				set->setOriginalValue(left);
				auto mod = std::make_shared<R>(m0, right_var, node->variable);
				function.insertBefore(instruction, set)->setDebug(node)->extract();
				function.insertBefore(instruction, mod)->setDebug(node)->extract();
			} else {
				throw std::runtime_error("Invalid RHS value type with constant LHS in remainder instruction: " +
					std::string(*right));
			}
		} else throw std::runtime_error("Unrecognized LHS value type in remainder instruction: " + std::string(*left));
	}

	int lowerMath(Function &function) {
		Timer timer("LowerMath");
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
				RemNode *rem = dynamic_cast<RemNode *>(llvm->node);
				if (rem->remType == RemNode::RemType::Srem)
					lowerRem<ModRInstruction, ModIInstruction>(function, instruction, rem);
				else
					lowerRem<ModuRInstruction, ModuIInstruction>(function, instruction, rem);
			} else if (type == NodeType::Shr) {
				ShrNode *shr = dynamic_cast<ShrNode *>(llvm->node);
				if (shr->shrType == ShrNode::ShrType::Ashr) {
					lowerNoncommutativeOrInverse<ShiftRightArithmeticRInstruction, ShiftRightArithmeticIInstruction,
						ShiftRightArithmeticInverseIInstruction>(function, instruction, shr);
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
