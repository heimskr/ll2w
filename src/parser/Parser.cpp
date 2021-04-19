#include <fstream>
#include <sstream>

#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"

namespace LL2W {
	void Parser::open(const std::string &filename_) {
		filename = filename_;
		llvmin = fopen(filename_.c_str(), "r");
	}

	void Parser::debug(bool flex, bool bison) {
		if (mode == Mode::LLVM) {
			llvm_flex_debug = flex;
			llvmdebug = bison;
		} else {
			wasm_flex_debug = flex;
			wasmdebug = bison;
		}
	}

	void Parser::parse() {
		if (mode == Mode::LLVM)
			llvmparse();
		else
			wasmparse();
	}

	void Parser::done() {
		if (mode == Mode::LLVM)
			llvmlex_destroy();
		else
			wasmlex_destroy();
		delete root;
	}

	const char * LL2W::Parser::getName(int symbol) {
		return mode == Mode::LLVM? getNameLLVM(symbol) : getNameWASM(symbol);
	}

	Parser llvmParser(Parser::Mode::LLVM), wasmParser(Parser::Mode::WASM);
}
