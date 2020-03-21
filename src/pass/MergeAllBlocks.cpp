#include "compiler/Function.h"
#include "pass/MakeCFG.h"
#include "pass/MergeAllBlocks.h"
#include "util/CompilerUtil.h"

namespace LL2W::Passes {
	void mergeAllBlocks(Function &function) {
		bool any_changed;
		bool changed;
		do {
			changed = false;
			auto pre_end = function.blocks.end();
			--pre_end;
			// Iterate through all blocks except the final block.
			for (auto iter = function.blocks.begin(); iter != pre_end; ++iter) {
				BasicBlockPtr &block = *iter;

				if (block->instructions.empty() || !CompilerUtil::isTerminator(block->instructions.back())) {
					// Don't merge if multiple blocks jump to the next block. That would cause other blocks to jump to
					// an earlier point than intended, which would cause incorrect behavior.
					if ((*++iter)->preds.size() == 1) {
						function.mergeBlocks(block, *iter);
						any_changed = changed = true;
						break;
					} else --iter;
				}
			}
		} while (changed);

		if (any_changed) {
			makeCFG(function);
			function.reindexBlocks();
		}
	}
}
