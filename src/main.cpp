#include "compiler/PaddedStructs.h"
#include "compiler/Program.h"
#include "graph/DJGraph.h"
#include "graph/DTree.h"
#include "graph/Graph.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "util/Timer.h"
#include "util/Util.h"
#include "Interactive.h"
#include "main.h"

#include "parser/Nodes.h"
#include "parser/StructNode.h"
#include "parser/Types.h"

#include <llvm/IR/LLVMContext.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

// #define DEBUGMODE
// #define INTERACTIVE
// #define CATCH

int global_argc = -1;
char **global_argv = nullptr;
std::atomic<const std::string *> global_function_name;

void compile(const std::string &, bool show_debug);
void wasmparsertest(const std::string &);
void interactive(LL2W::Program &);
void paddingtest();

std::map<LL2W::ASTNode *, std::string> extras;

int main(int argc, char **argv) {
	// paddingtest();
	// return 0;
	global_argc = argc;
	global_argv = argv;

	auto usage = [] { std::cerr << "Usage: ll2w [-d] <input>\n"; exit(1); };
	if (argc < 2)
		usage();
#ifdef CATCH
	try {
#endif
		if (argc == 3) {
			LL2W::Timer timer{"Main"};
			if (strcmp(argv[1], "-d") == 0) {
				compile(argv[2], true);
			} else {
				compile(argv[1], false);
			}
		} else if (argc == 2) {
			LL2W::Timer timer{"Main"};
			compile(argv[1], false);
		} else {
			usage();
		}
#ifdef CATCH
	} catch (...) {
		LL2W::Timer::summary();
		if (const std::string *name = global_function_name.load()) {
			std::cerr << "Caught exception in " << *name << ":\n";
		}
		throw;
	}
#endif

	LL2W::Timer::summary(0.1);

	LL2W::StructType::knownStructs.clear();

#ifdef TRACK_ASTNODES
	std::cerr << "Remaining nodes: " << all_nodes.size() << "\n";
	for (auto *remaining: all_nodes)
		remaining->debug();
#endif
}

bool hasArg(const char *arg) {
	if (global_argv) {
		for (int i = 0; i < global_argc; ++i) {
			if (strcmp(global_argv[i], arg) == 0) {
				return true;
			}
		}
	}
	return false;
}

void compile(const std::string &filename, bool show_debug) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Couldn't open file for reading");
	}
	std::string text;
	file.seekg(0, std::ios::end);
	text.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	text.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	signal(SIGINT, +[](int) {
		LL2W::Timer::summary();
		if (const std::string *name = global_function_name.load()) {
			std::cerr << "Canceled during analysis/compilation of \e[1m" << *name << "\e[22m.\n";
		}
		std::exit(128 + SIGINT);
	});

	signal(SIGUSR1, +[](int) {
		LL2W::Timer::summary(); // probably not safe but whatever
		if (const std::string *name = global_function_name.load()) {
			std::cerr << "\e[1m" << *name << "\e[22m\n";
		}
	});

	signal(SIGSEGV, +[](int) {
		LL2W::Timer::summary();
		std::cerr << "Segfault!\n";
		std::exit(128 + SIGSEGV);
	});

	// LL2W::llvmParser.in(text);
	// LL2W::llvmParser.debug(false, false);
	// LL2W::llvmParser.parse();
	// LL2W::Program prog(*LL2W::llvmParser.root);
	llvm::LLVMContext context;
	LL2W::Program prog(text, context);
	// return;
#ifdef INTERACTIVE
	(void) show_debug;
	LL2W::interactive(prog);
	std::cout << "Done.\n";
#else
	prog.analyze();
	prog.compile();
#ifdef DEBUGMODE
	prog.debug();
#else
	if (show_debug) {
		prog.debugSection(nullptr);
		for (const int index: prog.debugIndices) {
			const auto &location = prog.locations.at(index);
			std::cout << "\e[33m" << index << " \e[39;2m->\e[22m \e[32m" << location.index << " \e[39;2m->\e[22m "
			          << prog.files.at(location.file).filename << "\e[2m:\e[22m" << location.line << "\e[2m:\e[22m"
			          << location.column;
			if (prog.subprograms.count(location.scope) != 0)
				std::cout << " \e[2m(\e[22m" << prog.subprograms.at(location.scope).name << "\e[2m)\e[22m";
			std::cout << '\n';
		}
	} else {
		std::cout << prog.toString();
	}
#endif
#endif
	// for (const auto &[name, stype]: LL2W::StructType::knownStructs) {
	// 	std::cerr << name << ":\n";
	// 	auto snode = stype->node;
	// 	int i = 0;
	// 	for (const auto &type: snode->types) {
	// 		const int offset = LL2W::PaddedStructs::getOffset(stype, i);
	// 		std::cerr << "    " << i << " (" << std::string(*type) << "): " << offset / 8 << '\n';
	// 		++i;
	// 	}
	// 	std::cerr << "    Width: " << LL2W::PaddedStructs::getOffset(stype, snode->types.size()) / 8 << " B\n";
	// 	std::cerr << "    Alignment: " << stype->alignment() << " B\n\n";
	// }

#ifdef TRACK_ASTNODES
	for (auto *node: all_nodes)
		extras.emplace(node, std::string(node->location) + " " + node->debugExtra());
#endif

	LL2W::llvmParser.done();
}

void wasmparsertest(const std::string &filename) {
	LL2W::wasmParser.open(filename);
	LL2W::wasmParser.debug(false, false);
	LL2W::wasmParser.parse();
	LL2W::wasmParser.root->debug();
	LL2W::wasmParser.done();
}

void paddingtest() {
	using namespace LL2W;

	// llvm::ArrayType *i8x8 = llvm::ArrayType::get(i8, 8);
	// llvm::ArrayType *i8x32 = llvm::ArrayType::get(i8, 32);
	// // %"struct.std::__1::aligned_storage<24, 16>::type"
	// llvm::StructType *aligned24_16 = llvm::StructType::get(llvm, {i8x32}, false);
	// // %struct.StorageDevice
	// llvm::StructType *device = llvm::StructType::get(llvm, {i8p}, false); // Actually {i32 (...)**}
	// llvm::PointerType *device_ptr = llvm::PointerType::get(device, 0);
	// // %"class.std::__1::__function::__value_func"
	// llvm::StructType *s10 = llvm::StructType::get(llvm, {aligned24_16, device_ptr, i8x8}, false);

	auto i8 = IntType::make(8);
	auto i8x8 = ArrayType::make(8, i8);
	auto i8x32 = ArrayType::make(32, i8);
	auto i8p = PointerType::make(i8);
	auto aligned24_16 = StructType::make(StructNode::make(std::initializer_list<LL2W::TypePtr> {i8x32}, StructShape::Default));
	auto device = StructType::make(StructNode::make(std::initializer_list<LL2W::TypePtr> {i8p}, StructShape::Default));
	auto device_ptr = PointerType::make(i8);

	auto snode = std::make_shared<LL2W::StructNode>(std::initializer_list<LL2W::TypePtr> {aligned24_16, device_ptr, i8x8}, LL2W::StructShape::Default);
	auto stype = std::make_shared<LL2W::StructType>(snode);
	std::cout << "Custom: " << stype->barename() << '\n';
	int i = 0;
	for (const auto &type: snode->types) {
		const int offset = LL2W::PaddedStructs::getOffset(stype, i);
		std::cout << i << " (" << std::string(*type) << "): " << offset / 8 << '\n';
		++i;
	}
	std::cout << "Width: " << LL2W::PaddedStructs::getOffset(stype, snode->types.size()) / 8 << '\n';
}