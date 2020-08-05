#ifndef ALLOCATOR_COLORINGALLOCATOR_H_
#define ALLOCATOR_COLORINGALLOCATOR_H_

#include <memory>
#include <unordered_set>

#include "allocator/Allocator.h"
#include "graph/Graph.h"

namespace LL2W {
	class Function;
	class Variable;
}

namespace LL2W {
	/** Assigns registers using a graph coloring algorithm. */
	class ColoringAllocator: public Allocator {
		private:
			Graph interference;

			/** Creates an interference graph of all the function's variables. */
			void makeInterferenceGraph();

			/** Selects the variable whose corresponding node in the interference graph has the highest degree. */
			std::shared_ptr<Variable> selectHighestDegree() const;

			/** Selects the variable with the lowest spill cost. */
			std::shared_ptr<Variable> selectLowestSpillCost() const;

			std::unordered_set<int> triedIDs;
			std::unordered_set<std::string> triedLabels;

		public:
			using Allocator::Allocator;

			/** Makes an attempt to allocate registers. If the graph is uncolorable, the function attempts to spill a
			 *  variable. If one was spilled, it returns Spilled; otherwise, it returns NotSpilled. If the graph was
			 *  colorable, it returns Success. */
			Result attempt() override;
	};

	// int allocateColoring(Function &);


}

#endif
