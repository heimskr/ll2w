#include "compiler/Function.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "pass/UpdateArgumentLoads.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void updateArgumentLoads(Function &function, int offset) {
		Timer timer("UpdateArgumentLoads");
		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto add = std::dynamic_pointer_cast<AddIInstruction>(instruction)) {
				VariablePtr &rs = add->rs;
				VariablePtr &rd = add->rd;
				// Check for "$sp + x -> $m0" (loadArguments uses $m0).
				if (rs && rs->registers.size() == 1 && *rs->registers.begin() == WhyInfo::stackPointerOffset) {
					if (rd && rd->registers.size() == 1 && *rd->registers.begin() == WhyInfo::assemblerOffset) {
						if (std::holds_alternative<int>(add->imm)) {
							std::get<int>(add->imm) += offset;
						}
					}
				}
			}
		}
	}
}
