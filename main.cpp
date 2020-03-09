#include <iostream>
#include <map>
#include <string>

#include "graph/Graph.h"
#include "graph/DTree.h"
#include "graph/DJGraph.h"
#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "compiler/Program.h"

void lttest();
void djtest();
void rendertest();
void mergetest();
void mergetest2();
void parsertest(const std::string &);

int main(int argc, char **argv) {
	// if (argc != 3) {
	// 	std::cerr << "Usage: " << argv[0] << " <input> <output>\n";
	// 	return 1;
	// }

	// lttest();
	// djtest();
	// rendertest();

	if (1 < argc) {
		parsertest(argv[1]);
	} else {
		parsertest("ll/fat_newfile.ll");
		// mergetest2();
	}
}

void lttest() {
	LL2W::Graph lt_input {"R", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
	lt_input.addEdges("A:D B:A B:D B:E C:F C:G D:L E:H F:I G:I G:J H:E H:K I:K J:I K:I K:R L:H R:A R:B R:C");
	lt_input.renderTo("graph_lt_in.png");
	LL2W::DTree(lt_input, lt_input[0]).renderTo("graph_lt_out.png", "BT");
}

void djtest() {
	// http://citeseerx.ist.psu.edu/viewdoc/download;?doi=10.1.1.55.4084&rep=rep1&type=pdf
	// LL2W::Graph graph {"S", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "E"};
	// graph.addEdges("S:1 1:2 2:4 2:5 3:5 3:6 4:8 4:9 5:7 6:7 7:12 8:10 8:15 9:10 9:11 9:13 10:14 11:13 12:3 12:15 13:15 14:13 15:3 15:E S:E");
	LL2W::Graph graph {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
	graph.addEdges("1:2 2:3 2:11 3:4 3:8 4:5 5:6 6:5 6:7 7:2 8:9 9:6 9:10 10:8");

	graph.renderTo("graph_dj_in.png");
	LL2W::DJGraph dj(graph, graph[0]);
	LL2W::DTree(graph, graph[0]).renderTo("graph_dj_dt.png", "BT");
	dj.renderTo("graph_dj_out.png", "BT");
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

	graph.renderTo("graph_1234.png");

	graph -= "four";
	graph.renderTo("graph_123.png");

	graph.unlink("one", "two");
	graph.unlink("one", "three");
	graph.unlink("two", "three");
	graph.unlink("three", "three");
	graph.renderTo("graph_unlinked.png");
}

void mergetest() {
	LL2W::Graph graph254 {24};
	graph254.addEdges("0:1 0:2 2:3 3:4 3:5 3:23 3:8 5:6 5:7 8:9 8:10 8:14 14:15 14:16 10:11 11:12 12:13 16:22 16:17 17:21 17:18 18:19 18:20");
	graph254.addEdges("4:5 23:5 23:8 6:7 7:5 7:8 9:10 15:16 13:1 22:10 21:22 19:20 20:18 20:21");
	LL2W::DJGraph dj254(graph254, *graph254.nodes().front());
	graph254.renderTo("graph_254.png", "LR");
	dj254.renderTo("graph_254dj.png", "LR");

	LL2W::Node::Map merge = dj254.mergeSets(*dj254.nodes().front(), **std::next(dj254.nodes().begin(), 1));
	for (const std::pair<LL2W::Node *, LL2W::Node::Set> &pair: merge) {
		std::cout << "\e[32m" << pair.first->label() << "\e[0m:\e[33m";
		for (LL2W::Node *node: pair.second)
			std::cout << " " << node->label();
		std::cout << "\e[0m\n";
	}
}

void mergetest2() {
	LL2W::Graph graph {12};
	graph -= "0";
	graph.addEdges("1:2 2:3 2:11 3:4 3:8 4:5 5:6 6:5 6:7 7:2 8:9 9:6 9:10 10:8");
	LL2W::DJGraph dj11(graph, *graph.nodes().front());
	graph.renderTo("graph_11.png", "TB");
	dj11.renderTo("graph_11dj.png", "TB");

	LL2W::Node::Map merge = dj11.mergeSets(*dj11.nodes().front(), graph["11"]);
	for (const std::pair<LL2W::Node *, LL2W::Node::Set> &pair:
	           std::map<LL2W::Node *, LL2W::Node::Set>(merge.begin(), merge.end())) {
		std::cout << "\e[32m" << pair.first->label() << "\e[0m:\e[33m";
		for (LL2W::Node *node: std::set<LL2W::Node *, LL2W::Node::Node_less>(pair.second.begin(), pair.second.end()))
			std::cout << " " << node->label();
		std::cout << "\e[0m\n";
	}
}

void parsertest(const std::string &filename) {
	LL2W::Parser::open(filename);
	LL2W::Parser::debug(false, false);
	LL2W::Parser::parse();
	LL2W::Program prog(*LL2W::Parser::root);
	prog.extract();
	prog.debug();
	LL2W::Parser::done();
}
