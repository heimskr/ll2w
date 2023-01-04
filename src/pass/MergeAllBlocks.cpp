#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "pass/MakeCFG.h"
#include "pass/MergeAllBlocks.h"
#include "util/CompilerUtil.h"

namespace LL2W::Passes {
	size_t mergeAllBlocks(Function &function) {
		size_t changed_count = 0;
		bool changed;
		do {
			changed = false;
			auto pre_end = function.blocks.end();
			--pre_end;
			// Iterate through all blocks except the final block.
			for (auto iter = function.blocks.begin(); iter != pre_end; ++iter) {
				BasicBlockPtr &block = *iter;
				if (block->instructions.empty() || !block->instructions.back()->isBlockTerminal()) {
					// Don't merge if multiple blocks jump to the next block. That would cause other blocks to jump to
					// an earlier point than intended, which would cause incorrect behavior.
					if ((*++iter)->preds.size() == 1) {
						function.mergeBlocks(block, *iter);
						changed = true;
						++changed_count;
						break;
					}
					--iter;
				}
			}
		} while (changed);

		function.blocksAreMinimized = false;

		if (0 < changed_count) {
			makeCFG(function);
			function.reindexBlocks();
		}

		return changed_count;
	}
}
