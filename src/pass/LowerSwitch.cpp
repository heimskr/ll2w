#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "exception/TypeError.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/JumpConditionalInstruction.h"
#include "instruction/JumpInstruction.h"
#include "pass/LowerSwitch.h"

namespace LL2W::Passes {
	int lowerSwitch(Function &function) {
		std::list<InstructionPtr> to_remove;

		VariablePtr m0 = function.m0(function.getEntry());

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Switch)
				continue;
			SwitchNode *sw = dynamic_cast<SwitchNode *>(llvm->node);

			BasicBlockPtr block = instruction->parent.lock();
			InstructionPtr last_instruction = instruction;

			if (!sw->value->isLocal())
				throw TypeError("Expected a pvar in switch instruction", sw->type);

			VariablePtr switch_var = dynamic_cast<LocalValue *>(sw->value.get())->variable;

			for (const auto &[type, value, label]: sw->table) {
				if (!value->isInt())
					throw TypeError("Expected int constant in table of switch instruction", type);
				const std::string *transformed = StringSet::intern(function.transformLabel(*label));
				auto comp = std::make_shared<ComparisonIInstruction>(switch_var, value->intValue(), m0, IcmpCond::Eq);
				auto jump = std::make_shared<JumpConditionalInstruction>(m0, transformed, false);
				function.insertBefore(instruction, comp, false);
				function.insertBefore(instruction, jump, false);
				comp->extract();
				jump->extract();
			}

			auto jump = std::make_shared<JumpInstruction>(StringSet::intern(function.transformLabel(*sw->label)),
				false);
			function.insertBefore(instruction, jump, false);
			jump->extract();
			to_remove.push_back(instruction);
		}

		if (!to_remove.empty())
			function.reindexInstructions();

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
