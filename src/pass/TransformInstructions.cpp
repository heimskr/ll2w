#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "pass/TransformInstructions.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t transformInstructions(Function &function) {
		Timer timer("TransformInstructions");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto li = std::dynamic_pointer_cast<LoadIInstruction>(instruction)) {
				if (li->size == 4 || li->size == 2) {
					// TODO: verify
					auto var = function.newVariable(std::make_shared<PointerType>(IntType::make(64)),
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
				if (si->size == 4) {
					auto var = function.newVariable(std::make_shared<PointerType>(IntType::make(64)),
						si->parent.lock());
					auto set = std::make_shared<SetInstruction>(var, si->imm);
					auto s = std::make_shared<StoreRInstruction>(si->rs, var, si->size);
					function.insertBefore(instruction, set)->setDebug(si->debugIndex)->extract();
					function.insertBefore(instruction, s)->setDebug(si->debugIndex)->extract();
					to_remove.push_back(si);
				}
			} else if (auto s = std::dynamic_pointer_cast<StoreRInstruction>(instruction)) {
				if (s->size == 3 || s->size == 5 || s->size == 7) {
					// We have to break stores of strange sizes into multiple byte-sized stores.
					// TODO: verify.
					auto ptr_var = function.newVariable(std::make_shared<PointerType>(IntType::make(s->size * 8)),
						s->parent.lock());
					auto value_var = function.newVariable(IntType::make(s->size * 8), s->parent.lock());
					auto ptr_move = std::make_shared<MoveInstruction>(s->rt, ptr_var);
					auto value_move = std::make_shared<MoveInstruction>(s->rs, value_var);
					function.insertBefore(s, ptr_move)->setDebug(*s)->extract();
					function.insertBefore(s, value_move)->setDebug(*s)->extract();
					for (int i = 0; i < s->size; ++i) {
						auto new_s = std::make_shared<StoreRInstruction>(value_var, ptr_var, 1);
						function.insertBefore(s, new_s)->setDebug(*s)->extract();
						if (i != s->size - 1) {
							auto add = std::make_shared<AddIInstruction>(ptr_var, 1, ptr_var);
							auto shift = std::make_shared<ShiftRightLogicalIInstruction>(value_var, 8, value_var);
							function.insertBefore(s, add)->setDebug(*s)->extract();
							function.insertBefore(s, shift)->setDebug(*s)->extract();
						}
					}

					to_remove.push_back(s);
				}
			 }
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
