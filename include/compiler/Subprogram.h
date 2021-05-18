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

		private:
			int parseBang(const ASTNode &);
	};
}
