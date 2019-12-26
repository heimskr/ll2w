#ifndef NODE_H_
#define NODE_H_

#include <string>

namespace LL2W {
	class Graph;

	class Node {
		friend class Graph;

		private:
			Graph *parent;
			std::string label;

		public:
			Node() = delete;
			Node(Node &&) = delete;
			Node(const Node &) = delete;
			Node & operator=(Node &&) = delete;
			Node & operator=(const Node &) = delete;

			Node(Graph *parent_, const std::string &label_ = "");

			Node & rename(const std::string &);
	};
}

#endif
