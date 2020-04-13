#include "compiler/Function.h"
#include "instruction/Label.h"
#include "pass/InsertLabels.h"

namespace LL2W::Passes {
	void insertLabels(Function &function) {
		for (BasicBlockPtr &block: function.blocks) {
			auto label = std::make_shared<Label>(function.transformLabel(*block->label));
			block->instructions.push_front(label);
		}

		function.relinearize();
	}
}
