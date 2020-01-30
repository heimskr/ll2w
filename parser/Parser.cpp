#include <fstream>
#include <sstream>

#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"

namespace LL2W {
	std::string Parser::filename = "";
	ASTNode * Parser::root = nullptr;

	void Parser::open(const std::string &filename_) {
		Parser::filename = filename_;
		yyin = fopen(filename_.c_str(), "r");
	}

	void Parser::debug(bool flex, bool bison) {
		yy_flex_debug = flex;
		yydebug = bison;
	}

	void Parser::parse() {
		yyparse();
	}

	void Parser::done() {
		yylex_destroy();
		delete root;
	}
}
