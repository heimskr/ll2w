#include <fstream>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <llvm/AsmParser/Parser.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/LLVMContext.h>
#pragma GCC diagnostic pop

#include "Parser.h"
#include "Lexer.h"

namespace LL2W {
	std::string Parser::filename = "";
	ASTNode * Parser::root = nullptr;

	void Parser::open(const std::string &filename_) {
		Parser::filename = filename_;
		yyin = fopen(filename_.c_str(), "r");
		yy_flex_debug = 0;
		yydebug = 0;

		std::ifstream ifs(filename_, std::ifstream::in);
		std::stringstream ss;
		ss << ifs.rdbuf();

		llvm::SMDiagnostic err;
		llvm::LLVMContext context;
	}

	void Parser::parse() {
		yyparse();
	}

	void Parser::done() {
		yylex_destroy();
	}
}
