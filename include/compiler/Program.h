#pragma once

#include <list>
#include <unordered_map>
#include <unordered_set>

#include "compiler/File.h"
#include "compiler/Function.h"
#include "parser/AliasDef.h"
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
			std::map<int, std::unordered_set<ParAttr>> parattrs;
			std::unordered_map<const std::string *, AliasDef *> aliases;
			std::map<int, File> files;

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
