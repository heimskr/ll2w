#ifndef NODE_H_
#define NODE_H_

#include <string>

namespace LL2W {
	class Graph;

	class Node {
		private:
			Graph *parent;
			std::string label;

		public:
			Node(Graph *parent_, const std::string &label_ = "");

	};
}

#endif
