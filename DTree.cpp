#include <unordered_set>

#include "DTree.h"

namespace LL2W {
	DTree::DTree(Graph &graph, const std::string &label): DTree(graph, graph[label]) {}
	DTree::DTree(Graph &graph, Node &start) {
		const size_t gsize = graph.size();
		std::unordered_map<Node *, int> visited;
		std::vector<Node *> stack {&start}, vertices;
		std::vector<int> semis(gsize, -1);
		std::vector<int> ancestors(gsize, -1);
		std::vector<int> labels(gsize, -1);
		std::vector<int> parents(gsize, -1);
		std::vector<int> doms(gsize, -1);
		std::vector<std::unordered_set<int>> preds(gsize), buckets(gsize);

		std::function<void(Node *)> dfs = [&](Node *node) {
			visited[node] = vertices.size();
			const int v = node->index();
			assert(semis[v] == -1);
			semis[v] = vertices.size();
			vertices.push_back(node);
			labels[v] = v;
			for (Node *successor: *node) {
				const int w = successor->index();
				if (semis.at(w) == -1) {
					parents[w] = v;
					dfs(successor);
				}

				preds.at(w).insert(v);
			}
		};

		std::function<void(int)> compress = [&](int v) {
			if (ancestors.at(ancestors.at(v)) != -1) {
				compress(ancestors[v]);
				if (semis.at(labels.at(ancestors.at(v))) <= semis.at(labels.at(v)))
					labels.at(v) = labels.at(ancestors.at(v));
				ancestors[v] = ancestors.at(ancestors.at(v));
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

		dfs(&start);

		for (int i = gsize - 1; 1 <= i; --i) {
			int w = vertices[i]->index();

			for (int v: preds.at(w)) {
				int u = eval(v);
				if (semis.at(u) < semis.at(w))
					semis.at(w) = semis.at(u);
			}

			buckets[vertices.at(semis.at(w))->index()].insert(w);
			ancestors[w] = parents.at(w);

			std::unordered_set<int> &bucket = buckets.at(parents.at(w));
			for (auto iter = bucket.begin(); iter != bucket.end();) {
				int v = *iter;
				bucket.erase(iter++);
				int u = eval(v);
				doms[v] = semis.at(u) < semis.at(v)? u : parents.at(w);
			}
		}

		for (size_t i = 1; i < gsize; ++i) {
			int w = vertices.at(i)->index();
			if (doms.at(w) != vertices.at(semis.at(w))->index())
				doms[w] = doms.at(doms.at(w));
		}

		doms[start.index()] = 0;

		graph.cloneTo(*this);
		unlink();
		for (size_t i = 0, dlen = doms.size(); i < dlen; ++i)
			link((*this)[i].label(), (*this)[doms.at(i)].label());
	}

	std::unordered_map<Node *, Node *> DTree::dominators() const {
		std::unordered_map<Node *, Node *> out;
		for (Node *node: nodes()) {
			for (Node *successor: *node) {
				assert(out.count(successor) == 0);
				out.insert({successor, node});
			}
		}

		return out;
	}
}