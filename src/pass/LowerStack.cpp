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
	static int getOffset(const Function &function, const StackLocation &location) {
		int offset = location.offset;
		if (location.purpose != StackLocation::Purpose::Spill)
			offset += function.spillSize; // TODO: verify "+ 8"
		return offset;
	}

	int lowerStack(Function &function) {
		std::list<InstructionPtr> to_remove;

		VariablePtr base = function.fp(function.getEntry());
		// VariablePtr base = function.mx(8, function.getEntry());
		VariablePtr m2 = function.mx(2, function.getEntry());

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (StackStoreInstruction *stack_store = dynamic_cast<StackStoreInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_store->location);
				if (offset == 0) {
					// %var -> [base]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, base);
					function.insertBefore(instruction, store, "LowerStack: %var -> [base] for " +
						stack_store->location.variable->plainString())->setDebug(stack_store)->extract();
				} else {
					// base - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(base, offset, m2);
					// %var -> [$m2]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, m2);
					function.insertBefore(instruction, sub,   "LowerStack: base - offset -> $m2 for " +
						stack_store->location.variable->plainString())->setDebug(stack_store)->extract();
					function.insertBefore(instruction, store, "LowerStack: %var -> [$m2]")
						->setDebug(stack_store)->extract();
				}
			} else if (StackLoadInstruction *stack_load = dynamic_cast<StackLoadInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_load->location);
				if (offset == 0) {
					// [base] -> %var
					auto load = std::make_shared<LoadRInstruction>(base, stack_load->result);
					function.insertBefore(instruction, load, "LowerStack: [base] -> %var for " +
						stack_load->location.variable->plainString())->setDebug(stack_load)->extract();
				} else {
					// base - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(base, offset, m2);
					// [$m2] -> %var
					auto load = std::make_shared<LoadRInstruction>(m2, stack_load->result);
					function.insertBefore(instruction, sub,  "LowerStack: base - offset -> $m2 for " +
						stack_load->location.variable->plainString())->setDebug(stack_load)->extract();
					function.insertBefore(instruction, load, "LowerStack: [$m2] -> " +
						stack_load->result->plainString())->setDebug(stack_load)->extract();
				}
			} else continue;

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
