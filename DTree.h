#include "Graph.h"

namespace LL2W {
	class DTree: public Graph {
		public:
			/** Constructs a dominator tree from a graph. The dominator tree is a tree in which each node of the
			 *  original graph is linked to by its immediate dominator. */
			DTree(Graph &, Node &);
			DTree(Graph &, const std::string &);

			/** Returns a map of every node in the graph to its immediate dominator. */
			std::unordered_map<Node *, Node *> dominators() const;
	};
}
