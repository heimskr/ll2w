// Sorry for all the repetition.

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/AndRInstruction.h"
#include "instruction/DivIInstruction.h"
#include "instruction/DivRInstruction.h"
#include "instruction/DiviIInstruction.h"
#include "instruction/DivuIInstruction.h"
#include "instruction/DivuRInstruction.h"
#include "instruction/DivuiIInstruction.h"
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
#include "instruction/SextRInstruction.h"
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

#include <llvm/IR/Instruction.h>

#include <climits>
#include <iostream>

namespace LL2W::Passes {
	template <typename R, typename I, typename Inv>
	void lowerDiv(Function &function, const InstructionPtr &instruction, DivNode *node) {
		ValuePtr left  = node->left;
		ValuePtr right = node->right;

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
				throw std::runtime_error("Unexpected RHS value type in division instruction: " + value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				InstructionPtr new_instruction;

				if (left->overflows()) {
					VariablePtr left_var = function.get64(instruction, left->longValue());
					new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
				} else {
					auto new_inv = std::make_shared<Inv>(right_var, left->intValue(false), node->variable);
					new_inv->setOriginalValue(left);
					new_instruction = new_inv;
				}

				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
			} else {
				throw std::runtime_error("Invalid RHS value type with constant LHS in division instruction: " + std::string(*right));
			}
		} else {
			throw std::runtime_error("Unrecognized LHS value type in division instruction: " + std::string(*left));
		}
	}

	std::string getName(BasicMathNode *node) {
		return *node->oper;
	}

	std::string getName(LogicNode *node) {
		switch (node->logicType) {
			case LogicType::And: return "and";
			case LogicType::Or:  return "or";
			case LogicType::Xor: return "xor";
			default:
				return std::to_string(static_cast<int>(node->logicType));
		}
	}

	std::string getName(ShrNode *node) {
		switch (node->shrType) {
			case ShrNode::ShrType::Ashr: return "ashr";
			case ShrNode::ShrType::Lshr: return "lshr";
			default:
				return "invalid";
		}
	}

	template <typename R, typename I, typename N>
	void lowerCommutative(Function &function, const InstructionPtr &instruction, N *node) {
		auto values = node->allValues();
		ValuePtr left  = values.at(0);
		ValuePtr right = values.at(1);
		VariablePtr left_var;

		if (!left->isLocal()) {
			if (right->isLocal()) {
				// The operation is commutative, so we can get away with this.
				std::swap(left, right);
				left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			} else if (left->isIntLike() && right->isIntLike()) {
				const auto applied = I::apply(left->longValue(), right->longValue());
				auto set = SetInstruction::make(node->variable, static_cast<int>(applied));
				set->setOriginalValue(IntValue::make(applied));
				std::string comment = std::format("LowerCommutative: ({}, {}) -> {}", left->longValue(), right->longValue(), applied);
				function.insertBefore(instruction, std::move(set), std::move(comment))->setDebug(node)->extract();
				return;
			} else if (left->isGlobal()) {
				auto *global_name = dynamic_cast<GlobalValue *>(left.get())->name;
				left_var = function.newVariable(GlobalTemporaryType::make(global_name), instruction->parent.lock());
				function.insertBefore(instruction, SetInstruction::make(left_var, global_name))->setDebug(node)->extract();
			} else {
				std::cerr << instruction->debugExtra() << "\n";
				throw std::runtime_error("Left value of " + getName(node) + " instruction expected to be a pvar");
			}
		} else {
			left_var = dynamic_cast<LocalValue *>(left.get())->variable;
		}

		VariablePtr right_var;

		if (right->isGlobal()) {
			auto *global_name = dynamic_cast<GlobalValue *>(right.get())->name;
			right_var = function.newVariable(GlobalTemporaryType::make(global_name), instruction->parent.lock());
			function.insertBefore(instruction, SetInstruction::make(right_var, global_name))->setDebug(node)->extract();
		}

		if (right->isLocal() || right->isGlobal()) {
			if (!right_var) {
				right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			}
			auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
		} else if (right->isIntLike()) {
			InstructionPtr new_instruction;
			std::string comment;
			if (right->overflows()) {
				new_instruction = std::make_shared<R>(left_var, function.get64(instruction, right->longValue()), node->variable);
				comment = std::format("LowerMath: get64'd {}", right->longValue());
			} else {
				auto new_i = std::make_shared<I>(left_var, right->intValue(), node->variable);
				new_i->setOriginalValue(right);
				new_instruction = new_i;
				comment = std::format("LowerMath: no overflow for int value {} == long value {}", right->intValue(), right->longValue());
			}
			function.insertBefore(instruction, new_instruction, std::move(comment))->setDebug(node)->extract();
		} else {
			error() << std::string(*right) << '\n';
			throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " + value_map.at(right->valueType()));
		}
	}

	template <typename R, typename I, typename N>
	void lowerNoncommutative(Function &function, const InstructionPtr &instruction, N *node) {
		ValuePtr left  = node->left;
		ValuePtr right = node->right;

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
			InstructionPtr new_instruction;
			if (right->overflows()) {
				new_instruction = std::make_shared<R>(left_var, function.get64(instruction, right->longValue()), node->variable);
			} else {
				auto new_i = std::make_shared<I>(left_var, right->intValue(), node->variable);
				new_i->setOriginalValue(right);
				new_instruction = new_i;
			}
			function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
		} else {
			throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " + value_map.at(right->valueType()));
		}
	}

	static InstructionPtr insertCarefully(Function &function, const InstructionPtr &instruction, VariablePtr &variable, long value) {
		if (value < 0 || INT_MAX < value) {
			const int low  =  ((unsigned long) value)        & 0xffffffff;
			const int high = (((unsigned long) value) >> 32) & 0xffffffff;
			auto set = std::make_shared<SetInstruction>(variable, low);
			auto lui = std::make_shared<LuiInstruction>(variable, high);
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			function.insertBefore(instruction, lui)->setDebug(*instruction)->extract();
			return lui;
		} else {
			auto set = std::make_shared<SetInstruction>(variable, int(value));
			function.insertBefore(instruction, set)->setDebug(*instruction)->extract();
			return set;
		}
	}

	static InstructionPtr lowerNoncommutativeOrInverseBothIntlike(Function &function, const InstructionPtr &instruction, ShrNode *node) {
		const int64_t left  = node->left->longValue();
		const int64_t right = node->right->longValue();

		int64_t shifted;
		if (node->shrType == ShrNode::ShrType::Ashr) {
			shifted = left >> right;
		} else {
			shifted = static_cast<uint64_t>(left) >> static_cast<uint64_t>(right);
		}

		return insertCarefully(function, instruction, node->variable, shifted);
	}

	static InstructionPtr lowerNoncommutativeOrInverseBothIntlike(Function &function, const InstructionPtr &instruction, BasicMathNode *node) {
		const long left  = node->left->longValue();
		const long right = node->right->longValue();
		long computed = 0;

		switch (node->operSymbol) {
			case LLVMTOK_SHL:
				computed = left << right;
				break;
			default:
				throw std::runtime_error("lowerNoncommutativeOrInverseBothIntlike not implemented for " + *node->oper + ".");
		}

		return insertCarefully(function, instruction, node->variable, computed);
	}

	template <typename R, typename I, typename II, typename N>
	InstructionPtr lowerNoncommutativeOrInverse(Function &function, const InstructionPtr &instruction, N *node) {
		ValuePtr left  = node->left;
		ValuePtr right = node->right;
		if (left->isLocal()) {
			VariablePtr left_var = dynamic_cast<LocalValue *>(left.get())->variable;
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				auto new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
				return new_instruction;
			} else if (right->isIntLike()) {
				InstructionPtr new_instruction;
				if (right->overflows()) {
					new_instruction = std::make_shared<R>(left_var, function.get64(instruction, right->longValue()),
						node->variable);
				} else {
					auto new_i = std::make_shared<I>(left_var, right->intValue(), node->variable);
					new_i->setOriginalValue(right);
					new_instruction = new_i;
				}
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
				return new_instruction;
			} else {
				throw std::runtime_error("Unexpected value type in " + getName(node) + " instruction: " + value_map.at(right->valueType()));
			}
		} else if (left->isIntLike()) {
			if (right->isLocal()) {
				VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
				InstructionPtr new_instruction;
				if (left->overflows()) {
					VariablePtr left_var = function.get64(instruction, left->longValue());
					new_instruction = std::make_shared<R>(left_var, right_var, node->variable);
				} else {
					auto new_ii = std::make_shared<II>(right_var, left->intValue(false), node->variable);
					new_ii->setOriginalValue(left);
					new_instruction = new_ii;
				}
				function.insertBefore(instruction, new_instruction)->setDebug(node)->extract();
				return new_instruction;
			}

			if (right->isIntLike()) {
				return lowerNoncommutativeOrInverseBothIntlike(function, instruction, node);
			}

			node->debug();
			throw std::runtime_error("RHS must be a pvar or intlike when the LHS is intlike in a " + getName(node) + " instruction.");
		} else {
			node->debug();
			throw std::runtime_error("Only pvars and intlikes are unsupported on the LHS of a " + getName(node) + " instruction");
		}
	}

	static void truncate(Function &function, const InstructionPtr &last, BasicMathNode *node) {
		switch (node->type->width()) {
			case 64:
				break;
			case 32:
				function.insertAfter(last, std::make_shared<LuiInstruction>(node->variable, 0))->setDebug(node)->extract();
				break;
			case 24:
				function.insertAfter(last, std::make_shared<AndIInstruction>(node->variable, 0xffffff, node->variable))->setDebug(node)->extract();
				break;
			case 16:
				function.insertAfter(last, std::make_shared<AndIInstruction>(node->variable, 0xffff, node->variable))->setDebug(node)->extract();
				break;
			case 8:
				function.insertAfter(last, std::make_shared<AndIInstruction>(node->variable, 0xff, node->variable))->setDebug(node)->extract();
				break;
			default:
				node->debug();
				throw std::runtime_error("Unsupported bit width: " + std::to_string(node->type->width()));
		}
	}

	void lowerMath(Function &function, const InstructionPtr &instruction, BasicMathNode *node) {
		if (*node->oper == "add") {
			lowerCommutative<AddRInstruction, AddIInstruction>(function, instruction, node);
		} else if (*node->oper == "sub") {
			lowerSub(function, instruction, node);
		} else if (*node->oper == "mul") {
			lowerMult(function, instruction, node);
		} else if (*node->oper == "shl") {
			auto last = lowerNoncommutativeOrInverse<ShiftLeftLogicalRInstruction, ShiftLeftLogicalIInstruction, ShiftLeftLogicalInverseIInstruction>(function, instruction, node);
			// It's necessary to truncate the value if the operand's bit width is smaller than a register's capacity.
			truncate(function, last, node);
		} else {
			throw std::runtime_error("Unknown math operation: " + *node->oper);
		}
	}

	void lowerMult(Function &function, const InstructionPtr &instruction, BasicMathNode *node) {
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
			throw std::runtime_error("Unexpected value type in mult instruction: " + value_map.at(right->valueType()));
		}
	}

	void lowerSub(Function &function, const InstructionPtr &instruction, BasicMathNode *node) {
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
				throw std::runtime_error("Unexpected value type in sub instruction: " + value_map.at(right->valueType()));
			}
		} else if (right->isLocal()) {
			// If the LHS is intlike, we can't usually lower the instruction directly into one Why instruction because
			// there are no subtraction instructions that support immediate values in the LHS.
			if (!left->isIntLike()) {
				throw std::runtime_error("Unexpected value type in sub instruction: " + value_map.at(left->valueType()));
			}

			VariablePtr right_var = dynamic_cast<LocalValue *>(right.get())->variable;
			VariablePtr zero	  = function.makePrecoloredVariable(WhyInfo::zeroOffset, instruction->parent.lock());
			if (left->longValue() == 0) {
				// In cases where the LHS is zero, we can use the convenient zero register and use just one instruction.
				auto sub = std::make_shared<SubRInstruction>(zero, right_var, node->variable);
				function.insertBefore(instruction, sub)->setDebug(node)->extract();
			} else {
				// If the LHS is a non-zero integer, we need to use the property a-b = -(b-a) and then subtract the
				// result from the zero register to fix the sign.
				auto m0 = function.m0(instruction);
				InstructionPtr reverse;
				if (left->overflows()) {
					reverse = std::make_shared<SubRInstruction>(right_var, function.get64(instruction, left->longValue()), m0);
				} else {
					auto subi = std::make_shared<SubIInstruction>(right_var, left->intValue(false), m0);
					subi->setOriginalValue(left);
					reverse = subi;
				}
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

	void lowerLogic(Function &function, const InstructionPtr &instruction, LogicNode *node) {
		switch (node->logicType) {
			case LogicType::And:
				lowerCommutative<AndRInstruction, AndIInstruction>(function, instruction, node);
				break;
			case LogicType::Or:
				lowerCommutative<OrRInstruction, OrIInstruction>(function, instruction, node);
				break;
			case LogicType::Xor:
				lowerCommutative<XorRInstruction, XorIInstruction>(function, instruction, node);
				break;
			default:
				throw std::runtime_error("Unknown logic type: " + std::to_string(static_cast<int>(node->logicType)));
		}
	}

	template <typename R, typename I>
	void lowerRem(Function &function, const InstructionPtr &instruction, RemNode *node) {
		ValuePtr left  = node->left;
		ValuePtr right = node->right;

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
				throw std::runtime_error("Unexpected RHS value type in remainder instruction: " + value_map.at(right->valueType()));
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
				throw std::runtime_error("Invalid RHS value type with constant LHS in remainder instruction: " + std::string(*right));
			}
		} else {
			throw std::runtime_error("Unrecognized LHS value type in remainder instruction: " + std::string(*left));
		}
	}

	int lowerMath(Function &function) {
		Timer timer("LowerMath");
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			auto *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (llvm == nullptr) {
				continue;
			}

			const NodeType type = llvm->getNodeType();

			if (type == NodeType::BasicMath) {
				lowerMath(function, instruction, dynamic_cast<BasicMathNode *>(llvm->getNode()));
				to_remove.emplace_back(instruction);
				continue;
			}

			if (type == NodeType::Logic) {
				lowerLogic(function, instruction, dynamic_cast<LogicNode *>(llvm->getNode()));
				to_remove.emplace_back(instruction);
				continue;
			}

			if (type == NodeType::Div) {
				auto *div = dynamic_cast<DivNode *>(llvm->getNode());
				if (div->divType == DivNode::DivType::Udiv) {
					lowerDiv<DivuRInstruction, DivuIInstruction, DivuiIInstruction>(function, instruction, div);
				} else if (div->divType == DivNode::DivType::Sdiv) {
					lowerDiv<DivRInstruction, DivIInstruction, DiviIInstruction>(function, instruction, div);
				}
				to_remove.emplace_back(instruction);
				continue;
			}

			if (type == NodeType::Rem) {
				auto *rem = dynamic_cast<RemNode *>(llvm->getNode());
				if (rem->remType == RemNode::RemType::Srem) {
					lowerRem<ModRInstruction, ModIInstruction>(function, instruction, rem);
				} else {
					lowerRem<ModuRInstruction, ModuIInstruction>(function, instruction, rem);
				}
				to_remove.emplace_back(instruction);
				continue;
			}

			if (type == NodeType::Shr) {
				auto *shr = dynamic_cast<ShrNode *>(llvm->getNode());
				if (shr->shrType == ShrNode::ShrType::Ashr) {
					// If we're arithmetic-shifting a smaller value to the right, we need to sign extend it.
					const int  width	  = shr->type->width();
					const bool left_local = shr->left->isLocal();
					if ((width == 8 || width == 16 || width == 32) && left_local) {
						VariablePtr left = dynamic_cast<LocalValue *>(shr->left.get())->getVariable(function);
						VariablePtr left_alias = function.newVariable(IntType::make(64, true), llvm->parent.lock());
						left_alias->typeOverride = true;
						left_alias->makeAliasOf(left);
						function.insertBefore(instruction, std::make_shared<SextRInstruction>(left, left_alias))->setDebug(shr)->extract();
					} else if (width < 64 && left_local) {
						warn() << "Arithmetic shift right at " << shr->location << " needs to be sign extended from width "
						       << width << " to 64, but sign extension from that width is currently unsupported.\n";
					}
					lowerNoncommutativeOrInverse<ShiftRightArithmeticRInstruction, ShiftRightArithmeticIInstruction, ShiftRightArithmeticInverseIInstruction>(function, instruction, shr);
				} else {
					lowerNoncommutativeOrInverse<ShiftRightLogicalRInstruction, ShiftRightLogicalIInstruction, ShiftRightLogicalInverseIInstruction>(function, instruction, shr);
				}
				to_remove.emplace_back(instruction);
				continue;
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}
}
