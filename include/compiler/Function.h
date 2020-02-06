#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>
#include <map>

#include "compiler/BasicBlock.h"
#include "compiler/CFG.h"
#include "compiler/Variable.h"

namespace LL2W {
	class ASTNode;

	class Function {
		private:
			std::map<int, Variable> variableStore;
			const ASTNode *astnode;
			void extractBlocks();
			void extractVariables();
			bool extracted = false;

		public:
			const std::string *name;

			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;

			FunctionArgs *arguments = nullptr;
			CFG cfg;

			Function(const ASTNode &);

			CFG & makeCFG();
			void extract();
			Variable & getVariable(int label);
			BasicBlock & getEntry();
			void debug() const;
	};
}

#endif
