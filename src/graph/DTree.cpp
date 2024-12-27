#include <cassert>
#include <iostream>
#include <unordered_set>

#include "graph/DTree.h"
#include "util/Util.h"

namespace LL2W {
	DTree::DTree(Graph &graph, const std::string &label): DTree(graph, graph[label]) {}
	DTree::DTree(Graph &graph, Node &start) {
		const size_t gsize = graph.size();
		std::vector<Node *> stack {&start};
		std::vector<Node *> vertex(gsize, nullptr);
		std::unordered_map<Node *, int64_t> semi;
		std::unordered_map<Node *, int64_t> size;
		std::unordered_map<Node *, Node *> ancestor;
		std::unordered_map<Node *, Node *> label;
		std::unordered_map<Node *, Node *> parent;
		std::unordered_map<Node *, Node *> dom;
		std::unordered_map<Node *, Node *> child;
		std::unordered_map<Node *, std::unordered_set<Node *>> pred;
		std::unordered_map<Node *, std::unordered_set<Node *>> bucket;

		for (Node *node: graph.nodes()) {
			semi[node] = -1;
			size[node] = 0;
			ancestor[node] = label[node] = parent[node] = dom[node] = nullptr;
		}

		int64_t n = -1;
		std::function<void(Node *)> dfs = [&](Node *v) {
			semi[v] = ++n;
			vertex[n] = label[v] = v;
			ancestor[v] = nullptr;
			size[v] = 1;
			for (Node *w: *v) {
				if (semi[w] == -1) {
					parent[w] = v;
					dfs(w);
				}
				pred[w].insert(v);
			}
		};

		std::function<void(Node *)> compress = [&](Node *v) {
			assert(ancestor[v] != nullptr);

			if (ancestor[ancestor[v]] != nullptr) {
				compress(ancestor[v]);
				if (semi[label[ancestor[v]]] < semi[label[v]]) {
					label[v] = label[ancestor[v]];
				}
				ancestor[v] = ancestor[ancestor[v]];
			}
		};

		std::function<Node *(Node *)> eval = [&](Node *v) {
			if (ancestor[v] == nullptr) {
				return label[v];
			}

			compress(v);

			if (semi[label[ancestor[v]]] >= semi[label[v]]) {
				return label[v];
			}

			return label[ancestor[v]];
		};

		std::function<void(Node *, Node *)> link_ = [&](Node *v, Node *w) {
			Node *s = w;
			while (semi[label[w]] < semi[label[child[s]]]) {
				if (size[s] + size[child[child[s]]] >= 2 * size[child[s]]) {
					ancestor[child[s]] = s;
					child[s] = child[child[s]];
				} else {
					size[child[s]] = size[s];
					s = ancestor[s] = child[s];
				}
			}

			label[s] = label[w];
			size[v] += size[w];
			if (size[v] < 2 * size[w]) {
				std::swap(s, child[v]);
			}

			while (s != nullptr) {
				ancestor[s] = v;
				s = child[s];
			}
		};

		dfs(&start);

		for (size_t i = gsize - 1; 1 <= i; --i) {
			Node *w = vertex[i];
			for (Node *v: pred[w]) {
				Node *u = eval(v);
				if (semi[u] < semi[w]) {
					semi[w] = semi[u];
				}
			}

			if (w == nullptr) {
				// continue;
				graph.renderTo("w_null.png");
				throw std::runtime_error(std::format("w is null at i = {}, gsize = {}", i, gsize));
			}

			if (vertex[semi[w]] == nullptr) {
				throw std::runtime_error("vertex[semi[w]] is null");
			}

			bucket[vertex[semi[w]]].insert(w);
			link_(parent[w], w);

			std::unordered_set<Node *> &pwbucket = bucket[parent[w]];
			for (auto iter = pwbucket.begin(); iter != pwbucket.end();) {
				Node *v = *iter;
				iter = pwbucket.erase(iter);
				Node *u = eval(v);
				if (v == nullptr) {
					throw std::runtime_error("v is null");
				}
				dom[v] = semi[u] < semi[v]? u : parent[w];
			}
		}

		for (size_t i = 1; i < gsize; ++i) {
			Node *w = vertex[i];
			if (dom[w] != vertex[semi[w]]) {
				if (w == nullptr) {
					// continue;
					throw std::runtime_error("w is null (2)");
				}
				dom[w] = dom[dom[w]];
			}
		}

		dom[&start] = &start;
		graph.cloneTo(*this);
		startNode = &(*this)[start];
		unlink();
		for (const std::pair<Node * const, Node *> &pair: dom) {
			link((*this)[*pair.second].label(), (*this)[*pair.first].label());
		}
	}

	void DTree::findLevels() {
		levels.clear();
		std::function<void(Node *, int)> dfs = [&](Node *node, const int level) {
			levels.insert({node, level});
			for (Node *successor: *node) {
				if (successor != node)
					dfs(successor, level + 1);
			}
		};

		dfs(startNode, 0);
	}

	std::string DTree::commonDominator(std::vector<Node *> nodes) {
		// To find the common dominator of a set of nodes, assign each node a level in the DTree. Find the smallest
		// level of all the nodes. Until all nodes are at that level, keep moving upward from each node that isn't
		// already at that level. Once all nodes are at the same level, check whether they're all the same node. If not,
		// move all nodes up another level. once all nodes are the same, that node is the common dominator.

		if (levels.empty())
			findLevels();

		size_t max = nodes.size();
		for (size_t i = 0; i < max; ++i)
			nodes[i] = &(*this)[*nodes[i]];

		size_t smallest_level = levels[*std::min_element(nodes.begin(), nodes.end(), [&](Node *left, Node *right) {
			return levels[left] < levels[right];
		})];

		std::function<void()> move_nodes_up = [&]() {
			for (size_t i = 0; i < max; ++i) {
				while (smallest_level < levels[nodes[i]])
					nodes[i] = nodes[i]->parent();
			}
		};

		std::function<bool()> all_nodes_equal = [&]() {
			Node *first = nodes[0];
			for (size_t i = 1; i < max; ++i) {
				if (nodes[i] != first)
					return false;
			}
			return true;
		};

		move_nodes_up();
		while (!all_nodes_equal()) {
			--smallest_level;
			move_nodes_up();
		}

		return nodes[0]->label();
	}

	std::string DTree::commonDominator(const std::vector<std::string> &label) {
		std::vector<Node *> nodes;
		nodes.reserve(label.size());

		for (const std::string &label: label) {
			nodes.push_back(&(*this)[label]);
		}

		return commonDominator(nodes);
	}

	std::unordered_map<Node *, Node *> DTree::immediateDominators() const {
		std::unordered_map<Node *, Node *> out;

		for (Node *node: nodes()) {
			for (Node *successor: *node) {
				assert(!out.contains(successor));
				out.insert({successor, node});
			}
		}

		return out;
	}

	Node::Map DTree::strictDominators() const {
		Node::Map out_map;

		// For each node, add its parent to the set, and its parent's parent, and so on.
		for (Node *node: nodes()) {
			Node::Set &set = out_map[node];

			if (node->in().empty()) {
				continue;
			}

			Node *parent = *node->in().begin();

			for (;;) {
				set.emplace(parent);
				// Stop when we've reached the root. The node will have either no parent or only itself as its parent.
				if (parent->in().empty() || *parent->in().begin() == parent) {
					break;
				}
				parent = *parent->in().begin();
			}
		}

		return out_map;
	}

	std::unordered_map<std::string, std::unordered_set<std::string>> DTree::strictDominatorLabels() const {
		std::unordered_map<std::string, std::unordered_set<std::string>> out_map;

		for (const auto &[node, set]: strictDominators()) {
			auto &out_set = out_map[node->label()];
			for (Node *sub: set) {
				out_set.emplace(sub->label());
			}
		}

		return out_map;
	}
}
