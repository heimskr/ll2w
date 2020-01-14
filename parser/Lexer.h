#ifndef PARSER_LEXER_H_
#define PARSER_LEXER_H_

#include <unordered_map>

#include <stdio.h>

#include "ASTNode.h"

#define YYSTYPE_IS_DECLARED
typedef LL2W::ASTNode * YYSTYPE;

#include "yyparse.h"

#ifdef __APPLE__
typedef size_t yysize;
#else
typedef int yysize;
#endif

extern FILE *yyin;
extern char *yytext;
extern yysize yyleng;
extern int yy_flex_debug;
extern int yydebug;


namespace LL2W {
	struct Lexer {
		static Location location;
		static std::string line;
		static yysize last_yylength;
		static std::vector<std::string> filenames;
		static std::unordered_map<int, std::unordered_map<int, std::string>> lines;
		static bool failed;

		static const std::string * filename(int fileno);
		static void advance();
		static void newline();
		static void badchar(unsigned char);
		static int token(int symbol);
	};
}

int yylex();
int yylex_destroy();
int yyparse();
void yyerror(const char *message);

#endif
