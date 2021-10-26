#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "graph/Graph.h"
#include "instruction/SetInstruction.h"
#include "pass/CoalescePhi.h"

#define REMOVE_OLD_TEMPORARIES

namespace LL2W::Passes {
	void coalescePhi(Function &function, bool variablesOnly) {
		std::list<InstructionPtr> to_remove;
		std::unordered_set<Variable *> vars_to_erase;
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

			if (variablesOnly) {
				for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
					const LocalValue *local = pair.first->isLocal()?
						dynamic_cast<LocalValue *>(pair.first.get()) : nullptr;
					if (local) {
						VariablePtr to_alias = function.getVariable(*local->name);
						// to_alias->makeAliasOf(*target);
						target->phiParents.insert(to_alias.get());
						to_alias->phiChildren.insert(target.get());
					}
				}
			} else {
				for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
					const std::shared_ptr<LocalValue> local = pair.first->isLocal()?
						std::dynamic_pointer_cast<LocalValue>(pair.first) : nullptr;
					if (!local) {
						if (pair.first->isIntLike() || pair.first->isGlobal()) {
							// On rare occasions, one or more operands of a ϕ-instruction can be constants like "true".
							// In these cases, we can't eliminate the phi instruction by merging alone. We have to
							// insert instructions in the penultimate slots of the predicate labels for which the phi
							// function parameters specify a constant.
							// On even rarer occasions, the operands can be global variables.
							BasicBlockPtr block = function.bbMap.at(pair.second);
							InstructionPtr new_instr;
							if (pair.first->isIntLike())
								new_instr = std::make_shared<SetInstruction>(target, pair.first->intValue());
							else
								new_instr = std::make_shared<SetInstruction>(target,
									dynamic_cast<GlobalValue *>(pair.first.get())->name);
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
							std::cerr << "Value " << std::string(*pair.first) << " isn't intlike or global in "
							          << phi_node->debugExtra() << '\n';
						}
#ifdef REMOVE_OLD_TEMPORARIES
					} else {
						// Remove the old temporary from the variable store, then copy the name and type of the target
						// temporary.
						try {
							VariablePtr to_rename = function.getVariable(*local->name);
							if (to_rename->id != to_rename->parentID()) {
								// info() << "Retiring " << *to_rename << " (pid = " << *to_rename->parentID() << ")\n";
								function.extraVariables.emplace(to_rename->id, to_rename);
								vars_to_erase.insert(to_rename.get());
								// TODO: verify whether this is unneeded.
								// to_rename->makeAliasOf(target);
							}
						} catch (const std::out_of_range &err) {
							// Sometimes, the same variable will appear multiple times in the table, e.g.
							//     %41 = phi i32 [ %39, %28 ], [ %19, %24 ], [ %19, %16 ]
							// We do nothing if we've already aliased the variable and removed it from the variable
							// store.
						}
#endif
					}
				}

				to_remove.push_back(instruction);
				target->removeDefiner(phi_definer);
				target->removeDefinition(instruction);
			}
		}

		// Create a dependency graph. It's bidirectional for ease of traversal.
		Graph dependencies = function.makeDependencyGraph();

		// Iterate over the graph component by component, choosing one node arbitrarily from each component, running
		// a breadth-first search from that node and making the variables corresponding to each node reachable from
		// the source node an alias of the variable corresponding to the chosen node.
		std::unordered_set<Variable::ID> visited;
		for (const auto &[id, var]: function.variableStore) {
			Variable::ID name = var->originalID;
			if (visited.count(name) != 0)
				continue;
			visited.insert(name);
			for (Node *node: dependencies.BFS(*name)) {
				Variable *nodevar = node->get<Variable *>();
				if (nodevar == var.get())
					continue;
				visited.insert(nodevar->originalID);
				nodevar->makeAliasOf(var);
			}
		}

		for (const Variable *var: vars_to_erase) {
			// warn() << "Erasing " << *var << " (OID: " << var->originalID << ")\n";
			function.variableStore.erase(var->id);
		}

		for (InstructionPtr &ptr: to_remove)
			function.remove(ptr);

		if (should_relinearize)
			function.relinearize();
	}
}
