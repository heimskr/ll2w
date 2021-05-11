#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "compiler/Program.h"
#include "graph/Graph.h"
#include "graph/DTree.h"
#include "graph/DJGraph.h"
#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "util/Util.h"
#include "Interactive.h"

// #define DEBUGMODE
// #define INTERACTIVE

void compile(const std::string &);
void wasmparsertest(const std::string &);
void interactive(LL2W::Program &);

int main(int argc, char **argv) {
	if (1 < argc) {
		compile(argv[1]);
	} else {
		compile("ll/fat.ll");
	}
}

LL2W::Program *prog = nullptr;

void compile(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Couldn't open file for reading");
	std::string text;
	file.seekg(0, std::ios::end);
	text.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	text.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	LL2W::llvmParser.in(text);
	LL2W::llvmParser.debug(false, false);
	LL2W::llvmParser.parse();
	prog = new LL2W::Program(*LL2W::llvmParser.root);
#ifdef INTERACTIVE
	LL2W::interactive(*prog);
	std::cout << "Done.\n";
#else
	prog->compile();
#ifdef DEBUGMODE
	prog->debug();
#else
	std::cout << prog->toString();
#endif
#endif
	LL2W::llvmParser.done();
	delete prog;
}

void wasmparsertest(const std::string &filename) {
	LL2W::wasmParser.open(filename);
	LL2W::wasmParser.debug(false, false);
	LL2W::wasmParser.parse();
	LL2W::wasmParser.root->debug();
	LL2W::wasmParser.done();
}
