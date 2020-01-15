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

LETTER				[A-Za-z_]
DIGIT				[0-9]
NUMBER				("-"?{DIGIT}+)
IDENT				({LETTER}({LETTER}|{DIGIT}|_)*)
CHARCON				('([^\\'\n]|\\[\\'"0nt])')
STRING				(\"([^\\"\n]|\\[\\’"0nt])*\")
SGCOMMENT			(";"[^\n]*)
MLCOMMENT			("/*"([^*]|"*"[^/])*"*/")
INTTYPE				("i"{DIGIT}+)
GVAR				("@"{DOTIDENT})
PVAR				("%"{DOTIDENT})
DOTIDENT			(({DIGIT}+)|(({LETTER}|".")+({LETTER}|"."|{DIGIT})*))
CSTRING				("c"{STRING})
FLOATING			("-"?{DIGIT}+"."{DIGIT}+)
FLOATTYPE			("half"|"double"|"fp128"|"x86_fp80"|"ppc_fp128")
DLLPORT				("dllimport"|"dllexport")
THREAD_LOCAL_TYPE	("localdynamic"|"initialexec"|"localexec")
PARATTR				("byval"|"inalloca"|"sret"|"nocapture"|"readonly")
RETATTR				("zeroext"|"signext"|"inreg"|"noalias"|"nonnull")
DEREF				("dereferenceable"|"deferenceable_or_null")

%%

{SGCOMMENT}					{ }
{MLCOMMENT}					{ }
[ \t]+						{ }
\n							{ LL2W::Lexer::newline(); }

{PVAR}						{ RTOKEN(PVAR) }
{GVAR}						{ RTOKEN(GVAR) }
{INTTYPE}					{ RTOKEN(INTTYPE)  }
{FLOATTYPE}					{ RTOKEN(FLOATTYPE)  }
{DLLPORT}					{ RTOKEN(DLLPORT) }
{THREAD_LOCAL_TYPE}			{ RTOKEN(THREAD_LOCAL_TYPE) }
{PARATTR}					{ RTOKEN(PARATTR) }
{RETATTR}					{ RTOKEN(RETATTR) }
{DEREF}						{ RTOKEN(DEREF) }

"!"							{ RTOKEN(BANG)  }
"datalayout"				{ RTOKEN(DATALAYOUT) }
"="							{ RTOKEN(EQUALS) }
"source_filename"			{ RTOKEN(SOURCE_FILENAME) }
{CSTRING}					{ RTOKEN(CSTRING) }
{STRING}					{ RTOKEN(STRING) }
"target"					{ RTOKEN(TARGET) }
"triple"					{ RTOKEN(TRIPLE) }
{FLOATING}					{ RTOKEN(FLOATING) }
{NUMBER}					{ RTOKEN(DECIMAL) }
"distinct"					{ RTOKEN(DISTINCT) }
"."							{ RTOKEN(DOT) }
"!{"						{ RTOKEN(METADATA_OPEN) }
"{"							{ RTOKEN(LCURLY) }
"}"							{ RTOKEN(RCURLY) }
","							{ RTOKEN(COMMA) }
"%"							{ RTOKEN(PERCENT) }
"@"							{ RTOKEN(AT) }
"("							{ RTOKEN(LPAR) }
")"							{ RTOKEN(RPAR) }
"["							{ RTOKEN(LSQUARE) }
"]"							{ RTOKEN(RSQUARE) }
"x"							{ RTOKEN(X) }
"null"						{ RTOKEN(NULL) }
"float"						{ RTOKEN(FLOAT) }
"<"							{ RTOKEN(LANGLE) }
">"							{ RTOKEN(RANGLE) }

"trunc"						{ RTOKEN(TRUNC) }
"zext"						{ RTOKEN(ZEXT) }
"sext"						{ RTOKEN(SEXT) }
"fptrunc"					{ RTOKEN(FPTRUNC) }
"fpext"						{ RTOKEN(FPEXT) }
"fptoui"					{ RTOKEN(FPTOUI) }
"fptosi"					{ RTOKEN(FPTOSI) }
"uitofp"					{ RTOKEN(UITOFP) }
"sitofp"					{ RTOKEN(SITOFP) }
"ptrtoint"					{ RTOKEN(PTRTOINT) }
"inttoptr"					{ RTOKEN(INTTOPTR) }
"bitcast"					{ RTOKEN(BITCAST) }
"addrspacecast"				{ RTOKEN(ADDRSPACECAST) }

"private"					{ RTOKEN(PRIVATE) }
"appending"					{ RTOKEN(APPENDING) }
"available_externally"		{ RTOKEN(AVAILABLE_EXTERNALLY) }
"weak"						{ RTOKEN(WEAK) }
"linkonce"					{ RTOKEN(LINKONCE) }
"extern_weak"				{ RTOKEN(EXTERN_WEAK) }
"linkonce_odr"				{ RTOKEN(LINKONCE_ODR) }
"weak_odr"					{ RTOKEN(WEAK_ODR) }
"external"					{ RTOKEN(EXTERNAL) }
"common"					{ RTOKEN(COMMON) }
"internal"					{ RTOKEN(INTERNAL) }

"default"					{ RTOKEN(DEFAULT) }
"hidden"					{ RTOKEN(HIDDEN) }
"protected"					{ RTOKEN(PROTECTED) }

"thread_local"				{ RTOKEN(THREAD_LOCAL) }

"local_unnamed_addr"		{ RTOKEN(LOCAL_UNNAMED_ADDR) }
"unnamed_addr"				{ RTOKEN(UNNAMED_ADDR) }
"addrspace"					{ RTOKEN(ADDRSPACE) }
"zeroinitializer"			{ RTOKEN(ZEROINITIALIZER) }
"externally_initialized"	{ RTOKEN(EXTERNALLY_INITIALIZED) }
"global"					{ RTOKEN(GLOBAL) }
"constant"					{ RTOKEN(CONSTANT) }
"section"					{ RTOKEN(SECTION) }
"comdat"					{ RTOKEN(COMDAT) }
"align"						{ RTOKEN(ALIGN) }

{DOTIDENT}					{ RTOKEN(DOTIDENT) }

.						{ LL2W::Lexer::badchar(*yytext); }
%%

#undef RTOKEN