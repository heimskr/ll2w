#include "compiler/Function.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/InsertLabels.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void insertStackSkip(Function &function) {
		Timer timer("InsertStackSkip");
		if (function.isNaked())
			return;
		BasicBlockPtr entry = function.getEntry();
		auto sp = function.sp(entry);
		auto add = std::make_shared<SubIInstruction>(sp, 0, sp);
		function.insertBefore(function.linearInstructions.front(), add, "InsertStackSkip")
			->setDebug(function.initialDebugIndex)->extract();
		function.categories["StackSkip"].insert(add);
	}

	void readjustStackSkip(Function &function) {
		Timer timer("ReadjustStackSkip");
		if (function.isNaked())
			return;
		if (function.categories.count("StackSkip") == 0)
			throw std::runtime_error("No StackSkip category found in function " + *function.name);
		const auto &set = function.categories.at("StackSkip");
		if (set.size() != 1)
			throw std::runtime_error("Expected size of StackSkip set to be exactly one, but it's " +
				std::to_string(set.size()));
		// We need to add an offset of 8 because spush subtracts and then writes to memory.
		dynamic_cast<SubIInstruction *>(set.begin()->get())->imm = function.spillSize + 8;
	}
}
