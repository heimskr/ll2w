#include "compiler/Function.h"
#include "compiler/Program.h"
#include "instruction/Comment.h"
#include "instruction/Label.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/InsertPrologue.h"
#include "util/Timer.h"

// #define MOVE_STACK_POINTER

namespace LL2W::Passes {
	void insertPrologue(Function &function) {
		Timer timer("InsertPrologue");
		BasicBlockPtr front_block = function.blocks.front();
		InstructionPtr first = function.firstInstruction(true);

		if (!first)
			throw std::runtime_error("Couldn't find a non-label instruction in the initial block of " + *function.name);

		if (first->debugIndex == -1)
			first->debugIndex = function.initialDebugIndex;

		// Start by pushing a few special registers to the stack.
		VariablePtr rt = function.makePrecoloredVariable(WhyInfo::returnAddressOffset, front_block);
		VariablePtr fp = function.fp(front_block);
		VariablePtr sp = function.sp(front_block);
		VariablePtr m5 = function.mx(5, front_block);
		function.insertBefore(first, std::make_shared<StackPushInstruction>(rt), false)->setDebug(*first)->extract();
		function.insertBefore(first, std::make_shared<StackPushInstruction>(fp), false)->setDebug(*first)->extract();
		function.insertBefore(first, std::make_shared<StackPushInstruction>(m5), false)->setDebug(*first)->extract();
		function.insertBefore(first, std::make_shared<MoveInstruction>(sp, m5), false)->setDebug(*first)->extract();
		function.initialPushedBytes = 24;

		// Next, we need to push any variables that are written to.
		std::set<int> written;
		for (InstructionPtr &instruction: function.linearInstructions)
			for (const VariablePtr &variable: instruction->written)
				for (const int reg: variable->registers)
					if (!WhyInfo::isSpecialPurpose(reg))
						written.insert(reg);

		function.savedRegisters.clear();
		for (int reg: written) {
			function.savedRegisters.push_back(reg);
			VariablePtr variable = function.makePrecoloredVariable(reg, front_block);
			function.insertBefore(first, std::make_shared<StackPushInstruction>(variable), false)
				->setDebug(*first)->extract();
			function.initialPushedBytes += 8;
		}

		function.insertBefore(first, std::make_shared<MoveInstruction>(sp, fp), false)->setDebug(*first)->extract();

#ifdef MOVE_STACK_POINTER
		int to_skip = 0;
		for (const std::pair<int, StackLocation> &pair: function.stack)
			to_skip += pair.second.width;

		if (to_skip != 0)
			function.insertBefore(first, std::make_shared<SubIInstruction>(sp, to_skip, sp), false)
				->setDebug(*first)->extract();
#endif

		function.reindexInstructions();
	}
}
