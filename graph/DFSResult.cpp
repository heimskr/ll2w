#include "DFSResult.h"
#include "Graph.h"

namespace LL2W {
	DFSResult::DFSResult(Graph *graph_,
	                     const DFSResult::parent_map &parents_,
	                     const DFSResult::time_map &discovered_,
	                     const DFSResult::time_map &finished_):
		graph(graph_), parents(parents_), discovered(discovered_), finished(finished_) {}

	DFSResult::DFSResult(Graph *graph_,
	                     const std::vector<Node *> &parents_,
	                     const std::vector<int> &discovered_,
	                     const std::vector<int> &finished_): graph(graph_) {
		for (int i = 0, len = parents_.size(); i < len; ++i)
			parents[&(*graph)[i]] = parents_[i];
		for (int i = 0, len = discovered_.size(); i < len; ++i)
			discovered[&(*graph)[i]] = discovered_[i];
		for (int i = 0, len = finished_.size(); i < len; ++i)
			finished[&(*graph)[i]] = finished_[i];
	}

	std::ostream & operator<<(std::ostream &os, const DFSResult &result) {
		os << "Parents    [";
		for (const auto &pair: result.parents)
			os << " " << pair.first->label() << "<-" << pair.second->label();
		os << " ]\nDiscovered [";
		for (const auto &pair: result.discovered)
			os << " " << pair.first->label() << ":" << pair.second;
		os << " ]\nFinished   [";
		for (const auto &pair: result.finished)
			os << " " << pair.first->label() << ":" << pair.second;
		return os << "]\n";
	}
}
