#pragma once

#include <memory>
#include <unordered_set>

#include "allocator/Allocator.h"
#include "compiler/Variable.h"
#include "graph/Graph.h"

namespace LL2W {
	class Function;
}

namespace LL2W {
	/** Assigns registers using a graph coloring algorithm. */
	class ColoringAllocator: public Allocator {
		private:
			std::unordered_set<Variable::ID> triedIDs;
			std::unordered_set<std::string> triedLabels;

		public:
			Graph interference = Graph("interference");

			using Allocator::Allocator;

			/** Creates an interference graph of all the function's variables. */
			void makeInterferenceGraph();

			/** Selects the variable whose corresponding node in the interference graph has the highest degree. */
			std::shared_ptr<Variable> selectHighestDegree(int *degree_out = nullptr) const;

			/** Selects the variable with the lowest spill cost. */
			std::shared_ptr<Variable> selectLowestSpillCost() const;

			std::shared_ptr<Variable> selectMostLive(int *liveness_out = nullptr) const;

			std::shared_ptr<Variable> selectChaitin() const;

			/** Makes an attempt to allocate registers. If the graph is uncolorable, the function attempts to spill a
			 *  variable. If one was spilled, it returns Spilled; otherwise, it returns NotSpilled. If the graph was
			 *  colorable, it returns Success. */
			Result attempt() override;

			const decltype(triedIDs)    & getTriedIDs()    const { return triedIDs;    }
			const decltype(triedLabels) & getTriedLabels() const { return triedLabels; }
	};
}
