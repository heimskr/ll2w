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
		Parser::combineDotIdents(Parser::root);
	}

	void Parser::done() {
		yylex_destroy();
	}

	void Parser::combineDotIdents(ASTNode *node) {
		if (node->symbol == TOK_DOTIDENT) {
			node->lexerInfo = StringSet::intern(node->concatenate().c_str());
			node->clear();
		} else {
			for (ASTNode *child: node->children)
				Parser::combineDotIdents(child);
		}
	}
}
