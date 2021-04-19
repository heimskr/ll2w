#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <string>

#include <stdio.h>

#include "ASTNode.h"

namespace LL2W {
	class Parser {
		private:
			std::string filename;
			const char * getNameLLVM(int symbol);
			const char * getNameWASM(int symbol);

		public:
			enum class Mode {LLVM, WASM};

			Mode mode;
			ASTNode *root = nullptr;

			Parser(Mode mode_): mode(mode_) {}
			void open(const std::string &filename);
			void debug(bool flex, bool bison);
			void parse();
			void done();

			const char * getName(int symbol);
	};

	extern Parser llvmParser, wasmParser;
}

#endif
