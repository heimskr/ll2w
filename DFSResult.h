#ifndef DFSRESULT_H_
#define DFSRESULT_H_

#include <unordered_map>
#include <vector>

namespace LL2W {
	class Graph;
	class Node;

	struct DFSResult {
		using parent_map = std::unordered_map<Node *, Node *>;
		using time_map   = std::unordered_map<Node *, int>;

		Graph *graph;
		parent_map parents;
		time_map discovered, finished;

		DFSResult(Graph *graph_, const parent_map &parents_, const time_map &discovered_, const time_map &finished_);

		DFSResult(Graph *graph_,
		          const std::vector<Node *> &parents_,
		          const std::vector<int> &discovered_,
		          const std::vector<int> &finished_);
	};
}

#endif