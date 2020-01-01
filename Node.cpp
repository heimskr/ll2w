#include <iostream>
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
		return adjacent.count(const_cast<Node *>(this)) == 1;
	}

	bool Node::link(Node &other, bool bidirectional) {
		return link(&other, bidirectional);
	}

	bool Node::link(Node *other, bool bidirectional) {
		bool already_linked = adjacent.count(other) == 1;
		if (!already_linked)
			adjacent.insert(other);
		if (bidirectional && other != this)
			other->link(*this);
		return already_linked;
	}

	bool Node::unlink(Node &other, bool bidirectional) {
		return unlink(&other, bidirectional);
	}

	bool Node::unlink(Node *other, bool bidirectional) {
		bool exists = adjacent.count(other) == 1;
		if (exists)
			adjacent.erase(other);
		if (bidirectional && other != this)
			other->unlink(*this);
		return exists;
	}

	Node & Node::operator+=(Node &neighbor) {
		return *this += &neighbor;
	}

	Node & Node::operator+=(Node *neighbor) {
		adjacent.insert(neighbor);
		return *this;
	}

	Node & Node::operator-=(Node &neighbor) {
		return *this -= &neighbor;
	}

	Node & Node::operator-=(Node *neighbor) {
		adjacent.erase(neighbor);
		return *this;
	}

	Node & Node::operator-=(const std::string &label) {
		for (Node *node: adjacent) {
			if (node->label() == label)
				return *this -= node;
		}

		throw std::out_of_range("Can't remove: no neighbor with label \"" + label + "\" found");
	}
}
