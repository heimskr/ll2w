#include <climits>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#define DEBUG_BLOCKS
// #define DEBUG_LINEAR
#define DEBUG_VARS
// #define DEBUG_RENDER
// #define DEBUG_SPILL
// #define DEBUG_SPLIT
#define DEBUG_READ_WRITTEN
// #define DISABLE_COMMENTS
// #define DEBUG_ESTIMATIONS
// #define DEBUG_BLOCK_LIVENESS
#define DEBUG_VAR_LIVENESS
// #define DEBUG_ALIASES
#define DEBUG_STACK
#define STRICT_READ_CHECK
#define STRICT_WRITTEN_CHECK
// #define FN_CATCH_EXCEPTIONS

#include "allocator/ColoringAllocator.h"
#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "exception/NoChoiceError.h"
#include "instruction/AddIInstruction.h"
#include "instruction/Comment.h"
#include "instruction/Label.h"
#include "instruction/LuiInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "options.h"
#include "parser/ASTNode.h"
#include "parser/FunctionArgs.h"
#include "parser/FunctionHeader.h"
#include "pass/BreakUpBigSets.h"
#include "pass/CoalescePhi.h"
#include "pass/CopyArguments.h"
#include "pass/FillLocalValues.h"
#include "pass/FinishMultireg.h"
#include "pass/IgnoreIntrinsics.h"
#include "pass/InsertLabels.h"
#include "pass/InsertPrologue.h"
#include "pass/LoadArguments.h"
#include "pass/LowerAlloca.h"
#include "pass/LowerBranches.h"
#include "pass/LowerConversions.h"
#include "pass/LowerExtractvalue.h"
#include "pass/LowerFreeze.h"
#include "pass/LowerGetelementptr.h"
#include "pass/LowerIcmp.h"
#include "pass/LowerInlineAsm.h"
#include "pass/LowerMath.h"
#include "pass/LowerMemcpy.h"
#include "pass/LowerMemory.h"
#include "pass/LowerMemset.h"
#include "pass/LowerObjectsize.h"
#include "pass/LowerRet.h"
#include "pass/LowerSelect.h"
#include "pass/LowerStack.h"
#include "pass/LowerStackrestore.h"
#include "pass/LowerStacksave.h"
#include "pass/LowerSwitch.h"
#include "pass/LowerVarargs.h"
#include "pass/MakeCFG.h"
#include "pass/MergeAllBlocks.h"
#include "pass/RemoveRedundantMoves.h"
#include "pass/RemoveUnreachable.h"
#include "pass/RemoveUselessBranches.h"
#include "pass/ReplaceConstants.h"
#include "pass/ReplaceStoresAndLoads.h"
#include "pass/SetupCalls.h"
#include "pass/SplitBlocks.h"
#include "pass/SplitResultMoves.h"
#include "pass/StackSkip.h"
#include "pass/TransformInstructions.h"
#include "pass/TrimBlocks.h"
#include "pass/UpdateArgumentLoads.h"
#include "util/CompilerUtil.h"
#include "util/Util.h"
#include "Interactive.h"

namespace LL2W {
	Function::Function(Program &program, const ASTNode &node) {
		parent = &program;
		name = node.lexerInfo;
		FunctionHeader *header = dynamic_cast<FunctionHeader *>(node.front());
		if (!header)
			throw std::runtime_error("header is null in Function::Function");
		argumentsNode = header->arguments;
		arguments = &argumentsNode->arguments;
		astnode = &node;
		returnType = header->returnType;
		allocator = new ColoringAllocator(*this);
		debugIndex = header->debugIndex;
	}

	Function::~Function() {
		if (allocator)
			delete allocator;
	}

	Allocator::Result Function::attemptAllocation() {
		if ((lastAllocationResult = allocator->attempt()) == Allocator::Result::Success)
			allocationDone = true;
		return lastAllocationResult;
	}

	void Function::extractBlocks() {
		const std::string *label = StringSet::intern(std::to_string(arguments->size()));
		std::vector<const std::string *> preds {};
		std::list<std::shared_ptr<Instruction>> instructions;
		int offset = 0;
		int instructionIndex = -1;
		int blockIndex = -1;

		std::function<void(BasicBlockPtr)> finishBlock = [&](BasicBlockPtr block) {
			block->offset = offset;
			block->parent = this;
			block->index = ++blockIndex;
			bbLabels.insert(block->label);
			bbMap.emplace(block->label, block);
			for (std::shared_ptr<Instruction> &instruction: instructions) {
				instruction->parent = block;
				instruction->extract();
				for (const std::unordered_set<VariablePtr> *variables: {&instruction->read, &instruction->written})
					for (VariablePtr vptr: *variables)
						variableStore.insert({vptr->id, vptr});
			}
		};

		for (ASTNode *child: *astnode->at(1)) {
			if (child->symbol == LLVM_BLOCKHEADER) {
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
			for (auto &map: {variableStore, extraVariables})
				for (const auto &[id, var]: map) {
					var->setUsingBlocks({});
					var->setDefiningBlocks({});
					var->setDefinitions({});
					var->setUses({});
					var->setLastUse({});
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

		for (auto &map: {variableStore, extraVariables})
			for (const auto &[id, var]: map) {
				if (var->definingBlocks.empty()) {
					// Function arguments aren't defined by any instruction.
					// They're implicitly defined in the first block.
					if (isArgument(id)) {
						var->addDefiner(blocks.front());
						blocks.front()->written.insert(var);
					} else if (!var->usingBlocks.empty()) {
						BasicBlockPtr block = var->usingBlocks.begin()->lock();
						var->addDefiner(block);
						block->written.insert(var);
					}
				}
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

	Variable::ID Function::newLabel() const {
		int label = 0;
		if (!variableStore.empty()) {
			auto iter = variableStore.end();
			while (iter-- != variableStore.begin())
				if (Util::isNumeric(iter->first)) {
					label = Util::parseLong(iter->first) + 1;
					break;
				}
		}

		const std::string *interned;
		for (;;) {
			interned = StringSet::intern(std::to_string(label));
			if (0 < variableStore.count(interned) + extraVariables.count(interned) + bbLabels.count(interned))
				++label;
			else
				break;
		}

		return interned;
	}

	VariablePtr Function::newVariable(TypePtr type, std::shared_ptr<BasicBlock> definer) {
		return getVariable(newLabel(), type, definer);
	}

	bool Function::spill(VariablePtr variable, bool doDebug) {
		bool out = false;
		// Right after the definition of the variable to be spilled, store its value onto the stack in the proper
		// location. For each use of the original variable, replace the original variable with a new variable, and right
		// before the use insert a definition for the variable by loading it from the stack.
		if (variable->definitions.empty()) {
			debug();
			variable->debug();
			throw std::runtime_error("Cannot spill variable: no definitions");
		}

		const StackLocation &location = getSpill(variable, true);

		for (std::weak_ptr<Instruction> weak_definition: variable->definitions) {
			InstructionPtr definition = weak_definition.lock();
			// Because ϕ-instructions are eventually removed after aliasing the variables, they don't count as a real
			// definition here.
			if (definition->isPhi())
				continue;
#ifdef DEBUG_SPILL
			std::cerr << "  Trying to spill " << *variable << " (definition: " << definition->debugExtra() << " at "
			          << definition->index << ", OID: " << variable->originalID << ")\n";
#endif
			auto store = std::make_shared<StackStoreInstruction>(location, variable);
			auto next = after(definition);
			bool should_insert = true;

			// Skip comments.
			while (next && dynamic_cast<Comment *>(next.get()) != nullptr)
				next = after(next);

			if (next) {
				auto other_store = std::dynamic_pointer_cast<StackStoreInstruction>(next);
				if (other_store && *other_store == *store) {
					should_insert = false;
#ifdef DEBUG_SPILL
					std::cerr << "    A stack store already exists: " << next->debugExtra() << "\n";
#endif
				}
			}

			if (should_insert) {
				insertAfter(definition, store, false);
				insertBefore(store, std::make_shared<Comment>("Spill: stack store for " + variable->plainString()));
				VariablePtr new_var = mx(6, definition);
				definition->replaceWritten(variable, new_var);
				store->variable = new_var;
				store->extract();
				out = true;
#ifdef DEBUG_SPILL
				std::cerr << "    Inserting a stack store after definition: " << store->debugExtra() << "\n";
#endif
			} else {
				comment(after(definition), "Spill: no store inserted here for " + variable->plainString());
#ifdef DEBUG_SPILL
				std::cerr << "    \e[1mNot\e[22m inserting a stack store after definition: " << store->debugExtra()
				          << "\n";
#endif
			}
		}

#ifdef DEBUG_SPILL
		if (!out)
			std::cerr << "  No stores inserted for " << *variable << ".\n";
#endif

		if (doDebug)
			debug();

		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
			InstructionPtr &instruction = *iter;
#ifdef STRICT_READ_CHECK
			if (std::shared_ptr<Variable> read = instruction->doesRead(variable)) {
#else
			if (instruction->read.count(variable) != 0) {
#endif
				VariablePtr new_var = newVariable(variable->type, instruction->parent.lock());
				const std::string old_extra = instruction->debugExtra();
#ifdef STRICT_READ_CHECK
				const bool replaced = instruction->replaceRead(read, new_var);
#else
				const bool replaced = instruction->replaceRead(variable, new_var);
#endif
#ifdef DEBUG_SPILL
				BasicBlockPtr par = instruction->parent.lock();
				std::cerr << "    Creating new variable: " << *new_var << "\n";
				std::cerr << "    " << (replaced? "Replaced" : "Didn't replace")
				          << " in " << old_extra;
				if (par)
					std::cerr << " in block " << *par->label;
				if (replaced)
					std::cerr << " (now " << instruction->debugExtra() << ")";
				std::cerr << "\n";
#endif
				if (replaced) {
#ifdef STRICT_READ_CHECK
					instruction->read.erase(read);
#else
					instruction->read.erase(variable);
#endif
					instruction->read.insert(new_var);
					auto load = std::make_shared<StackLoadInstruction>(new_var, location, -1);
					insertBefore(instruction, load, "Spill: stack load: location=" + std::to_string(location.offset));
					load->extract();
					out = true;
#ifdef DEBUG_SPILL
				std::cerr << "      Inserting a stack load before " << instruction->debugExtra() << ": "
				          << load->debugExtra() << "\n";
#endif
					markSpilled(new_var);
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

		// TODO: can some of this be targeted to just the spilled variable?
		reindexInstructions();
		resetLiveness();
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		extractVariables(true); // Reset stale use/define data.
		computeLiveness();
		markSpilled(variable);
		return out;
	}

	void Function::markSpilled(VariablePtr variable) {
		spilledVariables.insert(variable->originalID);
	}

	bool Function::isSpilled(VariablePtr variable) const {
		return spilledVariables.count(variable->originalID) != 0;
	}

	bool Function::canSpill(VariablePtr variable) {
		if (variable->definitions.empty() || isSpilled(variable))
			return false;

		// If the only definition is a stack store, the variable can't be spilled.
		if (variable->definitions.size() == 1) {
			InstructionPtr single_def = variable->definitions.begin()->lock();
			auto *store = dynamic_cast<StackStoreInstruction *>(single_def.get());
			if (store && store->variable == variable)
				return false;
		}

		for (std::weak_ptr<Instruction> weak_definition: variable->definitions) {
			InstructionPtr definition = weak_definition.lock();
			// Because ϕ-instructions are eventually removed after aliasing the variables, they don't count as a real
			// definition here.
			if (definition->isPhi())
				continue;

			bool created;
			const StackLocation &location = getSpill(variable, true, &created);
			auto store = std::make_shared<StackStoreInstruction>(location, variable);
			auto next = after(definition);
			bool should_insert = true;

			// Skip comments.
			while (next && dynamic_cast<Comment *>(next.get()) != nullptr)
				next = after(next);

			if (next) {
				auto other_store = std::dynamic_pointer_cast<StackStoreInstruction>(next);
				if (other_store && *other_store == *store)
					should_insert = false;
			}

			if (created) {
				// Undo addToStack
				// warn() << "Undo addToStack for " << *variable << "\n";
				if (location.width != -1) {
					stackSize -= location.width;
					spillSize -= location.width;
				}
				stack.erase(location.offset);
			}

			if (should_insert)
				return true;
		}

		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
			InstructionPtr &instruction = *iter;
#ifdef STRICT_READ_CHECK
			if (std::shared_ptr<Variable> read = instruction->doesRead(variable))
				if (instruction->canReplaceRead(read))
					return true;
#else
			if (instruction->read.count(variable) != 0 && instruction->canReplaceRead(variable))
				return true;
#endif
		}

		return false;
	}

	bool Function::isArgument(Variable::ID id) const {
		return Variable::isLess(id, getArity());
	}

	std::shared_ptr<Instruction> Function::firstInstruction(bool includeComments) {
		if (includeComments) {
			for (InstructionPtr &instruction: blocks.front()->instructions)
				if (!dynamic_cast<Label *>(instruction.get()))
					return instruction;
		} else {
			for (InstructionPtr &instruction: blocks.front()->instructions)
				if (!dynamic_cast<Label *>(instruction.get()) && !dynamic_cast<Comment *>(instruction.get()))
					return instruction;
		}
		return nullptr;
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

	InstructionPtr Function::insertAfter(InstructionPtr base, InstructionPtr new_instruction, bool reindex) {
		BasicBlockPtr block = base->parent.lock();
		if (!block) {
			std::cerr << "\e[31;1m!\e[0m " << base->debugExtra() << "\n";
			throw std::runtime_error("Couldn't lock instruction's parent block");
		}

		if (new_instruction->debugIndex == -1)
			new_instruction->debugIndex = base->debugIndex;

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

		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, bool reindex) {
		BasicBlockPtr block = base->parent.lock();
		if (!block) {
			error() << base->debugExtra() << "\n";
			throw std::runtime_error("Couldn't lock instruction's parent block");
		}

		if (new_instruction->debugIndex == -1)
			new_instruction->debugIndex = base->debugIndex;

		if (reindex)
			new_instruction->index = base->index + 1;
		new_instruction->parent = base->parent;

		auto linearIter = std::find(linearInstructions.begin(), linearInstructions.end(), base);
		auto blockIter = std::find(block->instructions.begin(), block->instructions.end(), base);
		linearInstructions.insert(linearIter, new_instruction);
		block->instructions.insert(blockIter, new_instruction);
		if (reindex)
			for (auto end = linearInstructions.end(); linearIter != end; ++linearIter)
				++(*linearIter)->index;
		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, const std::string &text,
	                            bool reindex) {
		insertBefore(base, new_instruction, false);
		comment(new_instruction, text, reindex);
		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, const char *text,
	                            bool reindex) {
		insertBefore(base, new_instruction, std::string(text), reindex);
		return new_instruction;
	}

	InstructionPtr Function::comment(InstructionPtr instruction, const std::string &text, bool reindex) {
#ifndef DISABLE_COMMENTS
		InstructionPtr comment = std::make_shared<Comment>(text);
		insertBefore(instruction, comment, reindex);
		return comment;
#else
		return nullptr;
#endif
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
						const std::string destination = branch->destination->substr(1);
						if (*next->label == destination)
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
		const std::string *label = newLabel();
#ifdef DEBUG_SPLIT
		std::cerr << "Splitting " << *block->label << " (" << block->instructions.size() << ") into " << *block->label
		          << " & " << *label << "\n";
#endif
		auto end = block->instructions.end();
		auto iter = std::find(block->instructions.begin(), end, instruction);
		if (iter == end) {
#ifdef DEBUGS_SPLIT
			warn() << "Can't split " << *block->label << ": instruction is at end of block\n";
#endif
			return nullptr;
		}

		BasicBlockPtr new_block = std::make_shared<BasicBlock>(label, std::vector<const std::string *> {block->label},
			std::list<InstructionPtr>());
		new_block->parent = this;
		bbLabels.insert(label);
		bbMap.emplace(label, new_block);

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
		BrUncondNode *node = new BrUncondNode("%" + *label);
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
			for (const std::string *&pred: block->preds) {
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
		const std::string *before_p_label = StringSet::intern("%" + *before->label);
		const std::string *after_p_label  = StringSet::intern("%" + *after->label);
		const std::string *before_label   = before->label;
		const std::string *after_label    = after->label;
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
		const std::string end = str.front() == '%'? str.substr(1) : str;
		// Some lambdas will have names like "@\"_ZZ11kernel_mainENK3$_0clEm\""
		if (1 < name->size() && (*name)[1] == '"')
			return "\"__" + name->substr(2, name->size() - 3) + "_label" + end + "\"";
		return "__" + name->substr(1) + "_label" + end;
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
						value->name = value->variable->id;
				}
			}

			if (Writer *writer = dynamic_cast<Writer *>(node)) {
				if (writer->variable)
					writer->result = writer->variable->id;
			}
		}
	}

	void Function::resetRegisters(bool respectful) {
		if (!respectful)
			for (const auto &[id, var]: variableStore)
				var->setRegisters({});
		else
			for (const auto &[id, var]: variableStore) {
				std::unordered_set<int> to_remove;
				for (const int reg: var->registers)
					if (!WhyInfo::isSpecialPurpose(reg))
						to_remove.insert(reg);
				for (const int reg: to_remove)
					var->registers.erase(reg);
			}
	}

	void Function::initialCompile() {
		extractBlocks();
		makeInitialDebugIndex();
		Passes::insertStackSkip(*this);
		Passes::fillLocalValues(*this);
		Passes::lowerStacksave(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract();
		Passes::trimBlocks(*this);
		Passes::splitBlocks(*this);
		Passes::copyArguments(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		Passes::replaceConstants(*this);
		Passes::lowerAlloca(*this);
		Passes::loadArguments(*this);
		Passes::ignoreIntrinsics(*this);
		Passes::lowerObjectsize(*this);
		Passes::lowerIcmp(*this);
		Passes::lowerMath(*this);
		Passes::lowerConversions(*this);
		Passes::lowerGetelementptr(*this);
		Passes::lowerFreeze(*this);
		Passes::lowerSelect(*this);
		Passes::lowerSwitch(*this);
		initialStackSize = stackSize;
		extractVariables();
		Passes::lowerStackrestore(*this);
		Passes::makeCFG(*this);
		Passes::lowerVarargsFirst(*this);
		Passes::lowerMemcpy(*this);
		Passes::lowerMemset(*this);
		Passes::setupCalls(*this);
		Passes::lowerMemory(*this);
		Passes::lowerInlineAsm(*this);
		Passes::lowerExtractvalue(*this);
		Passes::transformInstructions(*this);
		for (BasicBlockPtr &block: blocks)
			block->extract(true);
		extractVariables();
		Passes::coalescePhi(*this, true);
		computeLiveness();
		updateInstructionNodes();
		reindexBlocks();
		initialDone = true;
		// Coalesce ϕ-instructions a second time, removing them instead of only gently aliasing variables.
		Passes::coalescePhi(*this);
	}

	void Function::finalCompile() {
		Passes::readjustStackSkip(*this);
		Passes::updateArgumentLoads(*this, stackSize - initialStackSize);
		Passes::replaceStoresAndLoads(*this);
		Passes::lowerStack(*this);
		Passes::splitResultMoves(*this);
		Passes::finishMultireg(*this);
		Passes::removeRedundantMoves(*this);
		Passes::removeUselessBranches(*this);
		Passes::mergeAllBlocks(*this);
		Passes::insertLabels(*this);
		Passes::lowerBranches(*this);
		const bool naked = isNaked();
		if (!naked)
			Passes::insertPrologue(*this);
		Passes::loadArgumentsReadjust(*this);
		if (!naked)
			Passes::lowerRet(*this);
		Passes::lowerVarargsSecond(*this);
		Passes::removeUnreachable(*this);
		Passes::breakUpBigSets(*this);
		hackVariables();
		for (InstructionPtr &instruction: linearInstructions)
			if (instruction->debugIndex != -1) {
				auto lock = parent->getLock();
				parent->debugIndices.insert(instruction->debugIndex);
			}
		finalDone = true;
	}

	void Function::compile() {
		initialCompile();

#ifdef DEBUG_ALIASES
		debug();
#endif


#ifdef FN_CATCH_EXCEPTIONS
		try {
#endif
			while (allocator->attempt() != Allocator::Result::Success);
#ifdef FN_CATCH_EXCEPTIONS
		} catch (std::exception &err) {
			error() << err.what() << "\n";
			if (parent)
				LL2W::interactive(*parent, this);
			throw;
		}
#endif

		finalCompile();

#ifdef DEBUG_SPILL
		info() << "Total spills: \e[1m" << allocator->getSpillCount() << "\e[0m. Finished \e[1m" << *name
		       << "\e[0m.\n\n";
#endif
	}

	VariablePtr Function::makePrecoloredVariable(unsigned char index, BasicBlockPtr definer) {
		if (WhyInfo::totalRegisters <= index)
			throw std::invalid_argument("Index too high: " + std::to_string(index));
		VariablePtr new_var = newVariable(std::make_shared<IntType>(64), definer);
		new_var->setRegisters({index});
		return new_var;

	}

	VariablePtr Function::makeAssemblerVariable(unsigned char index, BasicBlockPtr definer) {
		if (WhyInfo::assemblerCount <= index)
			throw std::invalid_argument("Index too high for assembler-reserved registers: " + std::to_string(index));
		if (assemblerVariables.count(index) == 0)
			assemblerVariables.emplace(index, makePrecoloredVariable(WhyInfo::assemblerOffset + index, definer));
		VariablePtr &found = assemblerVariables.at(index);
		if (definer)
			found->addDefiner(definer);
		return found;
	}

	void Function::precolorArguments(std::list<Interval> &intervals) {
		if (getCallingConvention() == CallingConvention::Reg16) {
			const int max = std::min(16, getArity());
			int reg = WhyInfo::argumentOffset - 1;
			for (Interval &interval: intervals)
				// TODO: change to support non-numeric argument variables
				if (interval.variable.lock()->isLess(max))
					interval.setRegisters({++reg});
		}
	}

	void Function::precolorArguments() {
		if (getCallingConvention() == CallingConvention::Reg16) {
			const int max = std::min(16, getArity());
			int reg = WhyInfo::argumentOffset - 1;
			// TODO: change to support non-numeric argument variables
			for (int i = 0; i < max; ++i)
				variableStore.at(StringSet::intern(std::to_string(i)))->setRegisters({++reg});
		}
	}

	StackLocation & Function::addToStack(VariablePtr variable, StackLocation::Purpose purpose, int width) {
		for (auto &[offset, location]: stack)
			if (*location.variable == *variable && location.purpose == purpose)
				return location;

		if (width == -1) {
			width = !variable || !variable->type? 8 : Util::upalign(variable->type->width() < 8? 1 :
				variable->type->width() / 8, 8);
		}

		auto &added = stack.emplace(stackSize, StackLocation(this, variable, purpose, stackSize, width)).first->second;
		stackSize += width;
		if (purpose == StackLocation::Purpose::Spill)
			spillSize += width;
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

		for (auto &[id, var]: variableStore) {
			var->removeUse(instruction);
			var->removeDefinition(instruction);
		}
	}

	void Function::remove(BasicBlockPtr block) {
		blocks.remove(block);
	}

	void Function::replace(InstructionPtr to_replace, InstructionPtr substitute) {
		insertBefore(to_replace, substitute);
		remove(substitute);
	}

	VariablePtr Function::get64(std::shared_ptr<Instruction> before, unsigned long value, bool reindex) {
		VariablePtr var = newVariable(std::make_shared<IntType>(64), before->parent.lock());
		auto set = std::make_shared<SetInstruction>(var, int(value & 0xffffffff));
		auto lui = std::make_shared<LuiInstruction>(var, int(value >> 32));
		insertBefore(before, set, false)->setDebug(before->debugIndex)->extract();
		insertBefore(before, lui, false)->setDebug(before->debugIndex)->extract();
		if (reindex)
			reindexInstructions();
		return var;
	}

	VariablePtr Function::getVariable(Variable::ID id, bool add_arguments) {
		if (variableStore.count(id) != 0)
			return variableStore.at(id);
		else if (add_arguments && getCallingConvention() == CallingConvention::Reg16 && isArgument(id))
			return getVariable(id, arguments->at(Util::parseLong(id)).type, getEntry());
		return extraVariables.at(id);
	}

	VariablePtr Function::getVariable(const std::string &label) {
		return getVariable(StringSet::intern(label));
	}

	VariablePtr Function::getVariable(Variable::ID id, const TypePtr type, BasicBlockPtr definer) {
		const size_t vcount = variableStore.count(id), ecount = extraVariables.count(id);
		if (vcount == 0 && ecount == 0) {
			auto out =
				variableStore.emplace(id, std::make_shared<Variable>(id, type? type->copy() : nullptr)).first->second;
			if (definer)
				out->addDefiner(definer);
			return out;
		}
		VariablePtr out;
		if (ecount)
			out = extraVariables.at(id);
		else
			out = variableStore.at(id);
		if (definer)
			out->addDefiner(definer);
		return out;
	}

	VariablePtr Function::getVariable(const std::string &id, const TypePtr type, BasicBlockPtr definer) {
		return getVariable(StringSet::intern(id), type, definer);
	}

	BasicBlockPtr Function::getEntry() {
		return blocks.front();
	}

	CallingConvention Function::getCallingConvention() const {
		return isVariadic()? CallingConvention::StackOnly : CallingConvention::Reg16;
	}

	void Function::computeLiveness() {
		for (BasicBlockPtr &block: blocks) {
			block->extractPhi();
			block->extract();
			for (VariablePtr var: block->phiUses) {
				block->liveOut.insert(var);
				upAndMark(block, var);
			}
			for (VariablePtr var: block->nonPhiRead)
				upAndMark(block, var);
		}
	}

	void Function::upAndMark(BasicBlockPtr block, VariablePtr var) {
		for (const std::shared_ptr<const Instruction> instruction: block->instructions) {
			if (instruction->isPhi())
				continue;
			// if def(v) ∈ B (φ excluded) then return
			if (instruction->written.count(var) != 0)
				return;
		}

		// if v ∈ LiveIn(B) then return
		if (block->liveIn.count(var) != 0)
			return;

		// LiveIn(B) = LiveIn(B) ∪ {v}
		block->liveIn.insert(var);

		// if v ∈ PhiDefs(B) then return
		if (block->inPhiDefs(var))
			return;

		// for each P ∈ CFG_preds(B) do
		try {
			for (const Node *node: bbNodeMap.at(block.get())->in()) {
				BasicBlockPtr p = node->get<std::weak_ptr<BasicBlock>>().lock();
				// LiveOut(P) = LiveOut(P) ∪ {v}
				p->liveOut.insert(var);
				upAndMark(p, var);
			}
		} catch (std::out_of_range &) {
			std::cerr << "Couldn't find block " << *block->label << ".";
			for (const auto &pair: bbNodeMap)
				std::cerr << " " << *pair.first->label;
			std::cerr << "\n";
			debug();
			throw;
		}
	}

	void Function::resetLiveness() {
		for (BasicBlockPtr &block: blocks) {
			block->liveIn.clear();
			block->liveOut.clear();
		}
	}

	std::unordered_set<std::shared_ptr<BasicBlock>> Function::getLive(std::shared_ptr<Variable> var,
	std::function<std::unordered_set<std::shared_ptr<Variable>> &(const std::shared_ptr<BasicBlock> &)> getter) const {
		std::unordered_set<std::shared_ptr<BasicBlock>> out;
		const std::unordered_set<Variable *> &alias_pointers = var->getAliases();
		std::unordered_set<std::shared_ptr<Variable>> aliases;
		for (const auto &[id, subvar]: variableStore)
			if (alias_pointers.count(subvar.get()) != 0)
				aliases.insert(subvar);
		aliases.insert(var);
		for (const auto &alias: aliases)
			for (const auto &block: blocks)
				if (getter(block).count(alias) != 0)
					out.insert(block);
		return out;
	}

	std::unordered_set<std::shared_ptr<BasicBlock>> Function::getLiveIn(std::shared_ptr<Variable> var) const {
		return getLive(var, [&](const auto &block) -> auto & {
			return block->liveIn;
		});
	}

	std::unordered_set<std::shared_ptr<BasicBlock>> Function::getLiveOut(std::shared_ptr<Variable> var) const {
		return getLive(var, [&](const auto &block) -> auto & {
			return block->liveOut;
		});
	}

	std::string Function::toString() {
		std::stringstream out;
		out << *name << "\n";
		for (InstructionPtr &instruction: linearInstructions) {
#ifdef SPACE_COUNT
			out << std::string(' ', SPACE_COUNT);
#else
			out << "\t";
#endif
			out << instruction->toString();
			const int dbg = instruction->debugIndex;
			if (dbg != -1 && instruction->showDebug()) {
				auto lock = parent->getLock();
				if (parent->locations.count(dbg) != 0)
					out << " !" << parent->locations.at(dbg).index;
				else
					warn() << "Couldn't find location for !" << dbg << "\n";
			}
			out << "\n";
		}
		out << "\t: $rt\n";
		return out.str();
	}

	std::string Function::headerString() const {
		std::stringstream out;
		out << *returnType << " \e[35m" << *name << "\e[94m(\e[39m";
		for (auto begin = arguments->begin(), iter = begin, end = arguments->end(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << *iter->type;
			if (iter->name)
				out << " " << *iter->name;
		}
		out << "\e[94m)\e[0m";
		return out.str();
	}

	void Function::debug() {
		debug(
#ifdef DEBUG_BLOCKS
			true,
#else
			false,
#endif
#ifdef DEBUG_LINEAR
			true,
#else
			false,
#endif
#ifdef DEBUG_VARS
			true,
#else
			false,
#endif
#ifdef DEBUG_BLOCK_LIVENESS
			true,
#else
			false,
#endif
#ifdef DEBUG_READ_WRITTEN
			true,
#else
			false,
#endif
#ifdef DEBUG_VAR_LIVENESS
			true,
#else
			false,
#endif
#ifdef DEBUG_RENDER
			true,
#else
			false,
#endif
#ifdef DEBUG_ESTIMATIONS
			true,
#else
			false,
#endif
#ifdef DEBUG_ALIASES
			true,
#else
			false,
#endif
#ifdef DEBUG_STACK
			true
#else
			false
#endif
		);
	}

	void Function::debug(bool doBlocks, bool linear, bool vars, bool blockLiveness, bool readWritten, bool varLiveness,
	                     bool render, bool estimations, bool aliases, bool stack) {
		if (doBlocks || linear || vars)
			std::cerr << headerString() + " \e[94m{\e[39m\n";
		if (doBlocks) {
			for (const BasicBlockPtr &block: blocks) {
				std::cerr << "    \e[2m; \e[4m<label>:\e[1m" << *block->label << "\e[22;2;4m @ " << block->index
						<< ": preds =";
				for (auto begin = block->preds.begin(), iter = begin, end = block->preds.end(); iter != end; ++iter) {
					if (iter != begin)
						std::cerr << ",";
					std::cerr << " %" << **iter;
				}
				if (blockLiveness) {
					if (!block->liveIn.empty()) {
						std::cerr << "; live-in =";
						const auto &liveIn = block->liveIn;
						for (auto begin = liveIn.begin(), iter = begin, end = liveIn.end(); iter != end; ++iter) {
							if (iter != begin)
								std::cerr << ",";
							std::cerr << " %" << (*iter)->id;
						}
					}
					if (!block->liveOut.empty()) {
						std::cerr << "; live-out =";
						const auto &liveOut = block->liveOut;
						for (auto begin = liveOut.begin(), iter = begin, end = liveOut.end(); iter != end; ++iter) {
							if (iter != begin)
								std::cerr << ",";
							std::cerr << " %" << (*iter)->id;
						}
					}
				}
				std::cerr << "\e[22;24m\n";
				if (readWritten)
					for (const std::shared_ptr<Instruction> &instruction: block->instructions) {
						int read, written;
						std::tie(read, written) = instruction->extract();
						std::cerr << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written
						          << "\e[0m\n";
					}
				else
					for (const std::shared_ptr<Instruction> &instruction: block->instructions)
						std::cerr << "    " << instruction->debugExtra() << "\n";
				std::cerr << "\n";
			}
		}
		if (linear)
			for (const std::shared_ptr<Instruction> &instruction: linearInstructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cerr << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written << "\e[0m\n";
			}
		if (vars) {
			std::cerr << "    \e[2m; Variables:\e[0m\n";

			auto all_vars = variableStore;
			for (const auto &pair: extraVariables)
				all_vars.insert(pair);

			for (auto &[id, var]: all_vars) {
				if (extraVariables.count(id) != 0)
					std::cerr << "\e[31m[e]\e[39m";
				else
					std::cerr << "   ";
				std::cerr << " \e[2m; \e[1m%" << std::left << std::setw(2) << *id << "/" << *var->id << "/"
				          << *var->originalID << "\e[0;2m  defs (" << var->definitions.size() << ") =";
				for (const std::weak_ptr<BasicBlock> &def: var->definingBlocks)
					std::cerr << " \e[1;2m" << std::setw(2) << *def.lock()->label << "\e[0m";
				std::cerr << "  \e[0;2muses =";
				for (const std::weak_ptr<BasicBlock> &use: var->usingBlocks)
					std::cerr << " \e[1;2m" << std::setw(2) << *use.lock()->label << "\e[0m";
				const int spill_cost = var->spillCost();
				std::cerr << "\e[2m  cost = \e[1m" << (spill_cost == INT_MAX? "∞" : std::to_string(spill_cost))
				          << "\e[0;2m";
				if (var->definingBlocks.size() > 1)
					std::cerr << " (multiple defs)";
				std::cerr << "  pid = \e[1m" << *var->parentID() << "\e[22;2m";
				std::cerr << "  aliases =\e[1m";
				for (Variable *alias: var->getAliases())
					std::cerr << " " << *alias->id;
				std::cerr << "\e[0m\n";
				if (varLiveness) {
					std::cerr << "    \e[2m;      \e[32min  =\e[1m";
					for (const BasicBlockPtr &block: blocks) {
						if (block->isLiveIn(var))
							std::cerr << " %" << *block->label;
					}
					std::cerr << "\e[0m\n";
					std::cerr << "    \e[2m;      \e[31mout =\e[1m";
					for (const BasicBlockPtr &block: blocks) {
						if (block->isLiveOut(var))
							std::cerr << " %" << *block->label;
					}
					std::cerr << "\e[0m\n";
				}
			}
		}
		if (doBlocks || linear || vars)
			std::cerr << "\e[94m}\e[39m\n\n";
		if (aliases) {
			std::cerr << "<Aliases>\n";
			for (auto &[id, var]: variableStore) {
				std::cerr << *id << " = " << *var;
				if (auto vparent = var->getParent().lock())
					std::cerr << "(parent = " << *vparent << ")";
				std::cerr << ":";
				for (Variable *alias: var->getAliases())
					std::cerr << " " << *alias;
				std::cerr << "\n";
			}
			std::cerr << "</Aliases>\n";
		}
		if (render) {
			std::cerr << "Rendering.\n";
			if (estimations)
				for (Node *node: cfg.nodes()) {
					if (node->data.has_value()) {
						BasicBlockPtr bb = node->get<std::weak_ptr<BasicBlock>>().lock();
						if (bb)
							node->rename("\"" + node->label() + ":" + std::to_string(bb->estimatedExecutions) + "\"");
					}
				}
			cfg.renderTo("graph_" + *name + ".png");
			if (dTree.has_value())
				dTree->renderTo("graph_D_" + *name + ".png");
			if (djGraph.has_value())
				djGraph->renderTo("graph_DJ_" + *name + ".png");
		}
		if (stack)
			debugStack();
	}

	void Function::debugStack() const {
		for (const std::pair<const int, StackLocation> &pair: stack)
			std::cerr << pair.first << "[" << pair.second.width << "]:" << *pair.second.variable << " ";
		std::cerr << "\n";
	}

	bool Function::isNaked() const {
		const FunctionHeader *header = dynamic_cast<const FunctionHeader *>(astnode->children.front());
		if (header->fnattrs.count(FnAttr::naked) != 0)
			return true;
		if (!parent) {
			warn() << "Function::isNaked(): parent is null\n";
			return false;
		}
		if (header->fnattrsIndex == -1)
			return false;
		auto lock = parent->getLock();
		return parent->fnattrs.at(header->fnattrsIndex).count(FnAttr::naked) != 0;
	}

	StackLocation & Function::getSpill(VariablePtr variable, bool create, bool *created) {
		if (created)
			*created = false;
		for (std::pair<const int, StackLocation> &pair: stack)
			if (pair.second.variable->id == variable->id && pair.second.purpose == StackLocation::Purpose::Spill)
				return pair.second;
		if (create) {
			if (created)
				*created = true;
			return addToStack(variable, StackLocation::Purpose::Spill);
		}
		throw std::out_of_range("Couldn't find a spill location for " + variable->plainString());
	}

	std::shared_ptr<LocalValue> Function::replaceGetelementptrValue(std::shared_ptr<GetelementptrValue> gep,
	InstructionPtr instruction) {
		TypePtr out_type;

		const std::list<long> indices = Getelementptr::getIndices(*gep);

		const long offset = Util::updiv(Getelementptr::compute(gep->ptrType, indices, &out_type), 8l);
		if (Util::outOfRange(offset))
			warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';

		switch (gep->variable->valueType()) {
			case ValueType::Global: {
				VariablePtr var1(newVariable(std::make_shared<IntType>(32))), var2(newVariable(out_type));
				auto set =
					std::make_shared<SetInstruction>(var1, dynamic_cast<GlobalValue *>(gep->variable.get())->name);
				auto addi = std::make_shared<AddIInstruction>(var1, int(offset), var2);
				insertBefore(instruction, set);
				insertBefore(instruction, addi);
				set->extract();
				addi->extract();
				return std::make_shared<LocalValue>(var2);
			}
			case ValueType::Local: {
				VariablePtr new_var(newVariable(out_type));
				auto addi = std::make_shared<AddIInstruction>(
					dynamic_cast<LocalValue *>(gep->variable.get())->getVariable(*this), int(offset), new_var);
				insertBefore(instruction, addi);
				addi->extract();
				return std::make_shared<LocalValue>(new_var);
			}
			default:;
		}

		if (gep->variable->isIntLike()) {
			VariablePtr new_var(newVariable(out_type));
			auto set = std::make_shared<SetInstruction>(new_var, gep->variable->intValue() + int(offset));
			insertBefore(instruction, set);
			set->extract();
			return std::make_shared<LocalValue>(new_var);
		}

		throw std::invalid_argument("Expected a global, local or intlike value in Function::replaceGetelementptrValue");
	}

	void Function::hackVariables() {
		std::list<VariablePtr> all_vars;
		for (auto &pair: extraVariables)
			all_vars.push_back(pair.second);
		for (auto &pair: variableStore)
			all_vars.push_back(pair.second);
		for (VariablePtr &var: all_vars) {
			auto var_parent = var->getParent().lock();
			if (var->registers.empty() && var_parent)
				var->registers = var_parent->registers;
			if (var->registers.empty()) {
				for (Variable *alias: var->getAliases())
					if (!alias->registers.empty()) {
						var->registers = alias->registers;
						break;
					}
				// As a last resort, if this variable *still* has no register assigned, check all other known variables
				// for a variable with the same id and try to absorb its register assignment.
				if (var->registers.empty()) {
					for (VariablePtr &other: all_vars)
						if (other != var && other->id == var->id && !other->registers.empty()) {
							var->registers = other->registers;
							break;
						}
					if (var->registers.empty())
						std::cerr << "hackVariables: last resort failed\n";
				}
			} else
				for (Variable *alias: var->getAliases())
					if (alias->registers.empty())
						alias->registers = var->registers;
		}
	}

	Graph Function::makeDependencyGraph() const {
		Graph dependencies;
		for (const auto &[id, var]: variableStore)
			dependencies.addNode(*var->originalID).data = var.get();
		for (const auto &[id, var]: variableStore) {
			for (Variable *phi_parent: var->phiParents)
				dependencies[*phi_parent->originalID].link(dependencies[*var->originalID], true);
			for (Variable *child: var->phiChildren)
				dependencies[*var->originalID].link(dependencies[*child->originalID], true);
		}
		return dependencies;
	}

	void Function::makeInitialDebugIndex() {
		if (!parent)
			throw std::runtime_error("Function " + *name + " is missing a parent");
		if (debugIndex == -1) // TODO: verify
			return;
		auto lock = parent->getLock();
		initialDebugIndex = parent->newDebugIndex();
		Subprogram &subprogram = parent->subprograms.at(debugIndex);
		Location location(subprogram.line, 1, debugIndex);
		location.file = subprogram.file;
		parent->locations.emplace(initialDebugIndex, location);
	}

	VariablePtr Function::mx(unsigned char index, BasicBlockPtr block) {
		return makeAssemblerVariable(index, block);
	}

	VariablePtr Function::mx(unsigned char index, InstructionPtr instruction) {
		return mx(index, instruction->parent.lock());
	}

	VariablePtr Function::ax(unsigned char index, BasicBlockPtr block) {
		return makePrecoloredVariable(WhyInfo::argumentOffset + index, block);
	}

	VariablePtr Function::ax(unsigned char index, InstructionPtr instruction) {
		return ax(index, instruction->parent.lock());
	}

	VariablePtr Function::m0(BasicBlockPtr block) {
		return mx(0, block);
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
