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
			std::unordered_set<int> triedIDs;
			std::unordered_set<std::string> triedLabels;

		public:
			Graph interference;

			using Allocator::Allocator;

			/** Creates an interference graph of all the function's variables. */
			void makeInterferenceGraph();

			/** Selects the variable whose corresponding node in the interference graph has the highest degree. */
			std::shared_ptr<Variable> selectHighestDegree(int *degree_out = nullptr) const;

			/** Selects the variable with the lowest spill cost. */
			std::shared_ptr<Variable> selectLowestSpillCost() const;

			/** Makes an attempt to allocate registers. If the graph is uncolorable, the function attempts to spill a
			 *  variable. If one was spilled, it returns Spilled; otherwise, it returns NotSpilled. If the graph was
			 *  colorable, it returns Success. */
			Result attempt() override;

			const std::unordered_set<int> getTriedIDs() const { return triedIDs; }
			const std::unordered_set<std::string> getTriedLabels() const { return triedLabels; }
	};

	// int allocateColoring(Function &);


}

#endif
