#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>
#include <optional>

#include "compiler/BasicBlock.h"
#include "compiler/CFG.h"
#include "compiler/Variable.h"
#include "graph/DJGraph.h"
#include "graph/DTree.h"

namespace LL2W {
	class ASTNode;

	/**
	 * StackOnly: all parameters are pushed to the stack, right-to-left. Used for variadic functions.
	 * Reg16: The first sixteen arguments are put in registers $a0 through $af, left-to-right. The rest are pushed to
	 *        the stack right-to-left.
	 */
	enum class CallingConvention {StackOnly, Reg16};

	class Function {
		private:
			std::map<int, Variable> variableStore;
			std::unordered_map<const BasicBlock *, Node *> bbMap;
			const ASTNode *astnode;
			bool extracted = false, livenessComputed = false;
			std::optional<DJGraph> djGraph;
			std::optional<DTree> dTree;
			Node::Map mergeSets;
			Node::Map succMergeSets;
			int walkCount = 0;

			void extractBlocks();
			void extractVariables();
			void computeSuccMergeSet(Node *);

			Node & operator[](const BasicBlock &) const;

		public:
			const std::string *name;
			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;
			/** A vector of all instructions in the order they appear in the source code. */
			std::vector<std::shared_ptr<Instruction>> linearInstructions;
			FunctionArgs *arguments = nullptr;
			CFG cfg;

			Function(const ASTNode &);

			int arity() const;
			bool variadic() const;
			CFG & makeCFG();
			/** Randomly walks through the CFG and counts executions of each basic block. */
			void walkCFG(size_t walks = 1, unsigned int seed = 0, size_t inner_limit = 1000);
			void computeSuccMergeSets();
			void extract();
			Variable & getVariable(int label);
			BasicBlock & getEntry();
			CallingConvention getCallingConvention() const;
			void computeLiveness();
			bool isLiveIn(BasicBlock &, Variable &);
			bool isLiveOut(BasicBlock &, Variable &);
			void debug();
			void debugMergeSets() const;
	};
}

#endif
