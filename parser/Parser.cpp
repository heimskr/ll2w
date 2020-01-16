#include <fstream>
#include <sstream>

#include "Parser.h"
#include "Lexer.h"
#include "StringSet.h"

namespace LL2W {
	std::string Parser::filename = "";
	ASTNode * Parser::root = nullptr;

	void Parser::open(const std::string &filename_) {
		Parser::filename = filename_;
		yyin = fopen(filename_.c_str(), "r");
		yy_flex_debug = 0;
		yydebug = 0;
	}

	void Parser::parse() {
		yyparse();
	}

	void Parser::done() {
		yylex_destroy();
	}
}
