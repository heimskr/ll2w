#include <cstring>
#include <fstream>
#include <sstream>

#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"

int llvmwrap() { return 1; }
int wasmwrap() { return 1; }

extern YY_BUFFER_STATE llvm_scan_buffer(char *, size_t);
extern YY_BUFFER_STATE wasm_scan_buffer(char *, size_t);
extern void llvm_delete_buffer(YY_BUFFER_STATE);
extern void wasm_delete_buffer(YY_BUFFER_STATE);

namespace LL2W {
	void Parser::open(const std::string &filename_) {
		errorCount = 0;
		filename = filename_;
		if (mode == Mode::LLVM)
			llvmin = fopen(filename.c_str(), "r");
		else
			wasmin = fopen(filename.c_str(), "r");
	}

	void Parser::in(const std::string &text) {
		errorCount = 0;
		buffer = new char[text.size() + 2];
		std::strncpy(buffer, text.c_str(), text.size() + 1);
		buffer[text.size() + 1] = '\0'; // Input to flex needs two null terminators.
		if (mode == Mode::LLVM)
			bufferState = llvm_scan_buffer(buffer, text.size() + 2);
		else
			bufferState = wasm_scan_buffer(buffer, text.size() + 2);
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

		if (buffer) {
			delete buffer;
			buffer = nullptr;
		}

		if (bufferState) {
			// Causes a double free—does llvmparse/wasmparse already do this?
			// if (mode == Mode::LLVM)
			// 	llvm_delete_buffer(bufferState);
			// else
			// 	wasm_delete_buffer(bufferState);
			// bufferState = nullptr;
		}
	}

	const char * Parser::getName(int symbol) {
		return mode == Mode::LLVM? getNameLLVM(symbol) : getNameWASM(symbol);
	}

	std::string Parser::getBuffer() const {
		return buffer? buffer : "";
	}

	Parser llvmParser(Parser::Mode::LLVM), wasmParser(Parser::Mode::WASM);
}
