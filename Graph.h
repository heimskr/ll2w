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
			Graph();
			Graph(size_t);

			~Graph();

			bool hasLabel(const std::string &) const;

			size_t size() const;

			Node & operator[](size_t) const;
			Node & operator[](const std::string &) const;
			Node & operator+=(const std::string &);

			Node & rename(const std::string &, const std::string &);
			Node & rename(Node &, const std::string &);
			Node & rename(Node *, const std::string &);

			void link(const std::string &, const std::string &, bool bidirectional = false);

			/** Takes a space-separated list of colon-separated pairs of labels and links each pair of nodes. */
			void addEdges(const std::string &);
	};
}

#endif
