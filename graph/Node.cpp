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
		return out_.count(const_cast<Node *>(this)) == 1;
	}

	bool Node::link(Node &other, bool bidirectional) {
		return link(&other, bidirectional);
	}

	bool Node::link(Node *other, bool bidirectional) {
		bool already_linked = out_.count(other) == 1;
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
		bool exists = out_.count(other) == 1;
		out_.erase(other);
		other->in_.erase(this);

		if (bidirectional && other != this)
			other->unlink(*this);

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

		for (const Node *node: parent->nodes()) {
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
		return *this;
	}

	Node & Node::operator-=(const std::string &label) {
		for (Node *node: out_) {
			if (node->label() == label)
				return *this -= node;
		}

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
