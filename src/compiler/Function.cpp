// #define USE_LINEAR_SCAN
#define DEBUG_BLOCKS
// #define DEBUG_LINEAR
#define DEBUG_VARS
// #define DEBUG_RENDER
// #define DEBUG_SPILL
#define DEBUG_SPLIT
#define DEBUG_READ_WRITTEN
// #define DISABLE_COMMENTS
// #define DEBUG_ESTIMATIONS
#define DEBUG_BLOCK_LIVENESS
#define DEBUG_VAR_LIVENESS
// #define DEBUG_ALIASES
#define DEBUG_STACK
// #define DEBUG_LABELS
// #define STRICT_READ_CHECK
// #define STRICT_WRITTEN_CHECK
// #define FN_CATCH_EXCEPTIONS
#define MOVE_PHI // Insert moves instead of coalescing ϕ-instructions.
// #define MERGE_SET_LIVENESS // Whether to use the slow and possibly badly implemented merge set method for liveness.
// #define TRADITIONAL_LIVENESS // Whether to calculate liveness using a traditional, non-SSA algorithm.

#include "allocator/ColoringAllocator.h"
#include "allocator/LinearScanAllocator.h"
#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "exception/NoChoiceError.h"
#include "instruction/AddIInstruction.h"
#include "instruction/Clobber.h"
#include "instruction/Comment.h"
#include "instruction/Label.h"
#include "instruction/LuiInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "main.h"
#include "options.h"
#include "parser/ASTNode.h"
#include "parser/FunctionArgs.h"
#include "parser/FunctionHeader.h"
#include "pass/BreakUpBigSets.h"
#include "pass/CopyArguments.h"
#include "pass/DiscardUnusedVars.h"
#include "pass/ExtractTypes.h"
#include "pass/FillLocalValues.h"
#include "pass/FinishMultireg.h"
#include "pass/FixSignedness.h"
#include "pass/IgnoreIntrinsics.h"
#include "pass/InsertLabels.h"
#include "pass/InsertPrologue.h"
#include "pass/LoadArguments.h"
#include "pass/LowerAlloca.h"
#include "pass/LowerBranches.h"
#include "pass/LowerClobber.h"
#include "pass/LowerConversions.h"
#include "pass/LowerExtractvalue.h"
#include "pass/LowerFreeze.h"
#include "pass/LowerGetelementptr.h"
#include "pass/LowerIcmp.h"
#include "pass/LowerInlineAsm.h"
#include "pass/LowerInsertvalue.h"
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
#include "pass/MinimizeBlocks.h"
#include "pass/Phi.h"
#include "pass/RemoveRedundantMoves.h"
#include "pass/RemoveUnreachable.h"
#include "pass/RemoveUselessBranches.h"
#include "pass/ReplaceConstants.h"
#include "pass/ReplaceStoresAndLoads.h"
#include "pass/SetupCalls.h"
#include "pass/SignChars.h"
#include "pass/SplitBlocks.h"
#include "pass/SplitResultMoves.h"
#include "pass/StackSkip.h"
#include "pass/TransformInstructions.h"
#include "pass/TransformLabels.h"
#include "pass/TrimBlocks.h"
#include "pass/UpdateArgumentLoads.h"
#include "util/CompilerUtil.h"
#include "util/strnatcmp.h"
#include "util/Timer.h"
#include "util/Util.h"
#include "Interactive.h"

#include <llvm/IR/CFG.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_os_ostream.h>

#include <climits>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <print>
#include <unistd.h>

namespace LL2W {
	Function::Function(Program &program, const ASTNode &node): parent(program) {
		name = node.lexerInfo;
		FunctionHeader *header = dynamic_cast<FunctionHeader *>(node.front());
		if (!header) {
			throw std::runtime_error("header is null in Function::Function");
		}
		argumentsNode = header->arguments;
		arguments = &argumentsNode->arguments;
		astnode = &node;
		returnType = header->returnType;
#ifdef USE_LINEAR_SCAN
		allocator = new LinearScanAllocator(*this);
#else
		allocator = new ColoringAllocator(*this);
#endif
		debugIndex = header->debugIndex;
	}

	Function::Function(Program &program, llvm::Function *function):
		llvmFunction(function),
		parent(program) {
			name = StringSet::intern('@' + function->getName().str());
			variadic = function->isVarArg();
			arguments = new std::vector<FunctionArgument>;
			for (const llvm::Argument &argument: function->args()) {
				llvm::Type *type = argument.getType();
				if (type->isMetadataTy()) {
					continue;
				}
				arguments->emplace_back(LL2W::Type::fromLLVM(*type), argument.getName().str());
			}
			returnType = LL2W::Type::fromLLVM(*function->getReturnType());
#ifdef USE_LINEAR_SCAN
			allocator = new LinearScanAllocator(*this);
#else
			allocator = new ColoringAllocator(*this);
#endif
		}

	Function::~Function() {
		if (allocator) {
			delete allocator;
		}
	}

	Allocator::Result Function::attemptAllocation() {
		if ((lastAllocationResult = allocator->attempt()) == Allocator::Result::Success) {
			allocationDone = true;
		}
		return lastAllocationResult;
	}

	Function::Type Function::analyze(ValuePtr *value_out, long *simple_index_out) {
		global_function_name = name;
		extractBlocks();
		Passes::ignoreIntrinsics(*this);
		if (linearInstructions.size() == 1) {
			Timer timer{"InnerAnalysis"};
			const auto &only = linearInstructions.front();
			if (const auto *llvm = dynamic_cast<const LLVMInstruction *>(only.get())) {
				if (const auto *ret = dynamic_cast<const RetNode *>(llvm->getNode())) {
					switch (ret->value->valueType()) {
						case ValueType::Void:
							// info() << "Useless: " << *name << '\n';
							return analyzedType = Type::Useless;
						case ValueType::Int:
						case ValueType::Undef:
						case ValueType::Null:
						case ValueType::Bool:
						case ValueType::Global:
						case ValueType::Double:
							// info() << "Constant: " << *name << " (" << *ret->value << ")\n";
							if (value_out) {
								*value_out = ret->value;
							}
							return analyzedType = Type::Constant;
						case ValueType::Local: {
							const Variable::ID pvar = dynamic_cast<const LocalValue *>(ret->value.get())->name;
							if (isArgument(pvar)) {
								if (simple_index_out) {
									if (!Util::isNumeric(std::string_view(*pvar).substr(1))) {
										warn() << "Argument pvar isn't numeric; not classifying function as simple: " << *pvar << '\n';
										break;
									}
									*simple_index_out = Util::parseLong(pvar);
									// info() << "Simple: " << *name << " (" << *simple_index_out << ")\n";
								} // else info() << "Simple: " << *name << '\n';
								return analyzedType = Type::Simple;
							} else {
								info() << "Not simple: " << *name << '\n';
							}
							break;
						}
						default:
							break;
					}
				}
			}
		}

		return analyzedType = Type::Complex;
	}

	void Function::extractBlocks() {
		if (astnode) {
			extractBlocksASTNode();
		} else {
			extractBlocksLLVM();
		}
	}

	void Function::extractBlocksLLVM() {
		assert(llvmFunction != nullptr);
		Timer timer{"ExtractBlocksLLVM"};

		linearInstructions.clear();
		bbLabels.clear();
		bbMap.clear();
		blocks.clear();

		int block_index = -1;
		int instruction_index = -1;

		for (llvm::BasicBlock &block: *llvmFunction) {
			const std::string *label = StringSet::intern(getOperandName(block));

			std::list<InstructionPtr> instructions;
			{
				Timer timer{"InstructionCreationLoop"};
				for (llvm::Instruction &instruction: block) {
					auto llvm = std::make_shared<LLVMInstruction>(InstructionNode::fromLLVM(&instruction), ++instruction_index, true);
					instructions.push_back(llvm);
					linearInstructions.push_back(std::move(llvm));
				}
			}

			std::vector<const std::string *> preds;

			for (const llvm::BasicBlock *predecessor: llvm::predecessors(&block)) {
				preds.emplace_back(StringSet::intern(getOperandName(*predecessor)));
			}

			BasicBlockPtr new_block = blocks.emplace_back(std::make_shared<BasicBlock>(label, std::move(preds), std::move(instructions)));
			new_block->parent = this;
			new_block->index = ++block_index;
			bbLabels.insert(new_block->getLabel());
			bbMap.emplace(new_block->getLabel(), new_block);

			{
				Timer timer{"InstructionExtractionLoop"};
				for (const InstructionPtr &instruction: new_block->instructions) {
					instruction->parent = new_block;
					instruction->extract();
					for (const std::unordered_set<VariablePtr> *variables: {&instruction->read, &instruction->written}) {
						for (VariablePtr vptr: *variables) {
							variableStore.insert({vptr->id, vptr});
						}
					}
				}
			}
		}
	}

	void Function::extractBlocksASTNode() {
		assert(astnode != nullptr);
		const std::string *label = StringSet::intern(std::to_string(arguments->size()));
		std::vector<const std::string *> preds;
		std::list<std::shared_ptr<Instruction>> instructions;
		int offset = 0;
		int instruction_index = -1;
		int block_index = -1;
		linearInstructions.clear();
		bbLabels.clear();
		bbMap.clear();
		blocks.clear();

		std::function<void(BasicBlockPtr)> finishBlock = [&](BasicBlockPtr block) {
			block->offset = offset;
			block->parent = this;
			block->index = ++block_index;
			bbLabels.insert(block->getLabel());
			bbMap.emplace(block->getLabel(), block);
			for (std::shared_ptr<Instruction> &instruction: instructions) {
				instruction->parent = block;
				instruction->extract();
				for (const std::unordered_set<VariablePtr> *variables: {&instruction->read, &instruction->written}) {
					for (VariablePtr vptr: *variables) {
						variableStore.insert({vptr->id, vptr});
					}
				}
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
				if (!header) {
					throw std::runtime_error("header is null in Function::extractBlocks");
				}
				label = header->label;
				preds = header->preds;
			} else if (InstructionNode *instruction = dynamic_cast<InstructionNode *>(child)) {
				instructions.push_back(std::make_shared<LLVMInstruction>(instruction, ++instruction_index));
				linearInstructions.push_back(instructions.back());
			}
		}

		if (!instructions.empty()) {
			blocks.push_back(std::make_shared<BasicBlock>(label, preds, instructions));
			finishBlock(blocks.back());
		}
	}

	BasicBlockPtr Function::getBlock(const std::string *label, bool can_throw) const {
		if (!bbMap.contains(label)) {
			if (can_throw) {
				std::cerr << "Want: " << *label << '\n';
				for (const auto &[bname, block]: bbMap) {
					std::cerr << "- " << *bname << '\n';
				}
				throw std::runtime_error("Couldn't find block " + *label + " in function " + *name);
			}
			return nullptr;
		}
		return bbMap.at(label);
	}

	void Function::extractVariables(bool reset) {
		Timer timer{"ExtractVariables"};
		if (reset) {
			for (auto &map: {variableStore, extraVariables}) {
				for (const auto &[id, var]: map) {
					var->setUsingBlocks({});
					var->setDefiningBlocks({});
					var->setDefinitions({});
					var->setUses({});
					var->setLastUse({});
				}
			}
		}

		for (BasicBlockPtr &block: blocks) {
			for (VariablePtr read_var: block->read) {
				read_var->addUsingBlock(block);
			}
			for (VariablePtr written_var: block->written) {
				written_var->addDefiner(block);
			}
			for (std::shared_ptr<Instruction> &instruction: block->instructions) {
				for (VariablePtr read_var: instruction->read) {
					read_var->setLastUse(instruction);
					read_var->addUse(instruction);
				}
				for (VariablePtr written_var: instruction->written)
					written_var->addDefinition(instruction);
			}
		}

		for (auto &map: {variableStore, extraVariables}) {
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
	}

	void Function::extractInstructions(bool force) {
		for (const InstructionPtr &instruction: linearInstructions) {
			instruction->extract(force);
		}
	}

	void Function::relinearize() {
		Timer timer{"Relinearize"};
		linearInstructions.clear();
		int index = -1;
		for (BasicBlockPtr &block: blocks) {
			for (InstructionPtr &instruction: block->instructions) {
				instruction->index = ++index;
				linearInstructions.push_back(instruction);
			}
		}
	}

	Variable::ID Function::newLabel() {
		auto *out = StringSet::intern("%#" + std::to_string(++lastArtificialLabel));
		// if (*out == "%#190") {
		// 	raise(SIGTRAP);
		// }
		return out;
	}

	VariablePtr Function::newVariable(const TypePtr &type, const BasicBlockPtr &definer) {
		if (variableFreeze) {
			throw std::logic_error("Can't call Function::newVariable when variableFreeze is true");
		}
		if (!type) {
			throw std::invalid_argument("Can't call Function::newVariable with a null type");
		}
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
			throw std::runtime_error("Can't spill variable: no definitions");
		}

		const StackLocation &location = getSpill(variable, true);

		for (std::weak_ptr<Instruction> weak_definition: variable->definitions) {
			InstructionPtr definition = weak_definition.lock();
			// Because ϕ-instructions are eventually removed after aliasing the variables, they don't count as a real
			// definition here.
			if (definition->isPhi()) {
				continue;
			}
#ifdef DEBUG_SPILL
			std::cerr << "  Trying to spill " << *variable << " (definition: " << definition->debugExtra() << " at " << definition->index << ", OID: " << variable->originalID << ")\n";
#endif
			auto store = std::make_shared<StackStoreInstruction>(location, variable);
			auto next = after(definition);
			bool should_insert = true;

			// Skip comments.
			while (next && dynamic_cast<Comment *>(next.get()) != nullptr) {
				next = after(next);
			}

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
				insertBefore(store, std::make_shared<Comment>("Spill: stack store for " + variable->plainString() + " into location=" + std::to_string(location.offset)));
				VariablePtr m6 = mx(6, definition);
				definition->replaceWritten(variable, m6);
				definition->extract();
				store->variable = m6;
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
		if (!out) {
			std::cerr << "  No stores inserted for " << *variable << ".\n";
		}
#endif

		if (doDebug) {
			debug();
		}

		std::vector<VariablePtr> new_variables;
		new_variables.reserve(32);

		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
#ifdef STRICT_READ_CHECK
			if (VariablePtr read = (*iter)->doesRead(variable)) {
#else
			if ((*iter)->read.contains(variable)) {
#endif
				InstructionPtr instruction = *iter;
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
				if (par) {
					std::cerr << " in block " << *par->label;
				}
				if (replaced) {
					std::cerr << " (now " << instruction->debugExtra() << ")";
				}
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
				std::cerr << "      Inserting a stack load before " << instruction->debugExtra() << ": " << load->debugExtra() << "\n";
#endif
					markSpilled(new_var);
					new_variables.emplace_back(std::move(new_var));
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
		for (BasicBlockPtr &block: blocks) {
			block->extract(true);
		}
		extractVariables(true); // Reset stale use/define data.
		computeLiveness();
		markSpilled(variable);
		allocator->afterSpill(variable, new_variables);
		return out;
	}

	void Function::markSpilled(VariablePtr variable) {
		spilledVariables.insert(variable->originalID);
	}

	bool Function::isSpilled(VariablePtr variable) const {
		return spilledVariables.contains(variable->originalID);
	}

	bool Function::canSpill(VariablePtr variable) {
		if (variable->definitions.empty() || isSpilled(variable)) {
			return false;
		}

		// If the only definition is a stack store, the variable can't be spilled.
		if (variable->definitions.size() == 1) {
			InstructionPtr single_def = variable->definitions.begin()->lock();
			auto *store = dynamic_cast<StackStoreInstruction *>(single_def.get());
			if (store && store->variable == variable) {
				return false;
			}
		}

		for (std::weak_ptr<Instruction> weak_definition: variable->definitions) {
			InstructionPtr definition = weak_definition.lock();
			// Because ϕ-instructions are eventually removed after aliasing the variables, they don't count as a real
			// definition here.
			if (definition->isPhi()) {
				continue;
			}

			bool created;
			const StackLocation &location = getSpill(variable, true, &created);
			auto store = std::make_shared<StackStoreInstruction>(location, variable);
			auto next = after(definition);
			bool should_insert = true;

			// Skip comments.
			while (next && dynamic_cast<Comment *>(next.get()) != nullptr) {
				next = after(next);
			}

			if (next) {
				auto other_store = std::dynamic_pointer_cast<StackStoreInstruction>(next);
				if (other_store && *other_store == *store) {
					should_insert = false;
				}
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

			if (should_insert) {
				return true;
			}
		}

		for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
			InstructionPtr &instruction = *iter;
#ifdef STRICT_READ_CHECK
			if (VariablePtr read = instruction->doesRead(variable)) {
				if (instruction->canReplaceRead(read)) {
					return true;
				}
			}
#else
			if (instruction->read.contains(variable) && instruction->canReplaceRead(variable)) {
				return true;
			}
#endif
		}

		return false;
	}

	bool Function::isArgument(Variable::ID id) const {
		return Variable::isLess(id, getArity());
	}

	std::shared_ptr<Instruction> Function::firstInstruction(bool includeComments) {
		if (includeComments) {
			for (InstructionPtr &instruction: blocks.front()->instructions) {
				if (!dynamic_cast<Label *>(instruction.get())) {
					return instruction;
				}
			}
		} else {
			for (InstructionPtr &instruction: blocks.front()->instructions) {
				if (!dynamic_cast<Label *>(instruction.get()) && !dynamic_cast<Comment *>(instruction.get())) {
					return instruction;
				}
			}
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

		if (new_instruction->debugIndex == -1) {
			new_instruction->debugIndex = base->debugIndex;
		}

		if (reindex) {
			// There used to be a + 1 here, but I removed it because I believe it gets incremented in the loop shortly
			// before the end of this function anyway.
			new_instruction->index = base->index;
		}

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
				for (auto end = linearInstructions.end(); iter != end; ++iter) {
					++(*iter)->index;
				}
			}
		}

		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, bool reindex, bool linear_warn, bool *should_relinearize_out) {
		assert(base != nullptr);
		BasicBlockPtr block = base->parent.lock();
		if (!block) {
			error() << base->debugExtra() << "\n";
			throw std::runtime_error("Couldn't lock instruction's parent block");
		}

		if (block->parent != this) {
			throw std::runtime_error("Block parent isn't equal to this in Function::insertBefore");
		}

		if (new_instruction->debugIndex == -1) {
			new_instruction->debugIndex = base->debugIndex;
		}

		new_instruction->parent = base->parent;

		auto linearIter = std::find(linearInstructions.begin(), linearInstructions.end(), base);
		if (linear_warn && linearIter == linearInstructions.end()) {
			warn() << "Couldn't find instruction in linearInstructions in " << *name << ": " << base->debugExtra() << '\n';
			throw std::runtime_error("Couldn't find instruction in linearInstructions in " + *name);
		}
		auto blockIter = std::find(block->instructions.begin(), block->instructions.end(), base);
		if (blockIter == block->instructions.end()) {
			warn() << "Couldn't find instruction in block " << *block->getLabel() << " of function " << *name << ": " << base->debugExtra() << '\n';
			std::cerr << "Index: " << block->index << '\n';
			for (const auto &subblock: blocks) {
				std::cerr << *subblock->getLabel() << '[' << subblock->index << "] ";
			}
			if (block->instructions.empty()) {
				std::cerr << "\nInstruction list is empty.\n";
			} else {
				std::cerr << "\nInstruction list:\n";
				for (const auto &block_instruction: block->instructions) {
					std::cerr << "    " << block_instruction->debugExtra() << '\n';
				}
			}
			cfg.renderTo("inf_cfg.png");
			throw std::runtime_error("Instruction not found in block");
		}

		const bool can_insert_linear = linearIter != linearInstructions.end();
		if (can_insert_linear) {
			linearInstructions.insert(linearIter, new_instruction);
			if (should_relinearize_out != nullptr) {
				*should_relinearize_out = false;
			}
		} else if (should_relinearize_out != nullptr) {
			*should_relinearize_out = true;
		}

		block->instructions.insert(blockIter, new_instruction);

		if (reindex && can_insert_linear) {
			new_instruction->index = base->index;
			for (auto end = linearInstructions.end(); linearIter != end; ++linearIter) {
				++(*linearIter)->index;
			}
		}

		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, const std::string &text, bool reindex) {
		insertBefore(base, new_instruction, false);
		comment(new_instruction, text, reindex);
		return new_instruction;
	}

	InstructionPtr Function::insertBefore(InstructionPtr base, InstructionPtr new_instruction, const char *text, bool reindex) {
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
		if (block->instructions.empty()) {
			return;
		}

		InstructionPtr &back = block->instructions.back();

		if (LLVMInstruction *llback = dynamic_cast<LLVMInstruction *>(back.get())) {
			if (llback->getNodeType() == NodeType::BrUncond) {
				if (const BrUncondNode *branch = dynamic_cast<BrUncondNode *>(llback->getNode())) {
					BasicBlockPtr next = after(block);
					if (next) {
						const std::string destination = branch->destination->substr(1);
						if (*next->getLabel() == destination) {
							remove(back);
						}
					}
				} else {
					throw std::runtime_error("branch is null in Function::removeUselessBranch");
				}
			}
		}
	}

	void Function::reindexInstructions() {
		int index = -1;
		for (const InstructionPtr &instruction: linearInstructions) {
			instruction->index = ++index;
		}
	}

	void Function::reindexBlocks() {
		int index = -1;
		for (const BasicBlockPtr &block: blocks) {
			block->index = ++index;
		}
	}

	BasicBlockPtr Function::splitBlock(BasicBlockPtr block, InstructionPtr instruction) {
		Timer timer{"SplitBlock"};
		const std::string *label = newLabel();
#ifdef DEBUG_SPLIT
		std::cerr << "Splitting " << *block->getLabel() << " (" << block->instructions.size() << ") into " << *block->getLabel() << " & " << *label << "\n";
#endif
		auto end = block->instructions.end();
		auto iter = std::find(block->instructions.begin(), end, instruction);
		if (iter == end) {
#ifdef DEBUG_SPLIT
			warn() << "Can't split " << *block->getLabel() << ": instruction is at end of block\n";
#endif
			return nullptr;
		}

		BasicBlockPtr new_block = std::make_shared<BasicBlock>(label, std::vector<const std::string *>{block->getLabel()}, std::list<InstructionPtr>());
		new_block->parent = this;
		bbLabels.insert(label);
		bbMap.emplace(label, new_block);

		for (++iter; iter != end;) {
			for (const VariablePtr &var: (*iter)->written) {
				var->removeDefiner(block);
				var->addDefiner(new_block);
			}

			// TODO(typed): verify whether this is needed
			for (const VariablePtr &var: (*iter)->read) {
				var->removeUsingBlock(block);
				var->addUsingBlock(new_block);
			}

			(*iter)->parent = new_block;
			new_block->instructions.push_back(*iter);
			block->instructions.erase(iter++);
		}

		// Replace the old label with the new label in the preds of all basic blocks.
		for (const BasicBlockPtr &possible_successor: blocks) {
			auto predIter = std::find(possible_successor->preds.begin(), possible_successor->preds.end(), block->getLabel());
			if (predIter != possible_successor->preds.end()) {
				*predIter = label;
			}
		}

		// Insert the new block after the original block.
		auto blockIter = std::find(blocks.begin(), blocks.end(), block);
		++blockIter;
		blocks.insert(blockIter, new_block);

		// Add an unconditional branch from the original block to the new block.
		BrUncondNode *node = new BrUncondNode(*label);
		std::shared_ptr<LLVMInstruction> branch = std::make_shared<LLVMInstruction>(node, -1, true);
		branch->parent = block;
		block->instructions.push_back(branch);
		iter = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		if (iter == linearInstructions.end()) {
			warn() << "Couldn't find instruction in Function::splitBlock: " << instruction->debugExtra() << '\n';
		}
		++iter;
		linearInstructions.insert(iter, branch);

		// We need to update ϕ-instructions.
		for (auto &possible_llvm: linearInstructions) {
			auto *llvm = dynamic_cast<LLVMInstruction *>(possible_llvm.get());
			if (llvm == nullptr || llvm->getNodeType() != NodeType::Phi) {
				continue;
			}
			auto *phi = dynamic_cast<PhiNode *>(llvm->getNode());
			for (auto &[value, phi_label]: phi->pairs) {
				if (phi_label == block->getLabel()) {
					phi_label = label;
				}
			}
		}

		block->extract(true);
		new_block->extract();

		reindexInstructions();
		return new_block;
	}

	void Function::mergeBlocks(BasicBlockPtr before, BasicBlockPtr after) {
		// Update the preds of all the blocks by replacing the after-block's label with the before-block's.
		for (const BasicBlockPtr &block: blocks) {
			for (const std::string *&pred: block->preds) {
				if (pred == after->getLabel()) {
					pred = before->getLabel();
				}
			}
		}

		// Move all instructions from the after-block to the before-block.
		for (const InstructionPtr &instruction: after->instructions) {
			before->instructions.push_back(instruction);
			instruction->parent = before;
		}

		after->instructions.clear();

		// Replace the after-block's label with the before-block's in all instructions.
		// TODO: When Why branches are implemented, add them here.
		const std::string *before_label = before->getLabel();
		const std::string *after_label  = after->getLabel();
		for (const InstructionPtr &instruction: linearInstructions) {
			if (BrUncondNode *branch = CompilerUtil::brUncondCast(instruction)) {
				if (branch->destination == after_label) {
					branch->destination = before_label;
				}
			} else if (BrCondNode *branch = CompilerUtil::brCondCast(instruction)) {
				if (branch->ifTrue == after_label) {
					branch->ifTrue = before_label;
				}
				if (branch->ifFalse == after_label) {
					branch->ifFalse = before_label;
				}
			} else if (SwitchNode *sw = CompilerUtil::switchCast(instruction)) {
				if (sw->label == after_label) {
					sw->label = before_label;
				}
				for (std::tuple<TypePtr, ValuePtr, const std::string *> &tuple: sw->table) {
					if (std::get<2>(tuple) == after_label) {
						std::get<2>(tuple) = before_label;
					}
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
		return argumentsNode? argumentsNode->ellipsis : variadic && *variadic;
	}

	std::string Function::transformLabel(const std::string &str) const {
		std::string_view end(str);
		if (end.front() == '%') {
			end.remove_prefix(1);
		}
		// Some lambdas will have names like "@\"_ZZ11kernel_mainENK3$_0clEm\""
		std::string_view name_view(*name);
		if (1 < name->size() && (*name)[1] == '"') {
			return std::format("\"__{}_label{}\"", name_view.substr(2, name_view.size() - 3), end);
		}
		return std::format("__{}_label{}", name_view.substr(1), end);
	}

	void Function::updateInstructionNodes() {
		Timer timer{"UpdateInstructionNodes"};
		for (const InstructionPtr &instruction: linearInstructions) {
			auto *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm) {
				continue;
			}

			InstructionNode *node = llvm->getNode();
			if (auto *reader = dynamic_cast<Reader *>(node)) {
				for (const std::shared_ptr<LocalValue> &value: reader->allLocals()) {
					if (value->variable) {
						value->name = value->variable->id;
					}
				}
			}

			if (auto *writer = dynamic_cast<Writer *>(node)) {
				if (writer->variable) {
					writer->result = writer->variable->id;
				}
			}
		}
	}

	void Function::resetRegisters(bool respectful) {
		if (!respectful) {
			for (const auto &[id, var]: variableStore) {
				var->setRegisters({});
			}
		} else {
			for (const auto &[id, var]: variableStore) {
				std::unordered_set<int> to_remove;
				for (const int reg: var->registers) {
					if (!WhyInfo::isSpecialPurpose(reg)) {
						to_remove.insert(reg);
					}
				}
				for (const int reg: to_remove) {
					var->registers.erase(reg);
				}
			}
		}
	}

	void Function::initialCompile() {
		Timer timer{"InitialCompile"};
		extractBlocks();
		makeInitialDebugIndex();
		Passes::ignoreIntrinsics(*this);
		Passes::insertStackSkip(*this);
		Passes::fillLocalValues(*this);
		Passes::lowerStacksave(*this);
		for (BasicBlockPtr &block: blocks) {
			block->extract();
		}
		Passes::trimBlocks(*this);
		Passes::splitBlocks(*this);
		Passes::copyArguments(*this);
		for (BasicBlockPtr &block: blocks) {
			block->extract(true);
		}
		Passes::replaceConstants(*this);
		Passes::lowerAlloca(*this);
		Passes::loadArguments(*this);
		Passes::lowerObjectsize(*this);
		Passes::lowerIcmp(*this);
		Passes::lowerMath(*this);
		Passes::lowerConversions(*this);
		Passes::lowerGetelementptr(*this);
		Passes::lowerFreeze(*this);
		Passes::lowerSelect(*this);
		initialStackSize = stackSize;
		extractVariables();
		Passes::extractTypes(*this);
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
		for (BasicBlockPtr &block: blocks) {
			block->extract(true);
		}
#ifdef MOVE_PHI
		Passes::movePhi(*this);
		for (BasicBlockPtr &block: blocks) {
			block->extract(true);
		}
		extractVariables(true);
#else
		Passes::cutPhi(*this);
		Passes::coalescePhi(*this, true);
#endif
		Passes::lowerSwitch(*this);
		Passes::minimizeBlocks(*this, true);
		// Passes::makeCFG(*this);
		forceLiveness();
		updateInstructionNodes();
		reindexBlocks();
		initialDone = true;
#ifndef MOVE_PHI
		// Coalesce ϕ-instructions a second time, removing them instead of only gently aliasing variables.
		Passes::coalescePhi(*this);
#endif

		// if (*name == "@main") {
		// 	debug();
		// }

		Passes::discardUnusedVars(*this);
	}

	void Function::finalCompile() {
		success() << "Starting final compilation.\n";
		Timer timer{"FinalCompile"};
		Passes::lowerInsertvalue(*this);
		Passes::readjustStackSkip(*this);
		Passes::updateArgumentLoads(*this, stackSize - initialStackSize);
		Passes::replaceStoresAndLoads(*this);
		Passes::lowerStack(*this);
		Passes::splitResultMoves(*this);
		Passes::finishMultireg(*this);
		Passes::removeRedundantMoves(*this);
		Passes::removeUselessBranches(*this);
		Passes::mergeAllBlocks(*this);
		forceLiveness();
		Passes::lowerBranches(*this);
		Passes::lowerClobber(*this);
		Passes::lowerStack(*this);
		const bool naked = isNaked();
		if (!naked) {
			Passes::insertPrologue(*this);
		}
		Passes::loadArgumentsReadjust(*this);
		if (!naked) {
			Passes::lowerRet(*this);
		}
		Passes::lowerVarargsSecond(*this);
		Passes::removeUnreachable(*this);
		Passes::breakUpBigSets(*this);
		// Passes::minimizeBlocks(*this, true);
		Passes::makeCFG(*this);
		computeLiveness();
		Passes::discardUnusedVars(*this);
		Passes::mergeAllBlocks(*this);
		Passes::transformLabels(*this);
		forceLiveness();
		Passes::insertLabels(*this);
		Passes::fixSignedness(*this);
		Passes::signChars(*this);
		hackVariables();
		forceLiveness();
		for (const InstructionPtr &instruction: linearInstructions) {
			if (instruction->debugIndex != -1) {
				auto lock = parent.getLock();
				parent.debugIndices.insert(instruction->debugIndex);
			}
			if (dynamic_cast<WhyInstruction *>(instruction.get()) == nullptr) {
				error() << "Untranslated instruction in " << *name << ":\n\n    " << instruction->debugExtra() << "\n\n";
			}
		}
		finalDone = true;
	}

	void Function::compile() {
		global_function_name = name;
		Timer timer{"Function_" + *name};

		initialCompile();

#ifdef DEBUG_ALIASES
		debug();
#endif

		Timer regalloc_timer{"RegisterAllocation"};
#ifdef FN_CATCH_EXCEPTIONS
		try {
#endif
			Allocator::Result allocator_result = allocator->firstAttempt();
			while (allocator_result != Allocator::Result::Success) {
				extractInstructions();
				extractVariables();
				allocator_result = allocator->attempt();
			}
#ifdef FN_CATCH_EXCEPTIONS
		} catch (std::exception &err) {
			error() << err.what() << "\n";
			if (parent) {
				LL2W::interactive(*parent, this);
			}
			throw;
		}
#endif
		regalloc_timer.stop();

		variableFreeze = true;

		finalCompile();

#ifdef DEBUG_SPILL
		info() << "Total spills: \e[1m" << allocator->getSpillCount() << "\e[22m. Finished \e[1m" << *name << "\e[22m.\n";
#endif
	}

	VariablePtr Function::makePrecoloredVariable(unsigned char index, BasicBlockPtr definer) {
		if (WhyInfo::totalRegisters <= index) {
			throw std::invalid_argument("Index too high: " + std::to_string(index));
		}
		const bool old_freeze = variableFreeze;
		variableFreeze = false;
		VariablePtr new_var = newVariable(AnyType::make(), definer);
		variableFreeze = old_freeze;
		new_var->setRegisters({index});
		return new_var;
	}

	VariablePtr Function::makeAssemblerVariable(unsigned char index, BasicBlockPtr definer) {
		if (WhyInfo::assemblerCount <= index) {
			throw std::invalid_argument("Index too high for assembler-reserved registers: " + std::to_string(index));
		}
		auto iter = assemblerVariables.find(index);
		if (iter == assemblerVariables.end()) {
			VariablePtr variable = makePrecoloredVariable(WhyInfo::assemblerOffset + index, definer);
			variable->setIsUtility(true);
			iter = assemblerVariables.emplace(index, std::move(variable)).first;
		}
		VariablePtr &found = iter->second;
		if (definer) {
			found->addDefiner(definer);
		}
		return found;
	}

	void Function::forceLiveness() {
		Timer timer{"ForceLiveness"};
		extractInstructions(true);
		for (const BasicBlockPtr &block: blocks) {
			block->extract(true);
		}
		extractVariables(true);
		resetLiveness();
		computeLiveness();
	}

	void Function::precolorArguments() {
		if (getCallingConvention() == CallingConvention::Reg16) {
			const int max = std::min(16, getArity());
			int reg = WhyInfo::argumentOffset - 1;
			// TODO: change to support non-numeric argument variables
			for (int i = 0; i < max; ++i) {
				variableStore.at(StringSet::intern('%' + std::to_string(i)))->setRegisters({++reg});
			}
		}
	}

	StackLocation & Function::addToStack(const VariablePtr &variable, StackLocation::Purpose purpose, int64_t width, int64_t align) {
		for (auto &[offset, location]: stack) {
			if (*location.variable == *variable && location.purpose == purpose) {
				return location;
			}
		}

		if (width == -1) {
			width = !variable || !variable->type? 8 : Util::upalign(variable->type->width() < 8? 1 : variable->type->width() / 8, 8);
		}

		if (align == 0) {
			align = 1;
		}

		stackSize = Util::upalign(stackSize + width, align);
		auto &added = stack.emplace(stackSize, StackLocation(this, variable, purpose, stackSize, width)).first->second;
		if (purpose == StackLocation::Purpose::Spill) {
			spillSize += width;
		}
		return added;
	}

	void Function::remove(InstructionPtr instruction) {
		instruction->parent.lock()->instructions.remove(instruction);
		auto found = std::find(linearInstructions.begin(), linearInstructions.end(), instruction);
		if (found != linearInstructions.end()) {
			auto iter = found;
			++iter;
			linearInstructions.erase(found);
			for (auto end = linearInstructions.end(); iter != end; ++iter) {
				--(*iter)->index;
			}
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
		VariablePtr var = newVariable(IntType::make(64), before->parent.lock());
		auto set = std::make_shared<SetInstruction>(var, int(value & 0xffffffff));
		auto lui = std::make_shared<LuiInstruction>(var, int(value >> 32));
		insertBefore(before, set, false)->setDebug(before->debugIndex)->extract();
		insertBefore(before, lui, false)->setDebug(before->debugIndex)->extract();
		if (reindex) {
			reindexInstructions();
		}
		return var;
	}

	VariablePtr Function::getVariable(Variable::ID id, bool add_arguments) {
		if (variableStore.contains(id)) {
			return variableStore.at(id);
		}

		if (add_arguments && getCallingConvention() == CallingConvention::Reg16 && isArgument(id)) {
			return getVariable(id, arguments->at(Util::parseLong(id)).type, getEntry());
		}

		if (extraVariables.contains(id) != 0) {
			return extraVariables.at(id);
		}

		info() << "variableStore:";

		for (const auto &[name, var]: variableStore) {
			if (*name == *id) {
				std::cerr << " \e[32m" << *name << '(' << name << ':' << id << ")\e[39m";
			} else {
				std::cerr << ' ' << *name;
			}
		}

		std::cerr << '\n';
		throw std::out_of_range("Couldn't find variable with ID " + *id + " in function " + *name);
	}

	VariablePtr Function::getVariable(const std::string &label) {
		return getVariable(StringSet::intern(label));
	}

	VariablePtr Function::getVariable(Variable::ID id, const TypePtr type, BasicBlockPtr definer) {
		const bool in_variable_store = variableStore.contains(id);
		const bool in_extra_variables = extraVariables.contains(id);
		if (!in_variable_store && !in_extra_variables) {
			assert(type != nullptr);
			VariablePtr out = variableStore.emplace(id, std::make_shared<Variable>(*this, id, type? type->copy() : nullptr)).first->second;
			if (definer) {
				out->addDefiner(definer);
			}
			return out;
		}
		VariablePtr out;
		if (in_extra_variables) {
			out = extraVariables.at(id);
		} else {
			out = variableStore.at(id);
		}
		if (definer) {
			out->addDefiner(definer);
		}
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

	bool Function::isLiveInUsingMergeSet(const Node::Map &merges, Node *block, VariablePtr var) {
		if (!djGraph.has_value()) {
			throw std::runtime_error("Can't compute liveness with merge sets when the DJ graph is empty");
		}

		// if (var->definingBlocks.size() != 1) {
		// 	warn() << "Variable " << *var << " has " << var->definingBlocks.size() << " defining blocks, not 1.\n";
		// 	return false;
		// }

		const Node::Set &merge = merges.at(block);
		const WeakSet<BasicBlock> &defs = var->definingBlocks;

		// M^r(n) = M(n) ∪ {n}
		Node::Set m_r(merge.begin(), merge.end());
		m_r.insert(block);

		// for t ∈ uses(a)
		for (const auto &weak_t: var->usingBlocks) {
			BasicBlockPtr t = weak_t.lock();
			if (!t) {
				throw std::runtime_error("Couldn't lock std::weak_ptr while computing liveness");
			}
			// while t != def(a)
			while (!defs.contains(t)) {
				// if t ∩ M^r (n)
				if (m_r.contains(&(*djGraph)[*t->getLabel()])) {
					return true;
				}
				Node *t_node = &(*djGraph)[*t->getLabel()];
				if (!t_node) {
					// error() << "t_node (" << *t->getLabel() << ") is null in isLiveInUsingMergeSet\n";
					break;
				}
				Node *parent = djGraph->parent(*t_node, *djGraph->startNode);
				if (!parent) {
					// error() << "parent of " << t_node->label() << " is null in isLiveInUsingMergeSet\n";
					break;
				}
				// t = dom-parent(t);
				t = bbMap.at(StringSet::intern(parent->label()));
			}
		}

		return false;
	}

	bool Function::isLiveOutUsingMergeSet(const Node::Map &merges, Node *block, VariablePtr var) {
		if (!djGraph.has_value())
			throw std::runtime_error("Can't compute liveness with merge sets when the DJ graph is empty");

		// if (var->definingBlocks.size() != 1) {
		// 	warn() << "Variable " << *var << " has " << var->definingBlocks.size() << " defining blocks, not 1.\n";
		// 	return false;
		// }

		const auto &defs = var->definingBlocks;

		// if def(a) = n
		if (defs.contains(bbMap.at(StringSet::intern(block->label())))) {
			// return uses(a)\def(a) = ∅
			// At least, I assume the use of φ in the PDF actually refers to the empty set.
			auto difference = var->usingBlocks;
			for (const auto &weak_block: var->definingBlocks) {
				difference.erase(weak_block);
			}
			return !difference.empty();
		}

		// M_s(n) = ∅
		Node::Set m_s;

		// for w ∈ succ(n)
		for (Node *successor: block->out()) {
			// M_s(n) = M_s(n) ∪ M^r(w)
			// The authors define M^r(n) as {M(n) ∪ {n}}.
			m_s.insert(successor);
			const Node::Set &m_r = merges.at(successor);
			m_s.insert(m_r.begin(), m_r.end());
		}

		// for t ∈ uses(a)
		for (auto weak_t: var->usingBlocks) {
			auto t = weak_t.lock();
			if (!t) {
				throw std::runtime_error("Couldn't lock std::weak_ptr while computing liveness");
			}
			// while t != def(a)
			while (!defs.contains(t)) {
				// if t ∩ M_s(n)
				if (m_s.contains(&(*djGraph)[*t->getLabel()])) {
					return true;
				}
				auto t_node = &(*djGraph)[*t->getLabel()];
				if (!t_node) {
					// error() << "t_node (" << *t->label << ") is null in isLiveOutUsingMergeSet\n";
					break;
				}
				auto parent = djGraph->parent(*t_node, *djGraph->startNode);
				if (!parent) {
					// error() << "parent of " << t_node->label() << " is null in isLiveOutUsingMergeSet\n";
					break;
				}
				// t = dom-parent(t);
				t = bbMap.at(StringSet::intern(parent->label()));
			}
		}

		return false;
	}

	void Function::computeLivenessMS() {
		Timer timer{"ComputeLivenessMS"};

		if (!djGraph.has_value()) {
			throw std::runtime_error("Can't compute liveness with merge sets when the DJ graph is empty");
		}

		auto mergesets = djGraph->getMergeSets();
		// There must be a better way than this brute-force approach. I'm just not smart enough to find it.
		// This is obviously O(bv), where b is the number of basic blocks and v is the number of variables.
		// I'm guessing that's around 45,000 for vsnprintf. That's absurd.
		for (const auto &[name, var]: variableStore) {
			if (!var->hasSpecialRegister()) {
				for (const auto &block: blocks) {
					if (isLiveInUsingMergeSet(mergesets, &(*djGraph)[*block->getLabel()], var)) {
						block->liveIn.insert(var);
						block->allLive.insert(var);
					}
					if (isLiveOutUsingMergeSet(mergesets, &(*djGraph)[*block->getLabel()], var)) {
						block->liveOut.insert(var);
						block->allLive.insert(var);
					}
				}
			}
		}
		for (const auto &[name, var]: extraVariables) {
			if (!var->hasSpecialRegister()) {
				for (const auto &block: blocks) {
					if (isLiveInUsingMergeSet(mergesets, &(*djGraph)[*block->getLabel()], var)) {
						block->liveIn.insert(var);
						block->allLive.insert(var);
					}
					if (isLiveOutUsingMergeSet(mergesets, &(*djGraph)[*block->getLabel()], var)) {
						block->liveOut.insert(var);
						block->allLive.insert(var);
					}
				}
			}
		}
	}

	void Function::computeLivenessTraditional() {
		Timer timer{"ComputeLivenessTraditional"};
		// https://www.classes.cs.uchicago.edu/archive/2004/spring/22620-1/docs/liveness.pdf, page 9
		std::map<BasicBlock::Label, std::set<VariablePtr>> in, out, in_, out_;
		std::map<BasicBlock::Label, std::vector<BasicBlockPtr>> goes_to;

		bool working;

		// Oh no.
		{
			Timer subtimer{"GoesTo"};
			for (auto &block: blocks) {
				goes_to.try_emplace(block->getLabel());
				for (auto &other: blocks) {
					if (Util::contains(other->preds, block->getLabel())) {
						goes_to[block->getLabel()].push_back(other);
					}
				}
			}
		}

		do {
			for (auto &block: blocks) {
				auto n = block->getLabel();
				in_[n]  = in[n];
				out_[n] = out[n];
				in[n] = block->read;
				for (auto &var: out[n]) {
					if (!block->written.contains(var)) {
						in[n].insert(var);
					}
				}
				out[n].clear();
				for (auto &succ: goes_to.at(n)) {
					for (auto &var: in[succ->getLabel()]) {
						out[n].insert(var);
					}
				}
			}

			working = false;
			for (auto &block: blocks) {
				auto n = block->getLabel();
				if (!(Util::equal(in_[n], in[n]) && Util::equal(out_[n], out[n]))) {
					working = true;
					break;
				}
			}
		} while (working);

		for (auto &block: blocks) {
			block->liveIn  = std::unordered_set<VariablePtr>(in[block->getLabel()].cbegin(),  in[block->getLabel()].cend());
			block->liveOut = std::unordered_set<VariablePtr>(out[block->getLabel()].cbegin(), out[block->getLabel()].cend());
			block->allLive = Util::merge(block->liveIn, block->liveOut);
		}
	}

	void Function::computeLiveness() {
#ifdef TRADITIONAL_LIVENESS
		computeLivenessTraditional();
#elif defined(MERGE_SET_LIVENESS)
		computeLivenessMS();
#else
		computeLivenessUAM();
#endif
	}

	void Function::upAndMark(BasicBlockPtr block, VariablePtr var) {
		for (const auto &instruction: block->instructions) {
			if (instruction->isPhi()) {
				continue;
			}
			// if def(v) ∈ B (φ excluded) then return
			if (instruction->written.contains(var) && !var->fromPhi) {
				return;
			}
		}

		// if v ∈ LiveIn(B) then return
		if (block->liveIn.contains(var)) {
			return;
		}

		// LiveIn(B) = LiveIn(B) ∪ {v}
		block->liveIn.insert(var);
		block->allLive.insert(var);

		// if v ∈ PhiDefs(B) then return
		if (block->inPhiDefs(var)) {
			return;
		}

		// for each P ∈ CFG_preds(B) do
		try {
			for (const Node *node: bbNodeMap.at(block.get())->in()) {
				BasicBlockPtr p = node->get<std::weak_ptr<BasicBlock>>().lock();
				// LiveOut(P) = LiveOut(P) ∪ {v}
				p->liveOut.insert(var);
				p->allLive.insert(var);
				upAndMark(p, var);
			}
		} catch (const std::out_of_range &) {
			debug();
			std::cerr << "Couldn't find block " << *block->getLabel() << " in " << *name << " while computing liveness.\n";
			if (!bbNodeMap.empty()) {
				std::cerr << "\nbbNodeMap:";
				for (const auto &[block, node]: bbNodeMap) {
					std::cerr << ' ' << *block->getLabel();
				}
				std::cerr << "\n\n";
			}
			throw;
		}
	}

	void Function::computeLivenessUAM() {
		Timer timer{"ComputeLivenessUAM"};
		for (const BasicBlockPtr &block: blocks) {
			block->extractPhi();
			block->extract();
			for (const VariablePtr &var: block->phiUses) {
				block->liveOut.insert(var);
				upAndMark(block, var);
			}
			for (const VariablePtr &var: block->nonPhiRead) {
				upAndMark(block, var);
			}
		}

		timer.stop();
		hackLiveness();
	}

	void Function::hackLiveness() {
		Timer timer{"HackLiveness"};
		for (const auto &[id, var]: variableStore) {
			const auto &defines = var->definingBlocks;
			const auto &uses = var->usingBlocks;
			if (defines.size() == 1 && uses.size() == 1 && defines.begin()->lock() == uses.begin()->lock()) {
				for (const BasicBlockPtr &block: blocks) {
					block->liveIn.erase(var);
					block->liveOut.erase(var);
					block->allLive.erase(var);
				}
			}
		}
	}

	void Function::resetLiveness() {
		for (BasicBlockPtr &block: blocks) {
			block->liveIn.clear();
			block->liveOut.clear();
			block->allLive.clear();
		}
	}

	std::unordered_set<std::shared_ptr<BasicBlock>> Function::getLive(const VariablePtr &var, BasicBlock::LivePtr lptr) const {
		Timer timer{"GetLive"};
		std::unordered_set<std::shared_ptr<BasicBlock>> out;
		const auto &alias_pointers = var->getAliases();
		std::unordered_set<VariablePtr> aliases;
		for (const auto &[id, subvar]: variableStore) {
			if (alias_pointers.contains(subvar.get())) {
				aliases.insert(subvar);
			}
		}
		aliases.insert(var);
		for (const auto &alias: aliases) {
			for (const auto &block: blocks) {
				if (((*block).*lptr).contains(alias)) {
					out.insert(block);
				}
			}
		}
		return out;
	}

	std::unordered_set<std::shared_ptr<BasicBlock>>
	Function::getLiveIn(const VariablePtr &var) const {
		return getLive(var, &BasicBlock::liveIn);
	}

	std::unordered_set<std::shared_ptr<BasicBlock>>
	Function::getLiveOut(const VariablePtr &var) const {
		return getLive(var, &BasicBlock::liveOut);
	}

	bool Function::isLiveOutAnywhere(const VariablePtr &var) const {
		Timer timer{"IsLiveOutAnywhere"};
		const auto &alias_pointers = var->getAliases();
		std::unordered_set<VariablePtr> aliases;
		for (const auto &[id, subvar]: variableStore) {
			if (alias_pointers.contains(subvar.get())) {
				aliases.insert(subvar);
			}
		}
		aliases.insert(var);
		for (const auto &alias: aliases) {
			for (const auto &block: blocks) {
				if (block->liveOut.contains(alias)) {
					return true;
				}
			}
		}
		return false;
	}

	std::string Function::toString() {
		Timer timer{"Function::toString"};
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
				auto lock = parent.getLock();
				if (parent.locations.contains(dbg)) {
					out << " !" << parent.locations.at(dbg).index;
				} else {
					warn() << "Couldn't find location for !" << dbg << "\n";
				}
			}
			out << "\n";
		}
		return out.str();
	}

	std::string Function::headerString() const {
		std::stringstream out;
		out << *returnType << " \e[35m" << *name << "\e[94m(\e[39m";
		for (auto begin = arguments->begin(), iter = begin, end = arguments->end(); iter != end; ++iter) {
			if (iter != begin) {
				out << "\e[2m,\e[22m ";
			}
			out << *iter->type;
			if (iter->name) {
				out << " " << *iter->name;
			}
		}
		out << "\e[94m)\e[39m";
		return out.str();
	}

	void Function::debug(std::ostream &stream) {
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
			true,
#else
			false,
#endif
#ifdef DEBUG_LABELS
			true,
#else
			false,
#endif
			stream
		);
	}

	void Function::debug(bool do_blocks, bool linear, bool vars, bool block_liveness, bool read_written, bool var_liveness, bool render,
						 bool estimations, bool aliases, bool stack, bool show_labels, std::ostream &stream) {
		if (do_blocks || linear || vars) {
			stream << headerString() + " \e[94m{\e[39m\n";
		}

		if (do_blocks) {
			for (const BasicBlockPtr &block: blocks) {
				stream << "    \e[2m; \e[4;1m" << *block->getLabel() << "\e[22;2;4m @ " << block->index << ": preds =";
				for (auto begin = block->preds.begin(), iter = begin, end = block->preds.end(); iter != end; ++iter) {
					if (iter != begin) {
						stream << ',';
					}
					stream << ' ' << **iter;
				}
				stream << '.';
				if (block_liveness) {
					if (!block->liveIn.empty()) {
						stream << "; live-in =";
						const auto &liveIn = block->liveIn;
						for (auto begin = liveIn.begin(), iter = begin, end = liveIn.end(); iter != end; ++iter) {
							if (iter != begin) {
								stream << ',';
							}
							stream << ' ' << *(*iter)->id;
						}
					}
					if (!block->liveOut.empty()) {
						stream << "; live-out =";
						const auto &liveOut = block->liveOut;
						for (auto begin = liveOut.begin(), iter = begin, end = liveOut.end(); iter != end; ++iter) {
							if (iter != begin) {
								stream << ',';
							}
							stream << ' ' << *(*iter)->id;
						}
					}
				}
				stream << "\e[22;24m\n";
				if (read_written) {
					for (const std::shared_ptr<Instruction> &instruction: block->instructions) {
						int read, written;
						std::tie(read, written) = instruction->extract();
						stream << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written << "\e[0m\n";
						if (show_labels) {
							if (auto labels = instruction->getLabels(); !labels.empty()) {
								stream << "    Labels:";
								for (const auto *label: labels) {
									stream << " \e[1m" << *label << "\e[22m";
								}
								stream << '\n';
							} else {
								stream << "    No labels.\n";
							}
						}
					}
				} else {
					for (const std::shared_ptr<Instruction> &instruction: block->instructions) {
						stream << "    " << instruction->debugExtra() << "\n";
					}
				}
				stream << "\n";
			}
		}
		if (linear) {
			for (const std::shared_ptr<Instruction> &instruction: linearInstructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				stream << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written << "\e[0m\n";
				if (show_labels) {
					if (auto labels = instruction->getLabels(); !labels.empty()) {
						stream << "    Labels:";
						for (const auto *label: labels) {
							stream << " \e[1m" << *label << "\e[22m";
						}
						stream << '\n';
					} else {
						stream << "    No labels.\n";
					}
				}
			}
		}
		if (vars) {
			stream << "    \e[2m; Variables:\e[0m\n";

			struct Compare {
				bool operator()(const Variable::ID &left, const Variable::ID &right) const {
					return strnatcmp(left->c_str(), right->c_str()) == -1;
				}
			};

			std::map<Variable::ID, VariablePtr, Compare> all_vars;
			all_vars.insert(variableStore.cbegin(), variableStore.cend());
			all_vars.insert(extraVariables.cbegin(), extraVariables.cend());

			for (auto &[id, var]: all_vars) {
				if (extraVariables.contains(id)) {
					stream << "\e[31m[e]\e[39m";
				} else {
					stream << "   ";
				}
				stream << " \e[2m; \e[1m" << *id << '/' << *var->id << '/' << *var->originalID << "\e[0;2m  defs (" << var->definitions.size() << ") =";
				for (const std::weak_ptr<BasicBlock> &def: var->definingBlocks) {
					if (auto locked = def.lock()) {
						stream << " \e[1;2m" << std::setw(2) << *locked->getLabel() << "\e[22m";
					} else {
						stream << " \e[2m??\e[22m";
					}
				}
				stream << "  \e[0;2muses (" << var->uses.size() << ") =";
				for (const std::weak_ptr<BasicBlock> &use: var->usingBlocks) {
					if (auto locked = use.lock()) {
						stream << " \e[1;2m" << std::setw(2) << *locked->getLabel() << "\e[22m";
					} else {
						stream << " \e[2m??\e[22m";
					}
				}
				const auto spill_cost = var->spillCost();
				stream << "\e[2m  cost = \e[1m" << (spill_cost == INT64_MAX? "∞" : std::to_string(spill_cost)) << "\e[0;2m";
				if (var->definingBlocks.size() > 1) {
					stream << " (multiple defs)";
				}
				stream << "  pid = \e[1m" << *var->parentID() << "\e[22;2m";
				const auto aliases = var->getAliases();
				if (!aliases.empty()) {
					stream << "  aliases =\e[1m";
					for (const Variable *alias: aliases) {
						stream << ' ' << *alias->id;
					}
					stream << "\e[22;2m";
				}
				if (var_liveness) {
					stream << "    \e[2m;      \e[32min  =\e[1m";
					for (const BasicBlockPtr &block: blocks) {
						if (block->isLiveIn(var)) {
							stream << ' ' << *block->getLabel();
						}
					}
					stream << "\e[0m\n";
					stream << "    \e[2m;      \e[31mout =\e[1m";
					for (const BasicBlockPtr &block: blocks) {
						if (block->isLiveOut(var)) {
							stream << ' ' << *block->getLabel();
						}
					}
					stream << "\e[0m\n";
				}
			}
		}
		if (do_blocks || linear || vars) {
			stream << "\e[94m}\e[39m\n\n";
		}
		if (aliases) {
			stream << "<Aliases>\n";
			for (auto &[id, var]: variableStore) {
				stream << *id << " = " << *var;
				if (auto vparent = var->getParent().lock()) {
					stream << "(parent = " << *vparent << ")";
				}
				stream << ':';
				for (Variable *alias: var->getAliases()) {
					stream << ' ' << *alias;
				}
				stream << '\n';
			}
			stream << "</Aliases>\n";
		}
		if (render) {
			stream << "Rendering.\n";
			if (estimations) {
				for (Node *node: cfg.nodes()) {
					if (node->data.has_value()) {
						if (BasicBlockPtr bb = node->get<std::weak_ptr<BasicBlock>>().lock()) {
							node->rename('"' + node->label() + ':' + std::to_string(bb->estimatedExecutions) + '"');
						}
					}
				}
			}
			cfg.renderTo("graph_" + *name + ".png");
			if (dTree.has_value()) {
				dTree->renderTo("graph_D_" + *name + ".png");
			}
			if (djGraph.has_value()) {
				djGraph->renderTo("graph_DJ_" + *name + ".png");
			}
		}
		if (stack) {
			debugStack(stream);
		}
	}

	void Function::debugStack(std::ostream &stream) const {
		for (const std::pair<const int, StackLocation> &pair: stack) {
			stream << pair.first << '[' << pair.second.width << "]:" << *pair.second.variable << ' ';
		}
		stream << '\n';
	}

	bool Function::isNaked() const {
		if (!astnode) {
			return naked? *naked : false;
		}

		const FunctionHeader *header = dynamic_cast<const FunctionHeader *>(astnode->children.front());
		if (header->fnattrs.contains(FnAttr::naked)) {
			return true;
		}
		if (header->fnattrsIndex == -1) {
			return false;
		}
		auto lock = parent.getLock();
		return parent.fnattrs.at(header->fnattrsIndex).contains(FnAttr::naked);
	}

	StackLocation & Function::getSpill(VariablePtr variable, bool create, bool *created) {
		if (created) {
			*created = false;
		}
		for (std::pair<const int, StackLocation> &pair: stack) {
			if (pair.second.variable->id == variable->id && pair.second.purpose == StackLocation::Purpose::Spill) {
				return pair.second;
			}
		}
		if (create) {
			if (created) {
				*created = true;
			}
			return addToStack(variable, StackLocation::Purpose::Spill);
		}
		throw std::out_of_range("Couldn't find a spill location for " + variable->plainString());
	}

	std::shared_ptr<LocalValue> Function::replaceGetelementptrValue(std::shared_ptr<GetelementptrValue> gep, InstructionPtr instruction) {
		TypePtr out_type;

		std::list<long> indices = Getelementptr::getLongIndices(*gep);

		const long offset = Util::updiv(Getelementptr::compute(gep->ptrType, std::move(indices), &out_type), 8l);
		if (Util::outOfRange(offset)) {
			warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
		}

		switch (gep->variable->valueType()) {
			case ValueType::Global: {
				VariablePtr var1(newVariable(IntType::make(32))), var2(newVariable(out_type));
				auto set = std::make_shared<SetInstruction>(var1, dynamic_cast<GlobalValue *>(gep->variable.get())->name);
				auto addi = std::make_shared<AddIInstruction>(var1, int(offset), var2);
				insertBefore(instruction, set)->setDebug(*instruction)->extract();
				insertBefore(instruction, addi)->setDebug(*instruction)->extract();
				return LocalValue::make(var2);
			}
			case ValueType::Local: {
				VariablePtr new_var(newVariable(out_type));
				auto addi = AddIInstruction::make(dynamic_cast<LocalValue *>(gep->variable.get())->getVariable(*this), int(offset), new_var);
				insertBefore(instruction, addi)->setDebug(*instruction)->extract();
				return LocalValue::make(new_var);
			}
			default:;
		}

		if (gep->variable->isIntLike()) {
			VariablePtr new_var(newVariable(out_type));
			insertBefore(instruction, SetInstruction::make(new_var, gep->variable->intValue() + int(offset)))->setDebug(*instruction)->extract();
			return LocalValue::make(new_var);
		}

		throw std::invalid_argument("Expected a global, local or intlike value in Function::replaceGetelementptrValue");
	}

	VariablePtr Function::makeVariable(ValuePtr value, InstructionPtr instruction, TypePtr hint) {
		VariablePtr new_var;
		std::shared_ptr<SetInstruction> set;

		switch (value->valueType()) {
			case ValueType::Getelementptr:
				return replaceGetelementptrValue(std::dynamic_pointer_cast<GetelementptrValue>(value), instruction)->getVariable(*this);
			case ValueType::Local:
				return dynamic_cast<LocalValue *>(value.get())->variable;
			case ValueType::Global: {
				auto *global = dynamic_cast<GlobalValue *>(value.get());
				new_var = newVariable(hint? hint : GlobalTemporaryType::make(global->name));
				set = SetInstruction::make(new_var, global->name);
				break;
			}
			case ValueType::Int:
			case ValueType::Bool:
			case ValueType::Null:
			case ValueType::Undef:
				new_var = newVariable(hint? hint : AnyType::make());
				set = SetInstruction::make(new_var, value->intValue(false));
				set->setOriginalValue(value);
				break;
			case ValueType::Icmp: {
				auto *icmp = dynamic_cast<IcmpValue *>(value.get());
				new_var = newVariable(hint? hint : IntType::make(8, Signedness::Unsigned));
				Passes::lowerIcmp(*this, instruction, icmp->makeNode(new_var).get());
				break;
			}
			case ValueType::Logic: {
				auto *logic = dynamic_cast<LogicValue *>(value.get());
				new_var = newVariable(hint? hint : logic->left->type);
				Passes::lowerLogic(*this, instruction, logic->makeNode(new_var).get());
				break;
			}
			default:
				throw std::runtime_error("Unhandled value in Function::makeVariable: " + value_map.at(value->valueType()));
		}

		if (!new_var) {
			throw std::runtime_error("new_var is null at the end of Function::makeVariable");
		}

		if (set) {
			insertBefore(instruction, set)->setDebug(*instruction)->extract();
		}

		return new_var;
	}

	void Function::hackVariables() {
		Timer timer{"HackVariables"};
		std::list<VariablePtr> all_vars;

		for (auto &pair: extraVariables) {
			all_vars.push_back(pair.second);
		}

		for (auto &pair: variableStore) {
			all_vars.push_back(pair.second);
		}

		for (VariablePtr &var: all_vars) {
			auto var_parent = var->getParent().lock();

			if (var->registers.empty() && var_parent != nullptr) {
				var->registers = var_parent->registers;
			}

			if (var->registers.empty()) {
				for (Variable *alias: var->getAliases()) {
					if (!alias->registers.empty()) {
						var->registers = alias->registers;
						break;
					}
				}
				// As a last resort, if this variable *still* has no register assigned, check all other known variables
				// for a variable with the same id and try to absorb its register assignment.
				if (var->registers.empty()) {
					for (VariablePtr &other: all_vars) {
						if (other != var && other->id == var->id && !other->registers.empty()) {
							var->registers = other->registers;
							break;
						}
					}
					if (var->registers.empty()) {
						warn() << "hackVariables: last resort failed for " << *var << " in function \e[1m" << *name << "\e[22m";
						if (variableStore.contains(var->id)) {
							std::cerr << "'s variableStore\n";
						} else if (extraVariables.contains(var->id)) {
							std::cerr << "'s extraVariables\n";
						} else {
							std::cerr << " somewhere\n";
						}
					}
				}
			} else {
				for (Variable *alias: var->getAliases()) {
					if (alias->registers.empty()) {
						alias->registers = var->registers;
					}
				}
			}
		}
	}

	Graph Function::makeDependencyGraph() const {
		Timer timer{"Function::makeDependencyGraph"};
		Graph dependencies;

		for (const auto &[id, var]: variableStore) {
			dependencies.addNode(*var->originalID).data = var.get();
		}

		for (const auto &[id, var]: variableStore) {
			for (Variable *phi_parent: var->phiParents) {
				dependencies[*phi_parent->originalID].link(dependencies[*var->originalID], true);
			}
			for (Variable *child: var->phiChildren) {
				dependencies[*var->originalID].link(dependencies[*child->originalID], true);
			}
		}

		return dependencies;
	}

	void Function::makeInitialDebugIndex() {
		if (debugIndex == -1) {
			return;
		}
		auto lock = parent.getLock();
		initialDebugIndex = parent.newDebugIndex();
		Subprogram &subprogram = parent.subprograms.at(debugIndex);
		Location location(subprogram.line, 1, debugIndex);
		location.file = subprogram.file;
		parent.locations.emplace(initialDebugIndex, location);
	}

	std::shared_ptr<Clobber> Function::clobber(const InstructionPtr &instruction, int reg) {
		auto out = Clobber::make(reg);
		insertBefore(instruction, out)->setDebug(*instruction);
		return out;
	}

	std::shared_ptr<Unclobber>
	Function::unclobber(const InstructionPtr &instruction, const std::shared_ptr<Clobber> &clob) {
		auto out = Unclobber::make(clob->reg);
		clob->unclobber = out;
		insertBefore(instruction, out)->setDebug(*instruction, true);
		return out;
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
		auto out = makePrecoloredVariable(WhyInfo::framePointerOffset, block);
		out->type = PointerType::make(VoidType::make());
		return out;
	}

	VariablePtr Function::fp(InstructionPtr instruction) {
		return fp(instruction->parent.lock());
	}

	VariablePtr Function::sp(BasicBlockPtr block) {
		auto out = makePrecoloredVariable(WhyInfo::stackPointerOffset, block);
		out->type = PointerType::make(VoidType::make());
		return out;
	}

	VariablePtr Function::sp(InstructionPtr instruction) {
		return sp(instruction->parent.lock());
	}

	VariablePtr Function::zero(BasicBlockPtr block) {
		return makePrecoloredVariable(WhyInfo::zeroOffset, block);
	}

	VariablePtr Function::zero(InstructionPtr instruction) {
		return zero(instruction->parent.lock());
	}

	VariablePtr Function::lo(BasicBlockPtr block) {
		return makePrecoloredVariable(WhyInfo::loOffset, block);
	}

	VariablePtr Function::lo(InstructionPtr instruction) {
		return lo(instruction->parent.lock());
	}
}
