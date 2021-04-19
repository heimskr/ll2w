%{
#include <cassert>
#include <cstdarg>
#include <initializer_list>

#define NO_YYPARSE
#include "parser/Lexer.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/GlobalVarDef.h"
#include "parser/FunctionHeader.h"
#include "parser/FunctionArgs.h"
#include "parser/Nodes.h"
#include "parser/StructNode.h"
#include "parser/Values.h"

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
%glr-parser

%define api.prefix {wasm}

%initial-action {
    LL2W::wasmParser.root = new LL2W::ASTNode(LL2W::wasmParser, WASMTOK_ROOT, {0, 0}, "");
}

%token WASMTOK_ROOT WASMTOK_IDENT

%token WASMTOK_BANG "!"
%token WASMTOK_EQUALS "="
%token WASMTOK_DOT "."
%token WASMTOK_TARGET "target"
%token WASMTOK_DATALAYOUT "datalayout"
%token WASMTOK_TRIPLE "triple"
%token WASMTOK_DISTINCT "distinct"
%token WASMTOK_METADATA_OPEN "!{"
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
%token WASMTOK_VOID "void"
%token WASMTOK_ELLIPSIS "..."
%token WASMTOK_ASTERISK "*"
%token WASMTOK_HASH "#"
%token WASMTOK_COLON ":"
%token WASMTOK_UNDEF "undef"
%token WASMTOK_NEWLINE

%token WASMTOK_TO "to"

%token WASMTOK_THREAD_LOCAL "thread_local"
%token WASMTOK_THREAD_LOCAL_TYPE

%token WASMTOK_LOCALDYNAMIC "localdynamic"
%token WASMTOK_INITIALEXEC "initialexec"
%token WASMTOK_LOCALEXEC "localexec"
%token WASMTOK_ADDRSPACE "addrspace"
%token WASMTOK_ZEROINITIALIZER "zeroinitializer"
%token WASMTOK_EXTERNALLY_INITIALIZED "externally_initialized"
%token WASMTOK_GLOBAL "global"
%token WASMTOK_WASM_CONSTANT "constant"
%token WASMTOK_SECTION "section"
%token WASMTOK_COMDAT "comdat"
%token WASMTOK_ALIGN "align"

%token WASMTOK_TYPE "type"
%token WASMTOK_OPAQUE "opaque"
%token WASMTOK_ATTRIBUTES "attributes"
%token WASMTOK_ALIGNSTACK "alignstack"
%token WASMTOK_ALLOCSIZE "allocsize"
%token WASMTOK_PATCHABLE_PROLOGUE "patchable-function=\"prologue-short-redirect\""
%token WASMTOK_READONLY "readonly"
%token WASMTOK_READNONE "readnone"
%token WASMTOK_DECLARE "declare"
%token WASMTOK_DEFINE "define"

%token WASMTOK_SELECT "select"
%token WASMTOK_ALLOCA "alloca"
%token WASMTOK_INALLOCA "inalloca"
%token WASMTOK_STORE "store"
%token WASMTOK_LOAD "load"
%token WASMTOK_VOLATILE "volatile"
%token WASMTOK_INVARIANT_GROUP "!invariant.group"
%token WASMTOK_INVARIANT_LOAD "!invariant.load"
%token WASMTOK_NONTEMPORAL "!nontemporal"
%token WASMTOK_NONNULL "!nonnull"
%token WASMTOK_DEREFERENCEABLE "!dereferenceable"
%token WASMTOK_DEREFERENCEABLE_OR_NULL "!dereferenceable_or_null"
%token WASMTOK_BANGALIGN "!align"
%token WASMTOK_SRCLOC "!srcloc"
%token WASMTOK_TBAA "!tbaa"
%token WASMTOK_PROF "!prof"
%token WASMTOK_CALLEES "!callees"
%token WASMTOK_SYNCSCOPE "syncscope"
%token WASMTOK_ATOMIC "atomic"
%token WASMTOK_ICMP "icmp"
%token WASMTOK_BR "br"
%token WASMTOK_LABEL "label"
%token WASMTOK_CALL "call"
%token WASMTOK_GETELEMENTPTR "getelementptr"
%token WASMTOK_INBOUNDS "inbounds"
%token WASMTOK_INRANGE "inrange"
%token WASMTOK_RET "ret"
%token WASMTOK_PERSONALITY "personality"
%token WASMTOK_INVOKE "invoke"
%token WASMTOK_UNWIND "unwind"
%token WASMTOK_CLEANUP "cleanup"
%token WASMTOK_CATCH "catch"
%token WASMTOK_LANDINGPAD "landingpad"
%token WASMTOK_EXTRACTVALUE "extractvalue"
%token WASMTOK_INSERTVALUE "insertvalue"
%token WASMTOK_RESUME "resume"
%token WASMTOK_FILTER "filter"
%token WASMTOK_BYVAL "byval"
%token WASMTOK_WRITEONLY "writeonly"
%token WASMTOK_NUW "nuw"
%token WASMTOK_NSW "nsw"
%token WASMTOK_ADD "add"
%token WASMTOK_SUB "sub"
%token WASMTOK_MUL "mul"
%token WASMTOK_SHL "shl"
%token WASMTOK_PHI "phi"
%token WASMTOK_SWITCH "switch"
%token WASMTOK_UNREACHABLE "unreachable"
%token WASMTOK_ASM "asm"
%token WASMTOK_SIDEEFFECT "sideeffect"
%token WASMTOK_INTELDIALECT "inteldialect"
%token WASMTOK_EXACT "exact"
%token WASMTOK_DSO_LOCAL "dso_local"
%token WASMTOK_DSO_PREEMPTABLE "dso_preemptable"

%token WASM_CONSTANT WASM_CONVERSION_EXPR WASM_INITIAL_VALUE_LIST WASM_ARRAYTYPE WASM_VECTORTYPE WASM_POINTERTYPE
%token WASM_TYPE_LIST WASM_FUNCTIONTYPE WASM_GDEF_EXTRAS WASM_STRUCTDEF WASM_ATTRIBUTE_LIST WASM_RETATTR_LIST
%token WASM_FNATTR_LIST WASM_FUNCTION_TYPE_LIST WASM_PARATTR_LIST WASM_FUNCTION_HEADER WASM_FUNCTION_ARGS
%token WASM_FUNCTION_DEF WASM_STATEMENTS WASM_LABEL WASM_INSTRUCTION WASM_FASTMATH_FLAGS WASM_VECTOR WASM_METADATA_LIST
%token WASM_PREDS_LIST WASM_FNTYPE WASM_CONSTANT_LIST WASM_GETELEMENTPTR_EXPR WASM_DECIMAL_LIST WASM_INDEX_LIST
%token WASM_STRUCT_VALUE WASM_VALUE_LIST WASM_ARRAY_VALUE WASM_CLAUSES WASM_GLOBAL_DEF WASM_PHI_PAIR WASM_SWITCH_LIST
%token WASM_BLOCKHEADER WASM_DECIMAL_PAIR_LIST WASM_BANGS

%start start

%%

start: program;

program: { $$ = LL2W::wasmParser.root; };

%%

#pragma GCC diagnostic pop

const char * LL2W::Parser::getNameWASM(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
