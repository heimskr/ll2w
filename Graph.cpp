#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include <unistd.h>

#include "Graph.h"

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

	Graph & Graph::operator+=(const std::string &label) {
		if (hasLabel(label))
			throw std::runtime_error("Can't add: a node with label \"" + label + "\" already exists");
		Node *node = new Node(this, label);
		labelMap.insert({label, node});
		nodes.push_back(node);
		return *this;
	}

	Graph & Graph::operator-=(Node &to_remove) {
		return *this -= &to_remove;
	}

	Graph & Graph::operator-=(Node *to_remove) {
		auto iter = std::find(nodes.begin(), nodes.end(), to_remove);
		if (iter == nodes.end())
			throw std::out_of_range("Can't remove: node is not in graph");
		for (Node *node: nodes) {
			*node -= to_remove;
			node->dirty();
		}

		nodes.erase(iter);
		delete to_remove;
		return *this;
	}

	Graph & Graph::operator-=(const std::string &label) {
		for (Node *node: nodes) {
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

	Graph Graph::clone(std::unordered_map<Node *, Node *> *rename_map) {
		Graph new_graph;

		// Maps old nodes to new nodes.
		std::unordered_map<Node *, Node *> node_map {};
		for (Node *node: nodes) {
			Node *new_node = new Node(&new_graph, node->label());
			node_map.insert({node, new_node});
			new_graph.nodes.push_back(new_node);
			new_graph.labelMap.insert({node->label(), new_node});
		}

		for (auto &pair: node_map) {
			Node *old_node = pair.first, *new_node = pair.second;
			for (Node *old_link: old_node->adjacent())
				new_node->link(node_map.at(old_link), false);
		}

		if (rename_map)
			*rename_map = node_map;

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
		while (!nodes.empty())
			*this -= nodes.front();
	}

	Node * Graph::find(std::function<bool(Node &)> predicate) {
		for (Node *node: nodes) {
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
			for (Node *out: node->adjacent()) {
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

	Graph Graph::lengauerTarjan(Node &start) {
		return lengauerTarjan(&start);
	}

	Graph Graph::lengauerTarjan(const std::string &label) {
		return lengauerTarjan((*this)[label]);
	}

	Graph Graph::lengauerTarjan(Node *start) {
		// TODO: cite dominators.rs

		std::unordered_map<Node *, Node *> parents;
		std::unordered_map<Node *, int> visited {};

		std::vector<Node *> stack {start}, vertices {};
		std::vector<int> semis {};
		std::unordered_set<Node *> seen {};
		std::unordered_map<Node *, std::unordered_set<Node *>> preds {};
		std::cerr << "\e[36m";

		//*
		while (!stack.empty()) {
			Node *node = stack.back();
			stack.pop_back();
			size_t vlen = vertices.size();
			vertices.push_back(node);

			assert(semis.size() == vlen);
			semis.push_back(vlen);

			assert(visited.count(node) == 0);
			visited.insert({node, vlen});
			for (Node *successor: *node) {
				std::cerr << node->label() << " -> " << successor->label() << "\n";
				if (seen.count(successor) == 0) {
					seen.insert(successor);
					if (successor != start) {
						stack.push_back(successor);
						assert(parents.count(successor) == 0);
						parents.insert({successor, node});
					}
				}

				assert(preds[successor].count(node) == 0);
				preds[successor].insert(node);
			}
		}

		const size_t vlen = vertices.size();

		std::cerr << "|visited|  == " << visited.size() << "\n";
		std::cerr << "|seen|     == " << seen.size() << "\n";
		std::cerr << "|semis|    == " << semis.size() << "\n";
		std::cerr << "|vertices| == " << vertices.size() << "\n";
		std::cerr << "|parents|  == " << parents.size() << "\n";
		std::cerr << "|preds|    == " << preds.size() << "\n";
		assert(visited.at(start) == 0);
		assert(visited.size() == seen.size());
		assert(visited.size() == semis.size());
		assert(visited.size() == vertices.size());
		assert(visited.size() - 1 == parents.size());
		assert(preds.size() == vertices.size() || preds.size() == vertices.size() - 1);

		std::vector<std::vector<int>> pred_vectors {};
		std::vector<int> parents_vector {};

		for (Node *vertex: vertices) {
			bool was_erased = preds.count(vertex) != 0;
			preds.erase(vertex);
			if (!was_erased) {
				assert(vertex == start); // Only the root is allowed to have no predecessors
				pred_vectors.push_back({});
			} else {
				pred_vectors.push_back({visited.at(vertex)});
			}

			if (vertex == start) {
				parents_vector.push_back(0);
			} else {
				parents_vector.push_back(visited.at(parents.at(vertex)));
				parents.erase(vertex);
			}
		}

		std::vector<std::unordered_set<int>> buckets(vlen);
		std::vector<int> doms(vlen, 0), ancestors(vlen, -1);
		std::vector<int> labels {};
		for (size_t i = 0; i < vlen; ++i)
			labels.push_back(i);

		std::function<void(int)> compress = [&](int v) {
			assert(ancestors[v] != -1);
			if (ancestors[ancestors[v]] != -1) {
				compress(ancestors[v]);
				if (semis[labels[ancestors[v]]] < semis[labels[v]])
					labels[v] = labels[ancestors[v]];
				ancestors[v] = ancestors[ancestors[v]];
			}
		};

		std::function<int(int)> eval = [&](int v) {
			if (ancestors[v] == -1) {
				return v;
			} else {
				compress(v);
				return labels[v];
			}
		};

		for (size_t w = vlen - 1; 1 <= w; --w) {
			for (int v: pred_vectors[w]) {
				int u = eval(v);
				if (semis[u] < semis[w])
					semis[w] = semis[u];
			}

			buckets[semis[w]].insert(w);
			ancestors[w] = parents_vector[w];

			for (int v: buckets[parents_vector[w]]) {
				int u = eval(v);
				doms[v] = semis[u] < semis[v]? u : parents_vector[w];
			}
		}

		for (size_t w = 1; w < vlen; ++w) {
			if (doms[w] != semis[w])
				doms[w] = doms[doms[w]];
		}

		// The root should dominate itself.
		assert(doms[0] == 0);

		std::unordered_map<int, Node *> visited_inverse {};
		for (const auto &pair: visited)
			visited_inverse.insert({pair.second, pair.first});

		Graph out_graph = clone();
		out_graph.unlink();
		for (size_t i = 0, dlen = doms.size(); i < dlen; ++i)
			out_graph.link(visited_inverse.at(i)->label(), visited_inverse.at(doms[i])->label());

		// procedure DOMINATORS(integer set array succ(1::n); integer r, n; integer array dom(1::n));
		// begin
		// 	integer array parent, ancestor, [child,] vertex(1::n);
		// 	integer array label, semi[, size](0::n);
		// 	integer set array pred, bucket(1::n);
		// 	integer u, v, x;

		// 	procedure DFS(integer v); begin
		// 		semi(v) := n := n + 1;
		// 		vertex(n) := label(v) := v;
		// 		ancestor(v) := [child(v) :=] 0;
		// 		[size(v) := 1;]
		// 		for each w in succ(v) do
		// 			if semi(w) == 0 then
		// 				parent(w) := v;
		// 				DFS (w);
		// 			fi
		// 			add v to pred(w)
		// 		od
		// 	end DFS;

		// int n = 0;
		// std::function<void(Node *)> dfs = [&](Node *node) {
			// semis
		// };



		// std::function<void(Node *)> compress = [&](Node *v) {
		// 	if (ancestors.count(ancestors.at(v)) != 0) {
		// 		compress(ancestors.at(v));
		// 		if (semi
		// 	}
		// };

		// 	procedure COMPRESS(integer v);
		// 		if ancestor(ancestor(v)) != 0 then
		// 			COMPRESS(ancestor(v))
		// 			if semi(label(ancestor(v))) <= semi(label(v)) then
		// 				label(v) := label(ancestor(v))
		// 			fi
		// 			ancestor(v) := ancestor(ancestor(v))
		// 		fi

		// 	integer procedure EVAL(integer v);
		// 		if ancestor(v) == 0 then
		// 			EVAL := v
		// 		else
		// 			COMPRESS(v);
		// 			EVAL := label(v);
		// 		fi

		// 	procedure LINK(integer v, w);
		// 		ancestor(w) := v;
		// step1:	for v := 1 until n do
		// 			pred(v) := bucket(v) := ∅;
		// 			semi(v) := 0;
		// 		od
		// 		n := 0
		// 		DFS(r);
		// 		[size(0) := label(0) := semi(0) := 0];
		// 		for i := n by -1 until 2 do
		// 			w := vertex(i);
		// step2:		for each v in pred(w) do
		// 				u := EVAL(v);
		// 				if semi(u) > semi(w) then
		// 					semi9w) := semi(u);
		// 				fi
		// 			od
		// 			add w to bucket(vertex(semi(w)));
		// 			LINK(parent(w), w)
		// step3:		for each v in bucket(parent(w)) do
		// 				delete v from bucket(parent(w));
		// 				u := EVAL(v);
		// 				if semi(u) < semi(v) then
		// 					dom(v) := u
		// 				else
		// 					dom(v) := parent(w)
		// 				fi
		// 			od
		// 		od

		// step4:	i := 2 until n do
		// 			u := vertex(i);
		// 			if dom(w) != vertex(semi(w)) then
		// 				dom(w) := dom(dom(w))
		// 			fi
		// 		od
		// 		dom(r) := 0
		// end DOMINATORS;

		std::cerr << "\e[0m";
		return out_graph;
	}

	Graph Graph::makeDTree(Node */* start */, bool /* bidirectional */) {
		// const [lentar] = this.lengauerTarjan(getID(startID));
		// const out = new Graph(Object.keys(lentar).length, {});
		// const fn = (bidirectional? out.edge : out.arc).bind(out);
		// Object.entries(lentar).forEach(([k, v]) => {
		// 	out.nodes[k].data = this.nodes[k].data;
		// 	fn(v == undefined? k : v, k)
		// });

		// return out;
		return {};
	}

	Graph Graph::makeDTree(Node &start, bool bidirectional) {
		return makeDTree(&start, bidirectional);
	}

	Graph Graph::makeDTree(const std::string &label, bool bidirectional) {
		return makeDTree((*this)[label], bidirectional);
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
				out << " " << node->label();
			out << ";\n";
		}

		out << "\tnode [shape = circle];";
		bool any_added = false;
		for (Node *node: nodes) {
			if (node->isolated()) {
				out << " " << node->label();
				any_added = true;
			}
		}

		if (any_added)
			out << ";";
		out << "\n";

		for (const Node *node: nodes) {
			for (const Node *neighbor: node->adjacent()) {
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
