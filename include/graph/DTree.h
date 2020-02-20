#ifndef DTREE_H_
#define DTREE_H_

#include <unordered_set>

#include "Graph.h"

namespace LL2W {
	class DTree: public Graph {
		public:
			Node *startNode = nullptr;
			std::unordered_map<Node *, int> levels;

			/** Constructs a dominator tree from a graph. The dominator tree is a tree in which each node of the
			 *  original graph is linked to by its immediate dominator. */
			DTree(Graph &, Node &);
			DTree(Graph &, const std::string &);

			/** Calculates the level of each node in the dominator tree. */
			void findLevels();

			/** Finds the label of the common dominator of a set of nodes. */
			std::string commonDominator(std::vector<Node *>);
			std::string commonDominator(const std::vector<std::string> &);

			/** Returns a map of every node in the graph to its immediate dominator. */
			std::unordered_map<Node *, Node *> immediateDominators() const;

			/** Returns a map that maps each node to a set of all its strict dominators. */
			Node::Map strictDominators() const;

			/** Returns a map that maps each node's label to a set of the labels of all its strict dominators. */
			std::unordered_map<std::string, std::unordered_set<std::string>> strictDominatorLabels() const;
	};
}

#endif
