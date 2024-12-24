#include "compiler/Function.h"
#include "pass/TrimBlocks.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void trimBlocks(Function &function) {
		Timer timer("TrimBlocks");
		std::list<BasicBlockPtr> to_remove;

		for (BasicBlockPtr &block: function.blocks) {
			if (!block->preds.empty() || block == function.blocks.front()) {
				continue;
			}

			to_remove.push_back(block);

			for (const BasicBlockPtr &other: function.blocks) {
				if (other != block) {
					auto found = std::find(other->preds.begin(), other->preds.end(), block->getLabel());
					if (found != other->preds.end()) {
						other->preds.erase(found);
					}
				}
			}
		}

		for (const BasicBlockPtr &block: to_remove) {
			function.remove(block);
		}

		function.relinearize();
	}
}
