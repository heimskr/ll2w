#pragma once

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
			std::vector<std::pair<Node *, Node *>> jEdges;

			DJGraph(Graph &, Node &start);
			DJGraph(Graph &, const std::string &start_label);

			virtual std::string toDot(const std::string &direction = "TB") override;

			Node::Map mergeSets(Node &start, const Node &exit);
	};

	struct MergeSet {
		Node *node;
		std::unordered_set<Node *> nodes;
		std::unordered_set<MergeSet *> references;
		MergeSet(Node *node_): node(node_) {};

		void insert(MergeSet &);
		void insert(MergeSet *);
		void insert(Node *);
		void flatten(Node::Set &out, std::unordered_set<MergeSet *> &processed);
		Node::Set flatten();
	};
}
