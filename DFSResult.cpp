#include "DFSResult.h"
#include "Graph.h"

namespace LL2W {
	DFSResult::DFSResult(Graph *graph_,
	                     const DFSResult::map_type &parents_,
	                     const DFSResult::map_type &discovered_,
	                     const DFSResult::map_type &finished_):
		graph(graph_), parents(parents_), discovered(discovered_), finished(finished_) {}

	DFSResult::DFSResult(Graph *graph_,
	                     const std::vector<int> &parents_,
	                     const std::vector<int> &discovered_,
	                     const std::vector<int> &finished_): graph(graph_) {
		for (int i = 0, len = parents_.size(); i < len; ++i)
			parents[&(*graph)[i]] = parents_[i];
		for (int i = 0, len = discovered_.size(); i < len; ++i)
			discovered[&(*graph)[i]] = discovered_[i];
		for (int i = 0, len = finished_.size(); i < len; ++i)
			finished[&(*graph)[i]] = finished_[i];
	}
}
