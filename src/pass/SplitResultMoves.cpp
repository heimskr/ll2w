#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/MoveInstruction.h"
#include "pass/SplitResultMoves.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t splitResultMoves(Function &function) {
		Timer timer{"SplitResultMoves"};
		std::vector<InstructionPtr> to_remove;

		for (const auto &weak_instruction: function.categories["SetupCalls:MoveFromResult"]) { // $r0 -> %var
			InstructionPtr instruction = weak_instruction.lock();
			if (!instruction) {
				continue;
			}

			auto *move = dynamic_cast<MoveInstruction *>(instruction.get());
			assert(move != nullptr);

			size_t register_count = move->rd->registers.size();

			if (register_count < 2) {
				continue;
			}

			if (WhyInfo::returnValueCount < register_count) {
				throw std::runtime_error("Cannot split multireg return values: too many return value registers needed");
			}

			auto iter = move->rd->registers.begin();

			for (size_t i = 0; i < register_count; ++i) {
				auto rx = function.makePrecoloredVariable(WhyInfo::returnValueOffset + i, instruction->parent.lock());
				auto new_move = std::make_shared<MoveInstruction>(rx, function.makePrecoloredVariable(*iter++, instruction->parent.lock()));
				function.insertBefore(instruction, new_move)->setDebug(move)->extract();
			}

			to_remove.push_back(instruction);
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction, false);
		}

		if (!to_remove.empty()) {
			function.reindexInstructions();
		}

		return to_remove.size();
	}
}
