#include <climits>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "options.h"
#include "parser/ASTNode.h"
#include "parser/FunctionArgs.h"
#include "parser/FunctionHeader.h"
#include "pass/CoalescePhi.h"
#include "pass/FillLocalValues.h"
#include "pass/InsertLabels.h"
#include "pass/InsertPrologue.h"
#include "pass/InsertLabels.h"
#include "pass/LinearScan.h"
#include "pass/LoadArguments.h"
#include "pass/LowerAlloca.h"
#include "pass/LowerBranches.h"
#include "pass/LowerConversions.h"
#include "pass/LowerGetelementptr.h"
#include "pass/LowerIcmp.h"
#include "pass/LowerMath.h"
#include "pass/LowerMemory.h"
#include "pass/LowerObjectsize.h"
#include "pass/LowerRet.h"
#include "pass/LowerSelect.h"
#include "pass/LowerStack.h"
#include "pass/LowerStackrestore.h"
#include "pass/LowerStacksave.h"
#include "pass/LowerSwitch.h"
#include "pass/MakeCFG.h"
#include "pass/MergeAllBlocks.h"
#include "pass/RemoveRedundantMoves.h"
#include "pass/RemoveUselessBranches.h"
#include "pass/ReplaceConstants.h"
#include "pass/ReplaceStoresAndLoads.h"
#include "pass/SetupCalls.h"
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
		returnType = header->returnType;
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
			variable->debug();
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

	std::string Function::transformLabel(const std::string &str) const {
		return "__" + name->substr(1) + "_label" + (str.front() == '%'? str.substr(1) : str);
	}

	void Function::computeSuccMergeSets() {
		succMergeSets.clear();
		computeSuccMergeSet(&djGraph.value()[*getEntry()->node]);
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
		Passes::fillLocalValues(*this);
		Passes::lowerStacksave(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract();
		Passes::splitBlocks(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		Passes::lowerAlloca(*this);
		Passes::loadArguments(*this);
		Passes::lowerObjectsize(*this);
		Passes::replaceConstants(*this);
		Passes::lowerIcmp(*this);
		Passes::lowerMath(*this);
		Passes::lowerConversions(*this);
		Passes::lowerGetelementptr(*this);
		Passes::lowerSelect(*this);
		Passes::lowerSwitch(*this);
		const int initial_stack_size = stackSize;
		extractVariables();
		Passes::lowerStackrestore(*this);
		Passes::setupCalls(*this);
		Passes::lowerMemory(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		extractVariables();
		Passes::makeCFG(*this);
		Passes::coalescePhi(*this);
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
			Passes::makeCFG(*this);
			resetRegisters();
			resetLiveness();
			computeLiveness();
			spilled = Passes::linearScan(*this);
		}

		// TODO: insert prologue and epilogue
		Passes::updateArgumentLoads(*this, stackSize - initial_stack_size);
		Passes::replaceStoresAndLoads(*this);
		Passes::lowerStack(*this);
		Passes::removeRedundantMoves(*this);
		Passes::removeUselessBranches(*this);
		Passes::mergeAllBlocks(*this);
		Passes::insertLabels(*this);
		Passes::lowerBranches(*this);
		Passes::insertPrologue(*this);
		Passes::lowerRet(*this);

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

	StackLocation & Function::addToStack(VariablePtr variable, StackLocation::Purpose purpose, int width) {
		if (variableLocations.count(variable) == 1)
			return *variableLocations.at(variable);

		if (width == -1)
			width = variable && variable->type? variable->type->width() / 8 : 8;

		auto &added = stack.emplace(stackSize, StackLocation(this, variable, purpose, stackSize, width)).first->second;
		stackSize += width;
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

	void Function::replace(InstructionPtr to_replace, InstructionPtr substitute) {
		insertBefore(to_replace, substitute);
		remove(substitute);
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

	std::string Function::toString() {
		std::stringstream out;
		out << "sub " << name->substr(1) << "() {\n";
		for (InstructionPtr &instruction: linearInstructions) {
#ifdef SPACE_COUNT
			out << std::string(' ', SPACE_COUNT);
#else
			out << "\t";
#endif
			out << instruction->toString() << "\n";
		}
		out << "}\n";
		return out.str();
	}

	void Function::debug() {
#if defined(DEBUG_BLOCKS) || defined(DEBUG_LINEAR) || defined(DEBUG_VARS)
		std::cout << *returnType << " \e[35m" << *name << "\e[94m(\e[39m";
		for (auto begin = arguments->begin(), iter = begin, end = arguments->end(); iter != end; ++iter) {
			if (iter != begin)
				std::cout << "\e[2m,\e[0m ";
			std::cout << *iter->type;
			if (iter->name)
				std::cout << " " << *iter->name;
		}
		std::cout << "\e[94m) {\e[39m\n";
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
		std::cout << "\e[94m}\e[39m\n\n";
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

	VariablePtr Function::m0(BasicBlockPtr block) {
		return makeAssemblerVariable(0, block);
	}

	VariablePtr Function::m0(InstructionPtr instruction) {
		return m0(instruction->parent.lock());
	}

	VariablePtr Function::fp(BasicBlockPtr block) {
		return makePrecoloredVariable(WhyInfo::framePointerOffset, block);
	}

	VariablePtr Function::fp(InstructionPtr instruction) {
		return fp(instruction->parent.lock());
	}

	VariablePtr Function::sp(BasicBlockPtr block) {
		return makePrecoloredVariable(WhyInfo::stackPointerOffset, block);
	}

	VariablePtr Function::sp(InstructionPtr instruction) {
		return sp(instruction->parent.lock());
	}
}
