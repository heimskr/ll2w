#pragma once

#include <string>

namespace LL2W {
	class ASTNode;

	class Subprogram {
		public:
			std::string name, linkageName;
			int scope, file, line, type, scopeLine, unit, declaration, retainedNodes;

			Subprogram(const ASTNode &);

		private:
			int parseBang(const ASTNode &);
	};
}