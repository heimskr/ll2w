#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/FixSignedness.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void fixSignedness(Function &function) {
		Timer timer("FixSignedness");
		for (InstructionPtr &instruction: function.linearInstructions) {
			const std::string old = instruction->debugExtra();
			try {
				instruction->fixSignedness();
			} catch (const std::exception &) {
				info() << "Offending instruction: " << old << " \e[1m!" << instruction->debugIndex << "\e[22m\n";
				std::cerr << "... in function " << *instruction->parent.lock()->parent->name << '\n';
				throw;
			}
		}
	}
}
