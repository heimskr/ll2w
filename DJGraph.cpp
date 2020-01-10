#include "DJGraph.h"
#include "DTree.h"

namespace LL2W {
	DJGraph::DJGraph(Graph &graph, const std::string &label): DJGraph(graph, graph[label]) {}

	DJGraph::DJGraph(Graph &graph, Node &start) {
		DTree dt(graph, start);
		std::unordered_map<Node *, std::unordered_set<Node *>> doms = dt.strictDominators();
		// for (const std::pair<Node &, Node &> &edge: allEdges()) {
		// 	if (doms.at(&edge.first).count(&edge.second) != 0)
		// 		continue;
		// }



		// const dj: DJGraph = start instanceof Graph? start.clone(false) : this.dTree(start, bidirectional);
		// const sdom = Graph.strictDominators(dj);
		// dj.data.jEdges = [];
		// this.allEdges()
		// 	.filter(([src, dst]) => !sdom[dst].includes(src))
		// 	.forEach(([src, dst]) => (dj.arc(src, dst), dj.data.jEdges.push([src, dst])));
		// dj.title = "DJ Graph";
		// return dj;
	}
}
