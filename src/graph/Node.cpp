#include <iostream>
#include <stdexcept>

#include "graph/Graph.h"
#include "graph/Node.h"

namespace LL2W {
	Node::Node(Graph *owner_, const std::string &label__): owner(owner_), label_(label__) {}

	Node & Node::setColorsNeeded(int count) {
		colorsNeeded = count;
		return *this;
	}

	const std::string & Node::label() const {
		return label_;
	}

	Node & Node::rename(const std::string &new_label) {
		return owner->rename(this, new_label);
	}

	bool Node::reflexive() const {
		return out_.contains(const_cast<Node *>(this));
	}

	bool Node::link(Node &other, bool bidirectional) {
		return link(&other, bidirectional);
	}

	bool Node::link(Node *other, bool bidirectional) {
		bool already_linked = out_.contains(other);
		if (!already_linked) {
			out_.insert(other);
			other->in_.insert(this);
		}

		if (bidirectional && other != this)
			other->link(*this);

		return already_linked;
	}

	bool Node::unlink(Node &other, bool bidirectional) {
		return unlink(&other, bidirectional);
	}

	bool Node::unlink(Node *other, bool bidirectional) {
		bool exists = out_.contains(other);
		out_.erase(other);
		other->in_.erase(this);
		reachability.erase(other);

		if (bidirectional && other != this)
			other->unlink(*this, false);

		return exists;
	}

	void Node::unlink() {
		for (Node *other: out_)
			other->in_.erase(this);
		out_.clear();
	}

	bool Node::isolated() const {
		return out_.empty();
	}

	void Node::dirty() {
		index_ = -1;
	}

	int Node::index() {
		if (index_ != -1)
			return index_;

		for (const Node *node: owner->nodes()) {
			++index_;
			if (node == this)
				return index_;
		}

		throw std::runtime_error("Node not found in parent graph");
	}

	const Node::Set & Node::out() const {
		return out_;
	}

	const Node::Set & Node::in() const {
		return in_;
	}

	Node::Set Node::allEdges() const {
		Set set = out_;
		set.insert(in_.begin(), in_.end());
		return set;
	}

	bool Node::canReach(Node &other) {
		if (other.owner != owner)
			return false;

		if (reachability.contains(&other))
			return reachability.at(&other);

		std::unordered_set<Node *> visited;
		std::list<Node *> queue {this};
		while (!queue.empty()) {
			Node *node = queue.front();
			queue.pop_front();
			for (Node *out_node: node->out()) {
				if (out_node == &other) {
					reachability.emplace(&other, true);
					return true;
				}

				if (!visited.contains(out_node)) {
					visited.insert(out_node);
					queue.push_back(out_node);
				}
			}
		}

		reachability.emplace(&other, false);
		return false;
	}

	void Node::clearReachability() {
		reachability.clear();
	}

	size_t Node::degree() const {
		size_t deg = out_.size();
		for (Node *neighbor: in_)
			if (!out_.contains(neighbor))
				++deg;
		return deg;
	}

	Node * Node::parent() const {
		if (in_.size() != 1)
			throw std::runtime_error("Cannot find parent of node with " + std::to_string(in_.size()) + " inward edges");
		return *in_.begin();
	}

	Node & Node::operator+=(Node &neighbor) {
		return *this += &neighbor;
	}

	Node & Node::operator+=(Node *neighbor) {
		out_.insert(neighbor);
		return *this;
	}

	Node & Node::operator-=(Node &neighbor) {
		return *this -= &neighbor;
	}

	Node & Node::operator-=(Node *neighbor) {
		out_.erase(neighbor);
		in_.erase(neighbor);
		return *this;
	}

	Node & Node::operator-=(const std::string &label) {
		for (Node *node: out_)
			if (node->label() == label)
				return *this -= node;
		throw std::out_of_range("Can't remove: no neighbor with label \"" + label + "\" found");
	}

	decltype(Node::out_)::iterator Node::begin() {
		return out_.begin();
	}

	decltype(Node::out_)::iterator Node::end() {
		return out_.end();
	}

	decltype(Node::in_)::iterator Node::ibegin() {
		return in_.begin();
	}

	decltype(Node::in_)::iterator Node::iend() {
		return in_.end();
	}

	std::ostream & operator<<(std::ostream &os, const Node &node) {
		return os << node.label();
	}
}
