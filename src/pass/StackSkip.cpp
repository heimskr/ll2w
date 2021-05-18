#include "compiler/Function.h"
#include "instruction/SubIInstruction.h"
#include "pass/InsertLabels.h"

namespace LL2W::Passes {
	void insertStackSkip(Function &function) {
		if (function.isNaked())
			return;
		BasicBlockPtr entry = function.getEntry();
		auto add = std::make_shared<SubIInstruction>(function.sp(entry), 0, function.mx(5, entry));
		function.insertBefore(function.linearInstructions.front(), add, "InsertStackSkip")->extract();
		function.categories["StackSkip"].push_back(add);
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
		// We need to add an offset of 8 because spush subtracts and then writes to memory.
		dynamic_cast<SubIInstruction *>(list.front().get())->imm = function.spillSize + 8;
	}
}
