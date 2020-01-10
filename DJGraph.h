#ifndef DJGRAPH_H_
#define DJGRAPH_H_

#include <unordered_set>

#include "Graph.h"

namespace LL2W {
	class DJGraph: public Graph {
		private:
			std::unordered_map<Node *, std::unordered_set<Node *>> jMap;

		public:
			std::vector<std::pair<Node &, Node &>> jEdges;

			DJGraph(Graph &, Node &);
			DJGraph(Graph &, const std::string &);

			virtual std::string toDot(const std::string &direction = "TB") override;
	};
}

#endif