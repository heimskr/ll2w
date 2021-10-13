#pragma once

#include <string>

namespace LL2W {
	class ASTNode;

	class Subprogram {
		public:
			std::string name, linkageName;
			int scope, file, line, type, scopeLine, unit, declaration, retainedNodes;
			/** The index of the subprogram within the debug data section, not within the LLVM IR. */
			int index = -1;

			Subprogram(const ASTNode &);

			/** This function returns the regular name if it isn't empty or the linkage name otherwise.
			 *  Removes quotes. */
			std::string getName() const;

		private:
			int parseBang(const ASTNode &);
	};
}
