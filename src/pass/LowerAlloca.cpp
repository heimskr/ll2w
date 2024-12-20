#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/ModIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "pass/LowerAlloca.h"
#include "util/Timer.h"
#include "util/Util.h"

// #define ADD_ALLOCA_TO_STACK

namespace LL2W::Passes {
	int lowerAlloca(Function &function) {
		Timer timer("LowerAlloca");
		std::list<InstructionPtr> to_remove;

		int replaced_count = 0;
		VariablePtr frame_pointer = function.fp(function.getEntry());
		VariablePtr sp = function.sp(function.getEntry());

		VariablePtr alloca_reg = sp;

		// Loop over all instructions, ignoring everything except allocas.
		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Alloca)
				continue;
			AllocaNode *alloca = dynamic_cast<AllocaNode *>(llvm->getNode());

			// First, mark the alloca instruction for removal.
			to_remove.push_back(instruction);

			// Move the stack pointer down to get the alignment right.
			if (0 < alloca->align) {
				int align = Util::upalign(alloca->align, 8);
				auto m0 = function.m0(instruction);
				auto mod = std::make_shared<ModIInstruction>(alloca_reg, align, m0);
				auto sub = std::make_shared<SubRInstruction>(alloca_reg, m0, alloca_reg);
				function.insertBefore(instruction, mod, "LowerAlloca: align stack pointer");
				function.insertAfter(mod, sub);
				mod->setDebug(alloca->debugIndex)->extract();
				sub->setDebug(alloca->debugIndex)->extract();
			}

			const int width = alloca->type->width() / 8;

			// The number of elements requested is usually an integer constant, but it can also be a local variable.
			// We need to copy the stack pointer to the result variable and then move the stack pointer down past the
			// allocated memory.
			int num_elements = -1;
			if (alloca->numelementsValue) {
				Value *value = alloca->numelementsValue.get();
				if (value->isInt()) {
					// If there's an integer constant, things are easy.
					num_elements = value->longValue();
				} else if (value->isLocal()) {
					// If it's a local variable instead, we can't do the multiplication at compile time.
					LocalValue *local = dynamic_cast<LocalValue *>(value);
					auto m0 = function.m0(instruction);
					auto move = std::make_shared<MoveInstruction>(alloca_reg, alloca->variable);
					function.insertBefore(instruction, move, "LowerAlloca: $sp -> %var");
					move->setDebug(alloca->debugIndex)->extract();
					if (width != 0) {
						auto lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
						// %var * width
						auto mult = std::make_shared<MultIInstruction>(local->variable, width);
						// $lo -> $m0
						auto movelo = std::make_shared<MoveInstruction>(lo, m0);
						// $sp -= $m0
						auto sub  = std::make_shared<SubRInstruction>(alloca_reg, m0, alloca_reg);
						function.insertBefore(instruction, mult,   "LowerAlloca: %var * width");
						function.insertBefore(instruction, movelo);
						function.insertBefore(instruction, sub, "LowerAlloca: move stack pointer");
						mult->setDebug(alloca->debugIndex)->extract();
						movelo->setDebug(alloca->debugIndex)->extract();
						sub->setDebug(alloca->debugIndex)->extract();
					}
				} else throw std::runtime_error("Unsupported value for numelementsValue: " + std::string(*value));
			} else {
				// If no number of elements is specified, it's one by default.
				num_elements = 1;
			}

			if (num_elements != -1) {
				// $sp -> %var
				auto move = std::make_shared<MoveInstruction>(alloca_reg, alloca->variable);
				function.insertBefore(instruction, move);
				move->setDebug(alloca->debugIndex)->extract();
				const int to_sub = Util::upalign(num_elements * width, 8);
				if (0 < to_sub) {
					auto sub = std::make_shared<SubIInstruction>(alloca_reg, to_sub, alloca_reg);
					function.insertBefore(move, sub, "LowerAlloca: $sp -= to_sub");
					sub->setDebug(alloca->debugIndex)->extract();
				}
				function.comment(move, "LowerAlloca: $sp -> " + alloca->variable->plainString());
			}

#ifdef ADD_ALLOCA_TO_STACK
			function.addToStack(alloca->variable, StackLocation::Purpose::Alloca);
#endif

			++replaced_count;
		}

		// Remove the alloca instructions to complete their replacement.
		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		if (replaced_count == 0) {
			// If we never ended up finding and replacing any alloca instructions, erase the precolored frame pointer
			// variable.
			function.variableStore.erase(frame_pointer->id);
		} else {
			// If we replaced any alloca instructions, we added a bunch of instructions in its place. This makes it
			// necessary to reindex all instructions.
			function.reindexInstructions();
		}

		return replaced_count;
	}
}
