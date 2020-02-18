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
			const ASTNode *astnode;
			bool extracted = false, livenessComputed = false;
			std::optional<DJGraph> djGraph;
			std::optional<DTree> dTree;
			Node::Map mergeSets;
			Node::Map succMergeSets;

			void extractBlocks();
			void extractVariables();
			void computeSuccMergeSet(Node *);

		public:
			const std::string *name;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;

			FunctionArgs *arguments = nullptr;
			CFG cfg;

			Function(const ASTNode &);

			int arity() const;
			bool variadic() const;
			CFG & makeCFG();
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
