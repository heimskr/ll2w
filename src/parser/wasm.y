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
%token WASMTOK_AND "&"
%token WASMTOK_NAND "~&"
%token WASMTOK_LAND "&&"
%token WASMTOK_LNAND "!&&"
%token WASMTOK_OR "|"
%token WASMTOK_NOR "~|"
%token WASMTOK_LOR "||"
%token WASMTOK_LNOR "!||"
%token WASMTOK_XNOR "~x"
%token WASMTOK_NOT "~"
%token WASMTOK_SLASH "/"
%token WASMTOK_LXNOR "!xx"
%token WASMTOK_LXOR "xx"
%token WASMTOK_SEMICOLON ";"
%token WASMTOK_UNSIGNED "/u"
%token WASMTOK_LEQ "<="
%token WASMTOK_DEQ "=="
%token WASMTOK_GEQ ">="
%token WASMTOK_BYTE "/b"
%token WASMTOK_NEWLINE "\n"
%token WASMTOK_REG
%token WASMTOK_NUMBER

%token WASM_RNODE WASM_STATEMENTS WASM_INODE WASM_COPYNODE WASM_LOADNODE WASM_STORENODE WASM_SETNODE WASM_LINODE

%start start

%%

start: program;

program: program statement { $$ = $1->adopt($2); }
       | program endop { $$ = $1; D($2); }
       | { $$ = LL2W::wasmParser.root; };

statement: operation;
endop: "\n" | ";";

operation: op_r | op_mult | op_multi | op_lui | op_i | op_c | op_l | op_s | op_set | op_divii | op_li;

op_r: reg basic_oper reg "->" reg _unsigned { $$ = new RNode($1, $2, $3, $5, $6); D($4); }
    | "~" reg "->" reg { $$ = new RNode($2, $1, $1, $4, nullptr); D($3); }; // rt will be "~" to indicate this is a unary op
basic_oper: "+" | "-"  | "&" | "|" | "&&" | "||" | "x" | "~x" | "!&&" | "!||" | "~&" | "~|" | "/" | "!xx" | "xx" | "%"
          | "<" | "<=" | "==" | ">" | ">=";
_unsigned: "/u" | { $$ = nullptr; };

op_mult: reg "*" reg _unsigned { $$ = $2->adopt({$1, $3, $4}); };

op_multi: reg "*" number _unsigned { $$ = $2->adopt({$1, $3, $4}); };

op_lui: "lui" ":" number "->" reg { $$ = $1->adopt({$3, $5}); D($2, $4); };

op_i: reg basic_oper number "->" reg _unsigned { $$ = new INode($1, $2, $3, $5, $6); D($4); };

op_c: "[" reg "]" "->" "[" reg "]" _byte { $$ = new WASMCopyNode($2, $6, $8); D($1, $3, $4, $5, $7); };
_byte: "/b" | { $$ = nullptr; };

op_l: "[" reg "]" "->" reg _byte { $$ = new WASMLoadNode($2, $5, $6); D($1, $3, $4); };

op_s: reg "->" "[" reg "]" _byte { $$ = new WASMStoreNode($1, $4, $6); D($2, $3, $5); };

op_set: number "->" reg { $$ = new WASMSetNode($1, $3); D($2); };

op_divii: number "/" reg "->" reg _unsigned { $$ = $2->adopt({$1, $3, $5, $6}); D($4); };

op_li: "[" number "]" "->" reg _byte { $$ = new WASMLiNode($2, $5, $6); D($1, $3, $4); };

reg: WASMTOK_REG;
number: WASMTOK_NUMBER;

%%

#pragma GCC diagnostic pop

const char * LL2W::Parser::getNameWASM(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
