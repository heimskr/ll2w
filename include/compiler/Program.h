#ifndef COMPILER_PROGRAM_H_
#define COMPILER_PROGRAM_H_

#include <list>
#include <unordered_map>
#include <unordered_set>

#include "compiler/Function.h"
#include "parser/FunctionHeader.h"

namespace LL2W {
	class ASTNode;

	class Program {
		public:
			std::unordered_map<std::string, Function *> functions;
			std::string sourceFilename;
			std::unordered_map<std::string, FunctionHeader *> declarations;
			std::map<std::string, GlobalVarDef *> globals; // keys include the "@"
			std::map<int, std::unordered_set<FnAttr>> fnattrs;

			Program(const ASTNode &);
			~Program();

			/** Compiles all the functions in the program. */
			void compile();

			/** Returns the source code of the program. */
			std::string toString();

			/** Outputs the data section (excluding the #data header) to a stream. */
			void dataSection(std::ostream &);

			/** Returns the size (in bits) of the global variable with a given name.
			 *  The name should include an initial "@". */
			int symbolSize(const std::string &) const;

			/** Prints debug information for all the functions in the program. */
			void debug();
	};
}

#endif
