#include <iostream>
#include <string>

#include "Graph.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input> <output>\n";
		return 1;
	}

	LL2W::Graph graph;
	graph += "one";
	graph += "two";
	graph += "three";
	graph += "four";
	graph.addEdges("one:two two:three three:four four:one one:four one:three two:four");
}
