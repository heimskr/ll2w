%{
#include "parser/Lexer.h"
#ifdef YY_USER_ACTION
#error "YY_USER_ACTION is already defined"
#endif
#define YY_USER_ACTION { LL2W::wasmLexer.advance(wasmtext); }
#define WASMRTOKEN(x) return LL2W::wasmLexer.token(wasmtext, WASMTOK_##x);

// Disable PVS-Studio warnings about branches that do the same thing.
//-V::1037

%}

%option 8bit
%option debug
%option nobackup
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option warn

WASM_LETTER				[A-Za-z_]
WASM_DIGIT				[0-9]
WASM_DECIMAL			("-"?{WASM_DIGIT}+)
WASM_HEXADECIMAL		("-"?0x[a-fA-F0-9]+)
WASM_CHAR				('([^'\\\n]|("\\""\\"?[nratb])|\$[()])')
WASM_NUMBER				({WASM_DECIMAL}|{WASM_HEXADECIMAL})
WASM_IDENT				([-a-zA-Z._][-a-zA-Z._0-9]*)
WASM_STRING				(\"([^\\"\n]|\\([\\'"nt]|[0-9a-fA-F][0-9a-fA-F]))*\")
WASM_SGCOMMENT			("//"[^\n]*)
WASM_MLCOMMENT			("/*"([^*]|"*"[^/])*"*/")
/* The LLVM IR generated for "$t0 -> %1" looks like "$$t0 -> $1" */
WASM_DOUBLE_REG			("$$"([0g]|[fs]"p"|"r"("t"|[0-9a-f])|"lo"|"hi"|[akm][0-9a-f]|[st]([0-9a-f]|"1"[0-6])|"st"|"f"[0-3]|"e"[0-5]))
WASM_SINGLE_REG			("$"[0-9]+)

%%

{WASM_SGCOMMENT}			{ }
{WASM_MLCOMMENT}			{ }
[ \t]+						{ }
\n							{ LL2W::wasmLexer.newline(); WASMRTOKEN(NEWLINE) }
"\\09"						{ }

{WASM_DOUBLE_REG}			{ WASMRTOKEN(REG) }
{WASM_SINGLE_REG}			{ WASMRTOKEN(REG) }
{WASM_CHAR}					{ WASMRTOKEN(CHAR) }
{WASM_STRING}				{ WASMRTOKEN(STRING) }

"translate"					{ WASMRTOKEN(TRANSLATE) }
"memset"					{ WASMRTOKEN(MEMSET) }
"sleep"						{ WASMRTOKEN(SLEEP) }
"%%setpt"					{ WASMRTOKEN(SETPT) }
"%setpt"					{ WASMRTOKEN(SETPT) }
"%%di"						{ WASMRTOKEN(DI) }
"%di"						{ WASMRTOKEN(DI) }
"%%ei"						{ WASMRTOKEN(EI) }
"%ei"						{ WASMRTOKEN(EI) }
"rest"						{ WASMRTOKEN(REST) }
"print"						{ WASMRTOKEN(PRINT) }
"*init"						{ WASMRTOKEN(INIT) }
"%%time"					{ WASMRTOKEN(TIME) }
"%%ring"					{ WASMRTOKEN(RING) }
"%%page"					{ WASMRTOKEN(PAGE) }
"sext32"					{ WASMRTOKEN(SEXT32) }
"sext16"					{ WASMRTOKEN(SEXT16) }
"%time"						{ WASMRTOKEN(TIME) }
"%ring"						{ WASMRTOKEN(RING) }
"%page"						{ WASMRTOKEN(PAGE) }
"sext8"						{ WASMRTOKEN(SEXT8) }
"%%int"						{ WASMRTOKEN(INT) }
"%%rit"						{ WASMRTOKEN(RIT) }
"%int"						{ WASMRTOKEN(INT) }
"%rit"						{ WASMRTOKEN(RIT) }
"halt"						{ WASMRTOKEN(HALT) }
"lui"						{ WASMRTOKEN(LUI) }
"prc"						{ WASMRTOKEN(PRC) }
"prx"						{ WASMRTOKEN(PRX) }
"prd"						{ WASMRTOKEN(PRD) }
"prb"						{ WASMRTOKEN(PRB) }
"off"						{ WASMRTOKEN(OFF) }
"mem"						{ WASMRTOKEN(MEM) }
">>>"						{ WASMRTOKEN(RL) }
"!&&"						{ WASMRTOKEN(LNAND) }
"!||"						{ WASMRTOKEN(LNOR) }
"!xx"						{ WASMRTOKEN(LXNOR) }
"if"						{ WASMRTOKEN(IF) }
"on"						{ WASMRTOKEN(ON) }
"->"						{ WASMRTOKEN(INTO) }
"&&"						{ WASMRTOKEN(LAND) }
"||"						{ WASMRTOKEN(LOR) }
"xx"						{ WASMRTOKEN(LXOR) }
"~&"						{ WASMRTOKEN(NAND) }
"~|"						{ WASMRTOKEN(NOR) }
"~x"						{ WASMRTOKEN(XNOR) }
"<="						{ WASMRTOKEN(LEQ) }
"=="						{ WASMRTOKEN(DEQ) }
">="						{ WASMRTOKEN(GEQ) }
"!="						{ WASMRTOKEN(NOTEQUAL) }
"<>"						{ WASMRTOKEN(NOP) }
"<<"						{ WASMRTOKEN(LL) }
">>"						{ WASMRTOKEN(RA) }
"io"						{ WASMRTOKEN(IO) }
"/b"						{ WASMRTOKEN(BYTE) }
"/h"						{ WASMRTOKEN(HALF) }
"/s"						{ WASMRTOKEN(SHORT) }

";"							{ WASMRTOKEN(SEMICOLON) }
"/"							{ WASMRTOKEN(SLASH) }
"~"							{ WASMRTOKEN(NOT) }
"&"							{ WASMRTOKEN(AND) }
"|"							{ WASMRTOKEN(OR) }
"!"							{ WASMRTOKEN(BANG) }
"="							{ WASMRTOKEN(EQUALS) }
"."							{ WASMRTOKEN(DOT) }
"{"							{ WASMRTOKEN(LCURLY) }
"}"							{ WASMRTOKEN(RCURLY) }
","							{ WASMRTOKEN(COMMA) }
"%"							{ WASMRTOKEN(PERCENT) }
"@"							{ WASMRTOKEN(AT) }
"("							{ WASMRTOKEN(LPAR) }
")"							{ WASMRTOKEN(RPAR) }
"["							{ WASMRTOKEN(LSQUARE) }
"]"							{ WASMRTOKEN(RSQUARE) }
"x"							{ WASMRTOKEN(X) }
"<"							{ WASMRTOKEN(LANGLE) }
">"							{ WASMRTOKEN(RANGLE) }
"*"							{ WASMRTOKEN(ASTERISK) }
"#"							{ WASMRTOKEN(HASH) }
":"							{ WASMRTOKEN(COLON) }
"+"							{ WASMRTOKEN(PLUS) }
"-"							{ WASMRTOKEN(MINUS) }
"?"							{ WASMRTOKEN(QUESTION) }
"p"							{ WASMRTOKEN(P) }

{WASM_NUMBER}				{ WASMRTOKEN(NUMBER) }
{WASM_IDENT}				{ WASMRTOKEN(IDENT) }
.							{ LL2W::wasmLexer.badchar(*yytext); }

%%

#undef WASMRTOKEN