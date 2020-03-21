#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/JumpSymbolInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SetSymbolInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "options.h"
#include "parser/ASTNode.h"
#include "parser/FunctionArgs.h"
#include "parser/FunctionHeader.h"
#include "pass/LinearScan.h"
#include "pass/MergeAllBlocks.h"
#include "pass/RemoveRedundantMoves.h"
#include "pass/RemoveUselessBranches.h"
#include "pass/ReplaceStoresAndLoads.h"
#include "pass/SplitBlocks.h"
#include "pass/UpdateArgumentLoads.h"
#include "util/CompilerUtil.h"
#include "util/Util.h"

namespace LL2W {
	Function::Function(Program &program, const ASTNode &node) {
		parent = &program;
		name = node.lexerInfo;
		FunctionHeader *header = dynamic_cast<FunctionHeader *>(node[0]);
		if (!header)
			throw std::runtime_error("header is null in Function::Function");
		argumentsNode = header->arguments;
		arguments = &argumentsNode->arguments;
		astnode = &node;
	}

	void Function::extractBlocks() {
		int label = arguments->size();
		std::vector<int> preds {};
		std::list<std::shared_ptr<Instruction>> instructions;
		int offset = 0;
		int instructionIndex = -1;
		int blockIndex = -1;

		std::function<void(BasicBlockPtr)> finishBlock = [&](BasicBlockPtr block) {
			block->offset = offset;
			block->parent = this;
			block->index = ++blockIndex;
			bbLabels.insert(block->label);
			bbMap.emplace(StringSet::intern(std::to_string(block->label)), block);
			for (std::shared_ptr<Instruction> &instruction: instructions) {
				instruction->parent = block;
				instruction->extract();
				for (const std::unordered_set<VariablePtr> &variables: {instruction->read, instruction->written}) {
					for (VariablePtr vptr: variables)
						variableStore.insert({vptr->id, vptr});
				}
			}
		};

		for (ASTNode *child: *astnode->at(1)) {
			if (child->symbol == BLOCKHEADER) {
				blocks.push_back(std::make_shared<BasicBlock>(label, preds, instructions));
				finishBlock(blocks.back());
				offset += instructions.size();
				preds.clear();
				instructions.clear();
				const HeaderNode *header = dynamic_cast<const HeaderNode *>(child);
				if (!header)
					throw std::runtime_error("header is null in Function::extractBlocks");
				label = header->label;
				preds = header->preds;
			} else if (InstructionNode *instruction = dynamic_cast<InstructionNode *>(child)) {
				instructions.push_back(std::make_shared<LLVMInstruction>(instruction, ++instructionIndex));
				linearInstructions.push_back(instructions.back());
			}
		}

		if (!instructions.empty()) {
			blocks.push_back(std::make_shared<BasicBlock>(label, preds, instructions));
			finishBlock(blocks.back());
		}
	}

	void Function::extractVariables(bool reset) {
		if (reset) {
			for (const std::pair<int, VariablePtr> &pair: variableStore) {
				pair.second->setUsingBlocks({});
				pair.second->setDefiningBlocks({});
				pair.second->setDefinitions({});
				pair.second->setUses({});
				pair.second->setLastUse({});
			}
		}

		for (BasicBlockPtr &block: blocks) {
			for (VariablePtr read_var: block->read)
				read_var->addUsingBlock(block);
			for (VariablePtr written_var: block->written)
				written_var->addDefiner(block);
			for (std::shared_ptr<Instruction> &instruction: block->instructions) {
				for (VariablePtr read_var: instruction->read) {
					read_var->setLastUse(instruction);
					read_var->addUse(instruction);
				}
				for (VariablePtr written_var: instruction->written)
					written_var->addDefinition(instruction);
			}
		}

		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			// Function arguments aren't defined by any instruction. They're implicitly defined in the first block.
			if (pair.second->definingBlocks.empty()) {
				pair.second->addDefiner(blocks.front());
				blocks.front()->written.insert(pair.second);
			}
		}
	}

	void Function::computeSuccMergeSet(Node *node) {
		auto &ms = succMergeSets[node];
		for (Node *succ: node->out()) {
			ms.insert(succ);
			for (Node *m: mergeSets.at(succ))
				ms.insert(m);
			if (succMergeSets.count(succ) == 0)
				computeSuccMergeSet(succ);
		}
	}

	void Function::relinearize() {
		linearInstructions.clear();
		int index = -1;
		for (BasicBlockPtr &block: blocks) {
			for (InstructionPtr &instruction: block->instructions) {
				instruction->index = ++index;
				linearInstructions.push_back(instruction);
			}
		}
	}

	void Function::coalescePhi() {
		std::list<InstructionPtr> to_remove;
		bool should_relinearize = false;

		// Scan through each instruction in order.
		for (InstructionPtr &instruction: linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || llvm_instruction->node->nodeType() != NodeType::Phi)
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			if (!phi_node)
				throw std::runtime_error("phi_node is null in Function::coalescePhi");

			// Otherwise, get its written temporary. This is what the other temporaries will be merged to.
			VariablePtr target = getVariable(*phi_node->result, phi_node->type);
			BasicBlockPtr phi_definer = target->onlyDefiner();

			for (const std::pair<ValuePtr, const std::string *> &pair: phi_node->pairs) {
				const std::shared_ptr<LocalValue> local = pair.first->valueType() == ValueType::Local?
					std::dynamic_pointer_cast<LocalValue>(pair.first) : nullptr;
				if (!local) {
					// On rare occasions, one or more operands of a ϕ-instruction can be constants like "true".
					// In these cases, we can't eliminate the phi instruction by merging alone. We have to insert
					// instructions in the penultimate slots of the predicate labels for which the phi function
					// parameters specify a constant.
					if (pair.first->valueType() == ValueType::Bool) {
						const std::shared_ptr<BoolValue> boolval = std::dynamic_pointer_cast<BoolValue>(pair.first);
						BasicBlockPtr block = bbMap.at(pair.second);

						auto new_instr = std::make_shared<SetInstruction>(target, boolval->value? 1 : 0, -1);
						new_instr->parent = block;
						if (block->instructions.empty()) {
							block->insertBeforeTerminal(new_instr);
							should_relinearize = true;
						} else {
							insertBefore(block->instructions.back(), new_instr);
						}
						target->addDefinition(new_instr);
						target->addDefiner(block);
					} else {
						std::cout << "? " << std::string(*pair.first) << ": " << phi_node->debugExtra() << "\n";
					}
				} else {
					// Remove the old temporary from the variable store, then copy the name and type of the target
					// temporary.
					VariablePtr to_rename = getVariable(*local->name);
					variableStore.erase(to_rename->id);
					to_rename->makeAliasOf(*target);
				}
			}

			to_remove.push_back(instruction);
			target->removeDefiner(phi_definer);
			target->removeDefinition(instruction);
		}

		for (InstructionPtr &ptr: to_remove)
			remove(ptr);

		if (should_relinearize)
			relinearize();
	}

	int Function::newLabel() const {
		int label = 0;
		if (!variableStore.empty()) {
			auto iter = variableStore.end();
			--iter;
			label = iter->first + 1;
		}

		for (; bbLabels.count(label) == 1; ++label);
		return label;
	}

	VariablePtr Function::newVariable(TypePtr type, std::shared_ptr<BasicBlock> definer) {
		return getVariable(newLabel(), type, definer);
	}

	bool Function::spill(VariablePtr variable) {
		bool out = false;
		// Right after the definition of the variable to be spilled, store its value onto the stack in the proper
		// location. For each use of the original variable, replace the original variable with a new variable, and right
		// before the use insert a definition for the variable by loading it from the stack.
		if (variable->definitions.empty()) {
			debug();
			std::cerr << *variable << "\n";
			throw std::runtime_error("Cannot spill variable: no definitions");
		}

		for (std::weak_ptr<Instruction> weak_definition: variable->definitions) {
			InstructionPtr definition = weak_definition.lock();
#ifdef DEBUG_SPILL
			std::cerr << "  Trying to spill " << *variable << " (definition: " << definition->debugExtra() << " at "
			          << definition->index << ")\n";
#endif
			auto store = std::make_shared<StackStoreInstruction>(*variableLocations.at(variable), variable);
			auto next = after(definition);
			bool should_insert = true;

			if (next) {
				std::shared_ptr<StackStoreInstruction> other_store =
					std::dynamic_pointer_cast<StackStoreInstruction>(next);
				if (other_store && *other_store == *store) {
					should_insert = false;
#ifdef DEBUG_SPILL
					std::cerr << "    A stack store already exists: " << next->debugExtra() << "\n";
#endif
				}
			}

			if (should_insert) {
				insertAfter(definition, store);
				out = true;
#ifdef DEBUG_SPILL
			std::cerr << "    Inserting a stack store after definition: " << store->debugExtra() << "\n";
#endif
			}
		}

		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
			InstructionPtr &instruction = *iter;
			if (instruction->read.count(variable) != 0) {
				VariablePtr new_var = newVariable(variable->type, instruction->parent.lock());
				bool replaced = instruction->replaceRead(variable, new_var);
#ifdef DEBUG_SPILL
				std::cerr << "    Creating new variable: " << *new_var << "\n";
				std::cerr << "    " << (replaced? "Replaced" : "Didn't replace")
				          << " in " << instruction->debugExtra() << "\n";
#endif
				if (replaced) {
					instruction->read.erase(variable);
					instruction->read.insert(new_var);
					auto load = std::make_shared<StackLoadInstruction>(new_var, *variableLocations.at(variable), -1);
					insertBefore(instruction, load);
					out = true;
#ifdef DEBUG_SPILL
				std::cerr << "      Inserting a stack load before " << instruction->debugExtra() << ": "
				          << load->debugExtra() << "\n";
#endif
				} else {
#ifdef DEBUG_SPILL
				std::cerr << "      Removing variable " << *new_var << "\n";
#endif
					variableStore.erase(new_var->id);
				}
			}
		}
#ifdef DEBUG_SPILL
		std::cerr << "\n";
#endif

		reindexInstructions();
		return out;
	}

	InstructionPtr Function::after(InstructionPtr instruction) {
		auto iter = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		++iter;
		return iter == linearInstructions.end()? nullptr : *iter;
	}

	BasicBlockPtr Function::after(BasicBlockPtr block) {
		auto iter = std::find(blocks.begin(), blocks.end(), block);
		++iter;
		return iter == blocks.end()? nullptr : *iter;
	}

	void Function::insertAfter(InstructionPtr base, InstructionPtr new_instruction, bool reindex) {
		BasicBlockPtr block = base->parent.lock();
		if (!block) {
			std::cerr << "\e[31;1m!\e[0m " << base->debugExtra() << "\n";
			throw std::runtime_error("Couldn't lock instruction's parent block");
		}

		if (reindex)
			new_instruction->index = base->index + 1;
		new_instruction->parent = base->parent;
		std::list<InstructionPtr>::iterator iter;

		if (base == linearInstructions.back()) {
			linearInstructions.push_back(new_instruction);
			block->instructions.push_back(new_instruction);
		} else {
			if (base == block->instructions.back()) {
				block->instructions.push_back(new_instruction);
			} else {
				iter = std::find(block->instructions.begin(), block->instructions.end(), base);
				++iter;
				block->instructions.insert(iter, new_instruction);
			}

			iter = std::find(linearInstructions.begin(), linearInstructions.end(), base);
			++iter;
			linearInstructions.insert(iter, new_instruction);

			if (reindex) {
				for (auto end = linearInstructions.end(); iter != end; ++iter)
					++(*iter)->index;
			}
		}
	}

	void Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, bool reindex) {
		BasicBlockPtr block = base->parent.lock();
		if (!block) {
			std::cerr << "\e[31;1m!\e[0m " << base->debugExtra() << "\n";
			throw std::runtime_error("Couldn't lock instruction's parent block");
		}

		if (reindex)
			new_instruction->index = base->index + 1;
		new_instruction->parent = base->parent;

		auto linearIter = std::find(linearInstructions.begin(), linearInstructions.end(), base);
		auto blockIter = std::find(block->instructions.begin(), block->instructions.end(), base);
		linearInstructions.insert(linearIter, new_instruction);
		block->instructions.insert(blockIter, new_instruction);
		if (reindex) {
			for (auto end = linearInstructions.end(); linearIter != end; ++linearIter)
				++(*linearIter)->index;
		}
	}

	void Function::removeUselessBranch(BasicBlockPtr block) {
		if (block->instructions.empty())
			return;

		InstructionPtr &back = block->instructions.back();

		if (LLVMInstruction *llback = dynamic_cast<LLVMInstruction *>(back.get())) {
			if (llback->node->nodeType() == NodeType::BrUncond) {
				if (const BrUncondNode *branch = dynamic_cast<BrUncondNode *>(llback->node)) {
					BasicBlockPtr next = after(block);
					if (next) {
						const int destination = std::atoi(branch->destination->substr(1).c_str());
						if (next->label == destination)
							remove(back);
					}
				} else throw std::runtime_error("branch is null in Function::removeUselessBranch");
			}
		}
	}

	void Function::reindexInstructions() {
		int index = -1;
		for (InstructionPtr &instruction: linearInstructions)
			instruction->index = ++index;
	}

	void Function::reindexBlocks() {
		int index = -1;
		for (BasicBlockPtr &block: blocks)
			block->index = ++index;
	}

	BasicBlockPtr Function::splitBlock(BasicBlockPtr block, InstructionPtr instruction) {
		const int label = newLabel();
#ifdef DEBUG_SPLIT
		std::cerr << "Splitting " << block->label << " (" << block->instructions.size() << ") into " << block->label
		          << " & " << label << "\n";
#endif
		BasicBlockPtr new_block = std::make_shared<BasicBlock>(label, std::vector<int> {block->label},
			std::list<InstructionPtr>());
		new_block->parent = this;
		bbLabels.insert(label);
		bbMap.emplace(StringSet::intern(std::to_string(label)), new_block);

		auto end = block->instructions.end();
		auto iter = std::find(block->instructions.begin(), end, instruction);
		for (++iter; iter != end;) {
			for (const VariablePtr &var: (*iter)->written) {
				var->removeDefiner(block);
				var->addDefiner(new_block);
			}

			(*iter)->parent = new_block;
			new_block->instructions.push_back(*iter);
			block->instructions.erase(iter++);
		}

		// Replace the old label with the new label in the preds of all basic blocks.
		for (BasicBlockPtr &possible_successor: blocks) {
			auto predIter = std::find(possible_successor->preds.begin(), possible_successor->preds.end(), block->label);
			if (predIter != possible_successor->preds.end())
				*predIter = label;
		}

		// Insert the new block after the original block.
		auto blockIter = std::find(blocks.begin(), blocks.end(), block);
		++blockIter;
		blocks.insert(blockIter, new_block);

		// Add an unconditional branch from the original block to the new block.
		BrUncondNode *node = new BrUncondNode("%" + std::to_string(label));
		std::shared_ptr<LLVMInstruction> branch = std::make_shared<LLVMInstruction>(node, -1, true);
		branch->parent = block;
		block->instructions.push_back(branch);
		iter = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		++iter;
		linearInstructions.insert(iter, branch);

		block->extract(true);
		new_block->extract();

		reindexInstructions();
		return new_block;
	}

	void Function::mergeBlocks(BasicBlockPtr before, BasicBlockPtr after) {
		// Update the preds of all the blocks by replacing the after-block's label with the before-block's.
		for (BasicBlockPtr &block: blocks) {
			for (int &pred: block->preds) {
				if (pred == after->label)
					pred = before->label;
			}
		}

		// Move all instructions from the after-block to the before-block.
		for (InstructionPtr &instruction: after->instructions)
			before->instructions.push_back(instruction);
		after->instructions.clear();

		// Replace the after-block's label with the before-block's in all instructions.
		// TODO: When Why.js branches are implemented, add them here.
		const std::string *before_p_label = StringSet::intern("%" + std::to_string(before->label));
		const std::string *after_p_label  = StringSet::intern("%" + std::to_string(after->label));
		const std::string *before_label = StringSet::intern(std::to_string(before->label));
		const std::string *after_label  = StringSet::intern(std::to_string(after->label));
		for (InstructionPtr &instruction: linearInstructions) {
			if (BrUncondNode *branch = CompilerUtil::brUncondCast(instruction)) {
				if (branch->destination == after_p_label)
					branch->destination = before_p_label;
			} else if (BrCondNode *branch = CompilerUtil::brCondCast(instruction)) {
				if (branch->ifTrue == after_p_label)
					branch->ifTrue = before_p_label;
				if (branch->ifFalse == after_p_label)
					branch->ifFalse = before_p_label;
			} else if (SwitchNode *sw = CompilerUtil::switchCast(instruction)) {
				if (sw->label == after_label)
					sw->label = before_label;
				for (std::tuple<TypePtr, ValuePtr, const std::string *> &tuple: sw->table) {
					if (std::get<2>(tuple) == after_label)
						std::get<2>(tuple) = before_label;
				}
			}
		}

		blocks.remove(after);
	}

	Node & Function::operator[](const BasicBlock &bb) const {
		return *bbNodeMap.at(&bb);
	}

	int Function::getArity() const {
		return arguments? arguments->size() : 0;
	}

	bool Function::isVariadic() const {
		return argumentsNode? argumentsNode->ellipsis : false;
	}

	CFG & Function::makeCFG() {
		cfg.clear();
		cfg.name = "CFG";

		// First pass: add all the nodes.
		for (BasicBlockPtr &block: blocks) {
			const std::string label = std::to_string(block->label);
			cfg += label;
			Node &node = cfg[label];
			node.data = block;
			block->node = &node;
			bbNodeMap.insert({block.get(), &node});
		}

		cfg += "exit";

		// Second pass: connect all the nodes.
		for (BasicBlockPtr &block: blocks) {
			const std::string label = std::to_string(block->label);
			for (int pred: block->preds)
				cfg.link(std::to_string(pred), label);
			if (!block->instructions.empty() && block->instructions.back()->isTerminal())
				cfg.link(label, "exit");
		}

		dTree.emplace(cfg, cfg[0]);
		dTree->name = "DTree";
		djGraph.emplace(cfg, cfg[0]);
		djGraph->name = "DJ Graph";
		mergeSets = djGraph->mergeSets((*djGraph)[0], (*djGraph)["exit"]);
		computeSuccMergeSets();
		walkCFG(1000, 0, 1000);
		return cfg;
	}

	void Function::walkCFG(size_t walks, unsigned int seed, size_t inner_limit) {
		srand(seed == 0? time(NULL) : seed);
		for (size_t walk = 0; walk < walks; ++walk) {
			Node *node = &cfg[0];
			Node *end = &cfg["exit"];
			size_t count = 0;
			// End the walk once we reach the exit or until we've reached the maximum number of moves allowed per walk.
			while (node != end && ++count <= inner_limit) {
				// Increase the estimated execution count of the node we just walked to.
				++node->get<BasicBlockPtr>()->estimatedExecutions;
				// Check the number of outward edges.
				size_t out_count = node->out().size();
				if (out_count == 0) {
					// If it's somehow zero, the walk is over.
					break;
				} else if (out_count == 1) {
					// If it's just one, simply go to the next node.
					node = *node->out().begin();
				} else {
					// Otherwise, if there are multiple options, choose one randomly.
					node = *std::next(node->out().begin(), rand() % out_count);
				}
			}
		}

		// Increase the random walk counter once we're done doing all the walks.
		walkCount += walks;
	}

	void Function::computeSuccMergeSets() {
		succMergeSets.clear();
		computeSuccMergeSet(&djGraph.value()[*getEntry()->node]);
	}

	void Function::fillLocalValues() {
		for (InstructionPtr &instruction: linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;

			InstructionNode *node = llvm->node;
			if (Reader *reader = dynamic_cast<Reader *>(node)) {
				for (std::shared_ptr<LocalValue> value: reader->allLocals())
					value->variable = getVariable(*value->name);
			}

			if (Writer *writer = dynamic_cast<Writer *>(node)) {
				if (writer->result)
					writer->variable = getVariable(*writer->result);
			}
		}
	}

	void Function::updateInstructionNodes() {
		for (InstructionPtr &instruction: linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;

			InstructionNode *node = llvm->node;
			if (Reader *reader = dynamic_cast<Reader *>(node)) {
				for (std::shared_ptr<LocalValue> value: reader->allLocals()) {
					if (value->variable)
						value->name = StringSet::intern(std::to_string(value->variable->id));
				}
			}

			if (Writer *writer = dynamic_cast<Writer *>(node)) {
				if (writer->variable)
					writer->result = StringSet::intern(std::to_string(writer->variable->id));
			}
		}
	}

	void Function::resetRegisters(bool respectful) {
		if (!respectful) {
			for (const std::pair<int, VariablePtr> &pair: variableStore)
				pair.second->setRegister(-1);
		} else {
			for (const std::pair<int, VariablePtr> &pair: variableStore) {
				if (!WhyInfo::isSpecialPurpose(pair.second->reg))
					pair.second->setRegister(-1);
			}
		}
	}

	void Function::compile() {
		if (compiled)
			return;

		extractBlocks();
		for (BasicBlockPtr &block: blocks)
			block->extract();
		Passes::splitBlocks(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		loadArguments();
		const int initial_stack_size = stackSize;
		extractVariables();
		replaceGetelementptrValues();
		fillLocalValues();
		setupCalls();
		makeCFG();
		coalescePhi();
		computeLiveness();
		updateInstructionNodes();

#ifdef DEBUG_SPILL
		debug();
#endif

		int spilled = Passes::linearScan(*this);
#ifdef DEBUG_SPILL
		int scans = 0;
#endif

		while (0 < spilled) {
#ifdef DEBUG_SPILL
			std::cerr << "Spills in scan " << ++scans << ": \e[1m" << spilled << "\e[0m\n\n";
			debug();
#endif
			Passes::splitBlocks(*this);
			for (BasicBlockPtr &block: blocks)
				block->extract();
			extractVariables(true);
			makeCFG();
			resetRegisters();
			resetLiveness();
			computeLiveness();
			spilled = Passes::linearScan(*this);
		}

		Passes::updateArgumentLoads(*this, stackSize - initial_stack_size);
		Passes::replaceStoresAndLoads(*this);
		Passes::removeRedundantMoves(*this);
		Passes::removeUselessBranches(*this);
		Passes::mergeAllBlocks(*this);

#ifdef DEBUG_SPILL
		std::cerr << "Spills in last scan: \e[1m" << spilled << "\e[0m. Finished \e[1m" << *name << "\e[0m.\n\n";
#endif

		compiled = true;
	}

	std::list<Interval> Function::sortedIntervals() {
		std::list<Interval> intervals;

		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			if (!WhyInfo::isSpecialPurpose(pair.second->reg))
				intervals.emplace_back(pair.second);
		}

		reindexBlocks();

		intervals.sort([&](const Interval &left, const Interval &right) {
			return left.firstDefinition->index < right.firstDefinition->index;
		});

		return intervals;
	}

	VariablePtr Function::makePrecoloredVariable(unsigned char index, BasicBlockPtr block) {
		if (WhyInfo::totalRegisters <= index)
			throw std::invalid_argument("Index too high: " + std::to_string(index));
		VariablePtr new_var = newVariable(std::make_shared<IntType>(64), block);
		new_var->setRegister(index);
		return new_var;

	}

	VariablePtr Function::makeAssemblerVariable(unsigned char index, BasicBlockPtr block) {
		if (WhyInfo::assemblerCount <= index)
			throw std::invalid_argument("Index too high for assembler-reserved registers: " + std::to_string(index));
		return makePrecoloredVariable(WhyInfo::assemblerOffset + index, block);
	}

	void Function::precolorArguments(std::list<Interval> &intervals) {
		if (getCallingConvention() == CallingConvention::Reg16) {
			int reg = WhyInfo::argumentOffset - 1, max = std::min(16, getArity());
			for (Interval &interval: intervals) {
				if (interval.variable->id < max)
					interval.setRegister(++reg);
			}
		}
	}

	void Function::loadArguments() {
		CallingConvention cconv = getCallingConvention();
		if (cconv == CallingConvention::StackOnly) {
			throw std::runtime_error("loadArguments is currently unimplemented for StackOnly functions.");
		} else if (cconv == CallingConvention::Reg16) {
			const int arity = getArity();
			if (arity <= WhyInfo::argumentCount)
				return;

			BasicBlockPtr entry = getEntry();
			std::shared_ptr<LoadRInstruction> first_load;
			for (int arg = arity - 1; WhyInfo::argumentCount <= arg; --arg) {
				VariablePtr arg_var = getVariable(arg, arguments->at(arg - WhyInfo::argumentCount).type, entry);
				VariablePtr temp_var = makeAssemblerVariable(0, entry);
				VariablePtr sp = makePrecoloredVariable(WhyInfo::stackPointerOffset, entry);

				// The stack frame looks like [ $rt | $fp | argN-1 | ... | arg16 | var1 | var2 | ... ].
				// The stack pointer will be pointing right after the stack frame. We need to skip over the local
				// variables and the arguments after this one.
				int to_skip = 0;
				for (const std::pair<int, StackLocation> &pair: stack)
					to_skip += pair.second.width;
				for (int arg2 = WhyInfo::argumentCount; arg2 < arg; ++arg2)
					to_skip += arguments->at(arg2 - WhyInfo::argumentCount).type->width() / 8;

				auto add  = std::make_shared<AddIInstruction> (sp, to_skip, temp_var);
				auto load = std::make_shared<LoadRInstruction>(temp_var, nullptr, arg_var, arg_var->type->width() / 8);
				if (!first_load)
					first_load = load;

				insertBefore(entry->instructions.front(), add, false);
				insertAfter(add, load, false);
			}

			reindexInstructions();
			splitBlock(entry, first_load);
			removeUselessBranch(entry);
		} else {
			throw std::invalid_argument("Invalid calling convention: " + std::to_string(static_cast<int>(cconv)));
		}
	}

	void Function::setupCalls() {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: linearInstructions) {
			// Look for a call instruction.
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);

			// Right now, calls to function pointers are unsupported. This might change once I come across an example.
			VariableValue *name_value = std::dynamic_pointer_cast<VariableValue>(call->name).get();
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(name_value);
			if (!global_name)
				throw std::runtime_error("Calls to function pointers are currently unsupported");

			// Now we need to find out about the function's arguments because we need to know how to call it.
			CallingConvention convention;
			std::vector<TypePtr> argument_types;
			bool ellipsis;

			// First, we check the call node itself—it sometimes contains the signature of the function.
			if (call->argumentsExplicit) {
				argument_types = call->argumentTypes;
				ellipsis = call->argumentEllipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
			} else if (parent->functions.count("@" + *global_name->name) != 0) {
				// When the arguments aren't explicit, we check the parent program's map of functions.
				Function &func = parent->functions.at("@" + *global_name->name);
				ellipsis = func.isVariadic();
				convention = func.getCallingConvention();
				argument_types.reserve(func.arguments->size());
				for (FunctionArgument &argument: *func.arguments)
					argument_types.push_back(argument.type);
			} else if (parent->declarations.count(*global_name->name) != 0) {
				// We can also check the map of declarations.
				FunctionHeader *header = parent->declarations.at(*global_name->name);
				ellipsis = header->arguments->ellipsis;
				convention = ellipsis? CallingConvention::StackOnly : CallingConvention::Reg16;
				argument_types.reserve(header->arguments->arguments.size());
				for (FunctionArgument &argument: header->arguments->arguments)
					argument_types.push_back(argument.type);
			} else throw std::runtime_error("Couldn't find signature for function " + *global_name->name);

			int reg_max = convention == CallingConvention::Reg16? WhyInfo::argumentCount : 0;
			int arg_count = argument_types.size();

			// First, move variables into the argument registers.
			for (int i = 0; i < reg_max && i < arg_count; ++i) {
				// Make a precolored dummy variable.
				VariablePtr new_var = newVariable(argument_types[i]);
				new_var->reg = WhyInfo::argumentOffset + i;
				setupCallValue(new_var, instruction, call->constants[i]);
			}

			// Next, push variables onto the stack, right to left.
			for (int i = arg_count - 1; reg_max <= i; --i) {
				pushCallValue(instruction, call->constants[i]);
			}

			// Once we're done putting the arguments in the proper place, remove the variables from the call
			// instruction's set of read variables so the register allocator doesn't try to insert any spills/loads.
			llvm->read.clear();

			insertBefore(instruction, std::make_shared<JumpSymbolInstruction>(*global_name->name, true));
			if (call->result) {
				auto move = std::make_shared<MoveInstruction>(makePrecoloredVariable(WhyInfo::returnValueOffset,
					instruction->parent.lock()), getVariable(*call->result));
				insertBefore(instruction, move);
				move->extract();
			}

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			remove(instruction);

		extractVariables();
	}

	void Function::pushCallValue(InstructionPtr instruction, ConstantPtr constant) {
		ValueType value_type = constant->value->valueType();
		if (value_type == ValueType::Local) {
			std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			insertBefore(instruction, std::make_shared<StackPushInstruction>(local->variable));
		} else if (value_type == ValueType::Int) {
			std::shared_ptr<IntValue> ival = std::dynamic_pointer_cast<IntValue>(constant->value);
			VariablePtr new_var = newVariable(constant->type);
			insertBefore(instruction, std::make_shared<SetInstruction>(new_var, ival->value));
			insertBefore(instruction, std::make_shared<StackPushInstruction>(new_var));
		} else if (value_type == ValueType::Bool) {
			std::shared_ptr<BoolValue> bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			VariablePtr new_var = newVariable(constant->type);
			insertBefore(instruction, std::make_shared<SetInstruction>(new_var, bval->value + 0));
			insertBefore(instruction, std::make_shared<StackPushInstruction>(new_var));
		} else if (value_type == ValueType::Getelementptr) {
			std::shared_ptr<GetelementptrValue> gep = std::dynamic_pointer_cast<GetelementptrValue>(constant->value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
			if (!gep_global) {
				std::cerr << "Not sure what to do when the argument of getelementptr isn't a global.\n";
				insertBefore(instruction, std::make_shared<InvalidInstruction>());
			} else {
				std::list<int> indices;
				for (const std::pair<int, long> &decimal_pair: gep->decimals)
					indices.push_back(decimal_pair.second);
				int  offset = updiv(Getelementptr::compute(gep->ptrType, indices), 8);
				VariablePtr new_var = newVariable(constant->type);
				auto setsym = std::make_shared<SetSymbolInstruction>(new_var, *gep_global->name);
				insertBefore(instruction, setsym);
				if (offset != 0) {
					auto addi   = std::make_shared<AddIInstruction>(new_var, offset, new_var);
					insertAfter(setsym, addi);
				}
				insertBefore(instruction, std::make_shared<StackPushInstruction>(new_var));
			}
		} else if (constant->conversionSource) {
			pushCallValue(instruction, constant->conversionSource);
		} else {
			std::cout << "Not sure what to do with " << *constant << "\n";
			insertBefore(instruction, std::make_shared<InvalidInstruction>());
		}
	}

	void Function::setupCallValue(VariablePtr new_var, InstructionPtr instruction, ConstantPtr constant) {
		ValueType value_type = constant->value->valueType();
		if (value_type == ValueType::Local) {
			// If it's a variable, move it into the argument register.
			std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(constant->value);
			insertBefore(instruction, std::make_shared<MoveInstruction>(local->variable, new_var));
		} else if (value_type == ValueType::Int) {
			// If it's an integer constant, set the argument register to it.
			std::shared_ptr<IntValue> ival = std::dynamic_pointer_cast<IntValue>(constant->value);
			insertBefore(instruction, std::make_shared<SetInstruction>(new_var, ival->value));
		} else if (value_type == ValueType::Bool) {
			// If it's a boolean constant, convert it to an integer and do the same.
			std::shared_ptr<BoolValue> bval = std::dynamic_pointer_cast<BoolValue>(constant->value);
			insertBefore(instruction, std::make_shared<SetInstruction>(new_var, bval->value + 0));
		} else if (value_type == ValueType::Getelementptr) {
			// If it's a getelementptr expression, things are a little more difficult.
			std::shared_ptr<GetelementptrValue> gep = std::dynamic_pointer_cast<GetelementptrValue>(constant->value);
			std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
			if (!gep_global) {
				std::cerr << "Not sure what to do when the argument of getelementptr isn't a global.\n";
				insertBefore(instruction, std::make_shared<InvalidInstruction>());
			} else {
				std::list<int> indices;
				for (const std::pair<int, long> &decimal_pair: gep->decimals)
					indices.push_back(decimal_pair.second);
				int  offset = updiv(Getelementptr::compute(gep->ptrType, indices), 8);
				auto setsym = std::make_shared<SetSymbolInstruction>(new_var, *gep_global->name);
				insertBefore(instruction, setsym);
				if (offset != 0) {
					auto addi   = std::make_shared<AddIInstruction>(new_var, offset, new_var);
					insertAfter(setsym, addi);
				}
			}
		} else if (constant->conversionSource) {
			setupCallValue(new_var, instruction, constant->conversionSource);
		} else {
			std::cout << "Not sure what to do with " << *constant << "\n";
			insertBefore(instruction, std::make_shared<InvalidInstruction>());
		}
	}

	void Function::replaceGetelementptrValues() {
		for (InstructionPtr &instruction: linearInstructions) {
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() == NodeType::Call)
				continue;
			Reader *reader = dynamic_cast<Reader *>(llvm->node);
			if (!reader)
				continue;
			for (ValuePtr *value: reader->allValuePointers()) {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value->get());
				if (!gep)
					continue;
				std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
				if (!gep_global) {
					std::cerr << "Not sure what to do when the argument of getelementptr isn't a global.\n";
					insertBefore(instruction, std::make_shared<InvalidInstruction>());
				} else {
					std::list<int> indices;
					for (const std::pair<int, long> &decimal_pair: gep->decimals)
						indices.push_back(decimal_pair.second);
					TypePtr out_type;
					int  offset = updiv(Getelementptr::compute(gep->ptrType, indices, &out_type), 8);
					VariablePtr new_var = newVariable(out_type, instruction->parent.lock());
					auto setsym = std::make_shared<SetSymbolInstruction>(new_var, *gep_global->name);
					insertBefore(instruction, setsym);
					setsym->extract();
					if (offset != 0) {
						auto addi   = std::make_shared<AddIInstruction>(new_var, offset, new_var);
						insertAfter(setsym, addi);
						addi->extract();
					}

					auto new_value = std::make_shared<LocalValue>(std::to_string(new_var->id));
					new_value->variable = new_var;
					*value = new_value;
				}
			}
			instruction->extract(true);
		}

		extractVariables();
	}

	StackLocation & Function::addToStack(VariablePtr variable) {
		if (variableLocations.count(variable) == 1)
			return *variableLocations.at(variable);

		const int to_add = variable && variable->type? variable->type->width() / 8 : 8;
		StackLocation &added = stack.emplace(stackSize, StackLocation(this, variable, stackSize, to_add)).first->second;
		stackSize += to_add;
		variableLocations.emplace(variable, &added);
		return added;
	}

	void Function::remove(InstructionPtr instruction) {
		instruction->parent.lock()->instructions.remove(instruction);
		auto found = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		if (found != linearInstructions.end()) {
			auto iter = found;
			++iter;
			linearInstructions.erase(found);
			for (auto end = linearInstructions.end(); iter != end; ++iter)
				--(*iter)->index;
		}

		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			pair.second->removeUse(instruction);
			pair.second->removeDefinition(instruction);
		}
	}

	VariablePtr Function::getVariable(int label) {
		return variableStore.at(label);
	}

	VariablePtr Function::getVariable(const std::string &label) {
		return getVariable(parseLong(label));
	}

	VariablePtr Function::getVariable(int label, const TypePtr type, BasicBlockPtr definer) {
		if (variableStore.count(label) == 0)
			variableStore.insert({label, std::make_shared<Variable>(label, type? type->copy() : nullptr)});
		VariablePtr out = variableStore.at(label);
		if (definer)
			out->addDefiner(definer);
		return out;
	}

	VariablePtr Function::getVariable(const std::string &label, const TypePtr type, BasicBlockPtr definer) {
		return getVariable(parseLong(label), type, definer);
	}

	BasicBlockPtr Function::getEntry() {
		return blocks.front();
	}

	CallingConvention Function::getCallingConvention() const {
		return isVariadic()? CallingConvention::StackOnly : CallingConvention::Reg16;
	}

	void Function::computeLiveness() {
		if (livenessComputed)
			return;

		livenessComputed = true;
		for (BasicBlockPtr &block: blocks) {
			std::unordered_set<Variable *> pool {};
			for (const VariablePtr &variable: block->read) {
				isLiveIn(*block, variable);
				isLiveOut(*block, variable);
				pool.insert(variable.get());
			}

			for (const VariablePtr &variable: block->written) {
				if (pool.count(variable.get()) == 0) {
					isLiveIn(*block, variable);
					isLiveOut(*block, variable);
				}
			}
		}
	}

	void Function::resetLiveness() {
		for (BasicBlockPtr &block: blocks) {
			block->liveIn.clear();
			block->liveOut.clear();
		}

		livenessComputed = false;
	}

	bool Function::isLiveIn(BasicBlock &block, VariablePtr var) {
		// M^r(block) = M(block) ∪ {block}; // Create a new set from the merge set
		Node::Set m_r = mergeSets.at(block.node);
		m_r.insert(block.node);

		// Iterate over all the uses of var
		// for t ∈ uses(var) do
		for (BasicBlockPtr t: var->usingBlocks) {
			// while t≠def(var) do
			// TODO: is this valid, or is the algorithm not valid after phi coalescing?
			while (var->definingBlocks.count(t) == 0) {
				// if t ∩ M^r(block) then
				if (m_r.count(t->node) > 0) {
					block.liveIn.insert(var);
					return true;
				}
				// t = dom-parent(t); // Climb up from node t in the DJ-Graph
				BasicBlockPtr t_new = cfg[*(*dTree)[*t->node].parent()].get<BasicBlockPtr>();
				if (t_new == t)
					break;
				t = t_new;
			}
		}

		return false;
	}

	bool Function::isLiveOut(BasicBlock &block, VariablePtr var) {
		// if def(a)=n

		for (BasicBlockPtr defining_block: var->definingBlocks) {
			if (defining_block.get() == &block) {
				// return uses(a)\def(a)≠∅;
				std::set<BasicBlockPtr> set = var->usingBlocks;
				for (BasicBlockPtr bb: var->definingBlocks)
					set.erase(bb);
				return !set.empty();
			}
		}

		// for t ∈ uses(a) do // Iterate over all the uses of a
		for (BasicBlockPtr t: var->usingBlocks) {
			// while t≠def(a) do
			while (var->definingBlocks.count(t) == 0) {
				// if t ∩ Ms(n) then
				if (0 < succMergeSets.at(block.node).count(t->node)) {
					block.liveOut.insert(var);
					return true;
				}

				// t = dom-parent(t);
				BasicBlockPtr t_new = cfg[*(*dTree)[*t->node].parent()].get<BasicBlockPtr>();
				if (t_new == t)
					break;
				t = t_new;
			}
		}

		return false;
	}

	void Function::debug() {
#if defined(DEBUG_BLOCKS) || defined(DEBUG_LINEAR) || defined(DEBUG_VARS)
		std::cout << "\e[1m" << *name << "\e[0m(";
		for (auto begin = arguments->begin(), iter = begin, end = arguments->end(); iter != end; ++iter) {
			if (iter != begin)
				std::cout << "\e[2m,\e[0m ";
			std::cout << *iter->type;
			if (iter->name)
				std::cout << " " << *iter->name;
		}
		std::cout << ") {\n";
#endif
#ifdef DEBUG_BLOCKS
		for (const BasicBlockPtr &block: blocks) {
			std::cout << "    \e[2m; \e[4m<label>:\e[1m" << block->label << "\e[0;2;4m @ " << block->offset << "/"
			          << block->index << ": preds =";
			for (auto begin = block->preds.begin(), iter = begin, end = block->preds.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << ",";
				std::cout << " %" << *iter;
			}
			std::cout << "\e[0m\n";
			for (const std::shared_ptr<Instruction> &instruction: block->instructions) {
#ifdef DEBUG_READ_WRITTEN
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cout << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written
				          << "\e[0m\n";
#else
				std::cout << "    " << instruction->debugExtra() << "\n";
#endif
			}
			std::cout << "\n";
		}
#endif
#ifdef DEBUG_LINEAR
		for (const std::shared_ptr<Instruction> &instruction: linearInstructions) {
			int read, written;
			std::tie(read, written) = instruction->extract();
			std::cout << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written << "\e[0m\n";
		}
#endif
#ifdef DEBUG_VARS
		std::cout << "    \e[2m; Variables:\e[0m\n";
		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			std::cout << "    \e[2m; \e[1m%" << std::left << std::setw(2) << pair.first << "\e[0;2m  defs ("
			          << pair.second->definitions.size() << ") =";
			for (const BasicBlockPtr &def: pair.second->definingBlocks)
				std::cout << " \e[1;2m%" << std::setw(2) << def->label << "\e[0m";
			std::cout << "  \e[0;2muses =";
			for (const BasicBlockPtr &use: pair.second->usingBlocks)
				std::cout << " \e[1;2m%" << std::setw(2) << use->label << "\e[0m";
			int spill_cost = pair.second->spillCost();
			std::cout << "\e[2m  cost = \e[1m" << (spill_cost == INT_MAX? "∞" : std::to_string(spill_cost)) + "\e[0;2m";
			if (pair.second->definingBlocks.size() > 1)
				std::cout << " (multiple defs)";
			std::cout << "\e[0m\n";
			std::cout << "    \e[2m;      \e[32min  =\e[1m";
			for (const BasicBlockPtr &block: blocks) {
				if (block->isLiveIn(pair.second))
					std::cout << " %" << block->label;
			}
			std::cout << "\e[0m\n";
			std::cout << "    \e[2m;      \e[31mout =\e[1m";
			for (const BasicBlockPtr &block: blocks) {
				if (block->isLiveOut(pair.second))
					std::cout << " %" << block->label;
			}
			std::cout << "\e[0m\n";
		}
#endif
#if defined(DEBUG_BLOCKS) || defined(DEBUG_LINEAR) || defined(DEBUG_VARS)
		std::cout << "}\n\n";
#endif
#ifdef DEBUG_RENDER
		for (Node *node: cfg.nodes()) {
			if (node->data.has_value()) {
				BasicBlockPtr bb = node->get<BasicBlockPtr>();
				if (bb)
					node->rename("\"" + node->label() + ":" + std::to_string(bb->estimatedExecutions) + "\"");
			}
		}

		cfg.renderTo("graph_" + *name + ".png");
		dTree->renderTo("graph_D_" + *name + ".png");
#endif
	}

	void Function::debugMergeSets() const {
		for (const Node::Map &map: {mergeSets, succMergeSets}) {
			std::cout << "--------------------------------\n";
			for (const std::pair<Node *, Node::Set> &pair: map) {
				std::cout << pair.first->label() << ":";
				for (Node *node: pair.second)
					std::cout << " " << node->label();
				std::cout << "\n";
			}
		}
	}

	void Function::debugStack() const {
		for (const std::pair<int, StackLocation> &pair: stack)
			std::cout << pair.first << "[" << pair.second.width << "]:" << *pair.second.variable << " ";
		std::cout << "\n";
	}
}
