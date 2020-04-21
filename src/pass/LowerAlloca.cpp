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

namespace LL2W::Passes {
	int lowerAlloca(Function &function) {
		std::list<InstructionPtr> to_remove;

		int replaced_count = 0;
		VariablePtr frame_pointer = function.fp(function.getEntry());
		VariablePtr stack_pointer = function.sp(function.getEntry());

		// Loop over all instructions, ignoring everything except allocas.
		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Alloca)
				continue;
			AllocaNode *alloca = dynamic_cast<AllocaNode *>(llvm->node);

			// First, mark the alloca instruction for removal.
			to_remove.push_back(instruction);

			// Move the stack pointer down to get the alignment right.
			if (0 < alloca->align) {
				auto m0 = function.m0(instruction);
				auto mod = std::make_shared<ModIInstruction>(stack_pointer, alloca->align, m0);
				auto sub = std::make_shared<SubRInstruction>(stack_pointer, m0, stack_pointer);
				function.insertBefore(instruction, mod, "LowerAlloca: align stack pointer");
				function.insertAfter(mod, sub);
				mod->extract();
				sub->extract();
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
					num_elements = value->intValue();
				} else if (value->isLocal()) {
					// If it's a local variable instead, we can't do the multiplication at compile time.
					LocalValue *local = dynamic_cast<LocalValue *>(value);
					auto m0 = function.m0(instruction);
					auto move = std::make_shared<MoveInstruction>(stack_pointer, alloca->variable);
					function.insertBefore(instruction, move, "LowerAlloca: $sp -> %var");
					move->extract();
					if (width != 0) {
						auto lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
						// %var * width
						auto mult = std::make_shared<MultIInstruction>(local->variable, width);
						// $l0 -> $m0
						auto movelo = std::make_shared<MoveInstruction>(lo, m0);
						// $sp -= $m0
						auto sub  = std::make_shared<SubRInstruction>(stack_pointer, m0, stack_pointer);
						function.insertBefore(instruction, mult,   "LowerAlloca: %var * width");
						function.insertBefore(instruction, movelo);
						function.insertBefore(instruction, sub);
						mult->extract();
						movelo->extract();
						sub->extract();
					}
				} else throw std::runtime_error("Unsupported value for numelementsValue: " + std::string(*value));
			} else {
				// If no number of elements is specified, it's one by default.
				num_elements = 1;
			}

			if (num_elements != -1) {
				auto move = std::make_shared<MoveInstruction>(stack_pointer, alloca->variable);
				function.insertBefore(instruction, move);
				move->extract();
				const int to_sub = num_elements * width;
				if (0 < to_sub) {
					auto sub = std::make_shared<SubIInstruction>(stack_pointer, to_sub, stack_pointer);
					function.insertAfter(move, sub);
					sub->extract();
				}
			}

			function.addToStack(alloca->variable, StackLocation::Purpose::Alloca);

			++replaced_count;
		}

		// Remove the alloca instructions to complete their replacement.
		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		if (replaced_count == 0) {
			// If we never ended up finding and replacing any alloca instructions, erase the precolored frame and stack
			// pointer variables.
			function.variableStore.erase(frame_pointer->id);
			function.variableStore.erase(stack_pointer->id);
		} else {
			// If we replaced any alloca instructions, we added a bunch of instructions in its place. This makes it
			// necessary to reindex all instructions.
			function.reindexInstructions();
		}

		// Functions often begin with lots of allocas. Each time one was replaced, a modulo instruction was inserted to
		// align the stack pointer. Often, the alignments are the same as the ones before them, rendering them
		// unnecessary. (For example, performing $sp %= 4 after an earlier invocation of the same instruction has no
		// effect.) We can reduce the number of unnecessary alignments by removing any alignment to n following an
		// alignment to m such that n is a factor of m. For example, an alignment of 4 after an alignment of 8 can be
		// safely removed.

		for (BasicBlockPtr &block: function.blocks) {
			do {
				int alignments_removed = 0;
				for (auto iter = block->instructions.begin(); iter != block->instructions.end(); ++iter) {
					InstructionPtr &instruction = *iter;
					ModIInstruction *mod = dynamic_cast<ModIInstruction *>(instruction.get());
					if (!mod)
						continue;
					auto next = iter;
					for (++next; next != block->instructions.end();) {
						ModIInstruction *nextmod = dynamic_cast<ModIInstruction *>(next->get());
						if (nextmod) {
							if (mod->imm % nextmod->imm == 0) {
								auto old = next++;
								function.remove(*old);
								++alignments_removed;
							}

							break;
						} else {
							++next;
						}
					}
				}

				if (alignments_removed == 0)
					break;
			} while (true);
		}

		return replaced_count;
	}
}
