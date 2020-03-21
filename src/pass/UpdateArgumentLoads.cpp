#include "compiler/Function.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "pass/UpdateArgumentLoads.h"

namespace LL2W::Passes {
	void updateArgumentLoads(Function &function, int offset) {
		for (InstructionPtr &instruction: function.linearInstructions) {
			if (std::shared_ptr<AddIInstruction> add = std::dynamic_pointer_cast<AddIInstruction>(instruction)) {
				std::shared_ptr<Variable> &rs = add->rs, &rd = add->rd;
				// Check for "$sp + x -> $m0" (loadArguments uses $m0).
				if (rs && rs->reg == WhyInfo::stackPointerOffset && rd && rd->reg == WhyInfo::assemblerOffset)
					add->imm += offset;
			}
		}
	}
}
