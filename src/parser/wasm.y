%{
#include <cassert>
#include <cstdarg>
#include <initializer_list>

#define NO_YYPARSE
#include "parser/Lexer.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "wasm/Nodes.h"

// Disable PVS-Studio warnings about branches that do the same thing.
//-V::1037

template <typename ...Args>
void D(Args && ...args) {
	(void) std::initializer_list<int> {
		((void) delete args, 0)...
	};
}

template <typename T>
const LL2W::Location & L(std::initializer_list<const T *> nodes) {
	for (const T *node: nodes) {
		if (node)
			return node->location;
	}
	throw std::runtime_error("Couldn't find location: all nodes are null");
}

using namespace LL2W;
using AN = LL2W::ASTNode;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
%}

%debug
%defines
%define parse.error verbose
%token-table
%verbose

%define api.prefix {wasm}

%initial-action {
    LL2W::wasmParser.root = new LL2W::ASTNode(LL2W::wasmParser, WASMTOK_ROOT, {0, 0}, "");
}

%token WASMTOK_ROOT WASMTOK_IDENT

%token WASMTOK_BANG "!"
%token WASMTOK_EQUALS "="
%token WASMTOK_DOT "."
%token WASMTOK_LCURLY "{"
%token WASMTOK_RCURLY "}"
%token WASMTOK_COMMA ","
%token WASMTOK_NULL "null"
%token WASMTOK_PERCENT "%"
%token WASMTOK_AT "@"
%token WASMTOK_LPAR "("
%token WASMTOK_RPAR ")"
%token WASMTOK_LSQUARE "["
%token WASMTOK_RSQUARE "]"
%token WASMTOK_X "x"
%token WASMTOK_LANGLE "<"
%token WASMTOK_RANGLE ">"
%token WASMTOK_MEMSET "memset"
%token WASMTOK_LUI "lui"
%token WASMTOK_ASTERISK "*"
%token WASMTOK_HASH "#"
%token WASMTOK_COLON ":"
%token WASMTOK_PLUS "+"
%token WASMTOK_MINUS "-"
%token WASMTOK_INTO "->"
%token WASMTOK_DOLLAR "$"
%token WASMTOK_NEWLINE
%token WASMTOK_REG

%token WASM_RNODE


%start start

%%

start: program;

program: program operation { $1->adopt($2); }
       | { $$ = LL2W::wasmParser.root; };

operation: op_add { $$ = $1; };

op_add: reg "+" reg "->" reg { $$ = new RNode($1, $2, $3, $5); D($4); };

reg: WASMTOK_REG;

%%

#pragma GCC diagnostic pop

const char * LL2W::Parser::getNameWASM(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
