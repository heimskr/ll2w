#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/LogicalNotRInstruction.h"
#include "pass/LowerIcmp.h"

namespace LL2W::Passes {
	int lowerIcmp(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Icmp)
				continue;
			lowerIcmp(function, instruction, dynamic_cast<IcmpNode *>(llvm->node));
			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void lowerIcmp(Function &function, InstructionPtr &instruction, IcmpNode *node) {
		if (node->type->typeType() == TypeType::Vector)
			throw std::runtime_error("Vectors are unsupported in icmp instructions");

		IcmpCond cond = node->cond;

		ValuePtr value1 = node->value1, value2 = node->value2;

		if (value1->valueType() != ValueType::Local) {
			if (value2->valueType() == ValueType::Local) {
				// Sometimes there's a non-pvar on the left and a pvar on the right. When this occurs, we can make
				// things simple by just swapping the two values and flipping the comparison operator.
				std::swap(value1, value2);
				cond = cond_rev_map.at(cond);
			} else throw std::runtime_error("First value of icmp instruction expected to be a pvar");
		}

		VariablePtr rs = dynamic_cast<LocalValue *>(value1.get())->variable;
		VariablePtr rd = node->variable;
		
		const ValueType type2 = value2->valueType();
		if (type2 == ValueType::Local) {
			VariablePtr rt = dynamic_cast<LocalValue *>(value2.get())->variable;
			if (cond == IcmpCond::Ne) {
				VariablePtr m3 = function.makeAssemblerVariable(3, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<ComparisonRInstruction>(rs, rt, m3, IcmpCond::Eq));
				function.insertBefore(instruction, std::make_shared<LogicalNotRInstruction>(m3));
			} else {
				function.insertBefore(instruction, std::make_shared<ComparisonRInstruction>(rs, rt, rd, cond));
			}
		} else {
			int imm;
			if (type2 == ValueType::Int) {
				imm = dynamic_cast<IntValue *>(value2.get())->value;
			} else if (type2 == ValueType::Null) {
				imm = 0;
			} else throw std::runtime_error("Unsupported value type in icmp instruction: " + value_map.at(type2));

			if (cond == IcmpCond::Ne) {
				VariablePtr m3 = function.makeAssemblerVariable(3, instruction->parent.lock());
				function.insertBefore(instruction, std::make_shared<ComparisonIInstruction>(rs, imm, m3, IcmpCond::Eq));
				function.insertBefore(instruction, std::make_shared<LogicalNotRInstruction>(m3, rd));
			} else {
				function.insertBefore(instruction, std::make_shared<ComparisonIInstruction>(rs, imm, rd, cond));
			}
		}
	}
}
