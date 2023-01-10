#pragma once

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "allocator/Allocator.h"
#include "compiler/BasicBlock.h"
#include "compiler/CFG.h"
#include "compiler/StackLocation.h"
#include "compiler/Variable.h"
#include "graph/DJGraph.h"
#include "graph/DTree.h"
#include "parser/FunctionArgs.h"

namespace LL2W {
	class ASTNode;
	class ColoringAllocator;
	class LinearScanAllocator;
	class Program;
	struct Clobber;
	struct FunctionArgs;
	struct Unclobber;

	using InstructionPtr = std::shared_ptr<Instruction>;

	/**
	 * StackOnly: all parameters are pushed to the stack, right-to-left. Used for variadic functions.
	 * Reg16: The first sixteen arguments are put in registers $a0 through $af, left-to-right. The rest are pushed to
	 *        the stack right-to-left.
	 */
	enum class CallingConvention {StackOnly, Reg16};

	/**
	 * Represents a function and contains code for converting functions from LLVM's intermediate representation into Why
	 * bytecode.
	 */
	class Function {
		public:
			/** Complex functions have multiple instructions.
			 *  Simple functions return the only argument and do nothing else.
			 *  Useless functions return void and do nothing else.
			 *  Constant functions return a constant value and do nothing else. */
			enum class Type {Complex, Simple, Useless, Constant};

		private:
			/** A pointer to an AST node that contains data about the function's arguments. */
			std::shared_ptr<FunctionArgs> argumentsNode = nullptr;

			/** Contains the AST node this object was constructed from. */
			const ASTNode *astnode;

			int initialStackSize = 0;

			/** Maps variables to their stack locations. */
			std::map<VariablePtr, StackLocation *> variableLocations;

			std::unordered_map<unsigned char, VariablePtr> assemblerVariables;

			void computeLivenessUAM();

			/** If a variable is defined in one block and used only in that block, mark it as not live anywhere. */
			void hackLiveness();

			bool isLiveInUsingMergeSet(const Node::Map &merges, Node *block, VariablePtr var);
			bool isLiveOutUsingMergeSet(const Node::Map &merges, Node *block, VariablePtr var);

			/** Computes liveness using merge sets. Seems to be broken? */
			void computeLivenessMS();

			/** Computes liveness using a traditional, non-SSA method. Broken. Do not use. */
			void computeLivenessTraditional();

			void upAndMark(BasicBlockPtr, VariablePtr);

			std::unordered_set<BasicBlockPtr> getLive(const VariablePtr &, BasicBlock::LivePtr) const;

		public:
			Program &parent;

			Type analyzedType = Type::Complex;

			/** A pointer to a list of all function arguments. */
			std::vector<FunctionArgument> *arguments = nullptr;

			/** A pointer to an interned string containing the name of the function. */
			const std::string *name;

			/** The type of the returned value. */
			TypePtr returnType;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlockPtr> blocks;

			/** A list of all instructions in the order they appear in the source code. */
			std::list<InstructionPtr> linearInstructions;

			/** Maps numeric labels to variables. This is the main storage for the function's variables. */
			std::map<Variable::ID, VariablePtr> variableStore;

			/** A map of variables that have been removed but are likely to be still referenced somewhere, or that
			 *  aren't in variableStore but need to be processed by hackVariables. */
			std::map<Variable::ID, VariablePtr> extraVariables;

			std::unordered_set<Variable::ID> spilledVariables;

			/** A list of physical registers that were pushed to the stack in the prologue. Filled in by
			 *  InsertPrologue. */
			std::list<int> savedRegisters;

			/** Maps offsets to stack location information. */
			std::map<int, StackLocation> stack;

			/** Maps interned strings representing labels to their corresponding basic blocks. This is the main storage
			 *  for the function's basic blocks. */
			std::map<const std::string *, BasicBlockPtr> bbMap;

			/** Maps basic blocks to their corresponding CFG nodes. */
			std::unordered_map<const BasicBlock *, Node *> bbNodeMap;

			/** A set of the labels of all the function's basic blocks. */
			std::unordered_set<const std::string *> bbLabels;

			/** MovePhi can insert blocks between a pair of blocks. This maps those pairs to the created blocks so that
			 *  extra blocks won't be created. */
			std::map<std::pair<const std::string *, const std::string *>, BasicBlockPtr> movePhiBlocks;

			/** Used by passes to indicate which instructions they produced so that later passes can pick up where they
			 *  left off after other things have occurred. For example, SetupCalls uses this to record the moves from
			 *  result registers into variables in case the variable is larger than one physical register and the move
			 *  needs to be split up after register allocation. */
			std::unordered_map<std::string, std::unordered_set<InstructionPtr>> categories;

			/** Stores stack locations for register clobbering. */
			std::unordered_map<int, const StackLocation *> clobbers;

			/** The control-flow graph computed by makeCFG. */
			CFG cfg;

			/** The dominator tree computed from the control-flow graph. */
			std::optional<DTree> dTree;

			/** The dominator tree computed from the control-flow graph with J-edges included. */
			std::optional<DJGraph> djGraph;

			/** The number of random walks that have been performed on the control flow graph. */
			int walkCount = 0;

			/** The number of bytes reserved on the stack for variables and spills. */
			int stackSize = 0;

			/** The number of bytes reserved on the stack for spills. */
			int spillSize = 0;

			/** Whether all blocks have been minimized to contain exactly one instruction each. */
			bool blocksAreMinimized = false;

			/** The number of bytes pushed to the stack when InsertPrologue saves registers, including $fp and $sp. */
			int initialPushedBytes = -1;

			int debugIndex = -1;
			int initialDebugIndex = -1;

			Allocator *allocator = nullptr;

			bool initialDone = false;
			bool allocationDone = false;
			bool finalDone = false;

			/** If true, newVariable will throw an exception. */
			bool variableFreeze = false;

			int lastArtificialLabel = -1;

			Allocator::Result lastAllocationResult;

			Function(const Function &) = delete;
			Function(Function &&) = delete;
			Function(Program &, const ASTNode &);

			~Function();

			Allocator::Result attemptAllocation();

			/** Analyzes the function's type. */
			Type analyze(ValuePtr *value_out = nullptr, long *simple_index_out = nullptr);

			/** Scans through the function AST for block headers and populates the list of BasicBlocks accordingly. */
			void extractBlocks();

			/** Attempts to find a basic block with a given label. The label is allowed to start with a percent sign. */
			BasicBlockPtr getBlock(const std::string *label, bool can_throw = true) const;

			/** Copies use/definition information from the BasicBlocks into the Variables. */
			void extractVariables(bool reset = false);

			/** Extracts read/written information from all instructions. */
			void extractInstructions(bool force = false);

			/** Recreates linearInstructions from each BasicBlock's vector of instructions and renumbers the
			 *  instructions. */
			void relinearize();

			/** Returns a label that hasn't yet been used for a basic block or variable. */
			Variable::ID newLabel();

			/** Produces a new variable with an as yet unused label. */
			VariablePtr newVariable(const TypePtr &, const BasicBlockPtr & = nullptr);

			/** Tries to spill a variable. Returns true if any instructions were inserted. */
			bool spill(VariablePtr, bool doDebug = false);

			void markSpilled(VariablePtr);

			bool isSpilled(VariablePtr) const;

			bool canSpill(VariablePtr);

			bool isArgument(Variable::ID) const;

			/** Returns the first instruction in the function that isn't a label or a comment. */
			InstructionPtr firstInstruction(bool includeComments = false);

			/** Returns a pointer to the instruction following a given instruction. */
			InstructionPtr after(InstructionPtr);

			/** Returns a pointer to the basic block following a given basic block. */
			BasicBlockPtr after(BasicBlockPtr);

			/** Inserts one instruction after another. Returns the inserted instruction. */
			InstructionPtr insertAfter(InstructionPtr base,
				InstructionPtr new_instruction, bool reindex = true);

			/** Inserts one instruction before another. Returns the inserted instruction. */
			InstructionPtr insertBefore(InstructionPtr base,
				InstructionPtr new_instruction, bool reindex = true, bool linear_warn = true,
				bool *should_relinearize_out = nullptr);

			/** Inserts one instruction before another and adds a comment before the inserted instruction.
			 *  Returns the inserted instruction. */
			InstructionPtr insertBefore(InstructionPtr base,
				InstructionPtr new_instruction, const std::string &, bool reindex = true);

			/** Inserts one instruction before another and adds a comment before the inserted instruction.
			 *  Returns the inserted instruction. */
			InstructionPtr insertBefore(InstructionPtr base,
				InstructionPtr new_instruction, const char *, bool reindex = true);

			/** Inserts a comment before an instruction. */
			InstructionPtr comment(InstructionPtr, const std::string &,
				bool reindex = true);

			/** Removes in a given block a branch instruction that redundantly jumps to the immediately following block
			 *  if such a branch instruction exists. */
			void removeUselessBranch(BasicBlockPtr);

			/** Reassigns indices to all instructions. */
			void reindexInstructions();

			/** Reassigns indices to all basic blocks. */
			void reindexBlocks();

			/** Splits a basic block after a given instruction. */
			BasicBlockPtr splitBlock(BasicBlockPtr, InstructionPtr);

			/** Creates a precolored variable corresponding to any register. */
			VariablePtr makePrecoloredVariable(unsigned char, BasicBlockPtr);

			/** Creates a precolored variable corresponding to a given $mx (assembler-reserved) register. */
			VariablePtr makeAssemblerVariable(unsigned char, BasicBlockPtr);

			/** Returns a given basic block's CFG node. */
			Node & operator[](const BasicBlock &) const;

			/** Returns the number of arguments the function takes. */
			int getArity() const;

			/** Returns whether the function is variadic (i.e., whether it takes a variable number of arguments). */
			bool isVariadic() const;

			/** Transforms a string like "%64" into "__functionname_label64". */
			std::string transformLabel(const std::string &) const;

			/** Sets the pvar names in all instructions to those of the connected variables. */
			void updateInstructionNodes();

			/** Removes the register assignments for all variables. If its argument is true, it won't reset variables
			 *  that have been assigned special registers. */
			void resetRegisters(bool respectful = true);

			/** Performs the first set of compiler passes on the function before register allocation. */
			void initialCompile();

			/** Performs the last set of compiler passes on the function after register allocation. */
			void finalCompile();

			/** Performs a full set of compiler passes on the function. */
			void compile();

			/** Force-extracts all instructions and blocks, resets liveness and computes liveness. */
			void forceLiveness();

			/** Assigns special argument registers to all variables as appropriate. */
			void precolorArguments();

			/** Assigns or looks up a stack location for a given variable. The width parameter is in bytes. */
			StackLocation & addToStack(const VariablePtr &, StackLocation::Purpose, int64_t width = -1,
			                           int64_t align = 1);

			/** Removes an instruction from the function. */
			void remove(InstructionPtr);

			/** Removes a basic block from the function. Any function that calls this should also be sure to relinearize
			 *  instructions after calling this. */
			void remove(BasicBlockPtr);

			/** Replaces the first instruction with the second. Not safe to call while iterating. */
			void replace(InstructionPtr, InstructionPtr);

			/** Loads a 64-bit value into a new variable before an instruction by means of set and lui. */
			VariablePtr get64(InstructionPtr before, unsigned long, bool reindex = false);

			/** Merges two basic blocks. The after-block is absorbed into the before-block. The caller of this function
			 *  is responsible for recreating the CFG and reindexing all blocks. */
			void mergeBlocks(BasicBlockPtr before, BasicBlockPtr after);

			/** Returns the variable with a given label. If the variable doesn't exist, an exception will be thrown,
			 *  unless the second argument is true and the variable is one of the argument variables, in which case
			 *  it'll be added to the variable store and returned. */
			VariablePtr getVariable(Variable::ID, bool add_arguments = true);

			/** Returns the variable with a given label. If the variable doesn't exist, an exception will be thrown. */
			VariablePtr getVariable(const std::string &);

			/** Returns the variable with a given label. If the variable doesn't exist, it will be created with the
			 *  given type and defining block options. */
			VariablePtr getVariable(Variable::ID, const TypePtr, BasicBlockPtr = nullptr);

			/** Returns the variable with a given label. If the variable doesn't exist, it will be created with the
			 *  given type and defining block options. */
			VariablePtr getVariable(const std::string &, const TypePtr, BasicBlockPtr = nullptr);

			/** Returns a pointer to the entry block. */
			BasicBlockPtr getEntry();

			/** Returns the calling convention of the function. It's chosen based on the number of arguments and whether
			 *  the function is variadic. */
			CallingConvention getCallingConvention() const;

			/** Performs liveness analysis on all variables. Requires ϕ-instructions to still be present. */
			void computeLiveness();

			/** Resets the liveness data for all variables. */
			void resetLiveness();

			/** Returns a set of all blocks where a given variable or any of its aliases are live-in. */
			std::unordered_set<BasicBlockPtr> getLiveIn(const VariablePtr &) const;

			/** Returns a set of all blocks where a given variable or any of its aliases are live-out. */
			std::unordered_set<BasicBlockPtr> getLiveOut(const VariablePtr &) const;

			/** Returns whether the variable's live-out set is non-empty. */
			bool isLiveOutAnywhere(const VariablePtr &) const;

			/** Returns the compiled assembly code. */
			std::string toString();

			/** Returns the function header as a formatted string. */
			std::string headerString() const;

			/** Prints debug information about the function. */
			void debug(std::ostream &);

			void debug() { debug(std::cerr); }

			/** Prints debug information about the function. */
			void debug(bool do_blocks, bool linear, bool vars, bool block_liveness, bool read_written,
			           bool var_liveness, bool render, bool estimations, bool aliases, bool stack, bool liveness,
			           std::ostream & = std::cerr);

			/** Prints debug information about the allocated stack locations. */
			void debugStack(std::ostream & = std::cerr) const;

			bool isNaked() const;

			/** Finds a spill stack location for a variable. */
			StackLocation & getSpill(VariablePtr, bool create = false, bool *created = nullptr);

			/** Computes a getelementptr value, places the result in a variable before the given instruction and returns
			 *  the variable as a value. */
			std::shared_ptr<LocalValue> replaceGetelementptrValue(std::shared_ptr<GetelementptrValue>, InstructionPtr);

			VariablePtr makeVariable(ValuePtr, InstructionPtr, TypePtr = nullptr);

			/** Through questionable methods, this function ensures that all variables with the same numeric ID share
			 *  the same register assignment. */
			void hackVariables();

			Graph makeDependencyGraph() const;

			void makeInitialDebugIndex();

			std::shared_ptr<Clobber> clobber(const InstructionPtr &, int reg);

			std::shared_ptr<Unclobber> unclobber(const InstructionPtr &, const std::shared_ptr<Clobber> &);

			/** Convenience method for creating a precolored assembler register. */
			VariablePtr mx(unsigned char, BasicBlockPtr);

			/** Convenience method for creating a precolored assembler register. */
			VariablePtr mx(unsigned char, InstructionPtr);

			/** Convenience method for creating a precolored argument register. */
			VariablePtr ax(unsigned char, BasicBlockPtr);

			/** Convenience method for creating a precolored argument register. */
			VariablePtr ax(unsigned char, InstructionPtr);

			/** Convenience method for creating a precolored $m0 register. */
			VariablePtr m0(BasicBlockPtr);

			/** Convenience method for creating a precolored $m0 register. */
			VariablePtr m0(InstructionPtr);

			/** Convenience method for creating a precolored $fp register. */
			VariablePtr fp(BasicBlockPtr);

			/** Convenience method for creating a precolored $fp register. */
			VariablePtr fp(InstructionPtr);

			/** Convenience method for creating a precolored $sp register. */
			VariablePtr sp(BasicBlockPtr);

			/** Convenience method for creating a precolored $sp register. */
			VariablePtr sp(InstructionPtr);

			/** Convenience method for creating a precolored $0 register. */
			VariablePtr zero(BasicBlockPtr);

			/** Convenience method for creating a precolored $0 register. */
			VariablePtr zero(InstructionPtr);

			/** Convenience method for creating a precolored $lo register. */
			VariablePtr lo(BasicBlockPtr);

			/** Convenience method for creating a precolored $lo register. */
			VariablePtr lo(InstructionPtr);

			template <typename Ins, bool Reindex = true, typename... Args>
			std::shared_ptr<Ins> insertBefore(const InstructionPtr &anchor, Args &&...args) {
				auto out = std::make_shared<Ins>(std::forward<Args>(args)...);
				insertBefore(anchor, out, Reindex)->setDebug(*anchor, true);
				return out;
			}

			template <typename Ins, bool Reindex = true, typename... Args>
			std::shared_ptr<Ins> insertAfter(const InstructionPtr &anchor, Args &&...args) {
				auto out = std::make_shared<Ins>(std::forward<Args>(args)...);
				insertAfter(anchor, out, Reindex)->setDebug(*anchor, true);
				return out;
			}
	};
}
