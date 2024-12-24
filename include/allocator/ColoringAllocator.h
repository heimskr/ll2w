#pragma once

#include <memory>
#include <unordered_set>

#include "allocator/Allocator.h"
#include "compiler/Variable.h"
#include "graph/Graph.h"

namespace LL2W {
	/** Assigns registers using a graph coloring algorithm. */
	class ColoringAllocator: public Allocator {
		public:
			Graph interference;

			ColoringAllocator(Function &);

			bool needsCFG() const final { return true; }

			/** Adjusts the interference graph after a spill. More targeted and performant than remaking the whole graph from scratch. */
			void afterSpill(VariablePtr spilled_var, std::span<VariablePtr> new_vars) final;

			/** Creates an interference graph of all the function's variables. */
			void makeInterferenceGraph();

			/** Selects the variable whose corresponding node in the interference graph has the highest degree. */
			std::shared_ptr<Variable> selectHighestDegree(int *degree_out = nullptr) const;

			std::shared_ptr<Variable> selectChaitin() const;

			Result firstAttempt() final;

			/** Makes an attempt to allocate registers. If the graph is uncolorable, the function attempts to spill a
			 *  variable. If one was spilled, it returns Spilled; otherwise, it returns NotSpilled. If the graph was
			 *  colorable, it returns Success. */
			Result attempt() final;

		private:
			std::map<std::set<int>, Node *> cachedPrecolored;
	};
}
