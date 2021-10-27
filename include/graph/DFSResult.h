#pragma once

#include <ostream>
#include <unordered_map>
#include <vector>

namespace LL2W {
	class Graph;
	class Node;

	struct DFSResult {
		using ParentMap = std::unordered_map<Node *, Node *>;
		using TimeMap   = std::unordered_map<Node *, int>;

		const Graph *graph;
		ParentMap parents;
		TimeMap discovered, finished;

		DFSResult(const Graph &graph_, const ParentMap &parents_, const TimeMap &discovered_, const TimeMap &finished_);

		DFSResult(const Graph &graph_,
		          const std::vector<Node *> &parents_,
		          const std::vector<int> &discovered_,
		          const std::vector<int> &finished_);
	};

	std::ostream & operator<<(std::ostream &, const DFSResult &);
}
