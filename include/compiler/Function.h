#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>
#include <optional>

#include "compiler/BasicBlock.h"
#include "compiler/CFG.h"
#include "compiler/Variable.h"
#include "graph/DJGraph.h"

namespace LL2W {
	class ASTNode;

	class Function {
		private:
			std::map<int, Variable> variableStore;
			const ASTNode *astnode;
			bool extracted = false;
			std::optional<DJGraph> djGraph;
			Node::Map mergeSets;
			Node::Map succMergeSets;

			void extractBlocks();
			void extractVariables();
			Node::USet computeSuccMergeSet(Node *);

		public:
			const std::string *name;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;

			FunctionArgs *arguments = nullptr;
			CFG cfg;

			Function(const ASTNode &);

			CFG & makeCFG();
			void computeSuccMergeSets();
			void extract();
			Variable & getVariable(int label);
			BasicBlock & getEntry();
			bool isLiveIn(BasicBlock &, Variable &);
			void debug();
	};
}

#endif
