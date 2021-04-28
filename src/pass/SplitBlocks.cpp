#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "pass/SplitBlocks.h"

namespace LL2W::Passes {
	int splitBlocks(Function &function) {
		// Liveness analysis appears to work on the level of basic blocks, rather than instructions. This means that
		// variables can't die until the end of a basic block. If there are more definitions in a basic block than there
		// are physical registers, register allocation is therefore impossible. A workaround is to ensure that no basic
		// block has too many definitions by splitting them at the point where the number of definitions is equal to the
		// number of physical registers. The terminator of the original block is moved to the end of the added block and
		// replaced with a branch to the added block.
		bool any_changed;
		int split_count = 0;
		for (;;) {
			any_changed = false;
			for (BasicBlockPtr &block: function.blocks) {
				int defs = 0;
				std::shared_ptr<Instruction> prev_instruction;
				for (InstructionPtr &instruction: block->instructions) {
					int regular_written_count = 0;
					for (const VariablePtr &variable: instruction->written)
						regular_written_count += variable->nonSpecialCount();

					if (WhyInfo::allocatableRegisters < defs + regular_written_count) {
						function.splitBlock(block, prev_instruction);
						any_changed = true;
						++split_count;
						goto next;
					}

					prev_instruction = instruction;
					defs += regular_written_count;
				}
			}

			next:
			if (!any_changed)
				break;
		}

		return split_count;
	}
}
