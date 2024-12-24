#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LowerStack.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static int getOffset(const Function &function, const StackLocation &location) {
		int offset = location.offset;
		if (location.purpose != StackLocation::Purpose::Spill)
			offset += function.spillSize + 8; // TODO: verify "+ 8"
		return offset;
	}

	int lowerStack(Function &function) {
		Timer timer("LowerStack");
		std::list<InstructionPtr> to_remove;

		VariablePtr base = function.fp(function.getEntry());
		// VariablePtr base = function.mx(8, function.getEntry());
		VariablePtr m2 = function.mx(2, function.getEntry());
		m2->type = PointerType::make(VoidType::make());

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (StackStoreInstruction *stack_store = dynamic_cast<StackStoreInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_store->location);
				const std::string plain_string = stack_store->location.variable->plainString();
				if (offset == 0) {
					// %var -> [base]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, base);
					function.insertBefore(instruction, store, "LowerStack: " + plain_string + " -> [base]")
						->setDebug(stack_store)->extract();
				} else {
					// base - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(base, offset, m2);
					// %var -> [$m2]
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, m2);
					function.insertBefore(instruction, sub,   "LowerStack: base - offset -> $m2 for " + plain_string)
						->setDebug(stack_store)->extract();
					function.insertBefore(instruction, store, "LowerStack: " + plain_string + " -> [$m2]")
						->setDebug(stack_store)->extract();
				}
			} else if (StackLoadInstruction *stack_load = dynamic_cast<StackLoadInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_load->location);
				const std::string plain_string = stack_load->location.variable->plainString();
				if (offset == 0) {
					// [base] -> %var
					auto load = std::make_shared<LoadRInstruction>(base, stack_load->result);
					function.insertBefore(instruction, load, "LowerStack: [base] -> " + plain_string)
						->setDebug(stack_load)->extract();
				} else {
					// base - offset -> $m2
					auto sub = std::make_shared<SubIInstruction>(base, offset, m2);
					// [$m2] -> %var
					auto load = std::make_shared<LoadRInstruction>(m2, stack_load->result);
					function.insertBefore(instruction, sub,  "LowerStack: base - offset -> $m2 for " + plain_string)->setDebug(stack_load)->extract();
					function.insertBefore(instruction, load, "LowerStack: [$m2] -> " + plain_string)->setDebug(stack_load)->extract();
				}
			} else continue;

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
