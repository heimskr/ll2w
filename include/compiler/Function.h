#ifndef COMPILER_FUNCTION_H_
#define COMPILER_FUNCTION_H_

#include <list>

#include "compiler/BasicBlock.h"

namespace LL2W {
	class ASTNode;

	class Function {
		public:
			/** A list of all basic blocks in the order they appear. */
			std::list<BasicBlock> blocks;

			Function(const ASTNode &);

			void debug() const;
	};
}

#endif
