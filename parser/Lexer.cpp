#include <iostream>

#include "Lexer.h"

namespace LL2W {
	yysize Lexer::last_yylength = 0;
	std::string Lexer::line;
	Location Lexer::location = {0, 0, 1};
	std::unordered_map<int, std::unordered_map<int, std::string>> Lexer::lines;
	bool Lexer::failed = false;

	void Lexer::advance() {
		Lexer::line += yytext;
		Lexer::location.column += last_yylength;
		Lexer::last_yylength = yyleng;
	}

	void Lexer::newline() {
		Lexer::lines[Lexer::location.fileno].insert({Lexer::location.line, Lexer::line});
		Lexer::line.clear();
		++Lexer::location.line;
		Lexer::location.column = 0;
	}

	void Lexer::badchar(unsigned char ch) {
		Lexer::failed = true;
		std::cerr << "Bad character at " << Lexer::location << ": ";
		if (isgraph(ch)) {
			std::cerr << "'" << ch << "'\n";
		} else {
			char buffer[10];
			sprintf(buffer, "'\\%03o'", ch);
			std::cerr << buffer << "\n";
		}
	}

	int Lexer::token(int symbol) {
		yylval = new ASTNode(symbol, Lexer::location, yytext);
		return symbol;
	}
}

void yyerror(const char *message) {
	std::cerr << "[Error at " << LL2W::Lexer::location << ": " << message << "]\n";
}