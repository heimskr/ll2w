#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>

#include "graph/Graph.h"
#include "compiler/BasicBlock.h"
#include "compiler/CFGData.h"
#include "compiler/Variable.h"

namespace LL2W {
	class ASTNode;

	class Function {
		private:
			std::map<int, Variable> variableStore;
			void extractVariables();
			bool extracted = false;

		public:
			const std::string *name;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;

			FunctionArgs *arguments = nullptr;
			Graph cfg;

			Function(const ASTNode &);

			Graph & makeCFG();
			void extract();
			Variable & getVariable(int label);
			void debug() const;
	};
}

#endif
