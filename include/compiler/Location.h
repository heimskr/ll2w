#pragma once

namespace LL2W {
	class ASTNode;

	struct Location {
		int line, column, scope;
		int file = -1;
		/** The index of the location within the debug data section, not within the LLVM IR. */
		int index = -1;
		Location(int line_, int column_, int scope_): line(line_), column(column_), scope(scope_) {}
		Location(const ASTNode &);
	};
}
