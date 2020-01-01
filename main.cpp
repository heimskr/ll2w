#include <iostream>
#include <string>

#include <unistd.h>

#include "Graph.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input> <output>\n";
		return 1;
	}

	LL2W::Graph graph {"one", "two", "three", "four"};
	graph.addEdges("one:two two:three three:four four:one one:four one:three two:four three:three");
	std::cout << graph.toDot();
	graph.renderTo("graph1234.png");
	usleep(100000);
	graph -= "four";
	std::cout << graph.toDot();
	graph.renderTo("graph123.png");
	usleep(100000);
	graph.unlink("one", "two");
	graph.unlink("one", "three");
	graph.unlink("two", "three");
	graph.unlink("three", "three");
	std::cout << graph.toDot();
	graph.renderTo("graph_unlinked.png");
}
