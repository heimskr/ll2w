#include <climits>
#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "graph/Graph.h"
#include "instruction/Comment.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/MakeCFG.h"
#include "pass/Phi.h"
#include "util/CompilerUtil.h"
#include "util/Timer.h"

#define REMOVE_OLD_TEMPORARIES
#define WEB_MAX 4

namespace LL2W::Passes {
	void coalescePhi(Function &function, bool variablesOnly) {
		Timer timer("CoalescePhi");
		std::vector<InstructionPtr> to_remove;
		std::unordered_set<Variable *> vars_to_erase;
		bool should_relinearize = false;

		// Scan through each instruction in order.
		for (const InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			auto *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());

			if (llvm_instruction == nullptr || !llvm_instruction->isPhi()) {
				continue;
			}

			const auto *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->getNode());

			if (phi_node == nullptr) {
				throw std::runtime_error("phi_node is null in Function::coalescePhi");
			}

			// Otherwise, get its written temporary. This is what the other temporaries will be merged to.
			VariablePtr target = function.getVariable(*phi_node->result, phi_node->type);
			BasicBlockPtr phi_definer = instruction->parent.lock();

			if (variablesOnly) {
				for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
					const LocalValue *local = pair.first->isLocal()? dynamic_cast<LocalValue *>(pair.first.get()) : nullptr;
					if (local != nullptr) {
						VariablePtr to_alias = function.getVariable(*local->name);
						// to_alias->makeAliasOf(*target);
						target->phiParents.insert(to_alias.get());
						to_alias->phiChildren.insert(target.get());
					}
				}
			} else {
				for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
					const std::shared_ptr<LocalValue> local = pair.first->isLocal()? std::dynamic_pointer_cast<LocalValue>(pair.first) : nullptr;
					if (!local) {
						if (pair.first->isIntLike() || pair.first->isGlobal()) {
							// On rare occasions, one or more operands of a ϕ-instruction can be constants like "true".
							// In these cases, we can't eliminate the phi instruction by merging alone. We have to
							// insert instructions in the penultimate slots of the predicate labels for which the phi
							// function parameters specify a constant.
							// On even rarer occasions, the operands can be global variables.
							BasicBlockPtr block = function.bbMap.at(pair.second);
							InstructionPtr new_instr;
							if (pair.first->isIntLike()) {
								new_instr = std::make_shared<SetInstruction>(target, pair.first->intValue(false));
							} else {
								new_instr = std::make_shared<SetInstruction>(target, dynamic_cast<GlobalValue *>(pair.first.get())->name);
							}
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
							warn() << "Value " << std::string(*pair.first) << " isn't intlike or global in " << phi_node->debugExtra() << '\n';
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
							// We do nothing if we've already aliased the variable and removed it from the variable store.
						}
#endif
					}
				}

				to_remove.emplace_back(instruction);
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
			if (visited.contains(name)) {
				continue;
			}

			visited.insert(name);

			for (Node *node: dependencies.BFS(*name)) {
				auto *nodevar = node->get<Variable *>();
				if (nodevar != var.get()) {
					visited.insert(nodevar->originalID);
					nodevar->makeAliasOf(var);
				}
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
		Timer timer("MovePhi");
		std::list<InstructionPtr> to_remove;

		bool block_made = false;

		auto &linear = function.linearInstructions;
		auto iter = linear.begin();
		// Scan through each instruction in order.
		for (; iter != linear.end();) {
			InstructionPtr instruction = *iter;
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			auto *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || !llvm_instruction->isPhi()) {
				++iter;
				continue;
			}

			const auto *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->getNode());

			if (phi_node == nullptr) {
				throw std::runtime_error("phi_node is null in Function::movePhi");
			}

			VariablePtr target = function.getVariable(*phi_node->result, phi_node->type);
			target->fromPhi = true;

			for (const auto &[value, block_label]: phi_node->pairs) {
				const LocalValue *local = value->isLocal()? dynamic_cast<LocalValue *>(value.get()) : nullptr;
				BasicBlockPtr block;

				try {
					block = function.bbMap.at(block_label);
				} catch (const std::out_of_range &) {
					error() << "Couldn't find " << *block_label << " in " << *function.name << "'s bbMap.\n    bbMap entries (" << function.bbMap.size() << "):\n";
					for (const auto &[bbname, bb]: function.bbMap) {
						std::cerr << "    - " << *bbname << '\n';
					}
					std::cerr << "    Phi node: " << phi_node->debugExtra() << '\n';
					throw;
				}

				InstructionPtr new_instruction;

				std::string comment;

				if (local != nullptr) {
					comment = "MovePhi: " + local->variable->plainString() + " -> " + target->plainString();
					new_instruction = std::make_shared<MoveInstruction>(local->variable, target);
					function.categories["MovePhi"].emplace(new_instruction);
				} else if (value->valueType() == ValueType::Undef) {
					// Do nothing for undef values. This allows us to insert moves in cutPhi.
					continue;
				} else if (value->isIntLike() || value->isGlobal()) {
					if (value->isIntLike()) {
						comment = "MovePhi: intlike -> " + target->plainString();
						new_instruction = std::make_shared<SetInstruction>(target, value->intValue(false));
					} else {
						comment = "MovePhi: global -> " + target->plainString();
						new_instruction = std::make_shared<SetInstruction>(target, dynamic_cast<GlobalValue *>(value.get())->name);
					}
				} else {
					warn() << "Value " << std::string(*value) << " isn't intlike or global in " << phi_node->debugExtra() << '\n';
					continue;
				}

				new_instruction->parent = block;

				if (block->instructions.empty()) {
					warn() << "Block " << *block->getLabel() << " is empty.\n";
					continue;
				}

				const auto out_blocks = block->goesTo();
				if (1 < out_blocks.size()) {
					// If there are multiple blocks, inserting a move before the end might be incorrect, or something?
					// We need to insert a block in between.

					BasicBlockPtr middle_block;
					bool middle_made = false;

					auto phi_block = llvm_instruction->parent.lock();
					const std::string *phi_block_label = phi_block->getLabel();
					if (function.movePhiBlocks.contains({block->getLabel(), phi_block_label})) {
						middle_block = function.movePhiBlocks.at({block->getLabel(), phi_block_label});

						// At this point, neither lowerSwitch nor lowerRet nor lowerBranches has been called, so we can
						// safely insert instructions before the last instruction in the block. Or something?

						bool should_relinearize = false;
						function.insertBefore(middle_block->instructions.back(), new_instruction, true, false, &should_relinearize);
						if (should_relinearize) {
							function.relinearize();
							iter = std::find(linear.begin(), linear.end(), instruction);
							if (iter == linear.end()) {
								warn() << "Couldn't find new instruction " << new_instruction->debugExtra() << " in @" << *function.name << "'s linear instructions.\n";
							}
						}

						function.comment(new_instruction, comment);
					} else {
						middle_made = block_made = true;
						const std::string *new_label = StringSet::intern(*function.newLabel());
						comment += " (in new block " + *new_label + " whose parent is " + *block->getLabel() + ")";
						middle_block = std::make_shared<BasicBlock>(new_label, std::vector{block->getLabel()}, std::list<InstructionPtr>());
						middle_block->parent = &function;
						auto block_iter = std::find(function.blocks.begin(), function.blocks.end(), block);
						if (block_iter == function.blocks.end()) {
							throw std::runtime_error("Can't find block in MovePhi");
						}
						function.blocks.insert(++block_iter, middle_block);
						function.bbMap.try_emplace(new_label, middle_block);
						function.bbLabels.insert(new_label);

						auto *uncond = new BrUncondNode(phi_block_label);
						auto new_llvm = std::make_shared<LLVMInstruction>(uncond, -1, true);
						new_llvm->parent = middle_block;

						auto comment_node = std::make_shared<Comment>(comment);
						comment_node->parent = new_instruction->parent = middle_block;
						middle_block->instructions.emplace_back(comment_node);
						middle_block->instructions.emplace_back(new_instruction);

						auto preds_iter = std::find(phi_block->preds.begin(), phi_block->preds.end(), block->getLabel());
						if (preds_iter == phi_block->preds.end()) {
							function.cfg.renderTo("cfg_error.png");
							throw std::runtime_error("Couldn't find " + *block->getLabel() + " in the preds for " + *phi_block->getLabel());
						}
						*preds_iter = new_label;
						middle_block->instructions.emplace_back(new_llvm);
						function.movePhiBlocks.emplace(std::make_pair(block->getLabel(), phi_block_label), middle_block);
					}

					if (middle_made) {
						const std::string *percent_label = StringSet::intern(*middle_block->getLabel());
						if (auto *parent_llvm = dynamic_cast<LLVMInstruction *>(block->instructions.back().get())) {
							auto type = parent_llvm->getNodeType();
							if (type == NodeType::BrCond) {
								auto *cond = dynamic_cast<BrCondNode *>(parent_llvm->getNode());
								const std::string **cond_label =
									(cond->ifTrue == phi_block_label)? &cond->ifTrue :
									((cond->ifFalse == phi_block_label)? &cond->ifFalse : nullptr);
								if (cond_label == nullptr) {
									error() << "Cond node doesn't jump to block " << *phi_block_label << ": " << parent_llvm->debugExtra() << '\n';
								} else {
									*cond_label = percent_label;
								}
							} else if (type == NodeType::Switch) {
								auto *switch_node = dynamic_cast<SwitchNode *>(parent_llvm->getNode());
								if (CompilerUtil::labelsMatch(*switch_node->label, *phi_block_label)) {
									switch_node->label = percent_label;
								} else {
									for (auto &[type, value, switch_label]: switch_node->table) {
										if (CompilerUtil::labelsMatch(*switch_label, *phi_block_label)) {
											switch_label = percent_label;
										}
									}
								}
							} else {
								error() << "Final instruction of block " << *block->getLabel() << " isn't a BrCond or Switch.\n";
							}
						} else {
							error() << "Final instruction of block " << *block->getLabel() << " isn't a BrCond or Switch.\n";
						}
						middle_block->extract();
					}
				} else {
					function.insertBefore(block->instructions.back(), std::make_shared<Comment>(comment), false, false);
					function.insertBefore(block->instructions.back(), new_instruction, true, false);
					target->addDefiner(block);
				}

				new_instruction->setDebug(phi_node)->extract();
				target->addDefinition(new_instruction);
			}

			++iter;
			function.remove(instruction);
		}

		if (block_made) {
			function.relinearize();
			Passes::makeCFG(function);
		}

		for (InstructionPtr &ptr: to_remove) {
			function.remove(ptr);
		}
	}

	static Graph getDependencies(Function &function) {
		Timer timer("GetDependencies");
		Graph dependencies;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			auto *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (llvm_instruction == nullptr || !llvm_instruction->isPhi()) {
				continue;
			}

			const auto *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->getNode());

			if (phi_node == nullptr) {
				throw std::runtime_error("phi_node is null");
			}

			if (!dependencies.hasLabel(*phi_node->result)) {
				dependencies.addNode(*phi_node->result);
			}

			for (const auto &[value, block_label]: phi_node->pairs) {
				if (value->valueType() == ValueType::Local) {
					auto *local = dynamic_cast<LocalValue *>(value.get());
					const std::string &name = *local->name;
					if (!dependencies.hasLabel(name)) {
						dependencies.addNode(name);
					}
					dependencies.link(name, *phi_node->result);
				}
			}
		}

		return dependencies;
	}

	void tracePhi(Function &function) {
		Graph dependencies = getDependencies(function);
		dependencies.renderTo("dependencies_" + *function.name + ".png");
	}

	void cutPhi(Function &function) {
		Timer timer("CutPhi");
		Graph dependencies = getDependencies(function);
		Timer timer2("CutPhi after getDependencies");
		bool should_relinearize = false;
		auto &insertions = function.categories["CutPhi:Insertions"];
		bool any_done = true;
		while (any_done) {
			any_done = false;
			std::list<Graph> components = dependencies.components();
			for (Graph &graph: components) {
				if (graph.size() <= WEB_MAX) {
					continue;
				}
				const auto bridges = graph.bridges();
				if (bridges.empty()) {
					warn() << "Couldn't find a bridge in one of function " << *function.name << "'s phi graph components.\n";
					continue;
				}
				ssize_t min_diff = SSIZE_MAX;
				bool min_swap = false;
				const std::pair<Graph::Label, Graph::Label> *min_pair = nullptr;
				for (const auto &pair: bridges) {
					const bool should_swap = !graph[pair.first].out().contains(&graph[pair.second]);

					if (should_swap) {
						graph.unlink(pair.second, pair.first);
					} else {
						graph.unlink(pair.first, pair.second);
					}

					const ssize_t diff = std::abs(static_cast<int64_t>(graph.size()) - 2l * static_cast<int64_t>(graph.undirectedSearch(*graph.begin()->second).size()));

					if (should_swap) {
						graph.link(pair.second, pair.first);
					} else {
						graph.link(pair.first, pair.second);
					}

					if (diff < min_diff) {
						min_diff = diff;
						min_pair = &pair;
						min_swap = should_swap;
					}
				}

				if (min_pair == nullptr) {
					throw std::runtime_error("min_pair is inexplicably null; do you have a phi graph component with " + std::to_string(SSIZE_MAX) + " nodes?");
				}

				auto source      = function.getVariable(StringSet::intern(min_swap? min_pair->second : min_pair->first));
				auto destination = function.getVariable(StringSet::intern(min_swap? min_pair->first  : min_pair->second));
				// Can't add definitions while iterating over definitions.
				std::vector<InstructionPtr> definitions_to_add;
				std::vector<BasicBlockPtr> definers_to_add;
				for (const auto &definition: destination->definitions) {
					auto *llvm = dynamic_cast<LLVMInstruction *>(definition.lock().get());
					if (llvm == nullptr || !llvm->isPhi()) {
						if (insertions.contains(definition.lock())) {
							// Sometimes, if the web is still too large, we repeat and run into the non-ϕ definitions we
							// inserted in a previous iteration. We need to ignore those.
							continue;
						}

						throw std::runtime_error("Definition of " + std::string(*destination) + " isn't a ϕ-instruction: " + definition.lock()->debugExtra());
					}

					auto *phi = dynamic_cast<PhiNode *>(llvm->getNode());

					for (auto &[value, block_label]: phi->pairs) {
						if (value->isLocal()) {
							auto *local = dynamic_cast<LocalValue *>(value.get());
							if (local->variable && *local->variable == *source) {
								auto block = function.bbMap.at(block_label);
								auto move = std::make_shared<MoveInstruction>(source, destination);
								const std::string comment = "CutPhi: " + source->plainString() + " -> " + destination->plainString();
								if (block->instructions.empty()) {
									block->insertBeforeTerminal(move);
									function.comment(move, comment); // TODO: does this work before relinearization?
									should_relinearize = true;
								} else {
									function.insertBefore(block->instructions.back(), move, comment);
								}
								move->setDebug(phi)->extract();
								definitions_to_add.emplace_back(move);
								definers_to_add.emplace_back(block);
								insertions.insert(move);
								value.reset(new UndefValue);
								any_done = true;
							}
						}
					}
				}

				for (auto &&definition: definitions_to_add) {
					destination->addDefinition(std::move(definition));
				}

				for (auto &&definer: definers_to_add) {
					destination->addDefiner(std::move(definer));
				}
			}
		}

		if (should_relinearize) {
			function.relinearize();
		}
	}
}
