#include <iostream>

#include "parser/Lexer.h"

namespace LL2W {
	yysize Lexer::last_yylength = 0;
	std::string Lexer::line;
	Location Lexer::location = {0, 1};
	std::unordered_map<int, std::string> Lexer::lines;
	bool Lexer::failed = false;
	std::vector<std::pair<std::string, Location>> Lexer::errors;

	void Lexer::advance() {
		Lexer::line += yytext;
		Lexer::location.column += last_yylength;
		Lexer::last_yylength = yyleng;

		size_t newline_count = 0, i = 0, col = Lexer::location.column;
		char ch = yytext[0];
		while (ch != '\0') {
			if (ch == '\n') {
				++newline_count;
				col = 0;
			} else ++col;
			ch = yytext[++i];
		}

		if (1 < newline_count) {
			Lexer::last_yylength = col;
			Lexer::line.clear();
			Lexer::location.line += newline_count;
		}
	}

	void Lexer::newline() {
		Lexer::lines.insert({Lexer::location.line, Lexer::line});
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
	yyerror(std::string(message));
}

void yyerror(const std::string &message, const LL2W::Location &location) {
	std::cerr << "\e[31mError at \e[1m" << location << "\e[22m: " << message << "\e[0m\n";
	LL2W::Lexer::errors.push_back({message, location});
}