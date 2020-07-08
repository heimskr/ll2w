#ifndef PASS_COLORINGALLOCATOR_H_
#define PASS_COLORINGALLOCATOR_H_

#include <memory>

#include "graph/Graph.h"

namespace LL2W {
	class Function;
	class Variable;
}

namespace LL2W::Passes {
	/** Assigns registers using a graph coloring algorithm. Returns the number of necessary spills. */
	int allocateColoring(Function &);

	std::shared_ptr<Variable> selectLowestSpillCost(Function &);

	/** Creates an interference graph of all a function's variables. */
	Graph makeInterferenceGraph(Function &);
}

#endif
