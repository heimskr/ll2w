#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <unordered_map>

#include "Node.h"

namespace LL2W {
	class Graph {
		private:
			std::list<Node *> nodes;
			std::unordered_map<std::string, Node *> label_map;

		public:
			Graph();
			Graph(size_t);

			~Graph();

			bool has_label(const std::string &) const;

			Node & operator[](size_t) const;
			Node & operator[](const std::string &) const;

			Node & rename(const std::string &, const std::string &);
			Node & rename(Node &, const std::string &);
			Node & rename(Node *, const std::string &);
	};
}

#endif
