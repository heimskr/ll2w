#include <iostream>

#include "DJGraph.h"
#include "DTree.h"

namespace LL2W {
	DJGraph::DJGraph(Graph &graph, const std::string &label): DJGraph(graph, graph[label]) {}
	DJGraph::DJGraph(Graph &graph, Node &start) {
		DTree dt(graph, start);
		dt.cloneTo(*this);
		std::unordered_map<std::string, std::unordered_set<std::string>> doms = dt.strictDominatorLabels();

		for (const auto [src, dest]: allEdges()) {
			if (doms.at(dest.label()).count(src.label()) != 0)
				continue;
			src.link(dest);
			std::cout << "J edge between " << src << " and " << dest << "\n";
			jEdges.push_back({src, dest});
		}
	}
}
