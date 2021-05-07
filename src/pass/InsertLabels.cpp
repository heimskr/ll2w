#include "compiler/Function.h"
#include "instruction/Label.h"
#include "instruction/Nop.h"
#include "pass/InsertLabels.h"

namespace LL2W::Passes {
	void insertLabels(Function &function) {
		for (BasicBlockPtr &block: function.blocks) {
			auto label = std::make_shared<Label>(function.transformLabel(*block->label));
			block->instructions.push_front(label);
			label->parent = block;
		}

		function.relinearize();

		// Ensure that no two labels occur in immediate succession. wasmc doesn't support that right now.
		for (BasicBlockPtr &block: function.blocks) {
			if (block->instructions.size() == 1 && dynamic_cast<Label *>(block->instructions.front().get()))
				function.insertAfter(block->instructions.front(), std::make_shared<Nop>());
		}
	}
}
