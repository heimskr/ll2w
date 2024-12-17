#include "compiler/Function.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/InsertLabels.h"
#include "pass/StackSkip.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void insertStackSkip(Function &function) {
		if (function.isNaked()) {
			return;
		}

		Timer timer("InsertStackSkip");
		BasicBlockPtr entry = function.getEntry();
		auto sp = function.sp(entry);
		auto sub = std::make_shared<SubIInstruction>(sp, 0, sp);
		function.insertBefore(function.linearInstructions.front(), sub, "InsertStackSkip")->setDebug(function.initialDebugIndex)->extract();
		function.categories["StackSkip"].insert(sub);
	}

	void readjustStackSkip(Function &function) {
		if (function.isNaked()) {
			return;
		}

		Timer timer("ReadjustStackSkip");

		if (function.categories.count("StackSkip") == 0) {
			throw std::runtime_error("No StackSkip category found in function " + *function.name);
		}

		const auto &set = function.categories.at("StackSkip");

		if (set.size() != 1) {
			throw std::runtime_error("Expected size of StackSkip set to be exactly one, but it's " + std::to_string(set.size()));
		}

		// We need to add an offset of 8 because spush subtracts and then writes to memory.
		dynamic_cast<SubIInstruction &>(**set.begin()).imm = function.spillSize + 8;
	}
}
