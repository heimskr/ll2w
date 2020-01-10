#ifndef DJGRAPH_H_
#define DJGRAPH_H_

#include "Graph.h"

namespace LL2W {
	class DJGraph: public Graph {
		public:
			std::vector<std::pair<Node &, Node &>> jEdges;

			DJGraph(Graph &, const std::string &);
			DJGraph(Graph &, Node &);
	};
}

#endif