#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/LogicalNotRInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SextRInstruction.h"
#include "pass/LowerIcmp.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	int lowerIcmp(Function &function) {
		Timer timer("LowerIcmp");
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Icmp) {
				continue;
			}
			lowerIcmp(function, instruction, dynamic_cast<IcmpNode *>(llvm->getNode()));
			to_remove.push_back(instruction);
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}

	static void lowerLocalIcmp(Function &function, const InstructionPtr &instruction, IcmpNode *node, const VariablePtr &rs, const VariablePtr &rt) {
		IcmpCond cond = node->cond;
		auto int_type = std::dynamic_pointer_cast<IntType>(node->getType());
		VariablePtr rd = node->variable;

		const int width = node->getType()->width();
		if (isSigned(cond) && int_type && width < 64) {
			if (width == 32 || width == 16) {
				VariablePtr rs_alias = function.newVariable(IntType::make(64, true), instruction->parent.lock());
				rs_alias->typeOverride = true;
				rs_alias->makeAliasOf(rs);
				function.insertBefore(instruction, std::make_shared<SextRInstruction>(rs, rs_alias))->setDebug(node)->extract();

				// Not necessary if the RHS is a 64-bit local created by a set (later broken up by BreakUpBigSets) below.
				if (rt->type->width() < 64) {
					VariablePtr rt_alias = function.newVariable(IntType::make(64, true), instruction->parent.lock());
					rt_alias->typeOverride = true;
					rt_alias->makeAliasOf(rt);
					function.insertBefore(instruction, std::make_shared<SextRInstruction>(rt, rt_alias))->setDebug(node)->extract();
				}
			} else {
				node->debug();
				warn() << "Signed compare with width less than 64 but not equal to 32: not sign extending\n";
			}
		}

		// Because Why lacks a not-equals comparison, we have to do an equals comparison and invert it.
		if (cond == IcmpCond::Ne) {
			VariablePtr m3 = function.mx(3, instruction->parent.lock());
			function.insertBefore(instruction, std::make_shared<ComparisonRInstruction>(rs, rt, m3, IcmpCond::Eq))->setDebug(node)->extract();
			function.insertBefore(instruction, std::make_shared<LogicalNotRInstruction>(m3, rd))->setDebug(node)->extract();
		} else {
			function.insertBefore(instruction, std::make_shared<ComparisonRInstruction>(rs, rt, rd, cond))->setDebug(node)->extract();
		}
	}

	void lowerIcmp(Function &function, const InstructionPtr &instruction, IcmpNode *node) {
		if (node->getType()->typeType() == TypeType::Vector) {
			throw std::runtime_error("Vectors are unsupported in icmp instructions");
		}

		IcmpCond cond = node->cond;

		auto values = node->allValuePointers();
		ValuePtr &value1 = *values[0], &value2 = *values[1];

		if (value1->valueType() != ValueType::Local) {
			if (value2->valueType() == ValueType::Local) {
				// Sometimes there's a non-pvar on the left and a pvar on the right. When this occurs, we can make
				// things simple by just swapping the two values and flipping the comparison operator.
				std::swap(value1, value2);
				cond = cond_rev_map.at(cond);
			} else {
				ValuePtr local = LocalValue::make(function.makeVariable(value1, instruction));
				std::swap(value1, local);
				// node->debug();
				// throw std::runtime_error("First value of icmp instruction expected to be a pvar");
			}
		}

		auto int_type = std::dynamic_pointer_cast<IntType>(node->getType());
		if (!int_type && node->getType()->typeType() != TypeType::Pointer) {
			node->debug();
			throw std::invalid_argument("icmp instructions must have an integer or pointer type");
		}

		VariablePtr rs = dynamic_cast<LocalValue *>(value1.get())->variable;
		VariablePtr rd = node->variable;
		rd->setType(IntType::make(1, false));

		const ValueType type2 = value2->valueType();

		if (type2 == ValueType::Local || type2 == ValueType::Global) {
			VariablePtr rt;

			if (type2 == ValueType::Local) {
				rt = dynamic_cast<LocalValue *>(value2.get())->variable;
			} else {
				rt = function.newVariable(node->getType(), instruction->parent.lock());
				// Because gvars are pointers instead of the actual values, we use set instead of load here.
				function.insertBefore(instruction, std::make_shared<SetInstruction>(rt, dynamic_cast<GlobalValue *>(value2.get())->name));
			}

			lowerLocalIcmp(function, instruction, node, rs, rt);
			return;
		}

		int imm{};

		if (type2 == ValueType::Int) {
			auto &intval = dynamic_cast<IntValue &>(*value2);

			if (Util::outOfRange(intval.value)) {
				VariablePtr rt = function.newVariable(IntType::make(64), instruction->parent.lock());
				auto set = std::make_shared<SetInstruction>(rt, static_cast<int>(intval.value));
				set->setOriginalValue(value2);
				function.insertBefore(instruction, std::move(set), "Big icmp", false);
				lowerLocalIcmp(function, instruction, node, rs, rt);
				return;
			}

			imm = intval.intValue();
		} else if (type2 == ValueType::Null) {
			imm = 0;
		} else {
			throw std::runtime_error("Unsupported value type in icmp instruction: " + value_map.at(type2));
		}

		const int width = node->getType()->width();
		if ((isSigned(cond) || imm < 0) && int_type && width < 64) {
			if (width == 32 || width == 16) {
				VariablePtr rs_alias = function.newVariable(IntType::make(64, true), instruction->parent.lock());
				rs_alias->typeOverride = true;
				rs_alias->makeAliasOf(rs);
				function.insertBefore(instruction, std::make_shared<SextRInstruction>(rs, rs_alias))->setDebug(node)->extract();
			} else {
				node->debug();
				warn() << "Signed compare with width less than 64 but not equal to 32: not sign extending\n";
			}
		}

		if (cond == IcmpCond::Ne) {
			VariablePtr m3 = function.mx(3, instruction->parent.lock());
			function.insertBefore(instruction, std::make_shared<ComparisonIInstruction>(rs, imm, m3, IcmpCond::Eq))->setDebug(node)->extract();
			function.insertBefore(instruction, std::make_shared<LogicalNotRInstruction>(m3, rd))->setDebug(node)->extract();
		} else {
			function.insertBefore(instruction, std::make_shared<ComparisonIInstruction>(rs, imm, rd, cond))->setDebug(node)->extract();
		}
	}
}
