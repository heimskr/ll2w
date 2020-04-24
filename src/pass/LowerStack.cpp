#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LowerStack.h"

namespace LL2W::Passes {
	int lowerStack(Function &function) {
		std::list<InstructionPtr> to_remove;

		VariablePtr fp = function.fp(function.getEntry());
		VariablePtr m2 = function.mx(2, function.getEntry());

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (StackStoreInstruction *stack_store = dynamic_cast<StackStoreInstruction *>(instruction.get())) {
				if (stack_store->location.offset == 0) {
					// %var -> [$fp]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, fp);
					function.insertBefore(instruction, store, "LowerStack: %var -> [$fp] for " +
						stack_store->location.variable->plainString());
					store->extract();
				} else {
					// $fp - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(fp, stack_store->location.offset, m2);
					// %var -> [$m2]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, m2);
					function.insertBefore(instruction, sub,   "LowerStack: $fp - offset -> $m2 for " +
						stack_store->location.variable->plainString());
					function.insertBefore(instruction, store, "LowerStack: %var -> [$m2]");
					sub->extract();
					store->extract();
				}
			} else if (StackLoadInstruction *stack_load = dynamic_cast<StackLoadInstruction *>(instruction.get())) {
				if (stack_load->location.offset == 0) {
					// [$fp] -> %var
					auto load = std::make_shared<LoadRInstruction>(fp, stack_load->result);
					function.insertBefore(instruction, load, "LowerStack: [$fp] -> %var for " +
						stack_load->location.variable->plainString());
					load->extract();
				} else {
					// $fp - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(fp, stack_load->location.offset, m2);
					// [$m2] -> %var
					auto load = std::make_shared<LoadRInstruction>(m2, stack_load->result);
					function.insertBefore(instruction, sub,  "LowerStack: $fp - offset -> $m2 for " +
						stack_load->location.variable->plainString());
					function.insertBefore(instruction, load, "LowerStack: [$m2] -> " +
						stack_load->result->plainString());
					sub->extract();
					load->extract();
				}
			} else continue;

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
