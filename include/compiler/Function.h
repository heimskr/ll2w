#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>

// #include "gra
#include "compiler/BasicBlock.h"

namespace LL2W {
	class ASTNode;

	class Function {
		private:
			// std::list<CFGData> dataStore;

		public:
			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;
			FunctionArgs *arguments = nullptr;
			// Graph cfg;

			Function(const ASTNode &);

			// Graph & makeCFG();
			void debug() const;
	};
}

#endif
