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

		std::cout << "Dom keys:\n";
		for (const auto &pair: std::map<std::string, std::unordered_set<std::string>>(doms.begin(), doms.end())) {
			std::cout << pair.first << ":";
			if (pair.second.empty()) {
				std::cout << " -";
			} else {
				for (const auto &x: std::set<std::string>(pair.second.begin(), pair.second.end()))
					std::cout << " " << x;
			}
			std::cout << "\n";
		}

		for (const auto [src, dest]: graph.allEdges()) {
			if (doms.at(dest.label()).count(src.label()) != 0)
				continue;
			link(src.label(), dest.label());
			std::cout << "J edge between " << src << " and " << dest << "\n";
			jEdges.push_back({(*this)[src.label()], (*this)[dest.label()]});
			jMap[&(*this)[src.label()]].insert(&(*this)[dest.label()]);
		}
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
		out << "edge [fontname = \"helvetica\"];\n";
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
}
