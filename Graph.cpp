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

	Graph Graph::clone(std::unordered_map<Node *, Node *> *rename_map) {
		Graph new_graph;

		// Maps old nodes to new nodes.
		std::unordered_map<Node *, Node *> node_map {};
		for (Node *node: nodes_) {
			Node *new_node = new Node(&new_graph, node->label());
			node_map.insert({node, new_node});
			new_graph.nodes_.push_back(new_node);
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
		// procedure DOMINATORS(integer set array succ(1::n); integer r, n; integer array dom(1::n));
		// begin
		// 	integer array parent, ancestor, [child,] vertex(1::n);
		// 	integer array label, semi[, size](0::n);
		// 	integer set array pred, bucket(1::n);
		// 	integer u, v, x;

		const size_t gsize = size();
		std::unordered_map<Node *, int> visited;
		std::vector<Node *> stack {start}, vertices;
		std::vector<int> semis(gsize, -1);
		std::vector<int> ancestors(gsize, -1);
		std::vector<int> labels(gsize, -1);
		std::vector<int> parents(gsize, -1);
		std::vector<int> doms(gsize, -1);
		std::vector<std::unordered_set<int>> preds(gsize), buckets(gsize);

		// auto lbl = [&](int x) -> std::string { return x == -1? "-1" : (std::to_string(x) + ":" + vertices.at(x)->label()); };
		auto lbl = [&](int x) -> std::string { return x == -1? "-1" : (std::to_string(x) + ":" + (*this)[x].label()); };

		/*
		// Converts a DFS index into a node index.
		auto d2n = [&](int dfs_index) -> int {
			return visited.at(vertices.at(dfs_index));
		};

		// Converts a node index into a DFS index.
		auto n2d = [&](int node_index) -> int {
			return visited.at((*this)[node_index]);
		};

		// Gets the value in semis for a DFS index.
		auto semi = [&](int dfs_index) -> int {
			return semis[d2n(dfs_index)];
		};
		//*/

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
		std::function<void(Node *)> dfs = [&](Node *node) {
			visited[node] = vertices.size();
			const int v = node->index();
			std::cout << "\e[32m" << node->label() << " is " << v << ".\e[0m\n";
			assert(semis[v] == -1);
			semis[v] = vertices.size();
			vertices.push_back(node);
			labels[v] = v;
			for (Node *successor: *node) {
				const int w = successor->index();
				if (semis.at(w) == -1) {
					std::cout << successor->label() << " [Ind:" << w << "]'s parent is " << node->label() << " [Ind:" << v << " DFS:" << semis[v] << "]\n";
					// std::cout << lbl(w) << "'s parent is " << node->label() << " [I:" << v << " D:" << semis[v] << "]\n";
					parents[w] = v;

					std::cout << "\e[36mparent[" << lbl(w) << "] == " << lbl(parents.at(w)) << "\e[0m\n";

					dfs(successor);
				}

				preds.at(w).insert(v);
			}
		};

		//	procedure COMPRESS(integer v);
		//	if ancestor(ancestor(v)) != 0 then
		//		COMPRESS(ancestor(v))
		//		if semi(label(ancestor(v))) <= semi(label(v)) then
		//			label(v) := label(ancestor(v))
		//		fi
		//		ancestor(v) := ancestor(ancestor(v))
		//	fi
		std::function<void(int)> compress = [&](int v) {
			if (ancestors[v] != -1 && ancestors[ancestors[v]] != -1) {
				compress(ancestors[v]);
				if (semis[labels[ancestors[v]]] <= semis[labels[v]])
					labels[v] = labels[ancestors[v]];
				ancestors[v] = ancestors[ancestors[v]];
			}
		};

		// 	integer procedure EVAL(integer v);
		// 		if ancestor(v) == 0 then
		// 			EVAL := v
		// 		else
		// 			COMPRESS(v);
		// 			EVAL := label(v);
		// 		fi
		std::function<int(int)> eval = [&](int v) {
			if (ancestors[v] == -1) {
				return v;
			} else {
				compress(v);
				return labels[v];
			}
		};

		// 	procedure LINK(integer v, w);
		// 		ancestor(w) := v;

		// step1:
		//		for v := 1 until n do
		// 			pred(v) := bucket(v) := ∅;
		// 			semi(v) := 0;
		// 		od
		// 		n := 0
		// 		DFS(r);
		// 		[size(0) := label(0) := semi(0) := 0];
		// 		for i := n by -1 until 2 do
		// 			w := vertex(i);
		dfs(start);
		for (int i = gsize - 1; 1 <= i; --i) {
			int w = vertices[i]->index();

		// step2:
		//			for each v in pred(w) do
		// 				u := EVAL(v);
		// 				if semi(u) > semi(w) then
		// 					semi(w) := semi(u);
		// 				fi
		// 			od
		// 			add w to bucket(vertex(semi(w)));
		// 			LINK(parent(w), w)
			for (int v: preds.at(w)) {
				int u = eval(v);
				std::cout << "semis[" << lbl(u) << "]: " << semis.at(u) << "; semis[" << lbl(w) << "]: " << semis.at(w) << "\n";
				if (semis.at(u) > semis.at(w))
					semis.at(w) = semis.at(u);
			}

			std::cout << "semis[" << lbl(w) << "] == " << lbl(semis.at(w)) << "\n";

			// std::cout << "\e[31mbuckets[" << lbl(visited.at(vertices.at(semis.at(w)))) << "].insert(" << lbl(w) << ")\e[0m\n";
			// buckets[visited.at(vertices.at(semis.at(w)))].insert(w);

			std::cout << "\e[31mbuckets[\e[1m" << lbl(vertices.at(semis.at(w))->index()) << "\e[22m].insert(\e[1m" << lbl(w) << "\e[22m)\e[0m\n";
			buckets[vertices.at(semis.at(w))->index()].insert(w);

			ancestors[w] = parents.at(w);

		// step3:
		//			for each v in bucket(parent(w)) do
		// 				delete v from bucket(parent(w));
		// 				u := EVAL(v);
		// 				if semi(u) < semi(v) then
		// 					dom(v) := u
		// 				else
		// 					dom(v) := parent(w)
		// 				fi
		// 			od
		// 		od
			// std::cout << "Parent for " << lbl(w) << " is " << lbl(parents.at(vertices.at(w)->index())) << "\n";
			std::cout << "Parent for " << lbl(w) << " is " << lbl(parents.at(w)) << "\n";
			std::unordered_set<int> &bucket = buckets.at(parents.at(w));
			// std::unordered_set<int> &bucket = buckets.at(parents.at(vertices.at(w)->index()));

			std::cout << "\e[32mBucket for \e[1m" << lbl(parents.at(w)) << "\e[22m:";
			if (bucket.empty()) std::cout << " (empty)";
			else for (int v: bucket) std::cout << " " << v;
			std::cout << "\e[0m\n";

			for (auto iter = bucket.begin(); iter != bucket.end();) {
				int v = *iter;
				bucket.erase(iter++);
				int u = eval(v);
				std::cout << "Picked " << lbl(v) << " from bucket of " << lbl(w) << "'s parent (" << parents.at(w) << "). Dom: ";
				doms[v] = semis.at(u) < semis.at(v)? u : parents.at(w);
				std::cout << lbl(doms[v]) << "\n";
			}
		}

		// step4:
		//		i := 2 until n do
		// 			w := vertex(i);
		// 			if dom(w) != vertex(semi(w)) then
		// 				dom(w) := dom(dom(w))
		// 			fi
		// 		od
		// 		dom(r) := 0
		// end DOMINATORS;

		for (size_t i = 1; i < gsize; ++i) {
			int w = vertices.at(i)->index();
			if (doms.at(w) != vertices.at(semis.at(w))->index()) {
				std::cout << "doms[" << lbl(w) << "] == " << doms.at(w) << "\n";
				doms[w] = doms.at(doms.at(w));
			}
		}

		assert(doms.at(start->index()) == 0);
		// doms[start->index()] = 0;

		std::unordered_map<int, Node *> visited_inverse {};
		for (const auto &pair: visited)
			visited_inverse.insert({pair.second, pair.first});

		Graph out_graph = clone();
		out_graph.unlink();
		for (size_t i = 0, dlen = doms.size(); i < dlen; ++i)
			out_graph.link(visited_inverse.at(i)->label(), visited_inverse.at(doms.at(i))->label());

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
