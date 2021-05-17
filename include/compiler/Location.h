#pragma once

namespace LL2W {
	struct Location {
		int line, column, scope;
		Location(int line_, int column_, int scope_): line(line_), column(column_), scope(scope_) {}
	};
}
