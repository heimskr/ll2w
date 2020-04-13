#include "compiler/Function.h"
#include "instruction/Label.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/InsertPrologue.h"

// #define MOVE_STACK_POINTER

namespace LL2W::Passes {
	void insertPrologue(Function &function) {
		BasicBlockPtr front_block = function.blocks.front();
		InstructionPtr first;
		for (InstructionPtr &instruction: front_block->instructions) {
			if (!dynamic_cast<Label *>(instruction.get())) {
				first = instruction;
				break;
			}
		}

		if (!first)
			throw std::runtime_error("Couldn't find a non-label instruction in the initial block of " + *function.name);

		VariablePtr rt = function.makePrecoloredVariable(WhyInfo::returnAddressOffset, front_block);
		VariablePtr fp = function.makePrecoloredVariable(WhyInfo::framePointerOffset, front_block);
		VariablePtr sp = function.makePrecoloredVariable(WhyInfo::stackPointerOffset, front_block);
		function.insertBefore(first, std::make_shared<StackPushInstruction>(rt), false);
		function.insertBefore(first, std::make_shared<StackPushInstruction>(fp), false);
		function.insertBefore(first, std::make_shared<MoveInstruction>(sp, fp), false);

#ifdef MOVE_STACK_POINTER
		int to_skip = 0;
		for (const std::pair<int, StackLocation> &pair: function.stack)
			to_skip += pair.second.width;

		if (to_skip != 0)
			function.insertBefore(first, std::make_shared<SubIInstruction>(sp, to_skip, sp), false);
#endif

		function.reindexInstructions();
	}
}
