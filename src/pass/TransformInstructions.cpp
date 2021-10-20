#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "pass/TransformInstructions.h"

namespace LL2W::Passes {
	size_t transformInstructions(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto li = std::dynamic_pointer_cast<LoadIInstruction>(instruction)) {
				if (li->size != 4)
					continue;
				// TODO: verify
				auto var = function.newVariable(std::make_shared<PointerType>(std::make_shared<IntType>(64)),
					li->parent.lock());
				auto set = std::make_shared<SetInstruction>(var, li->imm);
				auto l = std::make_shared<LoadRInstruction>(var, li->rd, li->size);
				function.insertBefore(instruction, set)->setDebug(li->debugIndex)->extract();
				function.insertBefore(instruction, l)->setDebug(li->debugIndex)->extract();
				to_remove.push_back(li);
			} else if (auto si = std::dynamic_pointer_cast<StoreIInstruction>(instruction)) {
				if (si->size != 4)
					continue;
				auto var = function.newVariable(std::make_shared<PointerType>(std::make_shared<IntType>(64)),
					si->parent.lock());
				auto set = std::make_shared<SetInstruction>(var, si->imm);
				auto s = std::make_shared<StoreRInstruction>(si->rs, var, si->size);
				function.insertBefore(instruction, set)->setDebug(si->debugIndex)->extract();
				function.insertBefore(instruction, s)->setDebug(si->debugIndex)->extract();
				to_remove.push_back(si);
			 }
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
