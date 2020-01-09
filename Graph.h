#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include <list>
#include <unordered_map>

#include "DFSResult.h"
#include "Node.h"

namespace LL2W {
	class Graph {
		private:
			std::list<Node *> nodes;
			std::unordered_map<std::string, Node *> labelMap;

		public:
			/** Constructs a graph with no nodes. */
			Graph();

			/** Constructs a graph with a number n of nodes with labels 0, 1, ..., n. */
			Graph(size_t);

			/** Constructs a graph with nodes with given labels. */
			Graph(std::initializer_list<std::string>);

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

			/** Removes any connection between two nodes with given labels (and optionally the inverse edge too). */
			void unlink(const std::string &, const std::string &, bool bidirectional = false);
			/** Removes all edges in the graph. */
			void unlink();

			/** Returns a clone of the graph. */
			Graph clone(std::unordered_map<Node *, Node *> *rename_map = nullptr);

			/** Takes a space-separated list of colon-separated pairs of labels and links each pair of nodes. */
			void addEdges(const std::string &);

			/** Removes all nodes from the graph. */
			void reset();

			/** Attempts to find the first node matching a predicate function. */
			Node * find(std::function<bool(Node &)>);

			/** Runs a depth-first search at a given start node. */
			DFSResult DFS(Node *);
			/** Runs a depth-first search at a given start node. */
			DFSResult DFS(Node &);
			/** Runs a depth-first search at a given start node. */
			DFSResult DFS(const std::string &);

			Graph lengauerTarjan(Node *);
			Graph lengauerTarjan(Node &);
			Graph lengauerTarjan(const std::string &);

			/** * Calculates the dominator tree of the graph for a given start node and returns a tree in which each
			 * node other than the start node is linked to by its immediate dominator. */
			Graph makeDTree(Node *, bool bidirectional = false);
			/** * Calculates the dominator tree of the graph for a given start node and returns a tree in which each
			 * node other than the start node is linked to by its immediate dominator. */
			Graph makeDTree(Node &, bool bidirectional = false);
			/** * Calculates the dominator tree of the graph for a given start node and returns a tree in which each
			 * node other than the start node is linked to by its immediate dominator. */
			Graph makeDTree(const std::string &, bool bidirectional = false);

			/** Returns a representation of the graph in graphviz dot syntax. */
			std::string toDot(const std::string &direction = "TB") const;

			/** Renders a PNG representation of the graph to an output file. */
			void renderTo(const std::string &png_path, const std::string &direction = "TB");

			decltype(labelMap)::iterator begin();
			decltype(labelMap)::iterator end();
	};
}

#endif
