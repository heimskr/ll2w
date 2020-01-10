#ifndef DTREE_H_
#define DTREE_H_

#include <unordered_set>

#include "Graph.h"

namespace LL2W {
	class DTree: public Graph {
		public:
			/** Constructs a dominator tree from a graph. The dominator tree is a tree in which each node of the
			 *  original graph is linked to by its immediate dominator. */
			DTree(Graph &, Node &);
			DTree(Graph &, const std::string &);

			/** Returns a map of every node in the graph to its immediate dominator. */
			std::unordered_map<Node *, Node *> immediateDominators() const;

			/** Returns a map that maps each node to a set of all its strict dominators. */
			std::unordered_map<Node *, std::unordered_set<Node *>> strictDominators() const;

			std::unordered_map<std::string, std::unordered_set<std::string>> strictDominatorLabels() const;
	};
}

#endif
