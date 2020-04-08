#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>
#include <optional>

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

			/** A set of the numeric labels of all the function's basic blocks. */
			std::unordered_set<int> bbLabels;

			/** Contains the AST node this object was constructed from. */
			const ASTNode *astnode;

			/** Whether the function has been compiled yet. */
			bool compiled = false;

			/** Whether liveness analysis has been performed on the function's variables yet. */
			bool livenessComputed = false;

			/** Maps nodes to their successor merge sets. */
			Node::Map succMergeSets;

			/** Maps variables to their stack locations. */
			std::map<std::shared_ptr<Variable>, StackLocation *> variableLocations;

		public:
			Program *parent = nullptr;

			/** A pointer to a list of all function arguments. */
			std::vector<FunctionArgument> *arguments = nullptr;

			/** A pointer to an interned string containing the name of the function. */
			const std::string *name;

			TypePtr returnType;

			/** A list of all basic blocks in the order they appear. */
			std::list<std::shared_ptr<BasicBlock>> blocks;

			/** A list of all instructions in the order they appear in the source code. */
			std::list<std::shared_ptr<Instruction>> linearInstructions;

			/** Maps numeric labels to variables. This is the main storage for the function's variables. */
			std::map<int, VariablePtr> variableStore;

			/** Maps offsets to stack location information. */
			std::map<int, StackLocation> stack;

			/** Maps interned strings representing labels to their corresponding basic blocks. This is the main storage
			 *  for the function's basic blocks. */
			std::map<const std::string *, std::shared_ptr<BasicBlock>> bbMap;

			/** Maps basic blocks to their corresponding CFG nodes. */
			std::unordered_map<const BasicBlock *, Node *> bbNodeMap;

			/** The control-flow graph computed by makeCFG. */
			CFG cfg;

			/** The dominator tree computed from the control-flow graph. */
			std::optional<DTree> dTree;

			/** The dominator tree computed from the control-flow graph with J-edges included. */
			std::optional<DJGraph> djGraph;

			/** Maps nodes to their merge sets. */
			Node::Map mergeSets;

			/** The number of random walks that have been performed on the control flow graph. */
			int walkCount = 0;

			/** The number of bytes reserved on the stack for variables and spills. */
			int stackSize = 0;

			Function(Program &, const ASTNode &);

			/** Scans through the function AST for block headers and populates the list of BasicBlocks accordingly. */
			void extractBlocks();

			/** Copies use/definition information from the BasicBlocks into the Variables. */
			void extractVariables(bool reset = false);

			/** Computes a given node's merge set. */
			void computeSuccMergeSet(Node *);

			/** Recreates linearInstructions from each BasicBlock's vector of instructions and renumbers the
			 *  instructions. */
			void relinearize();

			/** Returns a label that hasn't yet been used for a basic block or variable. */
			int newLabel() const;

			/** Produces a new variable with an as yet unused label. */
			std::shared_ptr<Variable> newVariable(TypePtr = nullptr, std::shared_ptr<BasicBlock> = nullptr);

			/** Tries to spill a variable. Returns true if any instructions were inserted. */
			bool spill(std::shared_ptr<Variable>);

			/** Returns a pointer to the instruction following a given instruction. */
			std::shared_ptr<Instruction> after(std::shared_ptr<Instruction>);

			/** Returns a pointer to the basic block following a given basic block. */
			std::shared_ptr<BasicBlock> after(std::shared_ptr<BasicBlock>);

			/** Inserts one instruction after another. */
			void insertAfter(std::shared_ptr<Instruction> base, std::shared_ptr<Instruction> new_instruction,
				bool reindex = true);

			/** Inserts one instruction before another. */
			void insertBefore(std::shared_ptr<Instruction> base, std::shared_ptr<Instruction> new_instruction,
				bool reindex = true);

			/** Removes in a given block a branch instruction that redundantly jumps to the immediately following block
			 *  if such a branch instruction exists. */
			void removeUselessBranch(std::shared_ptr<BasicBlock>);

			/** Reassigns indices to all instructions. */
			void reindexInstructions();

			/** Reassigns indices to all basic blocks. */
			void reindexBlocks();

			/** Splits a basic block after a given instruction. */
			std::shared_ptr<BasicBlock> splitBlock(std::shared_ptr<BasicBlock>, std::shared_ptr<Instruction>);

			/** Returns a list of intervals sorted by start point in ascending order. */
			std::list<Interval> sortedIntervals();

			/** Creates a precolored variable corresponding to any register. */
			VariablePtr makePrecoloredVariable(unsigned char, std::shared_ptr<BasicBlock>);

			/** Creates a precolored variable corresponding to a given $mx (assembler-reserved) register. */
			VariablePtr makeAssemblerVariable(unsigned char, std::shared_ptr<BasicBlock>);

			/** Returns a given basic block's CFG node. */
			Node & operator[](const BasicBlock &) const;

			/** Returns the number of arguments the function takes. */
			int getArity() const;

			/** Returns whether the function is variadic (i.e., whether it takes a variable number of arguments). */
			bool isVariadic() const;

			/** Transforms a string like "%64" into "__functionname_label64". */
			std::string transformLabel(const std::string &) const;

			/** Computes the merge sets for all nodes in the CFG. */
			void computeSuccMergeSets();

			/** Sets the pvar names in all instructions to those of the connected variables. */
			void updateInstructionNodes();

			/** Removes the register assignments for all variables. If its argument is true, it won't reset variables
			 *  that have been assigned special registers. */
			void resetRegisters(bool respectful = true);

			/** Performs a full set of compiler passes on the function. */
			void compile();

			/** Assigns special argument registers to variables in a list of intervals as appropriate. */
			void precolorArguments(std::list<Interval> &);

			/** Assigns or looks up a stack location for a given variable. */
			StackLocation & addToStack(std::shared_ptr<Variable>, StackLocation::Purpose, int width = -1);

			/** Removes an instruction from the function. */
			void remove(std::shared_ptr<Instruction>);

			/** Replaces the first instruction with the second. Not safe to call while iterating. */
			void replace(std::shared_ptr<Instruction>, std::shared_ptr<Instruction>);

			/** Merges two basic blocks. The after-block is absorbed into the before-block. The caller of this function
			 *  is responsible for recreating the CFG and reindexing all blocks. */
			void mergeBlocks(std::shared_ptr<BasicBlock> before, std::shared_ptr<BasicBlock> after);

			/** Returns the variable with a given label. If the variable doesn't exist, an exception will be thrown. */
			std::shared_ptr<Variable> getVariable(int);

			/** Returns the variable with a given label. If the variable doesn't exist, an exception will be thrown. */
			std::shared_ptr<Variable> getVariable(const std::string &);

			/** Returns the variable with a given label. If the variable doesn't exist, it will be created with the
			 *  given type and defining block options. */
			std::shared_ptr<Variable> getVariable(int, const TypePtr, BasicBlockPtr = nullptr);

			/** Returns the variable with a given label. If the variable doesn't exist, it will be created with the
			 *  given type and defining block options. */
			std::shared_ptr<Variable> getVariable(const std::string &, const TypePtr, BasicBlockPtr = nullptr);

			/** Returns a pointer to the entry block. */
			BasicBlockPtr getEntry();

			/** Returns the calling convention of the function. It's chosen based on the number of arguments and whether
			 *  the function is variadic. */
			CallingConvention getCallingConvention() const;

			/** Performs liveness analysis on all variables. */
			void computeLiveness();

			/** Resets the liveness data for all variables. */
			void resetLiveness();

			/** Determines whether a variable is live-in at a given basic block. */
			bool isLiveIn(BasicBlock &, VariablePtr);

			/** Determines whether a variable is live-out at a given basic block. */
			bool isLiveOut(BasicBlock &, VariablePtr);

			/** Returns the compiled assembly code. */
			std::string toString();

			/** Prints debug information about the function. */
			void debug();

			/** Prints debug information about the merge sets. */
			void debugMergeSets() const;

			/** Prints debug information about the allocated stack locations. */
			void debugStack() const;
	};
}

#endif
