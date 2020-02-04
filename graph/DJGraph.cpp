#include <iostream>
#include <map>
#include <set>
#include <sstream>

#include "DJGraph.h"
#include "DTree.h"

namespace LL2W {
	DJGraph::DJGraph(Graph &graph, const std::string &label): DJGraph(graph, graph[label]) {}
	DJGraph::DJGraph(Graph &graph, Node &start) {
		DTree dt(graph, start);
		dt.cloneTo(*this);
		std::unordered_map<std::string, std::unordered_set<std::string>> doms = dt.strictDominatorLabels();

		for (const auto [src, dest]: graph.allEdges()) {
			if (doms.at(dest.label()).count(src.label()) != 0)
				continue;
			link(src.label(), dest.label());
			jEdges.push_back({(*this)[src.label()], (*this)[dest.label()]});
			jMap[&(*this)[src.label()]].insert(&(*this)[dest.label()]);
		}
	}

	Node * DJGraph::parent(const Node &node, const Node &start) const {
		// Because this is a DJ graph, we're allowed to assume that a
		// given node (other than the start) has only one inward edge.
		return &node == &start? nullptr : *node.in().begin();
	};

	bool DJGraph::isJEdge(const Node &from, const Node &to) const {
		for (const std::pair<Node &, Node &> &j_edge: jEdges) {
			if (&j_edge.first == &from && &j_edge.second == &to)
				return true;
		}

		return false;
	}

	std::unordered_set<Node *> DJGraph::allInNodes(const Node &node) const {
		std::unordered_set<Node *> out = {node.in().begin(), node.in().end()};
		for (const std::pair<Node &, Node &> &j_edge: jEdges) {
			if (&j_edge.second == &node)
				out.insert(&j_edge.first);
		}

		return out;
	}

	int DJGraph::level(const Node &node, const Node &start) const {
		int out;
		const Node *nptr = &node;
		for (out = 0; nptr != &start; ++out)
			nptr = parent(*nptr, start);
		return out;
	}

	std::string DJGraph::toDot(const std::string &direction) {
		std::list<Node *> reflexives;
		for (Node *node: nodes()) {
			if (node->reflexive())
				reflexives.push_back(node);
		}

		std::ostringstream out;
		out << "digraph rendered_graph {\n";
		out << "graph [fontname = \"helvetica\"];\n";
		out << "node [fontname = \"helvetica\"];\n";
		out << "edge [fontname = \"helvetica\", arrowhead=open, arrowsize=0.666];\n";
		out << "\trankdir=" << direction << ";\n";
		if (!reflexives.empty()) {
			out << "\tnode [shape = doublecircle];";
			for (Node *node: reflexives)
				out << " " << node->label();
			out << ";\n";
		}

		out << "\tnode [shape = circle];";
		bool any_added = false;
		for (Node *node: nodes()) {
			if (node->isolated()) {
				out << " " << node->label();
				any_added = true;
			}
		}

		if (any_added)
			out << ";";
		out << "\n";

		for (Node *node: nodes()) {
			for (Node *neighbor: node->out()) {
				if (neighbor != node) {
					out << "\t" << node->label() << " -> " << neighbor->label();
					if (jMap[node].count(neighbor) != 0)
						out << " [style=dashed]";
					out << ";\n";
				}
			}
		}
		out << "}\n";
		return out.str();
	}

	Node::Map DJGraph::mergeSets(Node &start, const Node &exit) {
		std::vector<Node *> level_order = BFS(start);
		Node::Map visited;
		std::unordered_map<Node *, MergeSet> merge;

		std::function<void(Node *)> ensure = [&](Node *node) {
			if (merge.count(node) == 0)
				merge.insert({node, MergeSet(node)});
		};

		bool pass_required;
		do {
			pass_required = false;
			for (Node *node: level_order) {
				std::unordered_set<Node *> unvisited_j_edges;
				for (Node *in_node: allInNodes(*node)) {
					if (isJEdge(*in_node, *node) && node != &exit && visited[in_node].count(node) == 0)
						unvisited_j_edges.insert(in_node);
				}

				for (Node *in_node: unvisited_j_edges) {
					visited[in_node].insert(node);
					Node *l_node = nullptr;
					Node *tmp = in_node;
					while (level(*tmp, start) >= level(*node, start)) {
						ensure(tmp);
						ensure(node);
						merge.at(tmp).insert(merge.at(node));
						merge.at(tmp).insert(node);
						l_node = tmp;
						tmp = parent(*tmp, start);
					}
				}
			}
		} while (pass_required);

		return {};
	}

	void MergeSet::insert(MergeSet &other) {
		references.push_back(&other);
	}

	void MergeSet::insert(MergeSet *other) {
		references.push_back(other);
	}

	void MergeSet::insert(Node *node) {
		nodes.push_back(node);
	}

	void MergeSet::flatten(Node::Set &out, std::unordered_set<MergeSet *> &processed) {
		for (Node *node: nodes)
			out.insert(node);
		for (MergeSet *other: references) {
			if (other != this && processed.count(other) == 0) {
				processed.insert(other);
				other->flatten(out, processed);
			}
		}
	}

	Node::Set MergeSet::flatten() {
		Node::Set out;
		std::unordered_set<MergeSet *> processed;
		flatten(out, processed);
		return out;
	}
}
