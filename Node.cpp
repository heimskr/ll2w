#include <iostream>
#include <stdexcept>

#include "Graph.h"
#include "Node.h"

namespace LL2W {
	Node::Node(Graph *parent_, const std::string &label__): parent(parent_), label_(label__) {}

	const std::string & Node::label() const {
		return label_;
	}

	Node & Node::rename(const std::string &new_label) {
		return parent->rename(this, new_label);
	}

	bool Node::reflexive() const {
		return adjacent_.count(const_cast<Node *>(this)) == 1;
	}

	bool Node::link(Node &other, bool bidirectional) {
		return link(&other, bidirectional);
	}

	bool Node::link(Node *other, bool bidirectional) {
		bool already_linked = adjacent_.count(other) == 1;
		if (!already_linked)
			adjacent_.insert(other);
		if (bidirectional && other != this)
			other->link(*this);
		return already_linked;
	}

	bool Node::unlink(Node &other, bool bidirectional) {
		return unlink(&other, bidirectional);
	}

	bool Node::unlink(Node *other, bool bidirectional) {
		bool exists = adjacent_.count(other) == 1;
		if (exists)
			adjacent_.erase(other);
		if (bidirectional && other != this)
			other->unlink(*this);
		return exists;
	}

	void Node::unlink() {
		adjacent_.clear();
	}

	bool Node::isolated() const {
		return adjacent_.empty();
	}

	void Node::dirty() {
		index_ = -1;
	}

	int Node::index() {
		if (index_ != -1)
			return index_;

		for (const std::pair<const std::string &, Node *> pair: *parent) {
			++index_;
			if (pair.second == this)
				return index_;
		}

		throw std::runtime_error("Node not found in parent graph");
	}

	const std::set<Node *, Node::Node_less> Node::adjacent() const {
		return adjacent_;
	}

	Node & Node::operator+=(Node &neighbor) {
		return *this += &neighbor;
	}

	Node & Node::operator+=(Node *neighbor) {
		adjacent_.insert(neighbor);
		return *this;
	}

	Node & Node::operator-=(Node &neighbor) {
		return *this -= &neighbor;
	}

	Node & Node::operator-=(Node *neighbor) {
		adjacent_.erase(neighbor);
		return *this;
	}

	Node & Node::operator-=(const std::string &label) {
		for (Node *node: adjacent_) {
			if (node->label() == label)
				return *this -= node;
		}

		throw std::out_of_range("Can't remove: no neighbor with label \"" + label + "\" found");
	}

	decltype(Node::adjacent_)::iterator Node::begin() {
		return adjacent_.begin();
	}

	decltype(Node::adjacent_)::iterator Node::end() {
		return adjacent_.end();
	}
}
