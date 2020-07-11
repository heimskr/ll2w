#include <cassert>
#include <iostream>
#include <unordered_set>

#include "graph/DTree.h"

namespace LL2W {
	DTree::DTree(Graph &graph, const std::string &label): DTree(graph, graph[label]) {}
	DTree::DTree(Graph &graph, Node &start) {
		// Credit to Keith D. Cooper, Timothy J. Harvey and Ken Kennedy for this algorithm (and DTree::intersect).
		// <https://www.cs.rice.edu/~keith/EMBED/dom.pdf>

		const std::unordered_map<Node *, std::unordered_set<Node *>> preds = graph.predecessors();
		const std::vector<Node *> post = postOrder(start);
		std::vector<Node *> rpost = post;
		std::reverse(rpost.begin(), rpost.end());
		std::cerr << "rpost:"; for (const Node *n: rpost) std::cerr << " " << n->label(); std::cerr << "\n";

		for (size_t i = 0; i < post.size(); ++i)
			postIndices.insert({post[i], i});

		for (Node *node: graph.nodes())
			dominators.insert({node, nullptr});
		dominators[&start] = &start;

		std::cerr << "Start: " << start.label() << "\n";

		bool changed = true;
		while (changed) {
			changed = false;
			for (Node *b: rpost) {
				if (b == &start) {
					std::cerr << "no\n";
					continue;
				}

				std::cerr << "b: " << b->label() << "\n";

				const std::unordered_set<Node *> &bpreds = preds.at(b);
				Node *new_idom = *bpreds.begin();
				for (Node *p: bpreds) {
					if (p != new_idom && dominators[p] != nullptr)
						intersect(&start, p, new_idom);
				}

				if (dominators[b] != new_idom) {
					dominators[b] = new_idom;
					changed = true;
				}
			}
		}

		graph.cloneTo(*this);
		startNode = &(*this)[start];
		unlink();
		for (const std::pair<Node *, Node *> &pair: dominators)
			link((*this)[*pair.first].label(), (*this)[*pair.second].label());
		// for (size_t i = 0, dlen = dominators.size(); i < dlen; ++i)
		// 	link((*this)[dominators.at(i)].label(), (*this)[i].label());
	}

	Node * DTree::intersect(Node *start, Node *b1, Node *b2) {
		std::cerr << "Intersect(" << b1->label() << ", " << b2->label() << ")\n";
		Node *finger1 = b1, *finger2 = b2;
		while (finger1 != finger2) {
			std::cerr << "[" << finger1->label() << ", " << finger2->label() << "]\n";
			std::cerr << "pI: (" << postIndices[finger1] << ", " << postIndices[finger2] << ")\n";
			while (postIndices[finger1] < postIndices[finger2]) {
				finger1 = dominators[finger1];
				std::cerr << "1 := " << finger1->label() << ", pI: " << postIndices[finger1] << "\n";
				if (finger1 == start)
					break;
			}
			while (postIndices[finger2] < postIndices[finger1]) {
				finger2 = dominators[finger2];
				std::cerr << "2 := " << finger2->label() << ", pI: " << postIndices[finger2] << "\n";
				if (finger2 == start)
					break;
			}
		}
		return finger1;
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
