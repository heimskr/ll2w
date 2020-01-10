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

	LL2W::Graph complex {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	complex.addEdges("1:2 1:5 1:8 2:3 3:4 2:4 4:5 6:7 7:6 6:8 8:9");
	LL2W::DFSResult result = complex.DFS("1");
	std::cout << result;
	complex.renderTo("graph_complex.png");
	usleep(100000);

	LL2W::Graph lt_input {"R", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
	lt_input.addEdges("A:D B:A B:D B:E C:F C:G D:L E:H F:I G:I G:J H:E H:K I:K J:I K:I K:R L:H R:A R:B R:C");
	// LL2W::Graph lt_input {"0", "1", "2", "3", "4", "5", "6", "7"};
	// lt_input.addEdges("0:1 1:2 1:3 2:7 3:4 4:5 4:6 5:7 6:4");

	lt_input.renderTo("graph_lt_in.png");
	usleep(100000);
	lt_input.lengauerTarjan(lt_input["R"]).renderTo("graph_lt_out.png");
	usleep(100000);

	std::cout << graph.toDot();
	graph.renderTo("graph_1234.png");
	usleep(100000);

	graph -= "four";
	graph.renderTo("graph_123.png");
	usleep(100000);

	graph.unlink("one", "two");
	graph.unlink("one", "three");
	graph.unlink("two", "three");
	graph.unlink("three", "three");
	graph.renderTo("graph_unlinked.png");
}
