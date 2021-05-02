#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <string>

#include <stdio.h>

#include "ASTNode.h"

typedef struct yy_buffer_state * YY_BUFFER_STATE;

namespace LL2W {
	class Parser {
		private:
			std::string filename;
			char *buffer = nullptr;
			YY_BUFFER_STATE bufferState = nullptr;
			const char * getNameLLVM(int symbol);
			const char * getNameWASM(int symbol);

		public:
			enum class Mode {LLVM, WASM};

			Mode mode;
			ASTNode *root = nullptr;
			int errorCount = 0;

			Parser(Mode mode_): mode(mode_) {}
			void open(const std::string &filename);
			void in(const std::string &text);
			void debug(bool flex, bool bison);
			void parse();
			void done();

			const char * getName(int symbol);
			std::string getBuffer() const;
	};

	extern Parser llvmParser, wasmParser;
}

#endif
