#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>
#include <optional>

#include "allocator/Allocator.h"
#include "compiler/BasicBlock.h"
#include "compiler/CFG.h"
#include "compiler/Interval.h"
#include "compiler/StackLocation.h"
#include "compiler/Variable.h"
#include "graph/DJGraph.h"
#include "graph/DTree.h"
#include "parser/FunctionArgs.h"

namespace LL2W {
	class ASTNode;
	class ColoringAllocator;
	struct FunctionArgs;
	class Program;

	/**
	 * StackOnly: all parameters are pushed to the stack, right-to-left. Used for variadic functions.
	 * Reg16: The first sixteen arguments are put in registers $a0 through $af, left-to-right. The rest are pushed to
	 *        the stack right-to-left.
	 */
	enum class CallingConvention {StackOnly, Reg16};

	/**
	 * Represents a function and contains code for converting functions from LLVM's intermediate representation into
	 * Why.js bytecode.
	 */
	class Function {
		private:
			/** A pointer to an AST node that contains data about the function's arguments. */
			std::shared_ptr<FunctionArgs> argumentsNode = nullptr;

			/** A set of the labels of all the function's basic blocks. */
			std::unordered_set<const std::string *> bbLabels;

			/** Contains the AST node this object was constructed from. */
			const ASTNode *astnode;

			int initialStackSize = 0;

			/** Maps variables to their stack locations. */
			std::map<VariablePtr, StackLocation *> variableLocations;

			std::unordered_map<unsigned char, VariablePtr> assemblerVariables;

			void upAndMark(BasicBlockPtr, VariablePtr);

			std::unordered_set<std::shared_ptr<BasicBlock>> getLive(std::shared_ptr<Variable>,
				std::function<std::unordered_set<std::shared_ptr<Variable>> &(const std::shared_ptr<BasicBlock> &)>)
				const;

		public:
			Program *parent = nullptr;

			/** A pointer to a list of all function arguments. */
			std::vector<FunctionArgument> *arguments = nullptr;

			/** A pointer to an interned string containing the name of the function. */
			const std::string *name;

			/** The type of the returned value. */
			TypePtr returnType;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlockPtr> blocks;

			/** A list of all instructions in the order they appear in the source code. */
			std::list<std::shared_ptr<Instruction>> linearInstructions;

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

			/** Used by passes to indicate which instructions they produced so that later passes can pick up where they
			 *  left off after other things have occurred. For example, SetupCalls uses this to record the moves from
			 *  result registers into variables in case the variable is larger than one physical register and the move
			 *  needs to be split up after register allocation. */
			std::unordered_map<std::string, std::list<std::shared_ptr<Instruction>>> categories;

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

			/** The number of bytes pushed to the stack when InsertPrologue saves registers, including $fp and $sp. */
			int initialPushedBytes = -1;

			int debugIndex = -1;
			int initialDebugIndex = -1;

			ColoringAllocator *allocator = nullptr;

			bool initialDone = false, allocationDone = false, finalDone = false;

			Allocator::Result lastAllocationResult;

			Function(const Function &) = delete;
			Function(Function &&) = delete;
			Function(Program &, const ASTNode &);

			~Function();

			Allocator::Result attemptAllocation();

			/** Scans through the function AST for block headers and populates the list of BasicBlocks accordingly. */
			void extractBlocks();

			/** Copies use/definition information from the BasicBlocks into the Variables. */
			void extractVariables(bool reset = false);

			/** Recreates linearInstructions from each BasicBlock's vector of instructions and renumbers the
			 *  instructions. */
			void relinearize();

			/** Returns a label that hasn't yet been used for a basic block or variable. */
			Variable::ID newLabel() const;

			/** Produces a new variable with an as yet unused label. */
			VariablePtr newVariable(TypePtr = nullptr, BasicBlockPtr = nullptr);

			/** Tries to spill a variable. Returns true if any instructions were inserted. */
			bool spill(VariablePtr, bool doDebug = false);

			void markSpilled(VariablePtr);

			bool isSpilled(VariablePtr) const;

			bool canSpill(VariablePtr);

			bool isArgument(Variable::ID) const;

			/** Returns the first instruction in the function that isn't a label or a comment. */
			std::shared_ptr<Instruction> firstInstruction(bool includeComments = false);

			/** Returns a pointer to the instruction following a given instruction. */
			std::shared_ptr<Instruction> after(std::shared_ptr<Instruction>);

			/** Returns a pointer to the basic block following a given basic block. */
			BasicBlockPtr after(BasicBlockPtr);

			/** Inserts one instruction after another. Returns the inserted instructin=on. */
			std::shared_ptr<Instruction> insertAfter(std::shared_ptr<Instruction> base,
				std::shared_ptr<Instruction> new_instruction, bool reindex = true);

			/** Inserts one instruction before another. Returns the inserted instruction. */
			std::shared_ptr<Instruction> insertBefore(std::shared_ptr<Instruction> base,
				std::shared_ptr<Instruction> new_instruction, bool reindex = true);

			/** Inserts one instruction before another and adds a comment before the inserted instruction.
			 *  Returns the inserted instruction. */
			std::shared_ptr<Instruction> insertBefore(std::shared_ptr<Instruction> base,
				std::shared_ptr<Instruction> new_instruction, const std::string &, bool reindex = true);

			/** Inserts one instruction before another and adds a comment before the inserted instruction.
			 *  Returns the inserted instruction. */
			std::shared_ptr<Instruction> insertBefore(std::shared_ptr<Instruction> base,
				std::shared_ptr<Instruction> new_instruction, const char *, bool reindex = true);

			/** Inserts a comment before an instruction. */
			std::shared_ptr<Instruction> comment(std::shared_ptr<Instruction>, const std::string &,
				bool reindex = true);

			/** Removes in a given block a branch instruction that redundantly jumps to the immediately following block
			 *  if such a branch instruction exists. */
			void removeUselessBranch(BasicBlockPtr);

			/** Reassigns indices to all instructions. */
			void reindexInstructions();

			/** Reassigns indices to all basic blocks. */
			void reindexBlocks();

			/** Splits a basic block after a given instruction. */
			BasicBlockPtr splitBlock(BasicBlockPtr, std::shared_ptr<Instruction>);

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

			/** Assigns special argument registers to variables in a list of intervals as appropriate. */
			void precolorArguments(std::list<Interval> &);

			/** Assigns special argument registers to all variables as appropriate. */
			void precolorArguments();

			/** Assigns or looks up a stack location for a given variable. */
			StackLocation & addToStack(VariablePtr, StackLocation::Purpose, int width = -1);

			/** Removes an instruction from the function. */
			void remove(std::shared_ptr<Instruction>);

			/** Removes a basic block from the function. Any function that calls this should also be sure to relinearize
			 *  instructions after calling this. */
			void remove(BasicBlockPtr);

			/** Replaces the first instruction with the second. Not safe to call while iterating. */
			void replace(std::shared_ptr<Instruction>, std::shared_ptr<Instruction>);

			/** Loads a 64-bit value into a new variable before an instruction by means of set and lui. */
			VariablePtr get64(std::shared_ptr<Instruction> before, unsigned long, bool reindex = false);

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
			std::unordered_set<std::shared_ptr<BasicBlock>> getLiveIn(std::shared_ptr<Variable>) const;

			/** Returns a set of all blocks where a given variable or any of its aliases are live-out. */
			std::unordered_set<std::shared_ptr<BasicBlock>> getLiveOut(std::shared_ptr<Variable>) const;

			/** Returns the compiled assembly code. */
			std::string toString();

			/** Returns the function header as a formatted string. */
			std::string headerString() const;

			/** Prints debug information about the function. */
			void debug();

			/** Prints debug information about the function. */
			void debug(bool doBlocks, bool linear, bool vars, bool blockLiveness, bool readWritten, bool varLiveness,
			           bool render, bool estimations, bool aliases, bool stack);

			/** Prints debug information about the allocated stack locations. */
			void debugStack() const;

			bool isNaked() const;

			/** Finds a spill stack location for a variable. */
			StackLocation & getSpill(VariablePtr, bool create = false, bool *created = nullptr);

			/** Computes a getelementptr value, places the result in a variable before the given instruction and returns
			 *  the variable as a value. */
			std::shared_ptr<LocalValue> replaceGetelementptrValue(std::shared_ptr<GetelementptrValue>,
			                                                      std::shared_ptr<Instruction>);

			/** Through questionable methods, this function ensures that all variables with the same numeric ID share
			 *  the same register assignment. */
			void hackVariables();

			Graph makeDependencyGraph() const;

			void makeInitialDebugIndex();

			/** Convenience method for creating a precolored assembler register. */
			VariablePtr mx(unsigned char, BasicBlockPtr);

			/** Convenience method for creating a precolored assembler register. */
			VariablePtr mx(unsigned char, std::shared_ptr<Instruction>);

			/** Convenience method for creating a precolored argument register. */
			VariablePtr ax(unsigned char, BasicBlockPtr);

			/** Convenience method for creating a precolored argument register. */
			VariablePtr ax(unsigned char, std::shared_ptr<Instruction>);

			/** Convenience method for creating a precolored $m0 register. */
			VariablePtr m0(BasicBlockPtr);

			/** Convenience method for creating a precolored $m0 register. */
			VariablePtr m0(std::shared_ptr<Instruction>);

			/** Convenience method for creating a precolored $fp register. */
			VariablePtr fp(BasicBlockPtr);

			/** Convenience method for creating a precolored $fp register. */
			VariablePtr fp(std::shared_ptr<Instruction>);

			/** Convenience method for creating a precolored $sp register. */
			VariablePtr sp(BasicBlockPtr);

			/** Convenience method for creating a precolored $sp register. */
			VariablePtr sp(std::shared_ptr<Instruction>);
	};
}

#endif
