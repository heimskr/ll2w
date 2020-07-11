#include <cassert>
#include <iostream>
#include <unordered_set>

#include "graph/DTree.h"

namespace LL2W {
	DTree::DTree(Graph &graph, const std::string &label): DTree(graph, graph[label]) {}
	DTree::DTree(Graph &graph, Node &start) {
		const size_t gsize = graph.size();
		std::unordered_map<Node *, int> visited;
		std::vector<Node *> stack {&start}, vertices(graph.size(), nullptr);
		std::unordered_map<Node *, int> semis;
		std::unordered_map<Node *, Node *> ancestors, labels, parents, doms;
		std::unordered_map<Node *, std::unordered_set<Node *>> preds, buckets;

		for (Node *node: graph.nodes()) {
			semis[node] = -1;
			ancestors[node] = labels[node] = parents[node] = doms[node] = nullptr;
		}

		int n = -1;
		std::function<void(Node *)> dfs = [&](Node *v) {
			semis[v] = ++n;
			vertices[n] = v;
			ancestors[v] = nullptr;
			for (Node *w: *v) {
				if (semis[w] == -1) {
					parents[w] = v;
					dfs(w);
				}
				preds[w].insert(v);
			}
		};

		// std::function<void(Node *)> dfs = [&](Node *node) {
		// 	visited[node] = vertices.size();
		// 	const int v = node->index();
		// 	assert(semis[v] == -1);
		// 	semis[v] = vertices.size();
		// 	vertices.push_back(node);
		// 	labels[v] = v;
		// 	for (Node *successor: *node) {
		// 		const int w = successor->index();
		// 		if (semis.at(w) == -1) {
		// 			parents[w] = v;
		// 			dfs(successor);
		// 		}

		// 		preds.at(w).insert(v);
		// 	}
		// };

		std::function<void(Node *)> compress = [&](Node *v) {
			assert(ancestors[v] != nullptr);
			if (ancestors[ancestors[v]] != nullptr) {
				compress(ancestors[v]);
				if (semis[labels[ancestors[v]]] < semis[labels[v]])
					labels[v] = labels[ancestors[v]];
				ancestors[v] = ancestors[ancestors[v]];
			}
		};

		std::function<Node *(Node *)> eval = [&](Node *v) {
			if (ancestors[v] == nullptr) {
				return v;
			} else {
				compress(v);
				return labels[v];
			}
		};

		std::function<void(Node *, Node *)> link_ = [&](Node *v, Node *w) {
			ancestors[w] = v;
		};

		dfs(&start);
		for (size_t i = gsize - 1; 1 <= i; --i) {
			Node *w = vertices[i];
			for (Node *v: preds[w]) {
				Node *u = eval(v);
				if (semis[u] < semis[w])
					semis[w] = semis[u];
			}

			buckets[vertices[semis[w]]].insert(w);
			link_(parents[w], w);
			std::unordered_set<Node *> &bucket = buckets[parents[w]];
			for (auto iter = bucket.begin(); iter != bucket.end();) {
				Node *v = *iter;
				iter = bucket.erase(iter);
				Node *u = eval(v);
				doms[v] = semis[u] < semis[v]? u : parents[w];
			}

			for (size_t i = 1; i < gsize; ++i) {
				w = vertices[i];
				if (doms[w] != vertices[semis[w]])
					doms[w] = doms[doms[w]];
			}
		}

		doms[&start] = &start;

		// for (int i = gsize - 1; 1 <= i; --i) {
		// 	int w = vertices[i]->index();

			// for (int v: preds.at(w)) {
			// 	int u = eval(v);
			// 	if (semis.at(u) < semis.at(w))
			// 		semis.at(w) = semis.at(u);
			// }

		// 	buckets[vertices.at(semis.at(w))->index()].insert(w);
		// 	ancestors[w] = parents.at(w);

		// 	std::unordered_set<int> &bucket = buckets.at(parents.at(w));
		// 	for (auto iter = bucket.begin(); iter != bucket.end();) {
		// 		int v = *iter;
		// 		bucket.erase(iter++);
		// 		int u = eval(v);
		// 		doms[v] = semis.at(u) < semis.at(v)? u : parents.at(w);
		// 	}
		// }

		// for (size_t i = 1; i < gsize; ++i) {
		// 	int w = vertices.at(i)->index();
		// 	if (doms.at(w) != vertices.at(semis.at(w))->index())
		// 		doms[w] = doms.at(doms.at(w));
		// }

		// doms[&start] = &start;

		graph.cloneTo(*this);
		startNode = &(*this)[start];
		unlink();
		for (const std::pair<Node *, Node *> &pair: doms) {

			std::cerr << "doms[" << (pair.first? pair.first->label() : "null") << "] = " << (pair.second? pair.second->label() : "null") << "\n";
			// link((*this)[*pair.first].label(), (*this)[*pair.second].label());
		}
		std::cerr << "-----------\n";
		// for (size_t i = 0, dlen = doms.size(); i < dlen; ++i)
			// link((*this)[doms.at(i)].label(), (*this)[i].label());
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

		int max = nodes.size();
		for (int i = 0; i < max; ++i)
			nodes[i] = &(*this)[*nodes[i]];

		int smallest_level = levels[*std::min_element(nodes.begin(), nodes.end(), [&](Node *left, Node *right) {
			return levels[left] < levels[right];
		})];

		std::function<void()> move_nodes_up = [&]() {
			for (int i = 0; i < max; ++i) {
				while (smallest_level < levels[nodes[i]])
					nodes[i] = nodes[i]->parent();
			}
		};

		std::function<bool()> all_nodes_equal = [&]() {
			Node *first = nodes[0];
			for (int i = 1; i < max; ++i) {
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

	std::string DTree::commonDominator(const std::vector<std::string> &labels) {
		std::vector<Node *> nodes;
		nodes.reserve(labels.size());
		for (const std::string &label: labels)
			nodes.push_back(&(*this)[label]);
		return commonDominator(nodes);
	}

	std::unordered_map<Node *, Node *> DTree::immediateDominators() const {
		std::unordered_map<Node *, Node *> out;
		for (Node *node: nodes()) {
			for (Node *successor: *node) {
				assert(out.count(successor) == 0);
				out.insert({successor, node});
			}
		}

		return out;
	}

	Node::Map DTree::strictDominators() const {
		Node::Map out_map;

		// For each node, add its parent to the set, and its parent's parent, and so on.
		for (Node *node: nodes()) {
			out_map[node] = {};
			if (node->in().empty())
				continue;
			Node *parent = *node->in().begin();
			for (;;) {
				out_map[node].insert(parent);
				// Stop when we've reached the root. The node will have either no parents or only itself as its parent.
				if (parent->in().empty() || *parent->in().begin() == parent)
					break;
				parent = *parent->in().begin();
			}
		}

		return out_map;
	}

	std::unordered_map<std::string, std::unordered_set<std::string>> DTree::strictDominatorLabels() const {
		std::unordered_map<std::string, std::unordered_set<std::string>> out_map;
		for (const auto & [node, set]: strictDominators()) {
			const std::string &label = node->label();
			out_map.insert({label, {}});
			for (Node *sub: set)
				out_map[label].insert(sub->label());
		}

		return out_map;
	}
}
