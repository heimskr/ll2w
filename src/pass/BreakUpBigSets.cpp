#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/LuiInstruction.h"
#include "pass/BreakUpBigSets.h"

namespace LL2W::Passes {
	void breakUpBigSets(Function &function) {
		bool any_inserted = false;

		for (InstructionPtr &instruction: function.linearInstructions) {
			SetInstruction *set = dynamic_cast<SetInstruction *>(instruction.get());
			if (!set)
				continue;

			ValuePtr value = set->originalValue;

			if (value && value->valueType() == ValueType::Int) {
				const long long_value = value->longValue();
				if (long_value < INT_MIN || INT_MAX < long_value) {
					auto lui = std::make_shared<LuiInstruction>(set->rd, static_cast<int>(long_value >> 32));
					function.insertAfter(instruction, lui, false)->setDebug(set)->extract();
					function.comment(lui, "BreakUpBigSets", false);
					any_inserted = true;
				}
			}
		}

		if (any_inserted)
			function.reindexInstructions();
	}
}
