#include "compiler/Function.h"
#include "instruction/AddIInstruction.h"
#include "pass/InsertLabels.h"

namespace LL2W::Passes {
	void insertStackSkip(Function &function) {
		if (function.isNaked())
			return;
		BasicBlockPtr entry = function.getEntry();
		auto add = std::make_shared<AddIInstruction>(function.sp(entry), 0, function.mx(5, entry));
		function.insertBefore(function.linearInstructions.front(), add, "InsertStackSkip");
		function.categories["StackSkip"].push_back(add);
		add->extract();
	}

	void readjustStackSkip(Function &function) {
		if (function.isNaked())
			return;
		if (function.categories.count("StackSkip") == 0)
			throw std::runtime_error("No StackSkip category found in function " + *function.name);
		const auto &list = function.categories.at("StackSkip");
		if (list.size() != 1)
			throw std::runtime_error("Expected size of StackSkip list to be exactly one, but it's " +
				std::to_string(list.size()));
		auto add = dynamic_cast<AddIInstruction *>(list.front().get());
		add->imm = function.spillSize;
	}
}
