#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "exception/TypeError.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/JumpConditionalInstruction.h"
#include "instruction/JumpInstruction.h"
#include "pass/LowerSwitch.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t lowerSwitch(Function &function) {
		Timer timer("LowerSwitch");
		std::list<InstructionPtr> to_remove;

		VariablePtr m0 = function.m0(function.getEntry());

		for (const InstructionPtr &instruction: function.linearInstructions) {
			auto llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->getNodeType() != NodeType::Switch)
				continue;
			auto *sw = dynamic_cast<SwitchNode *>(llvm->getNode());

			BasicBlockPtr block = instruction->parent.lock();
			InstructionPtr last_instruction = instruction;

			if (!sw->value->isLocal())
				throw TypeError("Expected a pvar in switch instruction", sw->type);

			VariablePtr switch_var = dynamic_cast<LocalValue *>(sw->value.get())->variable;

			for (const auto &[type, value, label]: sw->table) {
				if (!value->isIntLike()) {
					std::cerr << instruction->debugExtra() << '\n';
					throw TypeError("Expected int constant in table of switch instruction", type);
				}
				auto comp = std::make_shared<ComparisonIInstruction>(switch_var, value->intValue(), m0, IcmpCond::Eq);
				comp->setOriginalValue(value);
				auto jump = std::make_shared<JumpConditionalInstruction>(m0, label, false);
				jump->needsTransformation = true;
				function.insertBefore(instruction, comp, false)->setDebug(*llvm, true);
				function.insertBefore(instruction, jump, false)->setDebug(*llvm, true);
			}

			auto jump = std::make_shared<JumpInstruction>(sw->label, false);
			jump->needsTransformation = true;
			function.insertBefore(instruction, jump, "LowerSwitch: default", false)->setDebug(*llvm, true);
			to_remove.push_back(instruction);
		}

		if (!to_remove.empty())
			function.reindexInstructions();

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
