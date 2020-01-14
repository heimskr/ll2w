%{
#include "Lexer.h"
#define YY_USER_ACTION { LL2W::Lexer::advance(); }
#define RTOKEN(x) return LL2W::Lexer::token(TOK_##x);
%}

%option 8bit
%option debug
%option nobackup
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option warn

LETTER          [A-Za-z_]
DIGIT           [0-9]
NUMBER          ({DIGIT}+)
IDENT           ({LETTER}({LETTER}|{DIGIT}|_)*)
CHARCON         ('([^\\'\n]|\\[\\'"0nt])')
PERCENTID       (%({LETTER}|{DIGIT})+)
STRING          (\"([^\\"\n]|\\[\\’"0nt])*\")
SGCOMMENT       (";"[^\n]*)
MLCOMMENT       ("/*"([^*]|"*"[^/])*"*/")
INTTYPE         ("i"{DIGIT}+)

%%

{SGCOMMENT}     { }
{MLCOMMENT}     { }
[ \t]+          { }
\n              { LL2W::Lexer::newline(); }

{PERCENTID}     { RTOKEN(PERCENTID) }
{INTTYPE}       { RTOKEN(INTTYPE);  }

"!"						{ RTOKEN(BANG);  }
"datalayout"			{ RTOKEN(DATALAYOUT) }
"="						{ RTOKEN(EQUALS) }
"source_filename"		{ RTOKEN(SOURCE_FILENAME) }
{STRING}				{ RTOKEN(STRING) }
"target"				{ RTOKEN(TARGET) }
"triple"				{ RTOKEN(TRIPLE) }
{NUMBER}				{ RTOKEN(INT_LITERAL) }
"distinct"				{ RTOKEN(DISTINCT) }
"."						{ RTOKEN(DOT) }
"!{"					{ RTOKEN(METADATA_OPEN) }
"}"						{ RTOKEN(CURLYC) }
","						{ RTOKEN(COMMA) }
"null"					{ RTOKEN(NULL) }
"byval"					{ RTOKEN(PARATTR) }
"inalloca"				{ RTOKEN(PARATTR) }
"sret"					{ RTOKEN(PARATTR) }
"nocapture"				{ RTOKEN(PARATTR) }
"readonly"				{ RTOKEN(PARATTR) }

{IDENT}					{ RTOKEN(IDENT) }

.				{ LL2W::Lexer::badchar(*yytext); }
%%

#undef RTOKEN