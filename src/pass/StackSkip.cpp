#include "compiler/Function.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SubRInstruction.h"
#include "pass/InsertLabels.h"
#include "pass/StackSkip.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void insertStackSkip(Function &function) {
		if (function.isNaked()) {
			return;
		}

		Timer timer{"InsertStackSkip"};
		BasicBlockPtr entry = function.getEntry();
		VariablePtr sp = function.sp(entry);
		VariablePtr m9 = function.mx(9, entry);
		auto set = std::make_shared<SetInstruction>(m9, 0);
		auto sub = std::make_shared<SubRInstruction>(sp, m9, sp);
		InstructionPtr anchor = function.linearInstructions.front();
		function.insertBefore(anchor, set, "InsertStackSkip")->setDebug(function.initialDebugIndex)->extract();
		function.insertBefore(anchor, std::move(sub))->setDebug(function.initialDebugIndex)->extract();
		function.categories["StackSkip"].emplace(std::move(set));
	}

	void readjustStackSkip(Function &function) {
		if (function.isNaked()) {
			return;
		}

		Timer timer{"ReadjustStackSkip"};

		auto iter = function.categories.find("StackSkip");
		if (iter == function.categories.end()) {
			throw std::runtime_error("No StackSkip category found in function " + *function.name);
		}

		const auto &set = iter->second;

		if (set.size() != 1) {
			throw std::runtime_error("Expected size of StackSkip set to be exactly one, but it's " + std::to_string(set.size()));
		}

		// We need to add an offset of 8 because spush subtracts and then writes to memory.
		dynamic_cast<IType &>(*set.begin()->lock()).imm = function.stackSize + 8;
	}
}
