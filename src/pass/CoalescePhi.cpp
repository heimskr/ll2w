#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/CoalescePhi.h"

namespace LL2W::Passes {
	void coalescePhi(Function &function) {
		std::list<InstructionPtr> to_remove;
		bool should_relinearize = false;

		// Scan through each instruction in order.
		for (InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || llvm_instruction->node->nodeType() != NodeType::Phi)
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			if (!phi_node)
				throw std::runtime_error("phi_node is null in Function::coalescePhi");

			// Otherwise, get its written temporary. This is what the other temporaries will be merged to.
			VariablePtr target = function.getVariable(*phi_node->result, phi_node->type);
			BasicBlockPtr phi_definer = instruction->parent.lock();

			for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
				const std::shared_ptr<LocalValue> local = pair.first->isLocal()?
					std::dynamic_pointer_cast<LocalValue>(pair.first) : nullptr;
				if (!local) {
					// On rare occasions, one or more operands of a ϕ-instruction can be constants like "true".
					// In these cases, we can't eliminate the phi instruction by merging alone. We have to insert
					// instructions in the penultimate slots of the predicate labels for which the phi function
					// parameters specify a constant.
					if (pair.first->isIntLike()) {
						BasicBlockPtr block = function.bbMap.at(pair.second);
						auto new_instr = std::make_shared<SetInstruction>(target, pair.first->intValue(), -1);
						new_instr->parent = block;
						if (block->instructions.empty()) {
							block->insertBeforeTerminal(new_instr);
							should_relinearize = true;
						} else {
							function.insertBefore(block->instructions.back(), new_instr);
						}
						target->addDefinition(new_instr);
						target->addDefiner(block);
						new_instr->extract();
					} else {
						std::cout << "pair.first (" << std::string(*pair.first) << ") isn't intlike in  "
						          << phi_node->debugExtra() << "\n";
					}
				} else {
					// Remove the old temporary from the variable store, then copy the name and type of the target
					// temporary.
					try {
						VariablePtr to_rename = function.getVariable(*local->name);
						function.variableStore.erase(to_rename->id);
						to_rename->makeAliasOf(target);
					} catch (const std::out_of_range &) {
						// Sometimes, the same variable will appear multiple times in the table, e.g.
						//     %41 = phi i32 [ %39, %28 ], [ %19, %24 ], [ %19, %16 ]
						// We do nothing if we've already aliased the variable and removed it from the variable store.
					}
				}
			}

			to_remove.push_back(instruction);
			target->removeDefiner(phi_definer);
			target->removeDefinition(instruction);
		}

		for (InstructionPtr &ptr: to_remove)
			function.remove(ptr);

		if (should_relinearize)
			function.relinearize();
	}
}
