#pragma once

#include <string>

namespace LL2W {
	class ASTNode;

	class Subprogram {
		public:
			std::string name;
			std::string linkageName;
			int scope = -1;
			int file = -1;
			int line = -1;
			int type = -1;
			int scopeLine = -1;
			int unit = -1;
			int declaration = -1;
			int retainedNodes = -1;
			/** The index of the subprogram within the debug data section, not within the LLVM IR. */
			int index = -1;

			Subprogram(const ASTNode &);

			/** This function returns the regular name if it isn't empty or the linkage name otherwise.
			 *  Removes quotes. */
			std::string getName() const;

		private:
			static int parseBang(const ASTNode &);
	};
}
