#ifndef COMPILER_PROGRAM_H_
#define COMPILER_PROGRAM_H_

#include <list>
#include <unordered_map>

#include "compiler/Function.h"

namespace LL2W {
	class ASTNode;

	class Program {
		public:
			std::unordered_map<std::string, Function> functions;

			Program(const ASTNode &);
			void debug() const;
	};
}

#endif
