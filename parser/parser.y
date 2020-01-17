%{
#include <cassert>

#include "Lexer.h"
#include "ASTNode.h"
#include "Parser.h"
#include "GlobalVarDef.h"

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

%token TOK_ROOT TOK_STRING TOK_PERCENTID TOK_INTTYPE TOK_DECIMAL TOK_FLOATING TOK_IDENT TOK_DOTIDENT TOK_METADATA_LIST
%token TOK_PARATTR TOK_METADATA TOK_CSTRING TOK_PVAR TOK_GVAR TOK_FLOATTYPE TOK_DLLPORT TOK_RETATTR TOK_DEREF
%token TOK_UNNAMED_ADDR_TYPE TOK_LINKAGE TOK_FNATTR_BASIC
%token TOK_STRUCTVAR
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
%token TOK_FLOAT "float"
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
%token TOK_ELLIPSE "..."
%token TOK_ASTERISK "*"
%token TOK_HASH "#"

// Conversion operations
%token TOK_TRUNC "trunc"
%token TOK_ZEXT "zext"
%token TOK_SEXT "sext"
%token TOK_FPTRUNC "fptrunc"
%token TOK_FPEXT "fpext"
%token TOK_FPTOUI "fptoui"
%token TOK_FPTOSI "fptosi"
%token TOK_UITOFP "uitofp"
%token TOK_SITOFP "sitofp"
%token TOK_PTRTOINT "ptrtoint"
%token TOK_INTTOPTR "inttoptr"
%token TOK_BITCAST "bitcast"
%token TOK_ADDRSPACECAST "addrspacecast"

%token TOK_TO "to"

// Visibility
%token TOK_DEFAULT "default"
%token TOK_HIDDEN "hidden"
%token TOK_PROTECTED "protected"

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

%token CONSTANT CONST_EXPR INITIAL_VALUE_LIST ARRAYTYPE VECTORTYPE POINTER TYPE_LIST FUNCTION GDEF_EXTRAS STRUCTDEF
%token ATTRIBUTE_LIST

%start start

%%

start: program { $$ = $1 = nullptr; };

program: program source_filename { $1->adopt($2); }
       | program target          { $1->adopt($2); }
       | program metadata_def    { $1->adopt($2); }
       | program global_def      { $1->adopt($2); }
       | program attributes      { $1->adopt($2); }
       | program struct_def      { $1->adopt($2); }
//       | program declaration     { $1->adopt($2); }
       | { $$ = Parser::root; };

// declaration: "declare" function_header { $1->adopt($2); };


// Struct definitions
struct_def: struct_def_left "opaque" { $$ = (new AN(STRUCTDEF, $1->lexerInfo))->adopt($2); delete $1; }
          | struct_def_left "{" types "}" { $$ = (new AN(STRUCTDEF, $1->lexerInfo))->adopt($3); delete $1; };
struct_def_left: TOK_STRUCTVAR "=" "type" { $$ = $1; delete $2; delete $3; };

// Attributes
attributes: "attributes" "#" TOK_DECIMAL "=" "{" attribute_list "}" { $$ = $1->adopt({$3, $6}); delete $2; delete $4; delete $5; delete $7; };
attribute_list: attribute_list attribute { $$ = $1->adopt($2); }
              | { $$ = new AN(ATTRIBUTE_LIST, ""); };
attribute: TOK_STRING "=" TOK_STRING { $$ = $2->adopt({$1, $3}); }
         | TOK_STRING
         | fnattr;

fnattr: TOK_FNATTR_BASIC | TOK_READONLY
      | "alignstack" "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); delete $2; delete $4; }
      | "allocsize" "(" TOK_DECIMAL "," TOK_DECIMAL ")" { $$ = $1->adopt({$3, $5}); delete $2; delete $4; delete $6; }
      | "allocsize" "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); delete $2; delete $4; }
      | TOK_PATCHABLE_PROLOGUE;

//
source_filename: "source_filename" "=" TOK_STRING { AN::destroy({$1, $2}); $$ = new AN(TOK_SOURCE_FILENAME, $3->lexerInfo); }

target: TOK_TARGET target_type "=" TOK_STRING { $$ = $1->adopt({$2, $4}); }
target_type: "datalayout" | "triple";

metadata_def: "!" dotident "=" metadata_distinct TOK_METADATA_OPEN metadata_list TOK_RCURLY { AN::destroy({$1, $3, $5, $7}); $$ = new MetadataDef($2, $4, $6); };

metadata_list: metadata_list "," metadata_listitem { $1->adopt($3); delete $2; }
             | metadata_listitem { $$ = (new AN(TOK_METADATA_LIST, ""))->adopt($1); }
             | { $$ = nullptr; };

metadata_listitem: "!" TOK_STRING      { delete $1; $$ = $2; }
                 | "!" TOK_DECIMAL { delete $1; $$ = $2; }
                 | constant
                 | "null";

metadata_distinct: "distinct" { $$ = new AN(TOK_DISTINCT, "distinct"); }
                 |            { $$ = nullptr; };

dotident: TOK_DECIMAL { $1->symbol = TOK_DOTIDENT; } | TOK_DOTIDENT;

// Types
type_any: TOK_INTTYPE | TOK_FLOATTYPE | TOK_FLOAT | type_array | type_vector | type_ptr | TOK_VOID | type_function | TOK_STRUCTVAR;
type_array: "[" TOK_DECIMAL "x" type_any "]" { $$ = (new AN(ARRAYTYPE, ""))->adopt({$2, $4}); delete $1; delete $3; delete $5; };
type_vector: "<" TOK_DECIMAL "x" vector_type ">" { $$ = (new AN(VECTORTYPE, ""))->adopt({$2, $4}); delete $1; delete $3; delete $5; };
vector_type: TOK_INTTYPE | type_ptr | TOK_FLOAT;
type_ptr: type_any "*" { $$ = (new AN(POINTER, "*"))->adopt($1); delete $2; };
type_function: type_any "(" types extra_ellipse ")" "*" { $$ = (new AN(FUNCTION, ""))->adopt({$1, $4, $3}); delete $2; delete $5; delete $6; }
             | type_any "(" optional_ellipse ")" "*" { $$ = (new AN(FUNCTION, ""))->adopt({$1, $3}); delete $2; delete $4; delete $5; };
types: types "," type_any { $$ = $1->adopt($3); delete $2; } | type_any { $$ = (new AN(TYPE_LIST, ""))->adopt($1); };
extra_ellipse: "," "..." { delete $1; $$ = $2; } | { $$ = nullptr; };
optional_ellipse: "..." | { $$ = nullptr; };

// Globals
global_def: TOK_GVAR "=" TOK_LINKAGE visibility dll_storage_class thread_local TOK_UNNAMED_ADDR_TYPE addrspace
           externally_initialized global_or_constant type_any optional_initial_value gdef_extras
           { delete $2; $$ = new GlobalVarDef($1, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); };

visibility: "default" | "hidden" | "protected" | { $$ = nullptr; };
dll_storage_class: TOK_DLLPORT | { $$ = nullptr; };
thread_local: "thread_local" "(" TOK_THREAD_LOCAL_TYPE ")" { $$ = $1->adopt($3); delete $2; delete $4; } | { $$ = nullptr; };
addrspace: "addrspace" "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); delete $2; delete $4; } | { $$ = nullptr; };
externally_initialized: TOK_EXTERNALLY_INITIALIZED | { $$ = nullptr; };
global_or_constant: "global" | "constant";
optional_initial_value: initial_value | { $$ = nullptr; };
initial_value: TOK_CSTRING | TOK_FLOATING | TOK_DECIMAL | "zeroinitializer" | "null"
             | "{" initial_value_list "}" { $$ = $2; delete $1; delete $3; };
initial_value_list: initial_value_list initial_value { $$ = $1->adopt($2); }
                  | { $$ = new AN(INITIAL_VALUE_LIST, ""); }
gdef_extras: gdef_extras "," gdef_section { $$ = $1->adopt($3); delete $2; }
           | gdef_extras "," gdef_comdat { $$ = $1->adopt($3); delete $2; }
           | gdef_extras "," gdef_align { $$ = $1->adopt($3); delete $2; }
           | { $$ = new AN(GDEF_EXTRAS, ""); };
gdef_section: TOK_SECTION TOK_STRING { $$ = $1->adopt($2); };
gdef_comdat: TOK_COMDAT "$" dotident { $$ = $1->adopt($3); delete $2; };
gdef_align: TOK_ALIGN TOK_DECIMAL { $$ = $1->adopt($2); };

// Constants
constant: type_any parattr_list constant_right { $$ = (new AN(CONSTANT, ""))->adopt({$1, $2, $3}); }
constant_right: operand | const_expr;
parattr_list: parattr_list parattr { $$ = $1->adopt($2); } | { $$ = nullptr; };
parattr: TOK_PARATTR | TOK_READONLY | retattr;
retattr: TOK_RETATTR | TOK_DEREF "(" TOK_DECIMAL ")" { $$ = $1->adopt($3); delete $2; delete $4; };
operand: TOK_PVAR | TOK_DECIMAL | TOK_GVAR | /* getelementptr_expr | */ "null";
const_expr: conv_op constant TOK_TO type_any { $$ = (new AN(CONST_EXPR, $1->lexerInfo))->adopt({$2, $4}); delete $3; }
conv_op: TOK_TRUNC | TOK_ZEXT | TOK_SEXT | TOK_FPTRUNC | TOK_FPEXT | TOK_FPTOUI | TOK_FPTOSI | TOK_UITOFP | TOK_SITOFP
       | TOK_PTRTOINT | TOK_INTTOPTR | TOK_BITCAST | TOK_ADDRSPACECAST;

%%

const char * LL2W::Parser::getName(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
