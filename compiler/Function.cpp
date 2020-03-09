#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "parser/ASTNode.h"
#include "parser/FunctionArgs.h"
#include "parser/FunctionHeader.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "util/Util.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"

// #define DEBUG_INTERVALS
#define DEBUG_INSTRUCTIONS
#define DEBUG_VARS
// #define DEBUG_RENDER

namespace LL2W {
	Function::Function(Program &program, const ASTNode &node) {
		parent = &program;
		name = node.lexerInfo;
		arguments = dynamic_cast<FunctionHeader *>(node[0])->arguments;
		astnode = &node;
	}

	void Function::extractBlocks() {
		int label = arguments->arguments.size();
		std::vector<int> preds {};
		std::list<std::shared_ptr<Instruction>> instructions;
		int offset = 0;
		int instructionIndex = 0;

		std::function<void(BasicBlockPtr)> finishBlock = [&](BasicBlockPtr block) {
			block->offset = offset;
			block->parent = this;
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
				label = header->label;
				preds = header->preds;
			} else if (InstructionNode *instruction = dynamic_cast<InstructionNode *>(child)) {
				instructions.push_back(std::make_shared<LLVMInstruction>(instruction, instructionIndex++));
				linearInstructions.push_back(instructions.back());
			}
		}

		if (!instructions.empty()) {
			blocks.push_back(std::make_shared<BasicBlock>(label, preds, instructions));
			finishBlock(blocks.back());
		}
	}

	void Function::extractVariables() {
		for (BasicBlockPtr &block: blocks) {
			for (VariablePtr read_var: block->read)
				read_var->usingBlocks.insert(block);
			for (VariablePtr written_var: block->written)
				written_var->definingBlocks.insert(block);
			for (std::shared_ptr<Instruction> &instruction: block->instructions) {
				for (VariablePtr read_var: instruction->read) {
					read_var->lastUse = instruction;
					read_var->uses.insert(instruction);
				}
				for (VariablePtr written_var: instruction->written)
					written_var->definitions.insert(instruction);
			}
		}

		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			// Function arguments aren't defined by any instruction. They're implicitly defined in the first block.
			if (pair.second->definingBlocks.empty()) {
				pair.second->definingBlocks.insert(blocks.front());
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

	void Function::assignIndices() {
		int index = -1;
		for (InstructionPtr &instruction: linearInstructions)
			instruction->index = ++index;
	}

	void Function::coalescePhi() {
		std::list<InstructionPtr> to_remove;

		// Scan through each instruction in order.
		for (InstructionPtr &instruction: linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || llvm_instruction->node->nodeType() != NodeType::Phi)
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			// Otherwise, get its written temporary. This is what the other temporaries will be merged to.
			VariablePtr target = getVariable(*phi_node->result, phi_node->type);
			BasicBlockPtr phi_definer = target->onlyDefiner();
			for (const std::pair<Value *, const std::string *> &pair: phi_node->pairs) {
				const LocalValue *local = dynamic_cast<LocalValue *>(pair.first);
				if (!local) {
					// In rare occasions, one or more operands of a phi instruction can be constants like "true".
					// In these cases, we can't eliminate the phi instruction by merging alone. We have to insert
					// instructions in the penultimate slots of the predicate labels for which the phi function
					// parameters specify a constant.
					if (pair.first->valueType() == ValueType::Bool) {
						const BoolValue *boolval = dynamic_cast<BoolValue *>(pair.first);
						BasicBlockPtr block = bbMap.at(pair.second);
						IntType *type = new IntType(32);
						VariablePtr new_var = newVariable(type, block);
						delete type;

						block->insertBeforeTerminal(std::make_shared<SetInstruction>(new_var,
							boolval->value? 1 : 0, -1));
						new_var->makeAliasOf(*target);
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
	}

	VariablePtr Function::newVariable(Type *type, std::shared_ptr<BasicBlock> definer) {
		int label = 0;
		if (!variableStore.empty()) {
			auto iter = variableStore.end();
			--iter;
			label = iter->first + 1;
		}

		for (; bbLabels.count(label) == 1; ++label);
		return getVariable(label, type, definer);
	}

	void Function::spill(VariablePtr variable) {
		// Right after the definition of the variable to be spilled, store its value onto the stack in the proper
		// location. For each use of the original variable, replace the original variable with a new variable, and right
		// before the use insert a definition for the variable by loading it from the stack.
		std::cerr << "Trying to spill " << *variable << " (definitions: " << variable->definitions.size() << ")\n";
		BasicBlockPtr block = variable->onlyDefiner();
		InstructionPtr definition = variable->onlyDefinition();
		insertAfter(definition, std::make_shared<StackStoreInstruction>(*variableLocations.at(variable), variable));
	}

	void Function::insertAfter(InstructionPtr base, InstructionPtr new_instruction) {
		BasicBlockPtr block = base->parent.lock();
		new_instruction->index = base->index + 1;
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

			for (auto end = linearInstructions.end(); iter != end; ++iter)
				++(*iter)->index;
		}
	}

	void Function::removeUselessBranches() {
		std::list<InstructionPtr> to_remove;
		for (auto iter = blocks.begin(), end = blocks.end(); iter != end; ++iter) {
			BasicBlockPtr &block = *iter;
			if (block->instructions.empty())
				continue;
			InstructionPtr &back = block->instructions.back();
			if (LLVMInstruction *llback = dynamic_cast<LLVMInstruction *>(back.get())) {
				if (llback->node->nodeType() == NodeType::BrUncond) {
					const BrUncondNode *branch = dynamic_cast<BrUncondNode *>(llback->node);
					auto next = iter;
					++next;
					if (next != end) {
						const int destination = std::atoi(branch->destination->substr(1).c_str());
						if ((*next)->label == destination)
							to_remove.push_back(back);
					}
				}
			}
		}

		for (InstructionPtr &ptr: to_remove)
			remove(ptr);
	}

	Node & Function::operator[](const BasicBlock &bb) const {
		return *bbNodeMap.at(&bb);
	}

	int Function::arity() const {
		return arguments? arguments->arguments.size() : 0;
	}

	bool Function::variadic() const {
		return arguments? arguments->ellipsis : false;
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
			if (block->instructions.back()->isTerminal())
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
		computeSuccMergeSet(&djGraph.value()[*getEntry()->node]);
	}

	void Function::fillLocalValues() {
		for (InstructionPtr &instruction: linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm)
				continue;

			InstructionNode *node = llvm->node;
			if (Reader *reader = dynamic_cast<Reader *>(node)) {
				for (LocalValue *value: reader->allLocals())
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
				for (LocalValue *value: reader->allLocals()) {
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

	void Function::extract() {
		if (extracted)
			return;

		extractBlocks();
		for (BasicBlockPtr &block: blocks)
			block->extract();
		extractVariables();
		makeCFG();
		fillLocalValues();
		coalescePhi();
		computeLiveness();
		updateInstructionNodes();
		linearScan();
		removeUselessBranches();
		extracted = true;
	}

	void Function::uncolorAll() {
		for (std::pair<const int, VariablePtr> &pair: variableStore)
			pair.second->setRegister(-1);
	}

	std::list<Interval> Function::sortedIntervals() {
		std::list<Interval> intervals;
		for (std::pair<const int, VariablePtr> &pair: variableStore)
			intervals.emplace_back(pair.second);
		intervals.sort([&](const Interval &left, const Interval &right) {
			return left.firstDefinition->label < right.firstDefinition->label;
		});
		return intervals;
	}

	void Function::precolorArguments(std::list<Interval> &intervals) {
		if (getCallingConvention() == CallingConvention::Reg16) {
			int reg = WhyInfo::argumentOffset - 1, max = std::min(16, arity());
			for (Interval &interval: intervals) {
				if (interval.variable->id < max)
					interval.setRegister(++reg);
			}
		}
	}

	StackLocation & Function::addToStack(VariablePtr variable) {
		const int to_add = variable && variable->type? variable->type->width() / 8 : 8;
		StackLocation &added = stack.emplace(stackSize, StackLocation(this, variable, stackSize, to_add)).first->second;
		stackSize += to_add;
		variableLocations.emplace(variable, &added);
		return added;
	}

	int Function::linearScan() {
		std::list<Interval> intervals = sortedIntervals();
		std::list<Interval *> active;
		std::set<int> pool = WhyInfo::makeRegisterPool();
		int spill_count = 0;

		std::function<void(Interval &)> addToActive = [&](Interval &interval) {
			int endpoint = interval.endpoint();
			for (auto iter = active.begin(), end = active.end(); iter != end; ++iter) {
				if (endpoint < (*iter)->endpoint()) {
					active.insert(iter, &interval);
					return;
				}
			}
			active.push_back(&interval);
		};

		std::function<void(Interval &)> addLocation = [&](Interval &interval) {
			addToStack(interval.variable);
			spill(interval.variable);
		};

		std::function<void(Interval &)> expireOldIntervals = [&](Interval &interval) {
			for (auto iter = active.begin(); iter != active.end();) {
				Interval &jnterval = **iter;
				if (interval.startpoint() <= jnterval.endpoint())
					return;
				pool.insert(jnterval.reg);
				iter = active.erase(iter);
			}
		};

		std::function<void(Interval &)> spillAtInterval = [&](Interval &interval) {
			Interval &spill = *active.back();
			++spill_count;
			if (interval.endpoint() < spill.endpoint()) {
				interval.setRegister(spill.reg);
				addLocation(spill);
				active.remove(&spill);
				addToActive(interval);
			} else {
				addLocation(interval);
			}
		};

		precolorArguments(intervals);

		for (Interval &interval: intervals) {
			if (WhyInfo::isSpecialPurpose(interval.reg))
				continue;
			expireOldIntervals(interval);
			if (active.size() == static_cast<size_t>(WhyInfo::generalPurposeRegisters)) {
				spillAtInterval(interval);
			} else {
				pool.erase(interval.setRegister(*pool.begin()));
				addToActive(interval);
			}
		}

#ifdef DEBUG_INTERVALS
		std::cout << "\e[1;4m" << *name << "(" << arity() << ")\e[0m [spills: " << spill_count << "]\n";
		for (Interval &interval: intervals) {
			std::cout << "    Interval for variable %" << interval.variable->id << ": [%" << interval.startpoint()
			          << ", %" << interval.endpoint() << "]; reg = $" << WhyInfo::registerName(interval.reg) << " ("
			          << interval.reg << ")\n";
		}

		if (!stack.empty()) {
			std::cout << "Stack (" << stack.size() << "):\n";
			for (const std::pair<const int, StackLocation> &pair: stack)
				std::cout << "    " << pair.first << ": " << pair.second.getName() << "\n";
		}
		std::cout << "\n";
#endif

		return spill_count;
	}

	void Function::remove(InstructionPtr instruction) {
		instruction->parent.lock()->instructions.remove(instruction);
		auto found = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		auto iter = found;
		if (found != linearInstructions.end()) {
			linearInstructions.erase(found);
			++iter;
			for (auto end = linearInstructions.end(); iter != end; ++iter)
				--(*iter)->index;
		}
	}

	VariablePtr Function::getVariable(int label) {
		return variableStore.at(label);
	}

	VariablePtr Function::getVariable(const std::string &label) {
		return getVariable(parseLong(label));
	}

	VariablePtr Function::getVariable(int label, const Type *type, BasicBlockPtr definer) {
		if (variableStore.count(label) == 0)
			variableStore.insert({label, std::make_shared<Variable>(label, type? type->copy() : nullptr)});
		VariablePtr out = variableStore.at(label);
		if (definer)
			out->addDefiner(definer);
		return out;
	}

	VariablePtr Function::getVariable(const std::string &label, const Type *type, BasicBlockPtr definer) {
		return getVariable(parseLong(label), type, definer);
	}

	BasicBlockPtr Function::getEntry() {
		return blocks.front();
	}

	CallingConvention Function::getCallingConvention() const {
		return variadic()? CallingConvention::StackOnly : CallingConvention::Reg16;
	}

	void Function::computeLiveness() {
		if (livenessComputed)
			return;

		livenessComputed = true;
		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			for (BasicBlockPtr &block: blocks) {
				isLiveIn(*block, pair.second);
				isLiveOut(*block, pair.second);
			}
		}
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
#if defined(DEBUG_INSTRUCTIONS) || defined(DEBUG_VARS)
		std::cout << "\e[1m" << *name << "\e[0m(";
		std::vector<FunctionArgument> &args = arguments->arguments;
		for (auto begin = args.begin(), iter = begin, end = args.end(); iter != end; ++iter) {
			if (iter != begin)
				std::cout << "\e[2m,\e[0m ";
			std::cout << *iter->type;
			if (iter->name)
				std::cout << " " << *iter->name;
		}
		std::cout << ") {\n";
#endif
#ifdef DEBUG_INSTRUCTIONS
		for (const BasicBlockPtr &block: blocks) {
			std::cout << "    \e[2m; \e[4m<label>:\e[1m" << block->label << "\e[0;2;4m @ " << block->offset <<
			             ": preds =";
			for (auto begin = block->preds.begin(), iter = begin, end = block->preds.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << ",";
				std::cout << " %" << *iter;
			}
			std::cout << "\e[0m\n";
			for (const std::shared_ptr<Instruction> &instruction: block->instructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cout << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written
				          << "\e[0m\n";
			}
			std::cout << "\n";
		}
#endif
#ifdef DEBUG_VARS
		std::cout << "    \e[2m; Variables:\e[0m\n";
		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			std::cout << "    \e[2m; \e[1m%" << std::left << std::setw(2) << pair.first << "\e[0;2m  defs =";
			for (const BasicBlockPtr &def: pair.second->definingBlocks)
				std::cout << " \e[1;2m%" << std::setw(2) << def->label << "\e[0m";
			std::cout << "  \e[0;2muses =";
			for (const BasicBlockPtr &use: pair.second->usingBlocks)
				std::cout << " \e[1;2m%" << std::setw(2) << use->label << "\e[0m";
			int spill_cost = pair.second->spillCost();
			std::cout << "\e[2m  cost = " << (spill_cost == INT_MAX? "∞" : std::to_string(spill_cost));
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
#if defined(DEBUG_INSTRUCTIONS) || defined(DEBUG_VARS)
		std::cout << "}\n\n";
#endif
		for (Node *node: cfg.nodes()) {
			if (node->data.has_value()) {
				BasicBlockPtr bb = node->get<BasicBlockPtr>();
				if (bb)
					node->rename("\"" + node->label() + ":" + std::to_string(bb->estimatedExecutions) + "\"");
			}
		}

#ifdef DEBUG_RENDER
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
}
