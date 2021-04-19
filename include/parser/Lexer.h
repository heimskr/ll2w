#ifndef PARSER_LEXER_H_
#define PARSER_LEXER_H_

#include <unordered_map>
#include <vector>

#include <stdio.h>

#include "parser/ASTNode.h"

#define LLVMSTYPE_IS_DECLARED
#define WASMSTYPE_IS_DECLARED
typedef LL2W::ASTNode * LLVMSTYPE;
typedef LL2W::ASTNode * WASMSTYPE;

#ifndef NO_YYPARSE
#include "yyparse.h"
#include "wasmparse.h"
#endif

#ifdef __APPLE__
typedef size_t yysize;
#else
typedef int yysize;
#endif

extern FILE *llvmin;
extern char *llvmtext;
extern yysize llvmleng;
extern int llvm_flex_debug;
extern int llvmdebug;

extern FILE *wasmin;
extern char *wasmtext;
extern yysize wasmleng;
extern int wasm_flex_debug;
extern int wasmdebug;

namespace LL2W {
	class Parser;

	class Lexer {
		private:
			Parser *parser;
			yysize *leng;
			ASTNode **lval;

		public:
			Location location = {0, 1};
			std::string line;
			yysize lastYylength = 0;
			std::unordered_map<int, std::string> lines;
			bool failed = false;
			std::vector<std::pair<std::string, Location>> errors;

			Lexer(Parser &, yysize &, ASTNode *&);
			const std::string * filename(int fileno);
			void advance(const char *);
			void newline();
			void badchar(unsigned char);
			int token(const char *, int symbol);
	};

	extern Lexer llvmLexer, wasmLexer;
}

int llvmlex();
int llvmlex_destroy();
int llvmparse();
int wasmlex();
int wasmlex_destroy();
int wasmparse();
void llvmerror(const char *);
void llvmerror(const std::string &, const LL2W::Location &);
void wasmerror(const char *);
void wasmerror(const std::string &, const LL2W::Location &);

#endif
