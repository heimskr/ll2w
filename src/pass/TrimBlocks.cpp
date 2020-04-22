#include <iostream>

#include "compiler/Function.h"
#include "pass/TrimBlocks.h"

namespace LL2W::Passes {
	void trimBlocks(Function &function) {
		std::list<BasicBlockPtr> to_remove;

		for (BasicBlockPtr &block: function.blocks) {
			if (block->preds.empty() && block != function.blocks.front())
				to_remove.push_back(block);
		}

		for (BasicBlockPtr &block: to_remove) {
			std::cout << "Removing block " << *block->label << " from " << *function.name << "\n";
			function.remove(block);
		}

		function.relinearize();
	}
}
