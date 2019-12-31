#include "Graph.h"
#include "Node.h"

namespace LL2W {
	Node::Node(Graph *parent_, const std::string &label_): parent(parent_), label(label_) {}

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
		if (bidirectional)
			other->link(*this);
		return already_linked;
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
			if (node->label == label)
				return *this -= node;
		}

		throw std::out_of_range("Can't remove: no neighbor with label \"" + label + "\" found");
	}
}
