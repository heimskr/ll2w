#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unistd.h>

#include "Graph.h"
#include "DTree.h"

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
		for (Node *node: nodes_)
			delete node;
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

	std::vector<std::pair<Node *, Node *>> Graph::allEdges() const {
		std::vector<std::pair<Node *, Node *>> out;
		for (Node *node: nodes_) {
			for (Node *successor: *node)
				out.push_back({node, successor});
		}

		return out;
	}


	Graph Graph::djGraph(Node &node) {
		return djGraph(&node);
	}

	Graph Graph::djGraph(const std::string &label) {
		return djGraph((*this)[label]);
	}

	Graph Graph::djGraph(Node *node) {
		DTree dj(*this, *node);
		std::unordered_map<Node *, Node *> doms = dj.dominators();
		for (const std::pair<Node *, Node *> &edge: allEdges()) {

		}

		return dj;


		// const dj: DJGraph = start instanceof Graph? start.clone(false) : this.dTree(start, bidirectional);
		// const sdom = Graph.strictDominators(dj);
		// dj.data.jEdges = [];
		// this.allEdges()
		// 	.filter(([src, dst]) => !sdom[dst].includes(src))
		// 	.forEach(([src, dst]) => (dj.arc(src, dst), dj.data.jEdges.push([src, dst])));
		// dj.title = "DJ Graph";
		// return dj;
	}

	std::string Graph::toDot(const std::string &direction) const {
		std::list<Node *> reflexives;
		for (Node *node: nodes_) {
			if (node->reflexive())
				reflexives.push_back(node);
		}

		std::ostringstream out;
		out << "digraph rendered_graph {\n";
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
		out.open("/tmp/ll2w_graph.dot");
		out << toDot(direction);
		out.close();
		if (fork() == 0)
			execlp("dot", "dot", "-Tpng", "/tmp/ll2w_graph.dot", "-o", png_path.c_str(), nullptr);
	}

	decltype(Graph::labelMap)::iterator Graph::begin() {
		return labelMap.begin();
	}

	decltype(Graph::labelMap)::iterator Graph::end() {
		return labelMap.end();
	}
}
