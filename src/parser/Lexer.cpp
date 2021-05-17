#include <iostream>

#include "parser/Lexer.h"
#include "parser/Parser.h"

namespace LL2W {
	Lexer llvmLexer(llvmParser, llvmleng, llvmlval), wasmLexer(wasmParser, wasmleng, wasmlval);

	Lexer::Lexer(Parser &parser_, yysize &yyleng_ref, ASTNode *&yylval_ref):
		parser(&parser_), leng(&yyleng_ref), lval(&yylval_ref) {}

	void Lexer::advance(const char *text) {
		line += text;
		location.column += lastYylength;
		lastYylength = *leng;

		size_t newline_count = 0, i = 0, col = location.column;
		char ch = text[0];
		while (ch != '\0') {
			if (ch == '\n') {
				++newline_count;
				col = 0;
			} else ++col;
			ch = text[++i];
		}

		if (1 < newline_count) {
			lastYylength = col;
			line.clear();
			location.line += newline_count;
		}
	}

	void Lexer::newline() {
		lines.insert({location.line, line});
		line.clear();
		++location.line;
		location.column = 0;
	}

	void Lexer::badchar(unsigned char ch) {
		failed = true;
		std::cerr << "\e[31mBad character at \e[1m" << location << "\e[22m:\e[39m ";
		if (isgraph(ch)) {
			std::cerr << "'" << ch << "'\n";
		} else {
			char buffer[10];
			sprintf(buffer, "'\\%03o'", ch);
			std::cerr << buffer << "\n";
		}
	}

	int Lexer::token(const char *text, int symbol) {
		*lval = new ASTNode(*parser, symbol, location, text);
		return symbol;
	}
}

void llvmerror(const char *message) {
	llvmerror(std::string(message), LL2W::llvmLexer.location);
}

void llvmerror(const std::string &message, const LL2W::ASTLocation &location) {
	std::cerr << "\e[31mLLVM IR error at \e[1m" << location << "\e[22m: " << message << "\e[0m\n";
	++LL2W::llvmParser.errorCount;
	LL2W::llvmLexer.errors.push_back({message, location});
}

void wasmerror(const char *message) {
	wasmerror(std::string(message), LL2W::wasmLexer.location);
}

void wasmerror(const std::string &message) {
	wasmerror(message, LL2W::wasmLexer.location);
}

void wasmerror(const std::string &message, const LL2W::ASTLocation &location) {
	std::cerr << LL2W::wasmParser.getBuffer() << "\n";
	std::cerr << "\e[31mWASM error at \e[1m" << location << "\e[22m: " << message << "\e[0m\n";
	++LL2W::wasmParser.errorCount;
	LL2W::wasmLexer.errors.push_back({message, location});
}
