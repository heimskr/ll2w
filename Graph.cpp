#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unistd.h>

#include "Graph.h"

namespace LL2W {
	Graph::Graph() {}

	Graph::Graph(size_t node_count) {
		for (size_t i = 0; i < node_count; ++i)
			nodes.push_back(new Node(this, std::to_string(i)));
	}

	Graph::~Graph() {
		for (Node *node: nodes)
			delete node;
	}

	bool Graph::hasLabel(const std::string &label) const {
		return labelMap.find(label) != labelMap.end();
	}

	size_t Graph::size() const {
		return nodes.size();
	}

	Node & Graph::operator[](size_t index) const {
		if (nodes.size() <= index)
			throw std::out_of_range("Invalid node index: " + std::to_string(index));
		Node *node = *std::next(nodes.begin(), index);
		if (!node)
			throw std::runtime_error("Node at index " + std::to_string(index) + " is null");
		return *node;
	}

	Node & Graph::operator[](const std::string &label) const {
		auto iter = labelMap.find(label);
		if (iter == labelMap.end())
			throw std::out_of_range("No node with label \"" + label + "\" found");
		return *iter->second;
	}

	Node & Graph::operator+=(const std::string &label) {
		if (hasLabel(label))
			throw std::runtime_error("Can't add: a node with label \"" + label + "\" already exists");
		Node *node = new Node(this, label);
		labelMap.insert({label, node});
		nodes.push_back(node);
		return *node;
	}

	Node & Graph::rename(const std::string &old_label, const std::string &new_label) {
		return rename((*this)[old_label], new_label);
	}

	Node & Graph::rename(Node &node, const std::string &new_label) {
		return rename(&node, new_label);
	}

	Node & Graph::rename(Node *node, const std::string &new_label) {
		if (!node)
			throw std::invalid_argument("Can't rename a null node");
		if (node->label == new_label)
			return *node;
		if (hasLabel(new_label))
			throw std::runtime_error("Can't rename: a node with label \"" + new_label + "\" already exists");
		labelMap.erase(node->label);
		node->label = new_label;
		labelMap.insert({new_label, node});
		return *node;
	}

	void Graph::link(const std::string &from, const std::string &to, bool bidirectional) {
		(*this)[from].link((*this)[to], bidirectional);
	}

	void Graph::addEdges(const std::string &pairs) {
		size_t last = 0, space;
		while (last != std::string::npos) {
			space = pairs.find(' ', last + 1);
			const std::string sub = pairs.substr(last? last + 1 : 0, space - (last + (last? 1 : 0)));
			const size_t colon = sub.find(':');
			const std::string from = sub.substr(0, colon);
			const std::string to = sub.substr(colon + 1);
			link(from, to, false);
			last = space;
		}
	}

	std::string Graph::toDot(const std::string &direction) const {
		std::list<Node *> reflexives;
		for (Node *node: nodes) {
			if (node->reflexive())
				reflexives.push_back(node);
		}

		std::ostringstream out;
		out << "digraph rendered_graph {\n";
		out << "\trankdir=" << direction << ";\n";
		if (!reflexives.empty()) {
			out << "\tnode [shape = doublecircle];";
			for (Node *node: reflexives)
				out << " " << node->label;
			out << ";\n";
		}
		out << "\tnode [shape = circle];\n";
		for (const Node *node: nodes) {
			for (const Node *neighbor: node->adjacent) {
				if (neighbor != node)
					out << "\t" << node->label << " -> " << neighbor->label << ";\n";
			}
		}
		out << "}\n";
		return out.str();
	}

	void Graph::renderTo(const std::string &png_path) {
		std::ofstream out;
		out.open("/tmp/ll2w_graph.dot");
		out << toDot();
		out.close();
		if (fork() == 0)
			execlp("dot", "dot", "-Tpng", "/tmp/ll2w_graph.dot", "-o", png_path.c_str(), nullptr);
	}
}
