%{
#include "parser/Lexer.h"
#ifdef YY_USER_ACTION
#error "YY_USER_ACTION is already defined"
#endif
#define YY_USER_ACTION { LL2W::wasmLexer.advance(wasmtext); }
#define WASMRTOKEN(x) return LL2W::wasmLexer.token(wasmtext, WASMTOK_##x);

// Disable PVS-Studio warnings about branches that do the same thing.
//-V::1037

// PARATTR and FNATTR_BASIC both include "readonly", which has to be treated specially.

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
WASM_NUMBER				({WASM_DECIMAL}|{WASM_HEXADECIMAL})
WASM_IDENT				([-a-zA-Z$._][-a-zA-Z$._0-9]*)
WASM_STRING				(\"([^\\"\n]|\\([\\'"nt]|[0-9a-fA-F][0-9a-fA-F]))*\")
WASM_SGCOMMENT			("//"[^\n]*)
WASM_MLCOMMENT			("/*"([^*]|"*"[^/])*"*/")

%%

"//"						{ }
{WASM_MLCOMMENT}			{ }
[ \t]+						{ }
\n							{ LL2W::wasmLexer.newline(); }


{WASM_IDENT}				{ WASMRTOKEN(IDENT) }

.							{ LL2W::wasmLexer.badchar(*yytext); }

%%

#undef WASMRTOKEN