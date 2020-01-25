%{
#include "Lexer.h"
#define YY_USER_ACTION { LL2W::Lexer::advance(); }
#define RTOKEN(x) return LL2W::Lexer::token(TOK_##x);

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

%x SGC
%x PREDS
%x LABEL1
%x LABEL2

LETTER				[A-Za-z_]
DIGIT				[0-9]
NUMBER				("-"?{DIGIT}+)
IDENT				([-a-zA-Z$._][-a-zA-Z$._0-9]*)
STRING				(\"([^\\"\n]|\\([\\'"nt]|[0-9a-fA-F][0-9a-fA-F]))*\")
SGCOMMENT			(";"[^\n]*)
MLCOMMENT			("/*"([^*]|"*"[^/])*"*/")
INTTYPE				("i"{DIGIT}+)
GVAR				("@"({NUMBER}|{IDENT}|{STRING}))
PVAR				("%"({NUMBER}|{IDENT}|{STRING}))
CSTRING				("c"{STRING})
INTBANG				("!"{DIGIT}+)
METABANG			("!"{IDENT})
FLOATING			("-"?{DIGIT}+"."{DIGIT}+)
FLOATTYPE			("half"|"float"|"double"|"fp128"|"x86_fp80"|"ppc_fp128")
DLLPORT				("dllimport"|"dllexport")
THREAD_LOCAL_TYPE	("localdynamic"|"initialexec"|"localexec")
PARATTR				("sret"|"nocapture"|"swiftself"|"swifterror"|"immarg"|"returned"|"nest")
RETATTR				("zeroext"|"signext"|"inreg"|"noalias"|"nonnull")
DEREF				("dereferenceable"|"dereferenceable_or_null")
STRUCTVAR			(("%struct."{IDENT})|("%\"struct."([^\\"\n]|\\[\\’"0nt])+\"))
CLASSVAR			(("%class."{IDENT})|("%\"class."([^\\"\n]|\\[\\’"0nt])+\"))
UNIONVAR			(("%union."{IDENT})|("%\"union."([^\\"\n]|\\[\\’"0nt])+\"))
UNNAMED_ADDR_TYPE	("local_unnamed_addr"|"unnamed_addr")
LINKAGE				("private"|"appending"|"available_externally"|"weak"|"linkonce"|"extern_weak"|"linkonce_odr"|"weak_odr"|"external"|"common"|"internal")
VISIBILITY			("default"|"hidden"|"protected")
FNATTR_BASIC		("alwaysinline"|"noredzone"|"convergent"|"norecurse"|"inlinehint"|"inaccessiblemem_or_argmemonly"|"sspreq"|"sanitize_memory"|"jumptable"|"minsize"|"nobuiltin"|"noduplicate"|"noimplicitfloat"|"builtin"|"uwtable"|"nounwind"|"optnone"|"optsize"|"readnone"|"naked"|"argmemonly"|"returns_twice"|"safestack"|"inaccessiblememonly"|"cold"|"noreturn"|"nonlazybind"|"sanitize_thread"|"thunk"|"sspstrong"|"sanitize_address"|"noinline"|"ssp"|"speculatable"|"sanitize_hwaddress")
CCONV				("ccc"|"cxx_fast_tlscc"|"fastcc"|"ghccc"|"swiftcc"|"preserve_allcc"|"preserve_mostcc"|"x86_vectorcallcc"|"cc10"|"cc11"|"arm_apcscc"|"coldcc"|"webkit_jscc"|"cc64"|"cc65"|"cc66"|"ptx_device"|"x86_stdcallcc"|"cc67"|"cc68"|"cc69"|"cc70"|"cc1023"|"anyregcc"|"cc71"|"cc72"|"cc75"|"msp430_intrcc"|"ptx_kernel"|"cc76"|"cc77"|"cc78"|"spir_func"|"x86_64_win64cc"|"cc79"|"cc80"|"arm_aapcs_vfpcc"|"intel_ocl_bicc"|"x86_64_sysvcc"|"x86_fastcallcc"|"x86_thiscallcc"|"arm_aapcscc"|"spir_kernel")
FASTMATH			("nnan"|"ninf"|"nsz"|"arcp"|"contract"|"afn"|"reassoc"|"fast")
BOOL				("true"|"false")
ORDERING			("unordered"|"monotonic"|"acquire"|"release"|"acq_rel"|"seq_cst")
ICMP_COND			("eq"|"ne"|"ugt"|"uge"|"ult"|"ule"|"sgt"|"sge"|"slt"|"sle")
TAIL				("tail"|"musttail"|"notail")
CONV_OP				("trunc"|"zext"|"sext"|"fptrunc"|"fpext"|"fptoui"|"fptosi"|"uitofp"|"sitofp"|"ptrtoint"|"inttoptr"|"bitcast"|"addrspacecast")
DIV					("sdiv"|"udiv")
REM					("srem"|"urem")
LOGIC				("and"|"or"|"xor")
SHR					("lshr"|"ashr")

%%

<SGC>"<label>:"				{ BEGIN(LABEL1); RTOKEN(LABEL_COMMENT) }
<LABEL1>[0-9]+				{ RTOKEN(DECIMAL) }
<LABEL1>":"					{ BEGIN(LABEL2); }
<LABEL1>\n					{ LL2W::Lexer::newline(); BEGIN(INITIAL); }
<LABEL1>[ \t]+				{ }
<LABEL1>.					{ LL2W::Lexer::badchar(*yytext); }
<LABEL2>"; preds ="			{ BEGIN(PREDS); RTOKEN(PREDS_COMMENT) }
<LABEL2>[ \t]+				{ }
<LABEL2>\n					{ LL2W::Lexer::newline(); BEGIN(INITIAL); }
<LABEL2>.					{ LL2W::Lexer::badchar(*yytext); }
<SGC>\n						{ LL2W::Lexer::newline(); BEGIN(INITIAL); }
<SGC>.						{ }
<PREDS>{PVAR}				{ RTOKEN(PVAR); }
<PREDS>[ \t,]+				{ }
<PREDS>\n					{ LL2W::Lexer::newline(); BEGIN(INITIAL); }
<PREDS>.					{ LL2W::Lexer::badchar(*yytext); }

";"							{ BEGIN(SGC); }
{MLCOMMENT}					{ }
[ \t]+						{ }
\n							{ LL2W::Lexer::newline(); }

{UNIONVAR}					{ RTOKEN(UNIONVAR) }
{CLASSVAR}					{ RTOKEN(CLASSVAR) }
{STRUCTVAR}					{ RTOKEN(STRUCTVAR) }
{PVAR}						{ RTOKEN(PVAR) }
{GVAR}						{ RTOKEN(GVAR) }
{INTTYPE}					{ RTOKEN(INTTYPE)  }
{FLOATTYPE}					{ RTOKEN(FLOATTYPE)  }
{DLLPORT}					{ RTOKEN(DLLPORT) }
{THREAD_LOCAL_TYPE}			{ RTOKEN(THREAD_LOCAL_TYPE) }
{PARATTR}					{ RTOKEN(PARATTR) }
{RETATTR}					{ RTOKEN(RETATTR) }
{DEREF}						{ RTOKEN(DEREF) }
{UNNAMED_ADDR_TYPE}			{ RTOKEN(UNNAMED_ADDR_TYPE) }
{LINKAGE}					{ RTOKEN(LINKAGE) }
{VISIBILITY}				{ RTOKEN(VISIBILITY) }
{FNATTR_BASIC}				{ RTOKEN(FNATTR_BASIC) }
{CCONV}						{ RTOKEN(CCONV) }
{FASTMATH}					{ RTOKEN(FASTMATH) }
{BOOL}						{ RTOKEN(BOOL) }
{ORDERING}					{ RTOKEN(ORDERING) }
{ICMP_COND}					{ RTOKEN(ICMP_COND) }
{TAIL}						{ RTOKEN(TAIL) }
{CONV_OP}					{ RTOKEN(CONV_OP) }
{DIV}						{ RTOKEN(DIV) }
{REM}						{ RTOKEN(REM) }
{LOGIC}						{ RTOKEN(LOGIC) }
{SHR}						{ RTOKEN(SHR) }

"!invariant.group"			{ RTOKEN(INVARIANT_GROUP) }
"!invariant.load"			{ RTOKEN(INVARIANT_LOAD) }
"!nontemporal"				{ RTOKEN(NONTEMPORAL) }
"!nonnull"					{ RTOKEN(NONNULL) }
"!dereferenceable"			{ RTOKEN(DEREFERENCEABLE) }
"!align"					{ RTOKEN(BANGALIGN) }
{INTBANG}					{ RTOKEN(INTBANG) }
{METABANG}					{ RTOKEN(METABANG) }
"define"					{ RTOKEN(DEFINE) }
"declare"					{ RTOKEN(DECLARE) }
"readonly"					{ RTOKEN(READONLY) }
"!"							{ RTOKEN(BANG)  }
"datalayout"				{ RTOKEN(DATALAYOUT) }
"="							{ RTOKEN(EQUALS) }
"source_filename"			{ RTOKEN(SOURCE_FILENAME) }
"patchable-function=\"prologue-short-redirect\"" { RTOKEN(PATCHABLE_PROLOGUE) }
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
"<"							{ RTOKEN(LANGLE) }
">"							{ RTOKEN(RANGLE) }
"void"						{ RTOKEN(VOID) }
"..."						{ RTOKEN(ELLIPSIS) }
"*"							{ RTOKEN(ASTERISK) }
"#"							{ RTOKEN(HASH) }
":"							{ RTOKEN(COLON) }

"select"					{ RTOKEN(SELECT) }
"alloca"					{ RTOKEN(ALLOCA) }
"inalloca"					{ RTOKEN(INALLOCA) }
"store"						{ RTOKEN(STORE) }
"load"						{ RTOKEN(LOAD) }
"volatile"					{ RTOKEN(VOLATILE) }

"thread_local"				{ RTOKEN(THREAD_LOCAL) }

"addrspace"					{ RTOKEN(ADDRSPACE) }
"zeroinitializer"			{ RTOKEN(ZEROINITIALIZER) }
"externally_initialized"	{ RTOKEN(EXTERNALLY_INITIALIZED) }
"global"					{ RTOKEN(GLOBAL) }
"constant"					{ RTOKEN(CONSTANT) }
"section"					{ RTOKEN(SECTION) }
"comdat"					{ RTOKEN(COMDAT) }
"align"						{ RTOKEN(ALIGN) }

"type"						{ RTOKEN(TYPE) }
"opaque"					{ RTOKEN(OPAQUE) }
"attributes"				{ RTOKEN(ATTRIBUTES) }
"alignstack"				{ RTOKEN(ALIGNSTACK) }
"allocsize"					{ RTOKEN(ALLOCSIZE) }
"syncscope"					{ RTOKEN(SYNCSCOPE) }
"atomic"					{ RTOKEN(ATOMIC) }
"icmp"						{ RTOKEN(ICMP) }
"br"						{ RTOKEN(BR) }
"label"						{ RTOKEN(LABEL) }
"call"						{ RTOKEN(CALL) }
"getelementptr"				{ RTOKEN(GETELEMENTPTR) }
"inbounds"					{ RTOKEN(INBOUNDS) }
"inrange"					{ RTOKEN(INRANGE) }
"ret"						{ RTOKEN(RET) }
"personality"				{ RTOKEN(PERSONALITY) }
"to"						{ RTOKEN(TO) }
"invoke"					{ RTOKEN(INVOKE) }
"unwind"					{ RTOKEN(UNWIND) }
"cleanup"					{ RTOKEN(CLEANUP) }
"catch"						{ RTOKEN(CATCH) }
"landingpad"				{ RTOKEN(LANDINGPAD) }
"filter"					{ RTOKEN(FILTER) }
"byval"						{ RTOKEN(BYVAL) }
"writeonly"					{ RTOKEN(WRITEONLY) }
"nuw"						{ RTOKEN(NUW) }
"nsw"						{ RTOKEN(NSW) }
"add"						{ RTOKEN(ADD) }
"sub"						{ RTOKEN(SUB) }
"mul"						{ RTOKEN(MUL) }
"shl"						{ RTOKEN(SHL) }
"phi"						{ RTOKEN(PHI) }
"switch"					{ RTOKEN(SWITCH) }
"unreachable"				{ RTOKEN(UNREACHABLE) }

{IDENT}						{ RTOKEN(IDENT) }

.							{ LL2W::Lexer::badchar(*yytext); }

%%

#undef RTOKEN