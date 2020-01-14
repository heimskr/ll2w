%{
#include <cassert>

#include "Lexer.h"
#include "ASTNode.h"
#include "Parser.h"

using namespace LL2W;
using AN = LL2W::ASTNode;
%}

%debug
%defines
%error-verbose
%token-table
%verbose

%initial-action {
    LL2W::Parser::root = new LL2W::ASTNode(TOK_ROOT, {0, 0, 0}, "");
}

%token TOK_ROOT TOK_STRING TOK_PERCENTID TOK_INTTYPE TOK_INT_LITERAL TOK_IDENT TOK_DOTIDENT TOK_METADATA_LIST TOK_PARATTR
%token TOK_SOURCE_FILENAME "source_filename"
%token TOK_BANG "!"
%token TOK_EQUALS "="
%token TOK_DOT "."
%token TOK_TARGET "target"
%token TOK_DATALAYOUT "datalayout"
%token TOK_TRIPLE "triple"
%token TOK_DISTINCT "distinct"
%token TOK_METADATA_OPEN "!{"
%token TOK_CURLYC "}"
%token TOK_COMMA ","
%token TOK_NULL "null"

%start start

%%

start: program { $$ = $1 = nullptr; };

program: program source_filename { $1->adopt($2); }
       | program target          { $1->adopt($2); }
       | program metadata_def    { $1->adopt($2); }
       | { $$ = Parser::root; }
       ;

source_filename: "source_filename" "=" TOK_STRING { AN::destroy({$1, $2}); $$ = new AN(TOK_SOURCE_FILENAME, $3->lexerInfo); }

target: TOK_TARGET target_type "=" TOK_STRING { $$ = $1->adopt({$2, $4}); }
target_type: "datalayout" | "triple";

metadata_def: "!" dotident "=" metadata_distinct TOK_METADATA_OPEN metadata_list TOK_CURLYC { AN::destroy({$1, $3, $5, $7}); $$ = new MetadataDef($2, $4, $6); };

metadata_list: metadata_list "," metadata_listitem { $1->adopt($3); delete $2; }
             | metadata_listitem { $$ = (new AN(TOK_METADATA_LIST, ""))->adopt($1); }
             | { $$ = nullptr; }
             ;

metadata_listitem: "!" TOK_STRING      { delete $1; $$ = $2; }
                 | "!" TOK_INT_LITERAL { delete $1; $$ = $2; }
                 | "null";

// constant -> type_any (__ parattr):* " " (operand | const_expr) {% d => [d[0], d[3][0], d[1].map(x => x[1])] %}

metadata_distinct: "distinct" { $$ = new AN(TOK_DISTINCT, "distinct"); }
                 |            { $$ = nullptr; }
                 ;

// decvar: TOK_INT_LITERAL | TOK_IDENT;

dotident: dotident "."             { $1->adopt($2); }
        | dotident TOK_IDENT       { $1->adopt($2); }
        | dotident TOK_INT_LITERAL { $1->adopt($2); }
        | { $$ = new AN(TOK_DOTIDENT, ""); }
        ;

// type_any: TOK_INTTYPE;

%%

const char * LL2W::Parser::getName(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}