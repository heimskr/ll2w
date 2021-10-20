#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/AndIInstruction.h"
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
				if (li->size == 4) {
					// TODO: verify
					auto var = function.newVariable(std::make_shared<PointerType>(std::make_shared<IntType>(64)),
						li->parent.lock());
					auto set = std::make_shared<SetInstruction>(var, li->imm);
					auto l = std::make_shared<LoadRInstruction>(var, li->rd, li->size);
					function.insertBefore(li, set)->setDebug(li->debugIndex)->extract();
					function.insertBefore(li, l)->setDebug(li->debugIndex)->extract();
					to_remove.push_back(li);
				} else if (li->size == 3) {
					// Sometimes, if you have a packed struct, you might get something like
					//     %14 = load i24, i24* %13
					// which normally translates to something like
					//     [$t9] -> $ta /3
					// Why has no instructions for 24-bit loads, so we have to apply a mask here.
					// For stores, which I'm too lazy to do now because I mercifully see no 24-bit stores in Thurisaz,
					// we'd have to break the store into multiple byte-sized stores, and that would be kind of a pain.
					li->size = 4;
					auto andi = std::make_shared<AndIInstruction>(li->rd, 0xffffff, li->rd);
					// I don't use insertAfter all that often. Neat.
					function.insertAfter(li, andi)->setDebug(li->debugIndex)->extract();
				} else continue;
			} else if (auto l = std::dynamic_pointer_cast<LoadRInstruction>(instruction)) {
				if (l->size == 3) {
					l->size = 4;
					auto andi = std::make_shared<AndIInstruction>(l->rd, 0xffffff, l->rd);
					function.insertAfter(l, andi)->setDebug(l->debugIndex)->extract();
				}
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
