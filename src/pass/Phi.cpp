#include <climits>
#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "graph/Graph.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/MakeCFG.h"
#include "pass/Phi.h"

#define REMOVE_OLD_TEMPORARIES
#define WEB_MAX 4

namespace LL2W::Passes {
	void coalescePhi(Function &function, bool variablesOnly) {
		std::list<InstructionPtr> to_remove;
		std::unordered_set<Variable *> vars_to_erase;
		bool should_relinearize = false;

		// Scan through each instruction in order.
		for (InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || !llvm_instruction->isPhi())
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
								new_instr = std::make_shared<SetInstruction>(target, pair.first->intValue(false));
							else
								new_instr = std::make_shared<SetInstruction>(target,
									dynamic_cast<GlobalValue *>(pair.first.get())->name);
							new_instr->parent = block;
							if (block->instructions.empty()) {
								block->insertBeforeTerminal(new_instr);
								should_relinearize = true;
							} else
								function.insertBefore(block->instructions.back(), new_instr);
							target->addDefinition(new_instr);
							target->addDefiner(block);
							new_instr->extract();
						} else
							std::cerr << "Value " << std::string(*pair.first) << " isn't intlike or global in "
							          << phi_node->debugExtra() << '\n';
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

	void movePhi(Function &function) {
		std::list<InstructionPtr> to_remove;

		bool block_made = false;

		// Scan through each instruction in order.
		for (InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || !llvm_instruction->isPhi())
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			if (!phi_node)
				throw std::runtime_error("phi_node is null in Function::movePhi");

			VariablePtr target = function.getVariable(*phi_node->result, phi_node->type);

			std::cerr << "INSTRUCTION: " << instruction->debugExtra() << " in block " << *instruction->parent.lock()->label << '\n';
			for (const auto &[value, block_label]: phi_node->pairs) {
				const LocalValue *local = value->isLocal()? dynamic_cast<LocalValue *>(value.get()) : nullptr;
				BasicBlockPtr block = function.bbMap.at(block_label);
				InstructionPtr new_instruction;

				std::string comment;

				if (local) {
					comment = "MovePhi: " + local->variable->plainString() + " -> " + target->plainString();
					new_instruction = std::make_shared<MoveInstruction>(local->variable, target);
				} else if (value->valueType() == ValueType::Undef) {
					// Do nothing for undef values. This allows us to insert moves in cutPhi.
					continue;
				} else if (value->isIntLike() || value->isGlobal()) {
					if (value->isIntLike()) {
						comment = "MovePhi: intlike -> " + target->plainString();
						new_instruction = std::make_shared<SetInstruction>(target, value->intValue(false));
					} else {
						comment = "MovePhi: global -> " + target->plainString();
						new_instruction = std::make_shared<SetInstruction>(target,
							dynamic_cast<GlobalValue *>(value.get())->name);
					}
				} else {
					std::cerr << "Value " << std::string(*value) << " isn't intlike or global in "
					          << phi_node->debugExtra() << '\n';
					continue;
				}

				new_instruction->parent = block;

				if (block->instructions.empty()) {
					error() << "Block " << *block->label << " is empty.\n";
					continue;
				}

				auto out_blocks = block->goesTo();
				if (1 < out_blocks.size()) {
					// If there are multiple blocks, inserting a move before the end might be incorrect, or something?
					// We need to insert a block in between.

					BasicBlockPtr middle_block;
					bool middle_made = false;

					auto phi_block = llvm_instruction->parent.lock();
					const std::string *phi_block_label = phi_block->label;
					if (function.movePhiBlocks.count({block->label, phi_block_label}) != 0) {
						middle_block = function.movePhiBlocks.at({block->label, phi_block_label});
					} else {
						middle_made = true;
						const std::string *new_label = function.newLabel();
						middle_block = std::make_shared<BasicBlock>(new_label, std::vector {block->label},
							std::list {new_instruction});
						auto iter = std::find(function.blocks.begin(), function.blocks.end(), block);
						if (iter == function.blocks.end())
							throw std::runtime_error("Can't find block in MovePhi");
						function.blocks.insert(++iter, middle_block);
						function.bbMap.try_emplace(new_label, middle_block);
						function.bbLabels.insert(new_label);
						BrUncondNode *uncond = new BrUncondNode(phi_block_label);
						auto new_llvm = std::make_shared<LLVMInstruction>(uncond, -1, true);
						new_instruction->parent = new_llvm->parent = middle_block;
						block_made = true;

						auto preds_iter = std::find(phi_block->preds.begin(), phi_block->preds.end(), block->label);
						if (preds_iter == phi_block->preds.end()) {
							function.cfg.renderTo("cfg_error.png");
							throw std::runtime_error("Couldn't find " + *block->label + " in the preds for " +
								*phi_block->label);
						}
						*preds_iter = new_label;
						middle_block->instructions.push_back(new_llvm);
						function.movePhiBlocks.emplace(std::make_pair(block->label, phi_block_label), middle_block);
					}

					middle_block->insertBeforeTerminal(new_instruction);

					if (middle_made) {
						const std::string *percent_label = StringSet::intern("%" + *middle_block->label);
						if (auto *parent_llvm = dynamic_cast<LLVMInstruction *>(block->instructions.back().get())) {
							auto type = parent_llvm->node->nodeType();
							if (type == NodeType::BrCond) {
								auto *cond = dynamic_cast<BrCondNode *>(parent_llvm->node);
								const std::string **cond_label = (cond->ifTrue->substr(1) == *phi_block_label)?
									&cond->ifTrue :
									((cond->ifFalse->substr(1) == *phi_block_label)? &cond->ifFalse : nullptr);
								if (!cond_label)
									error() << "Cond node doesn't jump to block " << *phi_block_label << ": "
											<< parent_llvm->debugExtra() << '\n';
								else
									*cond_label = percent_label;
							} else if (type == NodeType::Switch) {
								auto *switch_node = dynamic_cast<SwitchNode *>(parent_llvm->node);
								if (switch_node->label->substr(1) == *phi_block_label)
									switch_node->label = percent_label;
								else
									for (auto &[type, value, switch_label]: switch_node->table)
										if (switch_label->substr(1) == *phi_block_label)
											switch_label = percent_label;
							} else
								error() << "Final instruction of block " << *block->label
								        << " isn't a BrCond or Switch.\n";
						} else
							error() << "Final instruction of block " << *block->label
							        << " isn't a BrCond or Switch.\n";
					}
				} else {
					function.insertBefore(block->instructions.back(), new_instruction, comment);
					target->addDefiner(block);
				}

				new_instruction->setDebug(phi_node)->extract();
				target->addDefinition(new_instruction);
			}

			to_remove.push_back(instruction);
		}

		if (block_made) {
			function.relinearize();
			Passes::makeCFG(function);
		}

		for (InstructionPtr &ptr: to_remove)
			function.remove(ptr);
	}

	static Graph getDependencies(Function &function) {
		Graph dependencies;

		for (InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || !llvm_instruction->isPhi())
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			if (!phi_node)
				throw std::runtime_error("phi_node is null");

			if (!dependencies.hasLabel(*phi_node->result))
				dependencies.addNode(*phi_node->result);

			for (const auto &[value, block_label]: phi_node->pairs) {
				if (value->valueType() == ValueType::Local) {
					auto *local = dynamic_cast<LocalValue *>(value.get());
					const std::string &name = *local->name;
					if (!dependencies.hasLabel(name))
						dependencies.addNode(name);
					dependencies.link(name, *phi_node->result);
				}
			}
		}

		return dependencies;
	}

	void tracePhi(Function &function) {
		Graph dependencies = getDependencies(function);
		dependencies.renderTo("dependencies.png");
	}

	void cutPhi(Function &function) {
		Graph dependencies = getDependencies(function);
		bool should_relinearize = false;
		auto &insertions = function.categories["CutPhi:Insertions"];
		bool any_done = true;
		while (any_done) {
			any_done = false;
			std::list<Graph> components = dependencies.components();
			for (Graph &graph: components) {
				if (graph.size() <= WEB_MAX)
					continue;
				const auto bridges = graph.bridges();
				if (bridges.size() == 0) {
					warn() << "Couldn't find a bridge in one of function " << *function.name << "'s phi graph "
						"components.\n";
					continue;
				}
				ssize_t min_diff = SSIZE_MAX;
				bool min_swap = false;
				const std::pair<Graph::Label, Graph::Label> *min_pair = nullptr;
				for (const auto &pair: bridges) {
					const bool swap = graph[pair.first].out().count(&graph[pair.second]) == 0;
					if (swap)
						graph.unlink(pair.second, pair.first);
					else
						graph.unlink(pair.first, pair.second);
					const ssize_t diff =
						std::abs((long) graph.size() - 2l * (long) graph.undirectedSearch(*graph.begin()->second).size());
					if (swap)
						graph.link(pair.second, pair.first);
					else
						graph.link(pair.first, pair.second);
					if (diff < min_diff) {
						min_diff = diff;
						min_pair = &pair;
						min_swap = swap;
					}
				}
				if (!min_pair)
					throw std::runtime_error("min_pair is inexplicably null; do you have a phi graph component with " +
						std::to_string(SSIZE_MAX) + " nodes?");
				auto source      = function.getVariable(StringSet::intern(min_swap? min_pair->second : min_pair->first));
				auto destination = function.getVariable(StringSet::intern(min_swap? min_pair->first : min_pair->second));
				// Can't add definitions while iterating over definitions.
				std::list<InstructionPtr> definitions_to_add;
				std::list<BasicBlockPtr> definers_to_add;
				for (const auto &definition: destination->definitions) {
					auto *llvm = dynamic_cast<LLVMInstruction *>(definition.lock().get());
					if (!llvm || !llvm->isPhi()) {
						if (insertions.count(definition.lock()) != 0) {
							// Sometimes, if the web is still too large, we repeat and run into the non-ϕ definitions we
							// inserted in a previous iteration. We need to ignore those.
							continue;
						} else
							throw std::runtime_error("Definition of " + std::string(*destination) +
								" isn't a ϕ-instruction: " + definition.lock()->debugExtra());
					}
					auto *phi = dynamic_cast<PhiNode *>(llvm->node);
					bool did_reset = false;
					const std::string initial_debug_extra = phi->debugExtra();
					for (auto &[value, block_label]: phi->pairs)
						if (value->isLocal()) {
							auto *local = dynamic_cast<LocalValue *>(value.get());
							if (local->variable && *local->variable == *source) {
								// if (did_reset)
								// 	throw std::runtime_error("ϕ-instruction depends on variable " + std::string(*source) +
								// 		" from multiple blocks: " + initial_debug_extra);
								did_reset = true;
								auto block = function.bbMap.at(block_label);
								auto move = std::make_shared<MoveInstruction>(source, destination);
								const std::string comment = "CutPhi: " + source->plainString() + " -> " +
									destination->plainString();
								if (block->instructions.empty()) {
									block->insertBeforeTerminal(move);
									function.comment(move, comment); // TODO: does this work before relinearization?
									should_relinearize = true;
								} else
									function.insertBefore(block->instructions.back(), move, comment);
								move->setDebug(phi)->extract();
								definitions_to_add.push_back(move);
								definers_to_add.push_back(block);
								insertions.insert(move);
								value.reset(new UndefValue);
								any_done = true;
							}
						}
				}
				for (const auto &definition: definitions_to_add)
					destination->addDefinition(definition);
				for (const auto &definer: definers_to_add)
					destination->addDefiner(definer);
			}
		}

		if (should_relinearize)
			function.relinearize();
	}
}
