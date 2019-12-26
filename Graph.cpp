#include <stdexcept>

#include "Graph.h"

namespace LL2W {
	Graph::Graph() {}

	Graph::Graph(size_t node_count) {
		for (size_t i = 0; i < node_count; ++i)
			nodes.push_back(new Node(this));
	}

	Graph::~Graph() {
		for (Node *node: nodes)
			delete node;
	}

	bool Graph::has_label(const std::string &label) const {
		return label_map.find(label) != label_map.end();
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
		auto iter = label_map.find(label);
		if (iter == label_map.end())
			throw std::out_of_range("No node with label \"" + label + "\" found");
		return *iter->second;
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
		if (has_label(new_label))
			throw std::runtime_error("Can't rename: a node with label \"" + new_label + "\" already exists");
		label_map.erase(node->label);
		node->label = new_label;
		label_map.insert({new_label, node});
		return *node;
	}
}
