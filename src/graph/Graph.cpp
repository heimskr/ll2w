#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unistd.h>

#include "graph/Graph.h"

namespace LL2W {
	Graph::Graph() {}

	Graph::Graph(size_t node_count) {
		for (size_t i = 0; i < node_count; ++i)
			*this += std::to_string(i);
	}

	Graph::Graph(std::initializer_list<std::string> labels) {
		for (const std::string &label: labels)
			*this += label;
	}

	Graph::~Graph() {
		// We could just call clear(), but all we need to do is delete the pointers.
		// The compiler-generated part of the destructor will handle the rest.
		for (Node *node: nodes_)
			delete node;
	}

	void Graph::clear() {
		labelMap.clear();
		for (Node *node: nodes_)
			delete node;
		nodes_.clear();
	}

	bool Graph::hasLabel(const std::string &label) const {
		return labelMap.find(label) != labelMap.end();
	}

	size_t Graph::size() const {
		return nodes_.size();
	}

	const std::list<Node *> Graph::nodes() const {
		return nodes_;
	}

	Node & Graph::operator[](size_t index) const {
		if (nodes_.size() <= index)
			throw std::out_of_range("Invalid node index: " + std::to_string(index));
		Node *node = *std::next(nodes_.begin(), index);
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

	Node & Graph::operator[](const Node &node) const {
		return (*this)[node.label()];
	}

	Graph & Graph::operator+=(const std::string &label) {
		if (hasLabel(label))
			throw std::runtime_error("Can't add: a node with label \"" + label + "\" already exists");
		Node *node = new Node(this, label);
		labelMap.insert({label, node});
		nodes_.push_back(node);
		return *this;
	}

	Graph & Graph::operator-=(Node &to_remove) {
		return *this -= &to_remove;
	}

	Graph & Graph::operator-=(Node *to_remove) {
		auto iter = std::find(nodes_.begin(), nodes_.end(), to_remove);
		if (iter == nodes_.end())
			throw std::out_of_range("Can't remove: node is not in graph");
		for (Node *node: nodes_) {
			*node -= to_remove;
			node->dirty();
		}

		nodes_.erase(iter);
		delete to_remove;
		return *this;
	}

	Graph & Graph::operator-=(const std::string &label) {
		for (Node *node: nodes_) {
			if (node->label() == label)
				return *this -= node;
		}

		throw std::out_of_range("Can't remove: no node with label \"" + label + "\" found");
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
		if (node->label() == new_label)
			return *node;
		if (hasLabel(new_label))
			throw std::runtime_error("Can't rename: a node with label \"" + new_label + "\" already exists");
		labelMap.erase(node->label());
		node->label_ = new_label;
		labelMap.insert({new_label, node});
		return *node;
	}

	void Graph::link(const std::string &from, const std::string &to, bool bidirectional) {
		(*this)[from].link((*this)[to], bidirectional);
	}

	void Graph::unlink(const std::string &from, const std::string &to, bool bidirectional) {
		(*this)[from].unlink((*this)[to], bidirectional);
	}

	void Graph::unlink() {
		for (auto &pair: (*this))
			pair.second->unlink();
	}

	void Graph::cloneTo(Graph &out, std::unordered_map<Node *, Node *> *rename_map) {
		out.reset();

		// Maps old nodes to new nodes.
		std::unordered_map<Node *, Node *> node_map {};
		for (Node *node: nodes_) {
			Node *new_node = new Node(&out, node->label());
			node_map.insert({node, new_node});
			out.nodes_.push_back(new_node);
			out.labelMap.insert({node->label(), new_node});
		}

		for (auto &pair: node_map) {
			Node *old_node = pair.first, *new_node = pair.second;
			for (Node *old_link: old_node->out())
				new_node->link(node_map.at(old_link), false);
		}

		if (rename_map)
			*rename_map = node_map;
	}

	Graph Graph::clone(std::unordered_map<Node *, Node *> *rename_map) {
		Graph new_graph;
		cloneTo(new_graph, rename_map);
		return new_graph;
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

	void Graph::reset() {
		while (!nodes_.empty())
			*this -= nodes_.front();
	}

	Node * Graph::find(std::function<bool(Node &)> predicate) {
		for (Node *node: nodes_) {
			if (predicate(*node))
				return node;
		}

		return nullptr;
	}

	DFSResult Graph::DFS(Node *start) {
		DFSResult::parent_map parents;
		DFSResult::time_map discovered, finished;
		int time = 0;

		std::function<void(Node *)> visit = [&](Node *node) {
			discovered[node] = ++time;
			for (Node *out: node->out()) {
				if (discovered.count(out) == 0) {
					parents[out] = node;
					visit(out);
				}
			}

			finished[node] = ++time;
		};

		visit(start);
		return {this, parents, discovered, finished};
	}

	DFSResult Graph::DFS(Node &start) {
		return DFS(&start);
	}

	DFSResult Graph::DFS(const std::string &start_label) {
		return DFS((*this)[start_label]);
	}

	std::vector<Node *> Graph::BFS(Node &start) {
		std::list<Node *> queue = {&start};
		std::unordered_set<Node *> visited;
		std::vector<Node *> order;
		order.reserve(size());

		while (!queue.empty()) {
			Node *next = queue.front();
			queue.pop_front();
			for (Node *out: next->out()) {
				if (visited.count(out) == 0) {
					visited.insert(out);
					order.push_back(out);
					queue.push_back(out);
				}
			}
		}

		return order;
	}

	std::vector<Node *> Graph::BFS(const std::string &start_label) {
		return BFS((*this)[start_label]);
	}

	std::vector<Node *> Graph::postOrder(Node &start) const {
		std::vector<Node *> out;
		out.reserve(size());
		std::unordered_set<Node *> visited;

		std::function<void(Node *)> visit = [&](Node *node) {
			visited.insert(node);
			out.push_back(node);
			for (Node *successor: node->out()) {
				if (visited.count(successor) == 0)
					visit(successor);
			}
		};

		visit(&start);
		return out;
	}

	std::vector<Node *> Graph::reversePostOrder(Node &start) const {
		std::vector<Node *> post = postOrder(start);
		std::reverse(post.begin(), post.end());
		return post;
	}

	void Graph::color(Graph::ColoringAlgorithm algo, int max_colors) {
		if (algo == Graph::ColoringAlgorithm::Bad) {
			if (max_colors != -1 && max_colors < static_cast<int>(nodes_.size()))
				throw std::runtime_error("Unable to color graph: not enough colors");
			int color = -1;
			for (Node *node: nodes_)
				node->color = ++color;
		} else if (algo == Graph::ColoringAlgorithm::Greedy) {
			// if (max_colors == -1)
			std::set<int> all_colors;
			for (int i = 0; i < (max_colors == -1? static_cast<int>(size()) : max_colors); ++i)
				all_colors.insert(i);

			for (Node *node: nodes_) {
				std::set<int> available = all_colors;
				for (Node *neighbor: node->out()) {
					if (neighbor->color != -1)
						available.erase(neighbor->color);
				}
				for (Node *neighbor: node->in()) {
					if (neighbor->color != -1)
						available.erase(neighbor->color);
				}
				if (available.empty())
					throw std::runtime_error("Unable to color graph: not enough colors");
				node->color = *available.begin();
			}
			// throw std::runtime_error("Greedy coloring algorithm is unimplemented");
		} else {
			throw std::invalid_argument("Unknown graph coloring algorithm: " + std::to_string(static_cast<int>(algo)));
		}
	}

	std::vector<std::pair<Node &, Node &>> Graph::allEdges() const {
		std::vector<std::pair<Node &, Node &>> out;
		for (Node *node: nodes_) {
			for (Node *successor: *node)
				out.push_back({*node, *successor});
		}

		return out;
	}

	std::string Graph::toDot(const std::string &direction) {
		std::list<Node *> reflexives;
		for (Node *node: nodes_) {
			if (node->reflexive())
				reflexives.push_back(node);
		}

		std::ostringstream out;
		out << "digraph rendered_graph {\n";
		out << "graph [fontname = \"helvetica\"];\n";
		out << "node [fontname = \"helvetica\", style = \"filled\"];\n";
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
		for (Node *node: nodes_) {
			if (node->isolated()) {
				out << " " << node->label();
				any_added = true;
			}
		}

		if (any_added)
			out << ";";
		out << "\n";

		for (Node *node: nodes_) {
			if (0 <= node->color && static_cast<size_t>(node->color) < colors.size())
				out << "\t" << node->label() << " [fillcolor=" << colors.at(node->color) << "];\n";
		}

		for (const Node *node: nodes_) {
			for (const Node *neighbor: node->out()) {
				if (neighbor != node)
					out << "\t" << node->label() << " -> " << neighbor->label() << ";\n";
			}
		}
		out << "}\n";
		return out.str();
	}

	void Graph::renderTo(const std::string &png_path, const std::string &direction) {
		std::ofstream out;
		std::string path = "/tmp/ll2w_graph_";
		for (char ch: png_path) {
			if (std::isdigit(ch) || std::isalpha(ch) || ch == '_')
				path += ch;
		}
		path += ".dot";
		out.open(path);
		out << toDot(direction);
		out.close();
		if (fork() == 0)
			execlp("dot", "dot", "-Tpng", path.c_str(), "-o", png_path.c_str(), nullptr);
	}

	decltype(Graph::labelMap)::iterator Graph::begin() {
		return labelMap.begin();
	}

	decltype(Graph::labelMap)::iterator Graph::end() {
		return labelMap.end();
	}
}