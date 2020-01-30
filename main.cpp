#include <iostream>
#include <string>

#include <unistd.h>

#include "graph/Graph.h"
#include "graph/DTree.h"
#include "graph/DJGraph.h"
#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "compiler/Program.h"

void lttest();
void djtest();
void rendertest();
void parsertest();

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input> <output>\n";
		return 1;
	}

	// lttest();
	// djtest();
	// rendertest();
	parsertest();
}

void lttest() {
	LL2W::Graph lt_input {"R", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
	lt_input.addEdges("A:D B:A B:D B:E C:F C:G D:L E:H F:I G:I G:J H:E H:K I:K J:I K:I K:R L:H R:A R:B R:C");
	lt_input.renderTo("graph_lt_in.png");
	usleep(100000);
	LL2W::DTree(lt_input, lt_input[0]).renderTo("graph_lt_out.png", "BT");
	usleep(100000);
}

void djtest() {
	// http://citeseerx.ist.psu.edu/viewdoc/download;?doi=10.1.1.55.4084&rep=rep1&type=pdf
	// LL2W::Graph graph {"S", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "E"};
	// graph.addEdges("S:1 1:2 2:4 2:5 3:5 3:6 4:8 4:9 5:7 6:7 7:12 8:10 8:15 9:10 9:11 9:13 10:14 11:13 12:3 12:15 13:15 14:13 15:3 15:E S:E");
	LL2W::Graph graph {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
	graph.addEdges("1:2 2:3 2:11 3:4 3:8 4:5 5:6 6:5 6:7 7:2 8:9 9:6 9:10 10:8");

	graph.renderTo("graph_dj_in.png");
	usleep(100000);
	LL2W::DJGraph dj(graph, graph[0]);
	LL2W::DTree(graph, graph[0]).renderTo("graph_dj_dt.png", "BT");
	usleep(100000);
	dj.renderTo("graph_dj_out.png", "BT");
	usleep(100000);
	for (const auto [src, dest]: dj.jEdges)
		std::cout << src << " <-> " << dest << "\n";
}

void rendertest() {
	LL2W::Graph graph {"one", "two", "three", "four"};
	graph.addEdges("one:two two:three three:four four:one one:four one:three two:four three:three");

	LL2W::Graph complex {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	complex.addEdges("1:2 1:5 1:8 2:3 3:4 2:4 4:5 6:7 7:6 6:8 8:9");
	LL2W::DFSResult result = complex.DFS("1");
	std::cout << result;
	complex.renderTo("graph_complex.png");
	usleep(100000);

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

void parsertest() {
	LL2W::Parser::open("ll/reverse.ll");
	LL2W::Parser::debug(false, false);
	LL2W::Parser::parse();
	// LL2W::Parser::root->debug();
	LL2W::Program prog(*LL2W::Parser::root);
	LL2W::Parser::done();
}
