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

	class Function {
		private:
			Program *parent = nullptr;
			std::map<int, VariablePtr> variableStore;
			std::unordered_set<int> bbLabels;
			std::unordered_map<const BasicBlock *, Node *> bbNodeMap;
			std::map<const std::string *, std::shared_ptr<BasicBlock>> bbMap;
			const ASTNode *astnode;
			bool extracted = false, livenessComputed = false;
			std::optional<DJGraph> djGraph;
			std::optional<DTree> dTree;
			Node::Map mergeSets;
			Node::Map succMergeSets;
			int walkCount = 0;
			std::map<int, StackLocation> stack;

			void extractBlocks();
			void extractVariables();
			void computeSuccMergeSet(Node *);
			/** Recreates linearInstructions from each BasicBlock's vector of instructions and renumbers the
			 *  instructions. */
			void relinearize();
			/** Renumbers all instructions based on the order they appear in each BasicBlock's instructions vector. */
			void assignIndices();
			/** Merges arguments of phi instructions into single variables. */
			void coalescePhi();
			int nextStackOffset() const;
			std::shared_ptr<Variable> newVariable(Type * = nullptr, std::shared_ptr<BasicBlock> = nullptr);
			void removeUselessBranches();

			std::list<Interval> sortedIntervals();

			Node & operator[](const BasicBlock &) const;

		public:
			const std::string *name;
			/** A list of all basic blocks in the order they appear. */
			std::list<std::shared_ptr<BasicBlock>> blocks;
			/** A list of all instructions in the order they appear in the source code. */
			std::list<std::shared_ptr<Instruction>> linearInstructions;
			FunctionArgs *arguments = nullptr;
			CFG cfg;

			Function(Program &, const ASTNode &);

			int arity() const;
			bool variadic() const;
			CFG & makeCFG();
			/** Randomly walks through the CFG and counts executions of each basic block. */
			void walkCFG(size_t walks = 1, unsigned int seed = 0, size_t inner_limit = 1000);
			void computeSuccMergeSets();
			void fillLocalValues();
			void updateInstructionNodes();
			void extract();
			void uncolorAll();
			void precolorArguments(std::list<Interval> &);
			/** Assigns registers using a linear scan algorithm. Returns the number of necessary spills. */
			int linearScan();
			void remove(std::shared_ptr<Instruction>);
			std::shared_ptr<Variable> getVariable(int);
			std::shared_ptr<Variable> getVariable(const std::string &);
			std::shared_ptr<Variable> getVariable(int, const Type *, BasicBlockPtr = nullptr);
			std::shared_ptr<Variable> getVariable(const std::string &, const Type *, BasicBlockPtr = nullptr);
			BasicBlockPtr getEntry();
			CallingConvention getCallingConvention() const;
			void computeLiveness();
			bool isLiveIn(BasicBlock &, VariablePtr);
			bool isLiveOut(BasicBlock &, VariablePtr);
			void debug();
			void debugMergeSets() const;
	};
}

#endif
