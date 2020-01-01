#ifndef DFSRESULT_H_
#define DFSRESULT_H_

#include <unordered_map>
#include <vector>

namespace LL2W {
	class Graph;
	class Node;

	struct DFSResult {
		using map_type = std::unordered_map<Node *, int>;

		Graph *graph;
		map_type parents, discovered, finished;

		DFSResult(Graph *graph_, const map_type &parents_, const map_type &discovered_, const map_type &finished_);

		DFSResult(Graph *graph_,
		          const std::vector<int> &parents_,
		          const std::vector<int> &discovered_,
		          const std::vector<int> &finished_);
	};
}

#endif