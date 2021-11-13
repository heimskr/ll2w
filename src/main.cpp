#include <cstring>
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
#include "util/Timer.h"
#include "util/Util.h"
#include "Interactive.h"
#include "main.h"

#include "parser/Nodes.h"
#include "parser/StructNode.h"
#include "parser/Types.h"

// #define DEBUGMODE
// #define INTERACTIVE
// #define CATCH

int global_argc = -1;
char **global_argv = nullptr;

void compile(const std::string &, bool show_debug);
void wasmparsertest(const std::string &);
void interactive(LL2W::Program &);
void paddingtest();

int main(int argc, char **argv) {
	global_argc = argc;
	global_argv = argv;

	auto usage = [] { std::cerr << "Usage: ll2w [-d] <input>\n"; exit(1); };
	if (argc < 2)
		usage();
#ifdef CATCH
	try {
#endif
		if (argc == 3) {
			LL2W::Timer timer("Compile");
			if (strcmp(argv[1], "-d") == 0)
				compile(argv[2], true);
			else
				compile(argv[1], false);
		} else if (argc == 2) {
			LL2W::Timer timer("Compile");
			compile(argv[1], false);
		} else
			usage();
#ifdef CATCH
	} catch (...) {
		LL2W::Timer::summary();
		throw;
	}
#endif

	LL2W::Timer::summary();
}

bool hasArg(const char *arg) {
	if (global_argv)
		for (int i = 0; i < global_argc; ++i)
			if (strcmp(global_argv[i], arg) == 0)
				return true;
	return false;
}

LL2W::Program *prog = nullptr;

void compile(const std::string &filename, bool show_debug) {
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
	if (show_debug) {
		prog->debugSection(nullptr);
		for (const int index: prog->debugIndices) {
			const auto &location = prog->locations.at(index);
			std::cout << "\e[33m" << index << " \e[39;2m->\e[22m \e[32m" << location.index << " \e[39;2m->\e[22m "
			          << prog->files.at(location.file).filename << "\e[2m:\e[22m" << location.line << "\e[2m:\e[22m"
			          << location.column;
			if (prog->subprograms.count(location.scope) != 0)
				std::cout << " \e[2m(\e[22m" << prog->subprograms.at(location.scope).name << "\e[2m)\e[22m";
			std::cout << '\n';
		}
	}
	else
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

void paddingtest() {
	auto i1  = std::make_shared<LL2W::IntType>(1);
	auto i8  = std::make_shared<LL2W::IntType>(8);
	auto i16 = std::make_shared<LL2W::IntType>(16);
	auto i24 = std::make_shared<LL2W::IntType>(24);
	auto i32 = std::make_shared<LL2W::IntType>(32);
	auto i64 = std::make_shared<LL2W::IntType>(64);
	auto i8x3 = std::make_shared<LL2W::ArrayType>(3, i8);
	auto i24x3 = std::make_shared<LL2W::ArrayType>(3, i24);
	auto snode = std::make_shared<LL2W::StructNode>(std::initializer_list<LL2W::TypePtr> {
		i32, i8, i8x3, i8, i8, i8, i8, i64, i16, i32
	}, LL2W::StructShape::Default);
	auto stype = std::make_shared<LL2W::StructType>(snode);
	std::cout << "Custom: " << stype->barename() << '\n';
	int largest = 0, offset = 0, last_offset = 0, i = 0;
	for (const auto &type: snode->types) {
		const int align = type->alignment() * 8;
		const int width = type->width();
		if (align == 0)
			continue;
		offset = LL2W::Util::upalign(offset, align);
		last_offset = offset;
		std::cout << i++ << " (" << std::string(*type) << "): " << offset / 8 << '\n';
		offset += width;
		if (largest < width)
			largest = width;
	}
	std::cout << "Width: " << LL2W::Util::upalign(offset, largest) / 8 << '\n';
}