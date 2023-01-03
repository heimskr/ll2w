#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "instruction/MoveInstruction.h"
#include "pass/FixSignedness.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void fixSignedness(Function &function) {
		Timer timer("FixSignedness");

		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto move = std::dynamic_pointer_cast<MoveInstruction>(instruction)) {
				if (auto rs_int = std::dynamic_pointer_cast<IntType>(move->rs->type))
					rs_int->shareSignedness(*move->rd->type);
			}
		}
	}
}
