#ifndef COMPILER_CFGDATA_H_
#define COMPILER_CFGDATA_H_

#include <unordered_set>

#include "compiler/Variable.h"

namespace LL2W {
	/** Used as the data field of a node in a CFG. */
	struct CFGData {
		std::unordered_set<Variable *> uses, definitions;
		CFGData() {}
	};
}

#endif
