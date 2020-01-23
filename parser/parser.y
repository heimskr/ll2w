%{
#include <cassert>
#include <cstdarg>
#include <initializer_list>

#define NO_YYPARSE
#include "Lexer.h"
#include "ASTNode.h"
#include "Parser.h"
#include "GlobalVarDef.h"
#include "FunctionHeader.h"
#include "FunctionArgs.h"
#include "Instructions.h"
#include "StructNode.h"
#include "Values.h"

template <typename ...Args>
void D(Args && ...args) {
    (void) std::initializer_list<int> {
		((void) delete args, 0)...
	};
}

using namespace LL2W;
using AN = LL2W::ASTNode;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
%}

%debug
%defines
%error-verbose
%token-table
%verbose
%glr-parser

%initial-action {
    LL2W::Parser::root = new LL2W::ASTNode(TOK_ROOT, {0, 0}, "");
}

%token TOK_ROOT TOK_STRING TOK_PERCENTID TOK_INTTYPE TOK_DECIMAL TOK_FLOATING TOK_IDENT TOK_METABANG TOK_PARATTR
%token TOK_METADATA TOK_CSTRING TOK_PVAR TOK_GVAR TOK_FLOATTYPE TOK_DLLPORT TOK_BOOL TOK_RETATTR TOK_UNNAMED_ADDR_TYPE
%token TOK_DEREF TOK_LINKAGE TOK_FNATTR_BASIC TOK_CCONV TOK_VISIBILITY TOK_FASTMATH TOK_STRUCTVAR TOK_CLASSVAR
%token TOK_UNIONVAR TOK_INTBANG TOK_ORDERING TOK_ICMP_COND TOK_LABEL_COMMENT TOK_PREDS_COMMENT TOK_TAIL TOK_CONV_OP
%token TOK_SOURCE_FILENAME "source_filename"
%token TOK_BANG "!"
%token TOK_EQUALS "="
%token TOK_DOT "."
%token TOK_TARGET "target"
%token TOK_DATALAYOUT "datalayout"
%token TOK_TRIPLE "triple"
%token TOK_DISTINCT "distinct"
%token TOK_METADATA_OPEN "!{"
%token TOK_LCURLY "{"
%token TOK_RCURLY "}"
%token TOK_COMMA ","
%token TOK_NULL "null"
%token TOK_PERCENT "%"
%token TOK_AT "@"
%token TOK_LPAR "("
%token TOK_RPAR ")"
%token TOK_LSQUARE "["
%token TOK_RSQUARE "]"
%token TOK_X "x"
%token TOK_LANGLE "<"
%token TOK_RANGLE ">"
%token TOK_VOID "void"
%token TOK_ELLIPSIS "..."
%token TOK_ASTERISK "*"
%token TOK_HASH "#"
%token TOK_COLON ":"

%token TOK_TO "to"

%token TOK_THREAD_LOCAL "thread_local"
%token TOK_THREAD_LOCAL_TYPE

%token TOK_LOCALDYNAMIC "localdynamic"
%token TOK_INITIALEXEC "initialexec"
%token TOK_LOCALEXEC "localexec"
%token TOK_ADDRSPACE "addrspace"
%token TOK_ZEROINITIALIZER "zeroinitializer"
%token TOK_EXTERNALLY_INITIALIZED "externally_initialized"
%token TOK_GLOBAL "global"
%token TOK_CONSTANT "constant"
%token TOK_SECTION "section"
%token TOK_COMDAT "comdat"
%token TOK_ALIGN "align"

%token TOK_TYPE "type"
%token TOK_OPAQUE "opaque"
%token TOK_ATTRIBUTES "attributes"
%token TOK_ALIGNSTACK "alignstack"
%token TOK_ALLOCSIZE "allocsize"
%token TOK_PATCHABLE_PROLOGUE "patchable-function=\"prologue-short-redirect\""
%token TOK_READONLY "readonly"
%token TOK_DECLARE "declare"
%token TOK_DEFINE "define"

%token TOK_SELECT "select"
%token TOK_ALLOCA "alloca"
%token TOK_INALLOCA "inalloca"
%token TOK_STORE "store"
%token TOK_LOAD "load"
%token TOK_VOLATILE "volatile"
%token TOK_INVARIANT_GROUP "!invariant.group"
%token TOK_INVARIANT_LOAD "!invariant.load"
%token TOK_NONTEMPORAL "!nontemporal"
%token TOK_NONNULL "!nonnull"
%token TOK_DEREFERENCEABLE "!dereferenceable"
%token TOK_DEREFERENCEABLE_OR_NULL "!dereferenceable_or_null"
%token TOK_BANGALIGN "!align"
%token TOK_SYNCSCOPE "syncscope"
%token TOK_ATOMIC "atomic"
%token TOK_ICMP "icmp"
%token TOK_BR "br"
%token TOK_LABEL "label"
%token TOK_CALL "call"
%token TOK_GETELEMENTPTR "getelementptr"
%token TOK_INBOUNDS "inbounds"
%token TOK_INRANGE "inrange"
%token TOK_RET "ret"
%token TOK_PERSONALITY "personality"
%token TOK_INVOKE "invoke"
%token TOK_UNWIND "unwind"

%token CONSTANT CONST_EXPR INITIAL_VALUE_LIST ARRAYTYPE VECTORTYPE POINTERTYPE TYPE_LIST FUNCTIONTYPE GDEF_EXTRAS
%token STRUCTDEF ATTRIBUTE_LIST RETATTR_LIST FNATTR_LIST FUNCTION_TYPE_LIST PARATTR_LIST FUNCTION_HEADER FUNCTION_ARGS
%token FUNCTION_DEF STATEMENTS LABEL INSTRUCTION FASTMATH_FLAGS VECTOR METADATA_LIST PREDS_LIST FNTYPE CONSTANT_LIST
%token GETELEMENTPTR_EXPR DECIMAL_LIST INDEX_LIST STRUCT_VALUE VALUE_LIST ARRAY_VALUE

%start start

%%

start: program;

program: program source_filename { $1->adopt($2); }
       | program target          { $1->adopt($2); }
       | program metadata_def    { $1->adopt($2); }
       | program global_def      { $1->adopt($2); }
       | program attributes      { $1->adopt($2); }
       | program struct_def      { $1->adopt($2); }
       | program declaration     { $1->adopt($2); }
       | program function_def    { $1->adopt($2); }
       | { $$ = Parser::root; };

declaration: "declare" function_header { $1->adopt($2); };


// Struct definitions
struct_def: struct_def_left "opaque"      { $$ = new StructNode(StructShape::Opaque, $1, nullptr); D($2); }
          | struct_def_left "{" types "}" { $$ = new StructNode(StructShape::Default, $1, $3); D($2, $4); }
          | struct_def_left "<" "{" types "}" ">" { $$ = new StructNode(StructShape::Packed, $1, $4); D($2, $3, $5, $6); };
struct_def_left: csuvar "=" "type" { $$ = $1; D($2, $3); };
csuvar: TOK_STRUCTVAR | TOK_CLASSVAR | TOK_UNIONVAR;

// Attributes
attributes: "attributes" "#" TOK_DECIMAL "=" "{" attribute_list "}" { $$ = $1->adopt({$3, $6}); D($2, $4, $5, $7); };
attribute_list: attribute_list attribute { $$ = $1->adopt($2); }
              | { $$ = new AN(ATTRIBUTE_LIST); };
attribute: TOK_STRING "=" TOK_STRING { $$ = $2->adopt({$1, $3}); }
         | TOK_STRING
         | fnattr;

basic_fnattr: TOK_FNATTR_BASIC | TOK_READONLY { $1->symbol = TOK_FNATTR_BASIC; };
fnattr: basic_fnattr
      | "alignstack" "(" TOK_DECIMAL ")"                 { $$ = $1->adopt($3);       D($2, $4);     }
      | "allocsize"  "(" TOK_DECIMAL "," TOK_DECIMAL ")" { $$ = $1->adopt({$3, $5}); D($2, $4, $6); }
      | "allocsize"  "(" TOK_DECIMAL ")"                 { $$ = $1->adopt($3);       D($2, $4);     }
      | TOK_PATCHABLE_PROLOGUE;

//
source_filename: "source_filename" "=" TOK_STRING { D($1, $2); $$ = new AN(TOK_SOURCE_FILENAME, $3->lexerInfo); }

target: TOK_TARGET target_type "=" TOK_STRING { $$ = $1->adopt({$2, $4}); }
target_type: "datalayout" | "triple";

metadata_def: metabang "=" metadata_distinct "!{" metadata_list "}" { D($2, $4, $6); $$ = new MetadataDef($1, $3, $5); };

metadata_list: metadata_list "," metadata_listitem { $1->adopt($3); D($2); }
             | metadata_listitem { $$ = (new AN(METADATA_LIST))->adopt($1); }
             | { $$ = nullptr; };

metadata_listitem: "!" TOK_STRING { D($1); $$ = $2; } | metabang | constant | array | "null";

metadata_distinct: "distinct" { $$ = new AN(TOK_DISTINCT, "distinct"); }
                 |            { $$ = nullptr; };

metabang: TOK_METABANG | TOK_INTBANG { $1->symbol = TOK_METABANG; };

ident: TOK_IDENT | TOK_DECIMAL { $1->symbol = TOK_IDENT; }

value: TOK_FLOATING | TOK_DECIMAL | TOK_BOOL | vector | variable | struct | array | "null";
vector: "<" _vector_list ">" { $$ = $2; D($1, $3); };
_vector_list: vector_list | { $$ = nullptr; };
vector_list: vector_list "," type_any value { $$ = $1->adopt($2->adopt({$3, $4})); }
           | type_any value { $$ = (new AN(VECTOR))->adopt((new AN(TOK_COMMA, ","))->adopt({$1, $2})); };
struct: "{" _value_pairs "}" { $1->adopt($2); $1->symbol = STRUCT_VALUE; D($3); };
_value_pairs: { $$ = nullptr; } | value_pairs;
value_pairs: value_pairs "," type_any value { $1->adopt($2->adopt({$3, $4})); }
           | type_any value { $$ = (new AN(VALUE_LIST))->adopt((new AN(TOK_COMMA, ","))->adopt({$1, $2})); };
array: type_array "[" value_pairs "]" { $$ = $2->adopt({$1, $3}); $$->symbol = ARRAY_VALUE; D($4); };

// Types
type_any: type_nonvoid | TOK_VOID;
type_nonvoid: TOK_INTTYPE | TOK_FLOATTYPE | type_array | type_vector | type_ptr | type_function | type_struct | TOK_STRUCTVAR | TOK_CLASSVAR | TOK_UNIONVAR;
type_array:  "[" TOK_DECIMAL "x" type_any    "]" { $$ = (new AN(ARRAYTYPE,  ""))->adopt({$2, $4}); D($1, $3, $5); };
type_vector: "<" TOK_DECIMAL "x" vector_type ">" { $$ = (new AN(VECTORTYPE))->adopt({$2, $4}); D($1, $3, $5); };
vector_type: TOK_INTTYPE | type_ptr | TOK_FLOATTYPE;
type_ptr: type_any "*" { $$ = (new AN(POINTERTYPE, "*"))->adopt($1); D($2); };
type_function: type_any "(" types extra_ellipsis ")" "*" { $$ = (new AN(FUNCTIONTYPE))->adopt({$1, $4, $3}); D($2, $5, $6); }
             | type_any "("            _ellipsis ")" "*" { $$ = (new AN(FUNCTIONTYPE))->adopt({$1, $3});     D($2, $4, $5); };
type_struct: "{" types "}"         { $$ = new StructNode(StructShape::Default, $2); D($1, $3);         }
           | "<" "{" types "}" ">" { $$ = new StructNode(StructShape::Packed,  $3); D($1, $2, $4, $5); };
types: types "," type_any { $$ = $1->adopt($3); D($2); }
     | type_any           { $$ = (new AN(TYPE_LIST))->adopt($1); };
extra_ellipsis: "," "..." { D($1); $$ = $2; } | { $$ = nullptr; };
_ellipsis: "..." | { $$ = nullptr; };

// Globals
global_def: TOK_GVAR "=" _linkage _visibility _dll_storage_class _thread_local _unnamed_addr _addrspace
           _externally_initialized global_or_constant type_any _initial_value gdef_extras
           { D($2); $$ = new GlobalVarDef($1, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); };

_linkage: TOK_LINKAGE | { $$ = nullptr; };
_visibility: TOK_VISIBILITY | { $$ = nullptr; };
_dll_storage_class: TOK_DLLPORT | { $$ = nullptr; };
_thread_local: "thread_local" "(" TOK_THREAD_LOCAL_TYPE ")" { $$ = $1->adopt($3); D($2, $4); } | { $$ = nullptr; };
_addrspace: "addrspace" "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); D($2, $4); } | { $$ = nullptr; };
_externally_initialized: TOK_EXTERNALLY_INITIALIZED | { $$ = nullptr; };
global_or_constant: "global" | "constant";
_initial_value: initial_value | { $$ = nullptr; };
initial_value: TOK_CSTRING | TOK_FLOATING | TOK_DECIMAL | "zeroinitializer" | "null"
             | "{" initial_value_list "}" { $$ = $2; D($1, $3); };
initial_value_list: initial_value_list initial_value { $$ = $1->adopt($2); }
                  | { $$ = new AN(INITIAL_VALUE_LIST); }
gdef_extras: gdef_extras "," section { $$ = $1->adopt($3); D($2); }
           | gdef_extras "," comdat  { $$ = $1->adopt($3); D($2); }
           | gdef_extras "," TOK_ALIGN TOK_DECIMAL   { $$ = $1->adopt($3->adopt($4)); D($2); }
           | { $$ = new AN(GDEF_EXTRAS); };
section: TOK_SECTION TOK_STRING       { $$ = $1->adopt($2); };
comdat:  TOK_COMDAT "(" TOK_IDENT ")" { $$ = $1->adopt($3); D($2, $4); }
      |  TOK_COMDAT;

// Functions
function_header: _linkage _visibility _dll_storage_class _cconv _retattrs type_any function_name "(" function_args ")" _unnamed_addr _fnattrs _personality
                { $$ = new FunctionHeader($1, $2, $3, $4, $5, $6, $7, $9, $11, $12, $13); D($8, $10); };
_retattrs: _retattrs retattr { $1->adopt($2); } | { $$ = new AN(RETATTR_LIST); };
function_args: function_types "," "..." { $$ = new FunctionArgs($1, true); D($2, $3); }
             | function_types { $$ = new FunctionArgs($1, false); }
             | "..." { $$ = new FunctionArgs(nullptr, true); }
             | { $$ = new FunctionArgs(nullptr, false); };
function_types: function_types "," function_type { $1->adopt($3); D($2); } | function_type { $$ = (new AN(FUNCTION_TYPE_LIST))->adopt($1); };
function_type: type_any parattr_list _variable { $$ = $1->adopt({$2, $3}); };
_cconv: TOK_CCONV | { $$ = nullptr; };
_fnattrs: "#" TOK_DECIMAL { $$ = $2; D($1); } | fnattr_list;
fnattr_list: fnattr_list basic_fnattr { $1->adopt($2); } | { $$ = new AN(FNATTR_LIST); };
_unnamed_addr: TOK_UNNAMED_ADDR_TYPE | { $$ = nullptr; };
_variable: TOK_PVAR | { $$ = nullptr; };
variable: TOK_PVAR | TOK_GVAR;
_personality: "personality" constant { $1->adopt($2); } | { $$ = nullptr; };

function_def: "define" function_header "{" function_lines "}" { $$ = (new AN(FUNCTION_DEF, $2->lexerInfo))->adopt({$2, $4}); D($3, $5); };
function_lines: function_lines statement { $1->adopt($2); } | { $$ = new AN(STATEMENTS); };
statement: label_statement | instruction | bb_header;
label_statement: ident ":" { $1->symbol = LABEL; D($2); };
bb_header: TOK_LABEL_COMMENT TOK_DECIMAL TOK_PREDS_COMMENT preds_list { $1->adopt({$2, $3, $4}); };
preds_list: preds_list TOK_PVAR { $1->adopt($2); }
          | { $$ = new AN(PREDS_LIST); };


// Instructions
instruction: i_select | i_alloca | i_store | i_store_atomic | i_load | i_load_atomic | i_icmp | i_br_uncond | i_br_cond
           | i_call | i_getelementptr | i_ret | i_invoke;

i_select: TOK_PVAR "=" "select" fastmath_flags type_any value "," type_any value "," type_any value
          { $$ = new SelectNode($1, $4, $5, $6, $8, $9, $11, $12); D($2, $3, $7, $10); };

i_alloca: TOK_PVAR "=" "alloca" _inalloca type_any _alloca_numelements _align _alloca_addrspace
          { $$ = new AllocaNode($1, $4, $5, $6, $7, $8); D($2, $3); };
_inalloca: "inalloca" | { $$ = nullptr; };
_alloca_numelements: "," type_any TOK_DECIMAL { $$ = $1->adopt({$2, $3}); } | { $$ = nullptr; };
_align: align | { $$ = nullptr; };
align: "," "align" TOK_DECIMAL { $$ = $3; D($1, $2); };
_alloca_addrspace: "," "addrspace" "(" TOK_DECIMAL ")" { $$ = $4; D($1, $2, $3, $5); } | { $$ = nullptr; };

i_store: "store" _volatile type_any operand "," type_ptr TOK_PVAR _align _nontemporal _invariant_group
         { $$ = new StoreNode($2, $3, $4, $6, $7, $8, $9, $10); D($1, $5); };
_volatile: TOK_VOLATILE | { $$ = nullptr; };
_nontemporal: "," "!nontemporal" TOK_INTBANG { $$ = $3; D($1, $2); }  | { $$ = nullptr; };
_invariant_group: "," "!invariant.group" TOK_INTBANG { $$ = $3; D($1, $2); } | { $$ = nullptr; };

i_store_atomic: "store" "atomic" _volatile type_any operand "," type_ptr TOK_PVAR _syncscope TOK_ORDERING align _invariant_group
                { $$ = new StoreNode($3, $4, $5, $7, $8, $9, $10, $11, $12); D($1, $2, $6); };
_syncscope: "syncscope" "(" TOK_STRING ")" { $$ = $3; D($1, $2, $4); } | { $$ = nullptr; };

i_load: TOK_PVAR "=" "load" _volatile type_any "," type_ptr TOK_PVAR _align _nontemporal _invariant_load
        _invariant_group _nonnull _dereferenceable _dereferenceable_or_null _bang_align
        { $$ = new LoadNode($1, $4, $5, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16); D($2, $3, $6); };
// TODO: what is the actual form of the arguments for these?
_invariant_load:          "," "!invariant.load"          TOK_INTBANG { $$ = $3; D($1, $2); } | { $$ = nullptr; };
_nonnull:                 "," "!nonnull"                 TOK_INTBANG { $$ = $3; D($1, $2); } | { $$ = nullptr; };
_dereferenceable:         "," "!dereferenceable"         metabang    { $$ = $3; D($1, $2); } | { $$ = nullptr; };
_dereferenceable_or_null: "," "!dereferenceable_or_null" metabang    { $$ = $3; D($1, $2); } | { $$ = nullptr; };
_bang_align:              "," "!align"                   metabang    { $$ = $3; D($1, $2); } | { $$ = nullptr; };

i_load_atomic: TOK_PVAR "=" "load" "atomic" _volatile type_any "," type_ptr TOK_PVAR _syncscope TOK_ORDERING align _invariant_group
               { $$ = new LoadNode($1, $5, $6, $8, $9, $10, $11, $12, $13); D($2, $3, $4, $7); };

i_icmp: TOK_PVAR "=" "icmp" TOK_ICMP_COND type_any operand "," operand
      { $$ = new IcmpNode($1, $4, $5, $6, $8); D($2, $3, $7); };

i_br_uncond: "br" "label" TOK_PVAR { $$ = new BrUncondNode($3); D($1, $2); };

i_br_cond: "br" TOK_INTTYPE operand "," label "," label { $$ = new BrCondNode($2, $3, $5, $7); D($1, $4, $6); };
label: "label" TOK_PVAR { $$ = $2; D($1); };

i_call: _result _tail "call" fastmath_flags _cconv _retattrs _addrspace type_any _args function_name "(" _constants ")" call_attrs
        { $$ = new CallNode($1, $2, $4, $5, $6, $7, $8, $9, $10, $12, $14); D($3, $11, $13); };
_result: TOK_PVAR "=" { D($2); } | { $$ = nullptr; };
_args: args | { $$ = nullptr; };
args: "(" types extra_ellipsis ")" { $1->adopt({$2, $3}); D($4); }
    | "("            _ellipsis ")" { $1->adopt($2);       D($3); };

_tail: TOK_TAIL | { $$ = nullptr; };
function_name: TOK_GVAR | TOK_IDENT;
_constants: constants | { $$ = new AN(CONSTANT_LIST); };
constants: constants "," constant { $1->adopt($3); D($2); }
         | constant               { $$ = (new AN(CONSTANT_LIST))->adopt($1); };
call_attrs: call_attrs "#" TOK_DECIMAL { $1->adopt($3); D($2); } | { $$ = new AN(ATTRIBUTE_LIST); };

i_getelementptr: TOK_PVAR "=" "getelementptr" _inbounds type_any "," type_ptr TOK_PVAR gep_indices
               { $$ = new GetelementptrNode($1, $4, $5, $7, $8, $9); D($2, $3, $6); };
// TODO: vectors. <result> = getelementptr <ty>, <ptr vector> <ptrval>, [inrange] <vector index type> <idx>
gep_indices: { $$ = new AN(INDEX_LIST); } | gep_indices "," _inrange type_any TOK_DECIMAL { $1->adopt($2->adopt({$4, $5, $3})); };
_inrange: TOK_INRANGE | { $$ = nullptr; };

i_ret: "ret" type_nonvoid value { $$ = new RetNode($2, $3); D($1); } | "ret" "void" { $$ = new RetNode(); D($1, $2); };

i_invoke: _result "invoke" _cconv _retattrs _addrspace type_any _args function_name "(" _constants ")" call_attrs
          /* TODO: operand bundles */ "to" label "unwind" label
          { $$ = new InvokeNode($1, $3, $4, $5, $6, $7, $8, $10, $12, $14, $16); D($2, $9, $11, $13, $15); };

// Constants
constant: type_any parattr_list constant_right { $$ = (new AN(CONSTANT))->adopt({$1, $2, $3}); };
constant_right: operand | const_expr;
parattr_list: parattr_list parattr { $$ = $1->adopt($2); } | { $$ = new AN(PARATTR_LIST); };
parattr: TOK_PARATTR | TOK_INALLOCA { $1->symbol = TOK_PARATTR; } | TOK_READONLY { $1->symbol = TOK_PARATTR; } | retattr;
retattr: TOK_RETATTR | TOK_DEREF "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); D($2, $4); };
operand: TOK_PVAR | TOK_DECIMAL | TOK_GVAR | TOK_BOOL | getelementptr_expr | "null";
const_expr: TOK_CONV_OP constant TOK_TO type_any { $$ = (new AN(CONST_EXPR, $1->lexerInfo))->adopt({$2, $4}); D($3); }
          | TOK_CONV_OP "(" constant TOK_TO type_any ")" { $$ = (new AN(CONST_EXPR, $1->lexerInfo))->adopt({$3, $5}); D($2, $4, $6); };

getelementptr_expr: "getelementptr" _inbounds "(" type_any "," type_ptr variable decimals ")"
                  { $$ = new GetelementptrValue($2, $4, $6, $7, $8); D($1, $3, $5, $9); };
_inbounds: TOK_INBOUNDS | { $$ = nullptr; };
decimals: decimals "," TOK_INTTYPE TOK_DECIMAL { $1->adopt($2->adopt({$3, $4})); } | { $$ = new AN(DECIMAL_LIST); };

// Miscellaneous
fastmath_flags: fastmath_flags TOK_FASTMATH { $1->adopt($2); } | { $$ = new AN(FASTMATH_FLAGS) };

%%
#pragma GCC diagnostic pop

const char * LL2W::Parser::getName(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
