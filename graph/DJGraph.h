#ifndef DJGRAPH_H_
#define DJGRAPH_H_

#include <unordered_set>

#include "Graph.h"

namespace LL2W {
	class DJGraph: public Graph {
		private:
			Node::Map jMap;
			bool isJEdge(const Node &, const Node &) const;
			std::unordered_set<Node *> allInNodes(const Node &) const;
			int level(const Node &, const Node &start) const;
			Node * parent(const Node &, const Node &start) const;

		public:
			std::vector<std::pair<Node &, Node &>> jEdges;

			DJGraph(Graph &, Node &);
			DJGraph(Graph &, const std::string &);

			virtual std::string toDot(const std::string &direction = "TB") override;

			Node::Map mergeSets(Node &start, Node &exit);
	};
}

#endif
