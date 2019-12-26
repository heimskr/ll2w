#include "Graph.h"
#include "Node.h"

namespace LL2W {
	Node::Node(Graph *parent_, const std::string &label_): parent(parent_), label(label_) {}

	Node & Node::rename(const std::string &new_label) {
		return parent->rename(this, new_label);
	}
}
