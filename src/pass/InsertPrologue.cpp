#include "compiler/Function.h"
#include "instruction/Comment.h"
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
			if (!dynamic_cast<Label *>(instruction.get()) && !dynamic_cast<Comment *>(instruction.get())) {
				first = instruction;
				break;
			}
		}

		if (!first)
			throw std::runtime_error("Couldn't find a non-label instruction in the initial block of " + *function.name);

		// Start by pushing a few special registers to the stack.
		VariablePtr rt = function.makePrecoloredVariable(WhyInfo::returnAddressOffset, front_block);
		VariablePtr fp = function.fp(front_block);
		VariablePtr sp = function.sp(front_block);
		function.insertBefore(first, std::make_shared<StackPushInstruction>(rt), false);
		function.insertBefore(first, std::make_shared<StackPushInstruction>(fp), false);

		// Next, we need to push any variables that are written to.
		std::set<int> written;
		for (InstructionPtr &instruction: function.linearInstructions) {
			for (const VariablePtr &variable: instruction->written) {
				if (variable->reg != -1 && !WhyInfo::isSpecialPurpose(variable->reg))
					written.insert(variable->reg);
			}
		}

		function.savedRegisters.clear();
		for (int reg: written) {
			function.savedRegisters.push_back(reg);
			VariablePtr variable = function.makePrecoloredVariable(reg, front_block);
			function.insertBefore(first, std::make_shared<StackPushInstruction>(variable), false);
		}

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
