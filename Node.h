#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <unordered_set>

namespace LL2W {
	class Graph;

	class Node {
		friend class Graph;

		private:
			Graph *parent;
			std::string label;
			std::unordered_set<Node *> adjacent;

		public:
			Node() = delete;
			Node(Node &&) = delete;
			Node(const Node &) = delete;
			Node & operator=(Node &&) = delete;
			Node & operator=(const Node &) = delete;

			/** Creates a node with a parent graph and a given label. */
			Node(Graph *, const std::string &);

			/** Changes the node's label. */
			Node & rename(const std::string &);

			/** Returns whether the node is connected to itself. */
			bool reflexive() const;

			/** Adds a connection (unidirectional by default) to another node. */
			bool link(Node &, bool bidirectional = false);
			/** Adds a connection (unidirectional by default) to another node. */
			bool link(Node *, bool bidirectional = false);

			/** Adds a neighbor. */
			Node & operator+=(Node &);
			/** Adds a neighbor. */
			Node & operator+=(Node *);

			/** Removes a neighbor. */
			Node & operator-=(Node &);
			/** Removes a neighbor. */
			Node & operator-=(Node *);
			/** Removes a neighbor with a given label. */
			Node & operator-=(const std::string &);
	};
}

#endif
