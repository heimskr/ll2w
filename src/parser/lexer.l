%{
#include "parser/Lexer.h"
#ifdef YY_USER_ACTION
#error "YY_USER_ACTION is already defined"
#endif
#define YY_USER_ACTION { LL2W::llvmLexer.advance(llvmtext); }
#define LLVMRTOKEN(x) return LL2W::llvmLexer.token(llvmtext, LLVMTOK_##x);

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

%x SGC
%x PREDS
%x LABEL1
%x LABEL2

LLVM_LETTER				[A-Za-z_]
LLVM_DIGIT				[0-9]
LLVM_DECIMAL			("-"?{LLVM_DIGIT}+)
LLVM_HEXADECIMAL		("-"?0x[a-fA-F0-9]+)
LLVM_NUMBER				({LLVM_DECIMAL}|{LLVM_HEXADECIMAL})
LLVM_IDENT				([-a-zA-Z$._][-a-zA-Z$._0-9]*)
LLVM_STRING				(\"([^\\"\n]|\\([\\'"nt]|[0-9a-fA-F][0-9a-fA-F]))*\")
LLVM_SGCOMMENT			(";"[^\n]*)
LLVM_MLCOMMENT			("/*"([^*]|"*"[^/])*"*/")
LLVM_INTTYPE			("i"{LLVM_DIGIT}+)
LLVM_GVAR				("@"({LLVM_DECIMAL}|{LLVM_IDENT}|{LLVM_STRING}))
LLVM_PVAR				("%"({LLVM_DECIMAL}|{LLVM_IDENT}|{LLVM_STRING}))
LLVM_CSTRING			("c"{LLVM_STRING})
LLVM_INTBANG			("!"{LLVM_DIGIT}+)
LLVM_METABANG			("!"{LLVM_IDENT})
LLVM_FLOATING			("-"?[0-9]+"."[0-9]+("e"[+\-][0-9]+)?)
LLVM_FLOATTYPE			("half"|"float"|"double"|"fp128"|"x86_fp80"|"ppc_fp128")
LLVM_DLLPORT			("dllimport"|"dllexport")
LLVM_THREAD_LOCAL_TYPE	("localdynamic"|"initialexec"|"localexec")
LLVM_PARATTR			("sret"|"nocapture"|"swiftself"|"swifterror"|"immarg"|"returned"|"nest"|"nofree")
LLVM_RETATTR			("zeroext"|"signext"|"inreg"|"noalias"|"nonnull")
LLVM_DEREF				("dereferenceable"|"dereferenceable_or_null")
LLVM_STRUCTVAR			(("%struct."{LLVM_IDENT})|("%\"struct."([^\\"\n]|\\[\\’"0nt])+\"))
LLVM_CLASSVAR			(("%class."{LLVM_IDENT})|("%\"class."([^\\"\n]|\\[\\’"0nt])+\"))
LLVM_UNIONVAR			(("%union."{LLVM_IDENT})|("%\"union."([^\\"\n]|\\[\\’"0nt])+\"))
LLVM_UNNAMED_ADDR_TYPE	("local_unnamed_addr"|"unnamed_addr")
LLVM_LINKAGE			("private"|"appending"|"available_externally"|"weak"|"linkonce"|"extern_weak"|"linkonce_odr"|"weak_odr"|"external"|"common"|"internal")
LLVM_VISIBILITY			("default"|"hidden"|"protected")
LLVM_FNATTR_BASIC		("alwaysinline"|"noredzone"|"convergent"|"norecurse"|"inlinehint"|"inaccessiblemem_or_argmemonly"|"sspreq"|"sanitize_memory"|"jumptable"|"minsize"|"nobuiltin"|"noduplicate"|"noimplicitfloat"|"builtin"|"uwtable"|"nounwind"|"optnone"|"optsize"|"naked"|"argmemonly"|"returns_twice"|"safestack"|"inaccessiblememonly"|"cold"|"noreturn"|"nonlazybind"|"sanitize_thread"|"thunk"|"sspstrong"|"sanitize_address"|"noinline"|"ssp"|"speculatable"|"sanitize_hwaddress"|"willreturn"|"nosync")
LLVM_CCONV				("ccc"|"cxx_fast_tlscc"|"fastcc"|"ghccc"|"swiftcc"|"preserve_allcc"|"preserve_mostcc"|"x86_vectorcallcc"|"cc10"|"cc11"|"arm_apcscc"|"coldcc"|"webkit_jscc"|"cc64"|"cc65"|"cc66"|"ptx_device"|"x86_stdcallcc"|"cc67"|"cc68"|"cc69"|"cc70"|"cc1023"|"anyregcc"|"cc71"|"cc72"|"cc75"|"msp430_intrcc"|"ptx_kernel"|"cc76"|"cc77"|"cc78"|"spir_func"|"x86_64_win64cc"|"cc79"|"cc80"|"arm_aapcs_vfpcc"|"intel_ocl_bicc"|"x86_64_sysvcc"|"x86_fastcallcc"|"x86_thiscallcc"|"arm_aapcscc"|"spir_kernel")
LLVM_FASTMATH			("nnan"|"ninf"|"nsz"|"arcp"|"contract"|"afn"|"reassoc"|"fast")
LLVM_BOOL				("true"|"false")
LLVM_ORDERING			("unordered"|"monotonic"|"acquire"|"release"|"acq_rel"|"seq_cst")
LLVM_ICMP_COND			("eq"|"ne"|"ugt"|"uge"|"ult"|"ule"|"sgt"|"sge"|"slt"|"sle")
LLVM_TAIL				("tail"|"musttail"|"notail")
LLVM_CONV_OP			("trunc"|"zext"|"sext"|"fptrunc"|"fpext"|"fptoui"|"fptosi"|"uitofp"|"sitofp"|"ptrtoint"|"inttoptr"|"bitcast"|"addrspacecast")
LLVM_DIV				("sdiv"|"udiv")
LLVM_REM				("srem"|"urem")
LLVM_LOGIC				("and"|"or"|"xor")
LLVM_SHR				("lshr"|"ashr")
LLVM_FMATH				("fadd"|"fsub"|"fmul"|"fdiv"|"frem")
LLVM_COMDATTYPE			("any"|"exactmatch"|"largest"|"noduplicates"|"samesize")

%%

<SGC>"<label>:"				{ BEGIN(LABEL1); LLVMRTOKEN(LABEL_COMMENT) }
<SGC>" preds ="				{ BEGIN(PREDS); LLVMRTOKEN(PREDS_COMMENT) }
<SGC>" No predecessors!"	{ LLVMRTOKEN(NO_PREDS) }
<LABEL1>[0-9]+				{ LLVMRTOKEN(DECIMAL) }
<LABEL1>":"					{ BEGIN(LABEL2); }
<LABEL1>\n					{ LL2W::llvmLexer.newline(); BEGIN(INITIAL); }
<LABEL1>[ \t]+				{ }
<LABEL1>.					{ LL2W::llvmLexer.badchar(*llvmtext); }
<LABEL2>"; preds ="			{ BEGIN(PREDS); LLVMRTOKEN(PREDS_COMMENT) }
<LABEL2>[ \t]+				{ }
<LABEL2>\n					{ LL2W::llvmLexer.newline(); BEGIN(INITIAL); }
<LABEL2>.					{ LL2W::llvmLexer.badchar(*llvmtext); }
<SGC>\n						{ LL2W::llvmLexer.newline(); BEGIN(INITIAL); }
<SGC>.						{ }
<PREDS>{LLVM_PVAR}			{ LLVMRTOKEN(PVAR); }
<PREDS>[ \t,]+				{ }
<PREDS>\n					{ LL2W::llvmLexer.newline(); BEGIN(INITIAL); LLVMRTOKEN(NEWLINE) }
<PREDS>.					{ LL2W::llvmLexer.badchar(*llvmtext); }
[0-9]+":"					{ LLVMRTOKEN(SIMPLE_LABEL) }

";"							{ BEGIN(SGC); }
{LLVM_MLCOMMENT}			{ }
[ \t]+						{ }
\n							{ LL2W::llvmLexer.newline(); }

{LLVM_UNIONVAR}				{ LLVMRTOKEN(UNIONVAR) }
{LLVM_CLASSVAR}				{ LLVMRTOKEN(CLASSVAR) }
{LLVM_STRUCTVAR}			{ LLVMRTOKEN(STRUCTVAR) }
{LLVM_PVAR}					{ LLVMRTOKEN(PVAR) }
{LLVM_GVAR}					{ LLVMRTOKEN(GVAR) }
{LLVM_INTTYPE}				{ LLVMRTOKEN(INTTYPE)  }
{LLVM_FLOATTYPE}			{ LLVMRTOKEN(FLOATTYPE)  }
{LLVM_DLLPORT}				{ LLVMRTOKEN(DLLPORT) }
{LLVM_THREAD_LOCAL_TYPE}	{ LLVMRTOKEN(THREAD_LOCAL_TYPE) }
{LLVM_PARATTR}				{ LLVMRTOKEN(PARATTR) }
{LLVM_RETATTR}				{ LLVMRTOKEN(RETATTR) }
{LLVM_DEREF}				{ LLVMRTOKEN(DEREF) }
{LLVM_UNNAMED_ADDR_TYPE}	{ LLVMRTOKEN(UNNAMED_ADDR_TYPE) }
{LLVM_LINKAGE}				{ LLVMRTOKEN(LINKAGE) }
{LLVM_VISIBILITY}			{ LLVMRTOKEN(VISIBILITY) }
{LLVM_FNATTR_BASIC}			{ LLVMRTOKEN(FNATTR_BASIC) }
{LLVM_CCONV}				{ LLVMRTOKEN(CCONV) }
{LLVM_FASTMATH}				{ LLVMRTOKEN(FASTMATH) }
{LLVM_BOOL}					{ LLVMRTOKEN(BOOL) }
{LLVM_ORDERING}				{ LLVMRTOKEN(ORDERING) }
{LLVM_ICMP_COND}			{ LLVMRTOKEN(ICMP_COND) }
{LLVM_TAIL}					{ LLVMRTOKEN(TAIL) }
{LLVM_CONV_OP}				{ LLVMRTOKEN(CONV_OP) }
{LLVM_DIV}					{ LLVMRTOKEN(DIV) }
{LLVM_REM}					{ LLVMRTOKEN(REM) }
{LLVM_LOGIC}				{ LLVMRTOKEN(LOGIC) }
{LLVM_SHR}					{ LLVMRTOKEN(SHR) }
{LLVM_FMATH}				{ LLVMRTOKEN(FMATH) }
{LLVM_COMDATTYPE}			{ LLVMRTOKEN(COMDATTYPE) }

"!invariant.group"			{ LLVMRTOKEN(INVARIANT_GROUP) }
"!invariant.load"			{ LLVMRTOKEN(INVARIANT_LOAD) }
"!nontemporal"				{ LLVMRTOKEN(NONTEMPORAL) }
"!nonnull"					{ LLVMRTOKEN(NONNULL) }
"!dereferenceable"			{ LLVMRTOKEN(DEREFERENCEABLE) }
"!align"					{ LLVMRTOKEN(BANGALIGN) }
"!srcloc"					{ LLVMRTOKEN(SRCLOC) }
"!tbaa"						{ LLVMRTOKEN(TBAA) }
"!prof"						{ LLVMRTOKEN(PROF) }
"!callees"					{ LLVMRTOKEN(CALLEES) }
"!llvm.loop"				{ LLVMRTOKEN(LLVMLOOP) }
"!dbg"						{ LLVMRTOKEN(DBG) }
{LLVM_INTBANG}				{ LLVMRTOKEN(INTBANG) }
{LLVM_METABANG}				{ LLVMRTOKEN(METABANG) }
"define"					{ LLVMRTOKEN(DEFINE) }
"declare"					{ LLVMRTOKEN(DECLARE) }
"readonly"					{ LLVMRTOKEN(READONLY) }
"readnone"					{ LLVMRTOKEN(READNONE) }
"!"							{ LLVMRTOKEN(BANG)  }
"datalayout"				{ LLVMRTOKEN(DATALAYOUT) }
"="							{ LLVMRTOKEN(EQUALS) }
"source_filename"			{ LLVMRTOKEN(SOURCE_FILENAME) }
"patchable-function=\"prologue-short-redirect\"" { LLVMRTOKEN(PATCHABLE_PROLOGUE) }
{LLVM_CSTRING}				{ LLVMRTOKEN(CSTRING) }
{LLVM_STRING}				{ LLVMRTOKEN(STRING) }
"target"					{ LLVMRTOKEN(TARGET) }
"triple"					{ LLVMRTOKEN(TRIPLE) }
{LLVM_FLOATING}				{ LLVMRTOKEN(FLOATING) }
{LLVM_DECIMAL}				{ LLVMRTOKEN(DECIMAL) }
{LLVM_HEXADECIMAL}			{ LLVMRTOKEN(HEXADECIMAL) }
"distinct"					{ LLVMRTOKEN(DISTINCT) }
"."							{ LLVMRTOKEN(DOT) }
"!{"						{ LLVMRTOKEN(METADATA_OPEN) }
"{"							{ LLVMRTOKEN(LCURLY) }
"}"							{ LLVMRTOKEN(RCURLY) }
","							{ LLVMRTOKEN(COMMA) }
"%"							{ LLVMRTOKEN(PERCENT) }
"@"							{ LLVMRTOKEN(AT) }
"("							{ LLVMRTOKEN(LPAR) }
")"							{ LLVMRTOKEN(RPAR) }
"["							{ LLVMRTOKEN(LSQUARE) }
"]"							{ LLVMRTOKEN(RSQUARE) }
"x"							{ LLVMRTOKEN(X) }
"null"						{ LLVMRTOKEN(NULL) }
"<"							{ LLVMRTOKEN(LANGLE) }
">"							{ LLVMRTOKEN(RANGLE) }
"void"						{ LLVMRTOKEN(VOID) }
"..."						{ LLVMRTOKEN(ELLIPSIS) }
"*"							{ LLVMRTOKEN(ASTERISK) }
"#"							{ LLVMRTOKEN(HASH) }
":"							{ LLVMRTOKEN(COLON) }
"undef"						{ LLVMRTOKEN(UNDEF) }

"select"					{ LLVMRTOKEN(SELECT) }
"alloca"					{ LLVMRTOKEN(ALLOCA) }
"inalloca"					{ LLVMRTOKEN(INALLOCA) }
"store"						{ LLVMRTOKEN(STORE) }
"load"						{ LLVMRTOKEN(LOAD) }
"volatile"					{ LLVMRTOKEN(VOLATILE) }

"thread_local"				{ LLVMRTOKEN(THREAD_LOCAL) }

"addrspace"					{ LLVMRTOKEN(ADDRSPACE) }
"zeroinitializer"			{ LLVMRTOKEN(ZEROINITIALIZER) }
"externally_initialized"	{ LLVMRTOKEN(EXTERNALLY_INITIALIZED) }
"global"					{ LLVMRTOKEN(GLOBAL) }
"constant"					{ LLVMRTOKEN(CONSTANT) }
"section"					{ LLVMRTOKEN(SECTION) }
"comdat"					{ LLVMRTOKEN(COMDAT) }
"align"						{ LLVMRTOKEN(ALIGN) }

"type"						{ LLVMRTOKEN(TYPE) }
"opaque"					{ LLVMRTOKEN(OPAQUE) }
"attributes"				{ LLVMRTOKEN(ATTRIBUTES) }
"alignstack"				{ LLVMRTOKEN(ALIGNSTACK) }
"allocsize"					{ LLVMRTOKEN(ALLOCSIZE) }
"syncscope"					{ LLVMRTOKEN(SYNCSCOPE) }
"atomic"					{ LLVMRTOKEN(ATOMIC) }
"icmp"						{ LLVMRTOKEN(ICMP) }
"br"						{ LLVMRTOKEN(BR) }
"label"						{ LLVMRTOKEN(LABEL) }
"call"						{ LLVMRTOKEN(CALL) }
"getelementptr"				{ LLVMRTOKEN(GETELEMENTPTR) }
"inbounds"					{ LLVMRTOKEN(INBOUNDS) }
"inrange"					{ LLVMRTOKEN(INRANGE) }
"ret"						{ LLVMRTOKEN(RET) }
"personality"				{ LLVMRTOKEN(PERSONALITY) }
"to"						{ LLVMRTOKEN(TO) }
"invoke"					{ LLVMRTOKEN(INVOKE) }
"unwind"					{ LLVMRTOKEN(UNWIND) }
"cleanup"					{ LLVMRTOKEN(CLEANUP) }
"catch"						{ LLVMRTOKEN(CATCH) }
"landingpad"				{ LLVMRTOKEN(LANDINGPAD) }
"extractvalue"				{ LLVMRTOKEN(EXTRACTVALUE) }
"insertvalue"				{ LLVMRTOKEN(INSERTVALUE) }
"resume"					{ LLVMRTOKEN(RESUME) }
"filter"					{ LLVMRTOKEN(FILTER) }
"byval"						{ LLVMRTOKEN(BYVAL) }
"writeonly"					{ LLVMRTOKEN(WRITEONLY) }
"nuw"						{ LLVMRTOKEN(NUW) }
"nsw"						{ LLVMRTOKEN(NSW) }
"add"						{ LLVMRTOKEN(ADD) }
"sub"						{ LLVMRTOKEN(SUB) }
"mul"						{ LLVMRTOKEN(MUL) }
"shl"						{ LLVMRTOKEN(SHL) }
"phi"						{ LLVMRTOKEN(PHI) }
"switch"					{ LLVMRTOKEN(SWITCH) }
"unreachable"				{ LLVMRTOKEN(UNREACHABLE) }
"asm"						{ LLVMRTOKEN(ASM) }
"sideeffect"				{ LLVMRTOKEN(SIDEEFFECT) }
"inteldialect"				{ LLVMRTOKEN(INTELDIALECT) }
"exact"						{ LLVMRTOKEN(EXACT) }
"dso_local"					{ LLVMRTOKEN(DSO_LOCAL) }
"dso_preemptable"			{ LLVMRTOKEN(DSO_PREEMPTABLE) }
"alias"						{ LLVMRTOKEN(ALIAS) }

{LLVM_IDENT}				{ LLVMRTOKEN(IDENT) }

.							{ LL2W::llvmLexer.badchar(*llvmtext); }

%%

#undef LLVMRTOKEN