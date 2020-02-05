#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>

#include "graph/Graph.h"
#include "compiler/BasicBlock.h"
#include "compiler/CFGData.h"
#include "compiler/Variable.h"

namespace LL2W {
	class ASTNode;

	class Function {
		private:
			std::unordered_map<int, Variable> variableStore;

		public:
			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;
			FunctionArgs *arguments = nullptr;
			Graph cfg;

			Function(const ASTNode &);

			Graph & makeCFG();
			void extractVariables();
			Variable & getVariable(int label);
			void debug() const;
	};
}

#endif
