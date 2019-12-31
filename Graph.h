#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <unordered_map>

#include "Node.h"

namespace LL2W {
	class Graph {
		private:
			std::list<Node *> nodes;
			std::unordered_map<std::string, Node *> labelMap;

		public:
			/** Constructs a graph with no nodes. */
			Graph();

			/** Constructs a new graph with a number n of nodes with labels 0, 1, ..., n. */
			Graph(size_t);

			~Graph();

			/** Returns whether the graph contains a node with a given label. */
			bool hasLabel(const std::string &) const;

			/** Returns the number of nodes in the graph. */
			size_t size() const;

			/** Returns the node at a given index. Throws an exception if no node exists at the index. */
			Node & operator[](size_t) const;
			/** Returns the node with a given label. Throws an exception if no such node exists. */
			Node & operator[](const std::string &) const;

			/** Adds a node with a given label. */
			Graph & operator+=(const std::string &);

			/** Removes and deletes a node. */
			Graph & operator-=(Node &);
			/** Removes and deletes a node. */
			Graph & operator-=(Node *);
			/** Removes and deletes a node with a given label. */
			Graph & operator-=(const std::string &);

			/** Assigns a new label to a node with a given label and returns the node. */
			Node & rename(const std::string &, const std::string &);
			/** Assigns a new label to a node and returns the node. */
			Node & rename(Node &, const std::string &);
			/** Assigns a new label to a node and returns the node. */
			Node & rename(Node *, const std::string &);

			/** Connects two nodes with given labels (unidirectionally by default). */
			void link(const std::string &, const std::string &, bool bidirectional = false);

			/** Takes a space-separated list of colon-separated pairs of labels and links each pair of nodes. */
			void addEdges(const std::string &);

			/** Removes all nodes from the graph. */
			void reset();

			/** Returns a representation of the graph in graphviz dot syntax. */
			std::string toDot(const std::string &direction = "LR") const;

			/** Renders a PNG representation of the graph to an output file. */
			void renderTo(const std::string &png_path, const std::string &direction = "LR");

			decltype(labelMap)::iterator begin();
			decltype(labelMap)::iterator end();
	};
}

#endif
