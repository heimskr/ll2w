#include <iostream>
#include <string>

#include <unistd.h>

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
	graph.addEdges("one:two two:three three:four four:one one:four one:three two:four three:three");
	std::cout << graph.toDot();
	graph.renderTo("graph1234.png");
	usleep(100000);
	graph -= "four";
	std::cout << graph.toDot();
	graph.renderTo("graph123.png");
}
