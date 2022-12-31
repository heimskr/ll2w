%{
#include <cassert>
#include <cstdarg>
#include <initializer_list>

#define NO_YYPARSE
#include "parser/Lexer.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/GlobalVarDef.h"
#include "parser/AliasDef.h"
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
const LL2W::ASTLocation & L(std::initializer_list<const T *> nodes) {
	for (const T *node: nodes)
		if (node)
			return node->location;
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

%define api.prefix {llvm}

%initial-action {
    LL2W::llvmParser.root = new LL2W::ASTNode(LL2W::llvmParser, LLVMTOK_ROOT, {0, 0}, "");
}

%token LLVMTOK_ROOT LLVMTOK_STRING LLVMTOK_PERCENTID LLVMTOK_INTTYPE LLVMTOK_DECIMAL LLVMTOK_FLOATING LLVMTOK_IDENT
%token LLVMTOK_METABANG LLVMTOK_PARATTR LLVMTOK_CSTRING LLVMTOK_PVAR LLVMTOK_GVAR LLVMTOK_FLOATTYPE
%token LLVMTOK_DLLPORT LLVMTOK_BOOL LLVMTOK_RETATTR LLVMTOK_UNNAMED_ADDR_TYPE LLVMTOK_DEREF LLVMTOK_LINKAGE
%token LLVMTOK_FNATTR_BASIC LLVMTOK_CCONV LLVMTOK_VISIBILITY LLVMTOK_FASTMATH LLVMTOK_STRUCTVAR LLVMTOK_CLASSVAR
%token LLVMTOK_UNIONVAR LLVMTOK_INTBANG LLVMTOK_ORDERING LLVMTOK_ICMP_COND LLVMTOK_LABEL_COMMENT LLVMTOK_PREDS_COMMENT
%token LLVMTOK_TAIL LLVMTOK_CONV_OP LLVMTOK_DIV LLVMTOK_REM LLVMTOK_LOGIC LLVMTOK_SHR LLVMTOK_FMATH LLVMTOK_SIMPLE_LABEL
%token LLVMTOK_NO_PREDS LLVMTOK_HEXADECIMAL LLVMTOK_COMDATTYPE
%token LLVMTOK_SOURCE_FILENAME "source_filename"
%token LLVMTOK_BANG "!"
%token LLVMTOK_EQUALS "="
%token LLVMTOK_DOT "."
%token LLVMTOK_TARGET "target"
%token LLVMTOK_DATALAYOUT "datalayout"
%token LLVMTOK_TRIPLE "triple"
%token LLVMTOK_DISTINCT "distinct"
%token LLVMTOK_METADATA_OPEN "!{"
%token LLVMTOK_LCURLY "{"
%token LLVMTOK_RCURLY "}"
%token LLVMTOK_COMMA ","
%token LLVMTOK_NULL "null"
%token LLVMTOK_PERCENT "%"
%token LLVMTOK_AT "@"
%token LLVMTOK_LPAR "("
%token LLVMTOK_RPAR ")"
%token LLVMTOK_LSQUARE "["
%token LLVMTOK_RSQUARE "]"
%token LLVMTOK_X "x"
%token LLVMTOK_LANGLE "<"
%token LLVMTOK_RANGLE ">"
%token LLVMTOK_VOID "void"
%token LLVMTOK_ELLIPSIS "..."
%token LLVMTOK_ASTERISK "*"
%token LLVMTOK_HASH "#"
%token LLVMTOK_COLON ":"
%token LLVMTOK_UNDEF "undef"
%token LLVMTOK_POISON "poison"
%token LLVMTOK_NEWLINE

%token LLVMTOK_TO "to"

%token LLVMTOK_THREAD_LOCAL "thread_local"
%token LLVMTOK_THREAD_LOCAL_TYPE

%token LLVMTOK_LOCALDYNAMIC "localdynamic"
%token LLVMTOK_INITIALEXEC "initialexec"
%token LLVMTOK_LOCALEXEC "localexec"
%token LLVMTOK_ADDRSPACE "addrspace"
%token LLVMTOK_ZEROINITIALIZER "zeroinitializer"
%token LLVMTOK_EXTERNALLY_INITIALIZED "externally_initialized"
%token LLVMTOK_GLOBAL "global"
%token LLVMTOK_CONSTANT "constant"
%token LLVMTOK_SECTION "section"
%token LLVMTOK_COMDAT "comdat"
%token LLVMTOK_ALIGN "align"

%token LLVMTOK_TYPE "type"
%token LLVMTOK_OPAQUE "opaque"
%token LLVMTOK_ATTRIBUTES "attributes"
%token LLVMTOK_ALIGNSTACK "alignstack"
%token LLVMTOK_ALLOCSIZE "allocsize"
%token LLVMTOK_PATCHABLE_PROLOGUE "patchable-function=\"prologue-short-redirect\""
%token LLVMTOK_READONLY "readonly"
%token LLVMTOK_READNONE "readnone"
%token LLVMTOK_DECLARE "declare"
%token LLVMTOK_DEFINE "define"

%token LLVMTOK_SELECT "select"
%token LLVMTOK_ALLOCA "alloca"
%token LLVMTOK_INALLOCA "inalloca"
%token LLVMTOK_STORE "store"
%token LLVMTOK_LOAD "load"
%token LLVMTOK_VOLATILE "volatile"
%token LLVMTOK_INVARIANT_GROUP "!invariant.group"
%token LLVMTOK_INVARIANT_LOAD "!invariant.load"
%token LLVMTOK_NONTEMPORAL "!nontemporal"
%token LLVMTOK_NONNULL "!nonnull"
%token LLVMTOK_DEREFERENCEABLE "!dereferenceable"
%token LLVMTOK_DEREFERENCEABLE_OR_NULL "!dereferenceable_or_null"
%token LLVMTOK_BANGALIGN "!align"
%token LLVMTOK_SRCLOC "!srcloc"
%token LLVMTOK_TBAA "!tbaa"
%token LLVMTOK_TBAA_STRUCT "!tbaa.struct"
%token LLVMTOK_PROF "!prof"
%token LLVMTOK_CALLEES "!callees"
%token LLVMTOK_SYNCSCOPE "syncscope"
%token LLVMTOK_ATOMIC "atomic"
%token LLVMTOK_ICMP "icmp"
%token LLVMTOK_BR "br"
%token LLVMTOK_LABEL "label"
%token LLVMTOK_CALL "call"
%token LLVMTOK_GETELEMENTPTR "getelementptr"
%token LLVMTOK_INBOUNDS "inbounds"
%token LLVMTOK_INRANGE "inrange"
%token LLVMTOK_RET "ret"
%token LLVMTOK_PERSONALITY "personality"
%token LLVMTOK_INVOKE "invoke"
%token LLVMTOK_UNWIND "unwind"
%token LLVMTOK_CLEANUP "cleanup"
%token LLVMTOK_CATCH "catch"
%token LLVMTOK_LANDINGPAD "landingpad"
%token LLVMTOK_EXTRACTVALUE "extractvalue"
%token LLVMTOK_INSERTVALUE "insertvalue"
%token LLVMTOK_RESUME "resume"
%token LLVMTOK_FILTER "filter"
%token LLVMTOK_WRITEONLY "writeonly"
%token LLVMTOK_NUW "nuw"
%token LLVMTOK_NSW "nsw"
%token LLVMTOK_ADD "add"
%token LLVMTOK_SUB "sub"
%token LLVMTOK_MUL "mul"
%token LLVMTOK_SHL "shl"
%token LLVMTOK_PHI "phi"
%token LLVMTOK_SWITCH "switch"
%token LLVMTOK_UNREACHABLE "unreachable"
%token LLVMTOK_ASM "asm"
%token LLVMTOK_SIDEEFFECT "sideeffect"
%token LLVMTOK_INTELDIALECT "inteldialect"
%token LLVMTOK_EXACT "exact"
%token LLVMTOK_DSO_LOCAL "dso_local"
%token LLVMTOK_DSO_PREEMPTABLE "dso_preemptable"
%token LLVMTOK_ALIAS "alias"
%token LLVMTOK_LLVMLOOP "!llvm.loop"
%token LLVMTOK_DBG "!dbg"
%token LLVMTOK_DBG_VALUE "@llvm.dbg.value"
%token LLVMTOK_DBG_DECLARE "@llvm.dbg.declare"
%token LLVMTOK_METADATA "metadata"
%token LLVMTOK_DIEXPRESSION "!DIExpression"
%token LLVMTOK_VAR "var"
%token LLVMTOK_EXPR "expr"
%token LLVMTOK_DIGV "!DIGlobalVariable"
%token LLVMTOK_DIGVE "!DIGlobalVariableExpression"
%token LLVMTOK_NAME "name"
%token LLVMTOK_SCOPE "scope"
%token LLVMTOK_FILE "file"
%token LLVMTOK_LINE "line"
%token LLVMTOK_ISLOCAL "isLocal"
%token LLVMTOK_ISDEFINITION "isDefinition"
%token LLVMTOK_DICU "!DICompileUnit"
%token LLVMTOK_LANGUAGE "language"
%token LLVMTOK_PRODUCER "producer"
%token LLVMTOK_ISOPTIMIZED "isOptimized"
%token LLVMTOK_RUNTIMEVERSION "runtimeVersion"
%token LLVMTOK_EMISSIONKIND "emissionKind"
%token LLVMTOK_ENUMS "enums"
%token LLVMTOK_RETAINEDTYPES "retainedTypes"
%token LLVMTOK_GLOBALS "globals"
%token LLVMTOK_IMPORTS "imports"
%token LLVMTOK_SPLITDEBUGINLINING "splitDebugInlining"
%token LLVMTOK_NAMETABLEKIND "nameTableKind"
%token LLVMTOK_NONE "None"
%token LLVMTOK_DIFILE "!DIFile"
%token LLVMTOK_FILENAME "filename"
%token LLVMTOK_DIRECTORY "directory"
%token LLVMTOK_DIDT "!DIDerivedType"
%token LLVMTOK_TAG "tag"
%token LLVMTOK_BASETYPE "baseType"
%token LLVMTOK_SIZE "size"
%token LLVMTOK_DIBT "!DIBasicType"
%token LLVMTOK_ENCODING "encoding"
%token LLVMTOK_DIIE "!DIImportedEntity"
%token LLVMTOK_ENTITY "entity"
%token LLVMTOK_DINAMESPACE "!DINamespace"
%token LLVMTOK_FLAGS "flags"
%token LLVMTOK_ELEMENTS "elements"
%token LLVMTOK_DICT "!DICompositeType"
%token LLVMTOK_IDENTIFIER "identifier"
%token LLVMTOK_PIPE "|"
%token LLVMTOK_DIST "!DISubroutineType"
%token LLVMTOK_TYPES "types"
%token LLVMTOK_DISUBRANGE "!DISubrange"
%token LLVMTOK_COUNT "count"
%token LLVMTOK_OFFSET "offset"
%token LLVMTOK_LINKAGENAME "linkageName"
%token LLVMTOK_SCOPELINE "scopeLine"
%token LLVMTOK_SPFLAGS "spFlags"
%token LLVMTOK_UNIT "unit"
%token LLVMTOK_DECLARATION "declaration"
%token LLVMTOK_RETAINEDNODES "retainedNodes"
%token LLVMTOK_DISUBPROGRAM "!DISubprogram"
%token LLVMTOK_EXTRADATA "extraData"
%token LLVMTOK_DILV "!DILocalVariable"
%token LLVMTOK_ARG "arg"
%token LLVMTOK_DILOCATION "!DILocation"
%token LLVMTOK_COLUMN "column"
%token LLVMTOK_DILB "!DILexicalBlock"
%token LLVMTOK_ASSUME "@llvm.assume"
%token LLVMTOK_SYSROOT "sysroot"
%token LLVMTOK_SDK "sdk"
%token LLVMTOK_EXPORTSYMBOLS "exportSymbols"
%token LLVMTOK_TEMPLATEPARAMS "templateParams"
%token LLVMTOK_DITTP "!DITemplateTypeParameter"
%token LLVMTOK_DILBF "!DILexicalBlockFile"
%token LLVMTOK_DISCRIMINATOR "discriminator"
%token LLVMTOK_HEAPALLOCSITE "!heapallocsite"
%token LLVMTOK_RANGE "!range"
%token LLVMTOK_FREEZE "freeze"
%token LLVMTOK_INLINEDAT "inlinedAt"
%token LLVMTOK_DILABEL "!DILabel"
%token LLVMTOK_DBG_LABEL "@llvm.dbg.label"
%token LLVMTOK_VTABLEHOLDER "vtableHolder"
%token LLVMTOK_CONTAININGTYPE "containingType"
%token LLVMTOK_VIRTUALINDEX "virtualIndex"
%token LLVMTOK_TYPED_PARATTR
%token LLVMTOK_DITVP "!DITemplateValueParameter"
%token LLVMTOK_VALUE "value"
%token LLVMTOK_ISUNSIGNED "isUnsigned"
%token LLVMTOK_DIENUMERATOR "!DIEnumerator"
%token LLVMTOK_DEFAULTED "defaulted"
%token LLVMTOK_NOALIAS_SCOPE_DECL "@llvm.experimental.noalias.scope.decl"
%token LLVMTOK_NOALIAS "!noalias"
%token LLVMTOK_ALIAS_SCOPE "!alias.scope"
%token LLVMTOK_NOUNDEF "noundef"
%token LLVMTOK_DIARGLIST "!DIArgList"
%token LLVMTOK_CHECKSUMKIND "checksumkind"
%token LLVMTOK_CHECKSUM "checksum"

%token LLVM_CONSTANT LLVM_CONVERSION_EXPR LLVM_INITIAL_VALUE_LIST LLVM_ARRAYTYPE LLVM_VECTORTYPE LLVM_POINTERTYPE
%token LLVM_TYPE_LIST LLVM_FUNCTIONTYPE LLVM_GDEF_EXTRAS LLVM_STRUCTDEF LLVM_ATTRIBUTE_LIST LLVM_RETATTR_LIST
%token LLVM_FNATTR_LIST LLVM_FUNCTION_TYPE_LIST LLVM_PARATTR_LIST LLVM_FUNCTION_HEADER LLVM_FUNCTION_ARGS
%token LLVM_FUNCTION_DEF LLVM_STATEMENTS LLVM_LABEL LLVM_INSTRUCTION LLVM_FASTMATH_FLAGS LLVM_VECTOR LLVM_METADATA_LIST
%token LLVM_PREDS_LIST LLVM_FNTYPE LLVM_CONSTANT_LIST LLVM_GETELEMENTPTR_EXPR LLVM_DECIMAL_LIST LLVM_INDEX_LIST
%token LLVM_STRUCT_VALUE LLVM_VALUE_LIST LLVM_ARRAY_VALUE LLVM_CLAUSES LLVM_GLOBAL_DEF LLVM_PHI_PAIR LLVM_SWITCH_LIST
%token LLVM_BLOCKHEADER LLVM_DECIMAL_PAIR_LIST LLVM_BANGS LLVM_ALIAS_DEF LLVM_METADATA LLVM_DIEXPRESSION_LIST
%token LLVM_DIDT_LIST LLVM_PIPE_LIST LLVM_DICT_LIST LLVM_DICU_LIST LLVM_DISUBPROGRAM_LIST LLVM_DILV_LIST
%token LLVM_DILOCATION_LIST LLVM_DIGV_LIST LLVM_DITVP_LIST LLVM_DIE_LIST LLVM_DITTP_LIST LLVM_DIST_LIST

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
       | program comdat_def      { $1->adopt($2); }
       | program alias_def       { $1->adopt($2); }
       | { $$ = LL2W::llvmParser.root; };

declaration: "declare" _debug function_header { $1->adopt($3); D($2); }
           | "declare" "void" dbg_type "(" "metadata" "," "metadata" "," "metadata" ")" _fnattrs
             { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11); }
           | "declare" "void" "@llvm.dbg.label" "(" "metadata" ")" _fnattrs
             { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
           | "declare" "void" "@llvm.experimental.noalias.scope.decl" "(" "metadata" ")" _fnattrs
             { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
           | "declare" "void" "@llvm.assume" "(" function_args ")" _fnattrs
             { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); };



// Struct definitions

struct_def: struct_def_left "opaque"      { $$ = new StructNode(StructShape::Opaque, $1, nullptr); D($2); }
          | struct_def_left "{" types "}" { $$ = new StructNode(StructShape::Default, $1, $3); D($2, $4); }
          | struct_def_left "<" "{" types "}" ">" { $$ = new StructNode(StructShape::Packed, $1, $4); D($2, $3, $5, $6); };
struct_def_left: csuvar "=" "type" { $$ = $1; D($2, $3); };
csuvar: LLVMTOK_STRUCTVAR | LLVMTOK_CLASSVAR | LLVMTOK_UNIONVAR;



// Attributes

attributes: "attributes" "#" LLVMTOK_DECIMAL "=" "{" attribute_list "}"
            { $$ = new AttributesNode($1->adopt({$3, $6})); D($2, $4, $5, $7); };
attribute_list: attribute_list attribute { $$ = $1->adopt($2); }
              | { $$ = new AN(llvmParser, LLVM_ATTRIBUTE_LIST); };
attribute: LLVMTOK_STRING "=" LLVMTOK_STRING { $$ = $2->adopt({$1, $3}); }
         | LLVMTOK_STRING
         | attribute_fnattr
         | attribute_parattr
         | "writeonly"
         | "readnone"
         | "readonly";

basic_fnattr: LLVMTOK_FNATTR_BASIC | convertible_fnattr { $1->symbol = LLVMTOK_FNATTR_BASIC; };
convertible_fnattr: "writeonly" | "readonly" | "readnone" | LLVMTOK_PATCHABLE_PROLOGUE;

attribute_basic_fnattr: LLVMTOK_FNATTR_BASIC | attribute_convertible_fnattr { $1->symbol = LLVMTOK_FNATTR_BASIC; };
attribute_convertible_fnattr: LLVMTOK_PATCHABLE_PROLOGUE;
attribute_fnattr: attribute_basic_fnattr
      | "alignstack" "(" LLVMTOK_DECIMAL ")"                     { $$ = $1->adopt($3);       D($2, $4);     }
      | "allocsize"  "(" LLVMTOK_DECIMAL "," LLVMTOK_DECIMAL ")" { $$ = $1->adopt({$3, $5}); D($2, $4, $6); }
      | "allocsize"  "(" LLVMTOK_DECIMAL ")"                     { $$ = $1->adopt($3);       D($2, $4);     };

attribute_parattr: LLVMTOK_PARATTR
                 | attribute_parattr_simple                 { $1->symbol = LLVMTOK_PARATTR;  }
                 | LLVMTOK_TYPED_PARATTR "(" type_any ")" { $$ = $1->adopt($3); D($2, $4); }
                 | "inalloca" "(" type_any ")" { $$ = $1->adopt($3); D($2, $4); }
                 | retattr;
attribute_parattr_simple: LLVMTOK_INALLOCA;



// Miscellaneous

source_filename: "source_filename" "=" LLVMTOK_STRING { $$ = (new AN(llvmParser, LLVMTOK_SOURCE_FILENAME, $3->lexerInfo))->locate($3); D($1, $2, $3); }

target: LLVMTOK_TARGET target_type "=" LLVMTOK_STRING { $$ = $1->adopt({$2, $4}); D($3); }
target_type: "datalayout" | "triple";

metadata_def: metabang "=" metadata_distinct "!{" metadata_list "}"
              { D($2, $4, $6); $$ = new MetadataDef($1, $3, $5); }
            | metabang "=" metadata_distinct "!DIGlobalVariableExpression" "(" "var" ":" LLVMTOK_INTBANG "," "expr" ":"
              diexpression ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); }
            | metabang "=" metadata_distinct "!DIGlobalVariable" "(" digv_list ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
            | metabang "=" metadata_distinct "!DICompileUnit" "(" dicu_list ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
            | metabang "=" metadata_distinct "!DIFile" "(" "filename" ":" LLVMTOK_STRING "," "directory" ":"
              LLVMTOK_STRING ")"
              { $$ = $4->adopt({$1, $8, $12}); D($2, $3, $5, $6, $7, $9, $10, $11, $13); }
            | metabang "=" metadata_distinct "!DIFile" "(" "filename" ":" LLVMTOK_STRING "," "directory" ":" LLVMTOK_STRING 
              "," "checksumkind" ":" any_ident "," "checksum" ":" LLVMTOK_STRING ")"
              { $$ = $4->adopt({$1, $8, $12}); D($2, $3, $5, $6, $7, $9, $10, $11, $13, $14, $15, $16, $17, $18, $19, $20, $21); }
            | metabang "=" metadata_distinct "!DIDerivedType" "(" didt_list ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
            | metabang "=" metadata_distinct "!DIBasicType" "(" "name" ":" LLVMTOK_STRING "," "size" ":" LLVMTOK_DECIMAL
              "," "encoding" ":" any_ident ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17); }
            | metabang "=" metadata_distinct "!DIBasicType" "(" "tag" ":" any_ident "," "name" ":" LLVMTOK_STRING
              ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); }
            | metabang "=" "!DIImportedEntity" "(" "tag" ":" any_ident "," "scope" ":" LLVMTOK_INTBANG "," "entity"
              ":" LLVMTOK_INTBANG "," "file" ":" LLVMTOK_INTBANG "," "line" ":" LLVMTOK_DECIMAL ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24); }
            | metabang "=" metadata_distinct "!DINamespace" "(" "name" ":" LLVMTOK_STRING "," "scope" ":" intnullbang
              ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); }
            | metabang "=" metadata_distinct "!DINamespace" "(" "name" ":" LLVMTOK_STRING "," "scope" ":" intnullbang
              "," "exportSymbols" ":" LLVMTOK_BOOL ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17); }
            | metabang "=" metadata_distinct "!DINamespace" "(" "scope" ":" intnullbang ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9); }
            | metabang "=" metadata_distinct "!DICompositeType" "(" dict_list ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
            | metabang "=" metadata_distinct "!DISubroutineType" "(" dist_list ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7); }
            | metabang "=" metadata_distinct "!DISubrange" "(" "count" ":" LLVMTOK_DECIMAL ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9); }
            | metabang "=" metadata_distinct "!DISubrange" "(" "count" ":" LLVMTOK_INTBANG ")"
              { $$ = nullptr; D($1, $2, $3, $4, $5, $6, $7, $8, $9); }
            | metabang "=" metadata_distinct "!DISubprogram" "(" disubprogram_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DILocalVariable" "(" dilv_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DILocation" "(" dilocation_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DITemplateValueParameter" "(" ditvp_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DIEnumerator" "(" die_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DILexicalBlock" "(" "scope" ":" intnullbang "," "file" ":" intnullbang
              "," "line" ":" LLVMTOK_DECIMAL "," "column" ":" LLVMTOK_DECIMAL ")"
              { $$ = $4->adopt({$1, $8, $12}); D($2, $3, $5, $6, $7, $9, $10, $11, $13, $14, $15, $16, $17, $18, $19, $20, $21); }
            | metabang "=" metadata_distinct "!DITemplateTypeParameter" "(" dittp_list ")"
              { $$ = $4->adopt({$1, $6}); D($2, $3, $5, $7); }
            | metabang "=" metadata_distinct "!DILexicalBlockFile" "(" "scope" ":" intnullbang "," "file" ":"
              intnullbang "," "discriminator" ":" LLVMTOK_DECIMAL ")"
              { $$ = $4->adopt({$1, $8, $12, $16}); D($2, $3, $5, $6, $7, $9, $10, $11, $13, $14, $15, $17); }
            | metabang "=" metadata_distinct "!DILabel" "(" "scope" ":" intnullbang "," "name" ":" LLVMTOK_STRING ","
              "file" ":" intnullbang "," "line" ":" LLVMTOK_DECIMAL ")"
              { $$ = $4->adopt({$1, $8, $12, $16, $20}); D($2, $3, $5, $6, $7, $9, $10, $11, $13, $14, $15, $17, $18, $19, $21); };

didt_item: "size"      ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "tag"       ":" any_ident       { $$ = $1->adopt($3); D($2); }
         | "baseType"  ":" intnullbang     { $$ = $1->adopt($3); D($2); }
         | "name"      ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "file"      ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "line"      ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "scope"     ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "offset"    ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "flags"     ":" pipe_list       { $$ = $1->adopt($3); D($2); }
         | "extraData" ":" constant        { $$ = $1->adopt($3); D($2); }
         | "extraData" ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "align"     ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); };
didt_list: didt_list "," didt_item { $$ = $1->adopt($3); D($2); }
         | didt_item { $$ = (new AN(llvmParser, LLVM_DIDT_LIST))->adopt($1); };
intnullbang: LLVMTOK_INTBANG | "null";
pipe_list: pipe_list "|" any_ident       { $$ = $1->adopt($3); D($2); }
         | pipe_list "|" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | any_ident                     { $$ = (new AN(llvmParser, LLVM_PIPE_LIST))->adopt($1); }
         | LLVMTOK_DECIMAL               { $$ = (new AN(llvmParser, LLVM_PIPE_LIST))->adopt($1); };
dict_item: "tag"            ":" any_ident       { $$ = $1->adopt($3); D($2); }
         | "name"           ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "file"           ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "line"           ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "size"           ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "flags"          ":" pipe_list       { $$ = $1->adopt($3); D($2); }
         | "elements"       ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "identifier"     ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "baseType"       ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "scope"          ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "vtableHolder"   ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "templateParams" ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "align"          ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); };
dict_list: dict_list "," dict_item { $$ = $1->adopt($3); D($2); }
         | dict_item { $$ = (new AN(llvmParser, LLVM_DICT_LIST))->adopt($1); };
dicu_item: "language"           ":" any_ident       { $$ = $1->adopt($3); D($2); }
         | "file"               ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "producer"           ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "isOptimized"        ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); }
         | "runtimeVersion"     ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "emissionKind"       ":" any_ident       { $$ = $1->adopt($3); D($2); }
         | "enums"              ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "retainedTypes"      ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "globals"            ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "imports"            ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "splitDebugInlining" ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); }
         | "nameTableKind"      ":" "None"          { $$ = $1->adopt($3); D($2); }
         | "sysroot"            ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "sdk"                ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); };
dicu_list: dicu_list "," dicu_item { $$ = $1->adopt($3); D($2); }
         | dicu_item { $$ = (new AN(llvmParser, LLVM_DICU_LIST))->adopt($1); };
disubprogram_item: "name"           ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
                 | "linkageName"    ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
                 | "scope"          ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "file"           ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "line"           ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
                 | "type"           ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "scopeLine"      ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
                 | "flags"          ":" pipe_list       { $$ = $1->adopt($3); D($2); }
                 | "spFlags"        ":" pipe_list       { $$ = $1->adopt($3); D($2); }
                 | "unit"           ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "declaration"    ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "retainedNodes"  ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "templateParams" ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "containingType" ":" intnullbang     { $$ = $1->adopt($3); D($2); }
                 | "virtualIndex"   ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); };
disubprogram_list: disubprogram_list "," disubprogram_item { $$ = $1->adopt($3); D($2); }
         | disubprogram_item { $$ = (new AN(llvmParser, LLVM_DISUBPROGRAM_LIST))->adopt($1); };
dilv_item: "name"  ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); };
         | "arg"   ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); };
         | "scope" ":" intnullbang     { $$ = $1->adopt($3); D($2); };
         | "file"  ":" intnullbang     { $$ = $1->adopt($3); D($2); };
         | "line"  ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); };
         | "type"  ":" intnullbang     { $$ = $1->adopt($3); D($2); };
         | "flags" ":" pipe_list       { $$ = $1->adopt($3); D($2); };
dilv_list: dilv_list "," dilv_item { $$ = $1->adopt($3); D($2); }
         | dilv_item { $$ = (new AN(llvmParser, LLVM_DILV_LIST))->adopt($1); };
dilocation_item: "line"      ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
               | "scope"     ":" intnullbang     { $$ = $1->adopt($3); D($2); }
               | "column"    ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
               | "inlinedAt" ":" intnullbang     { $$ = $1->adopt($3); D($2); };
dilocation_list: dilocation_list "," dilocation_item { $$ = $1->adopt($3); D($2); }
         | dilocation_item { $$ = (new AN(llvmParser, LLVM_DILOCATION_LIST))->adopt($1); };

digv_item: "name"         ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "scope"        ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "file"         ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "line"         ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "type"         ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "isLocal"      ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); }
         | "isDefinition" ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); }
         | "align"        ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
         | "linkageName"  ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
         | "declaration"  ":" intnullbang     { $$ = $1->adopt($3); D($2); };
digv_list: digv_list "," digv_item { $$ = $1->adopt($3); D($2); }
         | digv_item { $$ = (new AN(llvmParser, LLVM_DIGV_LIST))->adopt($1); };

ditvp_item: "name"      ":" LLVMTOK_STRING     { $$ = $1->adopt($3); D($2); }
          | "type"      ":" LLVMTOK_INTBANG    { $$ = $1->adopt($3); D($2); }
          | "value"     ":" constant           { $$ = $1->adopt($3); D($2); }
          | "value"     ":" LLVMTOK_INTBANG    { $$ = $1->adopt($3); D($2); }
          | "value"     ":" "!" LLVMTOK_STRING { $$ = $1->adopt($4); D($2, $3); }
          | "tag"       ":" any_ident          { $$ = $1->adopt($3); D($2); }
          | "defaulted" ":" LLVMTOK_BOOL       { $$ = $1->adopt($3); D($2); };
ditvp_list: ditvp_list "," ditvp_item { $$ = $1->adopt($3); D($2); }
          | ditvp_item { $$ = (new AN(llvmParser, LLVM_DITVP_LIST))->adopt($1); };

die_item: "name"       ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
        | "value"      ":" LLVMTOK_DECIMAL { $$ = $1->adopt($3); D($2); }
        | "isUnsigned" ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); };
die_list: die_list "," die_item { $$ = $1->adopt($3); D($2); }
        | die_item { $$ = (new AN(llvmParser, LLVM_DIE_LIST))->adopt($1); };

dittp_item: "name"      ":" LLVMTOK_STRING  { $$ = $1->adopt($3); D($2); }
          | "type"      ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
          | "type"      ":" "null"          { $$ = $1->adopt($3); D($2); }
          | "defaulted" ":" LLVMTOK_BOOL    { $$ = $1->adopt($3); D($2); };
dittp_list: dittp_list "," dittp_item { $$ = $1->adopt($3); D($2); }
          | dittp_item { $$ = (new AN(llvmParser, LLVM_DITTP_LIST))->adopt($1); };

dist_item: "types" ":" LLVMTOK_INTBANG { $$ = $1->adopt($3); D($2); }
         | "flags" ":" pipe_list       { $$ = $1->adopt($3); D($2); };
dist_list: dist_list "," dist_item { $$ = $1->adopt($3); D($2); }
          | dist_item { $$ = (new AN(llvmParser, LLVM_DIST_LIST))->adopt($1); };

metadata_list: metadata_list "," metadata_listitem { $1->adopt($3); D($2); }
             | metadata_listitem { $$ = (new AN(llvmParser, LLVM_METADATA_LIST))->adopt($1); }
             | { $$ = nullptr; };

metadata_listitem: "!" LLVMTOK_STRING { D($1); $$ = $2; } | metabang | constant | "null";

metadata_distinct: "distinct" | { $$ = nullptr; };

metabang: LLVMTOK_METABANG
        | LLVMTOK_INTBANG  { $1->symbol = LLVMTOK_METABANG; };

ident: LLVMTOK_IDENT
     | LLVMTOK_DECIMAL     { $1->symbol = LLVMTOK_IDENT; }
     | LLVMTOK_HEXADECIMAL { $1->symbol = LLVMTOK_IDENT; }
     | LLVMTOK_COMDATTYPE  { $1->symbol = LLVMTOK_IDENT; };

// Not exactly a great name, considering the rule simply named "ident" is more expansive.
// It's 2:02 AM as of this writing though. (:
any_ident: LLVMTOK_IDENT
        //  | "value"      { $1->symbol = LLVMTOK_IDENT; }
        //  | "distinct"   { $1->symbol = LLVMTOK_IDENT; }
        //  | "target"     { $1->symbol = LLVMTOK_IDENT; }
        //  | "triple"     { $1->symbol = LLVMTOK_IDENT; }
        // ... insert a billion other things here ...
        //  | "isUnsigned" { $1->symbol = LLVMTOK_IDENT; }
        ;

value: LLVMTOK_FLOATING | LLVMTOK_HEXADECIMAL | LLVMTOK_DECIMAL | LLVMTOK_BOOL | vector | variable | struct | array
     | getelementptr_expr | conversion_expr | icmp_expr | "null" | "zeroinitializer" | "undef" | "poison";
vector: "<" _vector_list ">" { $$ = $2; D($1, $3); };
_vector_list: vector_list | { $$ = nullptr; };
vector_list: vector_list "," type_any value { $$ = $1->adopt($2->adopt({$3, $4})); }
           | type_any value { $$ = (new AN(llvmParser, LLVM_VECTOR))->adopt((new AN(llvmParser, LLVMTOK_COMMA, ","))->adopt({$1, $2})); };
struct: "{" _value_pairs "}"         { $1->adopt($2); $1->symbol = LLVM_STRUCT_VALUE; D($3); }
      | "<" "{" _value_pairs "}" ">" { $1->adopt($3); $1->symbol = LLVM_STRUCT_VALUE; D($2, $4, $5); };
_value_pairs: { $$ = nullptr; } | value_pairs;
value_pairs: value_pairs "," value_pair { $1->adopt($3); D($2); }
           | value_pair { $$ = (new AN(llvmParser, LLVM_VALUE_LIST))->adopt($1); };
value_pair: constant;
full_array: type_array "[" value_pairs "]" { $$ = $2->adopt({$1, $3}); $$->symbol = LLVM_ARRAY_VALUE; D($4); };
bare_array: "[" value_pairs "]" { $$ = $2; D($1, $3); };
array: full_array;

fastmath_flags: fastmath_flags LLVMTOK_FASTMATH { $1->adopt($2); } | { $$ = new AN(llvmParser, LLVM_FASTMATH_FLAGS); };

comdat_def: any_ident "=" "comdat" LLVMTOK_COMDATTYPE { $$ = $3->adopt({$1, $4}); D($2); };

debug: "!dbg" LLVMTOK_INTBANG { $$ = $1->adopt($2); };
cdebug: "," debug { $$ = $2; D($1); };
_debug: debug | { $$ = nullptr; };
_cdebug: cdebug | { $$ = nullptr; };



// Types

type_any: type_nonvoid | LLVMTOK_VOID;
type_nonvoid: LLVMTOK_INTTYPE | LLVMTOK_FLOATTYPE | type_array | type_vector | type_ptr | type_function | type_struct | LLVMTOK_STRUCTVAR | LLVMTOK_CLASSVAR | LLVMTOK_UNIONVAR;
type_nonfn: LLVMTOK_INTTYPE | LLVMTOK_FLOATTYPE | type_array | type_vector | type_ptr | type_struct | LLVMTOK_STRUCTVAR | LLVMTOK_CLASSVAR | LLVMTOK_UNIONVAR | LLVMTOK_VOID;
type_array:  "[" LLVMTOK_DECIMAL "x" type_any    "]" { $$ = (new AN(llvmParser, LLVM_ARRAYTYPE,  ""))->adopt({$2, $4}); D($1, $3, $5); };
type_vector: "<" LLVMTOK_DECIMAL "x" vector_type ">" { $$ = (new AN(llvmParser, LLVM_VECTORTYPE))->adopt({$2, $4}); D($1, $3, $5); };
vector_type: LLVMTOK_INTTYPE | type_ptr | LLVMTOK_FLOATTYPE;
type_ptr: type_any "*" { $$ = (new AN(llvmParser, LLVM_POINTERTYPE, "*"))->adopt($1); D($2); };
type_function: type_any "(" types extra_ellipsis ")" { $$ = (new AN(llvmParser, LLVM_FUNCTIONTYPE))->adopt({$1, $3, $4}); D($2, $5); }
             | type_any "("            _ellipsis ")" { $$ = (new AN(llvmParser, LLVM_FUNCTIONTYPE))->adopt({$1, $3});     D($2, $4); };
type_struct: "{" types "}"         { $$ = new StructNode(StructShape::Default, $2); D($1, $3);         }
           | "<" "{" types "}" ">" { $$ = new StructNode(StructShape::Packed,  $3); D($1, $2, $4, $5); };
types: types "," type_any { $$ = $1->adopt($3); D($2); }
     | type_any           { $$ = (new AN(llvmParser, LLVM_TYPE_LIST))->adopt($1); };
extra_ellipsis: "," "..." { D($1); $$ = $2; } | { $$ = nullptr; };
_ellipsis: "..." | { $$ = nullptr; };



// Globals

global_def: LLVMTOK_GVAR "=" _linkage _preemption _visibility _dll_storage_class _thread_local _unnamed_addr _addrspace
            _externally_initialized global_or_constant type_any gdef_extras
            { D($2); $$ = new GlobalVarDef($1, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); }
          | LLVMTOK_GVAR "=" _linkage _preemption _visibility _dll_storage_class _thread_local _unnamed_addr _addrspace
            _externally_initialized global_or_constant constant gdef_extras
            { D($2); $$ = new GlobalVarDef($1, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13); };

_linkage: LLVMTOK_LINKAGE | { $$ = nullptr; };
_visibility: LLVMTOK_VISIBILITY | { $$ = nullptr; };
_dll_storage_class: LLVMTOK_DLLPORT | { $$ = nullptr; };
_thread_local: "thread_local" "(" LLVMTOK_THREAD_LOCAL_TYPE ")" { $$ = $1->adopt($3); D($2, $4); } | { $$ = nullptr; };
_addrspace: "addrspace" "(" LLVMTOK_DECIMAL ")" { $$ = $1->adopt($3); D($2, $4); } | { $$ = nullptr; };
_externally_initialized: LLVMTOK_EXTERNALLY_INITIALIZED | { $$ = nullptr; };
global_or_constant: "global" | "constant";
gdef_extras: gdef_extras "," section { $$ = $1->adopt($3); D($2); }
           | gdef_extras "," comdat  { $$ = $1->adopt($3); D($2); }
           | gdef_extras "," LLVMTOK_ALIGN LLVMTOK_DECIMAL { $$ = $1->adopt($3->adopt($4)); D($2); }
           | gdef_extras cdebug { $$ = $1->adopt($2); }
           | { $$ = new AN(llvmParser, LLVM_GDEF_EXTRAS); };
section: LLVMTOK_SECTION LLVMTOK_STRING       { $$ = $1->adopt($2); };
comdat:  LLVMTOK_COMDAT "(" any_ident ")" { $$ = $1->adopt($3); D($2, $4); }
      |  LLVMTOK_COMDAT;



// Functions

function_header: _linkage _preemption _visibility _dll_storage_class _cconv _retattrs type_any function_name "("
                 function_args ")" _unnamed_addr _fnattrs _header_section _header_comdat _header_align _personality _debug
                 { $$ = new FunctionHeader($1, $2, $3, $4, $5, $6, $7, $8, $10, $12, $13, $14, $15, $16, $17, $18); D($9, $11); };
_preemption: preemption | { $$ = nullptr; };
preemption: "dso_preemptable" | "dso_local";
_retattrs: _retattrs retattr { $1->adopt($2); } | { $$ = new AN(llvmParser, LLVM_RETATTR_LIST); };
function_args: function_types "," "..." { $$ = new FunctionArgs($1, true); D($2, $3); }
             | function_types { $$ = new FunctionArgs($1, false); }
             | "..." { $$ = new FunctionArgs(nullptr, true); }
             | { $$ = new FunctionArgs(nullptr, false); };
function_types: function_types "," function_type { $1->adopt($3); D($2); } | function_type { $$ = (new AN(llvmParser, LLVM_FUNCTION_TYPE_LIST))->adopt($1); };
function_type: type_any parattr_list _variable { $$ = $1->adopt({$2, $3}); };
             | type_any _variable { $$ = $1->adopt({new AN(llvmParser, LLVM_PARATTR_LIST), $2}); };
_cconv: LLVMTOK_CCONV | { $$ = nullptr; };
_fnattrs: "#" LLVMTOK_DECIMAL { $$ = $2; D($1); } | fnattr_list;
fnattr_list: fnattr_list basic_fnattr { $1->adopt($2); } | { $$ = new AN(llvmParser, LLVM_FNATTR_LIST); };
_header_align: "align" LLVMTOK_DECIMAL { $1->adopt($2); } | { $$ = nullptr; };
_unnamed_addr: LLVMTOK_UNNAMED_ADDR_TYPE | { $$ = nullptr; };
_variable: LLVMTOK_PVAR | { $$ = nullptr; };
variable: LLVMTOK_PVAR | LLVMTOK_GVAR;
_personality: "personality" constant { $1->adopt($2); } | { $$ = nullptr; };
_header_section: "section" LLVMTOK_STRING { $1->adopt($2); } | { $$ = nullptr; };
_header_comdat: "comdat" any_ident { $1->adopt($2); }
              | "comdat" "(" any_ident ")" { $1->adopt($3); D($2, $4); }
              | "comdat"
              | { $$ = nullptr; };

function_def: "define" function_header "{" function_lines "}" { $$ = (new AN(llvmParser, LLVM_FUNCTION_DEF, $2->lexerInfo))->adopt({$2, $4}); D($1, $3, $5); };
function_lines: function_lines statement { $1->adopt($2); } | { $$ = new AN(llvmParser, LLVM_STATEMENTS); };
statement: label_statement | instruction | bb_header;
label_statement: ident ":" { $1->symbol = LLVM_LABEL; D($2); };
bb_header: LLVMTOK_LABEL_COMMENT LLVMTOK_DECIMAL LLVMTOK_PREDS_COMMENT preds_list LLVMTOK_NEWLINE { $$ = new HeaderNode(false, $1->adopt({$2, $3, $4})); D($5); }
         | simple_label LLVMTOK_PREDS_COMMENT preds_list LLVMTOK_NEWLINE { $$ = new HeaderNode(true, $1->adopt({$2, $3})); D($4); }
         | simple_label LLVMTOK_NO_PREDS { $$ = new HeaderNode($1); D($2); };
preds_list: preds_list LLVMTOK_PVAR { $1->adopt($2); }
          | { $$ = new AN(llvmParser, LLVM_PREDS_LIST); };
simple_label: label_statement | LLVMTOK_STRING ":" { D($2); };

// Aliases

alias_def: LLVMTOK_GVAR "=" _alias_linkage _preemption _visibility _dll_storage_class _thread_local _unnamed_addr
           "alias" type_any "," alias_def_right
           { $$ = new AliasDef($1, $3, $4, $5, $6, $7, $8, $10, $12); D($2, $9, $11); };
alias_def_right: constant | conversion_expr;
_alias_linkage: LLVMTOK_LINKAGE | { $$ = nullptr; };



// Instructions

instruction: i_select | i_alloca | i_store | i_store_atomic | i_load | i_load_atomic | i_icmp | i_br_uncond | i_br_cond
           | i_call | i_getelementptr | i_ret | i_invoke | i_landingpad | i_convert | i_basicmath | i_phi | i_div
           | i_rem | i_logic | i_switch | i_shr | i_fmath | i_extractvalue | i_insertvalue | i_resume | i_unreachable
           | i_dbg | i_assume | i_freeze;

unibangs: unibangs unibang { $$ = $1->adopt($2); } | { $$ = new AN(llvmParser, LLVM_BANGS); }; // applicable to all instructions
unibang: "," "!prof"          LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!callees"       LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!llvm.loop"     LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!heapallocsite" LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!range"         LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!tbaa.struct"   LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!noalias"       LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | "," "!alias.scope"   LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
       | tbaa
       | cdebug;

i_select: result "select" fastmath_flags type_any value "," type_any value "," type_any value unibangs
          { auto loc = $1->location; $$ = (new SelectNode($1, $3, $4, $5, $7, $8, $10, $11, $12))->locate(loc); D($2, $6, $9); };

i_alloca: result "alloca" _inalloca type_any _alloca_numelements _align _alloca_addrspace unibangs
          { auto loc = $1->location; $$ = (new AllocaNode($1, $3, $4, $5, $6, $7, $8))->locate(loc); D($2); };
_inalloca: "inalloca" | { $$ = nullptr; };
_alloca_numelements: "," type_any value { $$ = $1->adopt({$2, $3}); } | { $$ = nullptr; };
_align: align | { $$ = nullptr; };
align: "," "align" LLVMTOK_DECIMAL { $$ = $3; D($1, $2); };
_alloca_addrspace: "," "addrspace" "(" LLVMTOK_DECIMAL ")" { $$ = $4; D($1, $2, $3, $5); } | { $$ = nullptr; };

i_store: "store" _volatile constant "," constant _align store_bangs
         { $$ = (new StoreNode($2, $3, $5, $6, $7))->locate($1); D($1, $4); };
_volatile: LLVMTOK_VOLATILE | { $$ = nullptr; };
store_bangs: store_bangs invariant_group { $$ = $1->adopt($2); }
           | store_bangs nontemporal     { $$ = $1->adopt($2); }
           | store_bangs unibang         { $$ = $1->adopt($2); }
           | { $$ = new AN(llvmParser, LLVM_BANGS); };
nontemporal: "," "!nontemporal" LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); };
invariant_group: "," "!invariant.group" LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); }
tbaa:  "," "!tbaa" LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); };

i_store_atomic: "store" "atomic" _volatile constant "," constant _syncscope LLVMTOK_ORDERING _align store_bangs
                { $$ = (new StoreNode($3, $4, $6, $7, $8, $9, $10))->locate($1); D($1, $2, $5); };
_syncscope: "syncscope" "(" LLVMTOK_STRING ")" { $$ = $3; D($1, $2, $4); } | { $$ = nullptr; };

i_load: result "load" _volatile type_any "," constant _align load_bangs
        { auto loc = $1->location; $$ = (new LoadNode($1, $3, $4, $6, $7, $8))->locate(loc); D($2, $5); };
// TODO: what is the actual form of the arguments for these?
load_bangs: load_bangs invariant_load          { $$ = $1->adopt($2); }
          | load_bangs nonnull                 { $$ = $1->adopt($2); }
          | load_bangs dereferenceable         { $$ = $1->adopt($2); }
          | load_bangs dereferenceable_or_null { $$ = $1->adopt($2); }
          | load_bangs bang_align              { $$ = $1->adopt($2); }
          | load_bangs nontemporal             { $$ = $1->adopt($2); }
          | load_bangs invariant_group         { $$ = $1->adopt($2); }
          | load_bangs unibang                 { $$ = $1->adopt($2); }
          | { $$ = new AN(llvmParser, LLVM_BANGS); };
invariant_load:          "," "!invariant.load"          LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); };
nonnull:                 "," "!nonnull"                 LLVMTOK_INTBANG { $$ = $2->adopt($3); D($1); };
dereferenceable:         "," "!dereferenceable"         metabang    { $$ = $2->adopt($3); D($1); };
dereferenceable_or_null: "," "!dereferenceable_or_null" metabang    { $$ = $2->adopt($3); D($1); };
bang_align:              "," "!align"                   metabang    { $$ = $2->adopt($3); D($1); };

i_load_atomic: result "load" "atomic" _volatile type_any "," constant _syncscope LLVMTOK_ORDERING align load_bangs
               { auto loc = $1->location; $$ = (new LoadNode($1, $4, $5, $7, $8, $9, $10, $11))->locate(loc); D($2, $3, $6); };

i_icmp: result "icmp" LLVMTOK_ICMP_COND constant "," constant_right unibangs
        { auto loc = $1->location; $$ = (new IcmpNode($1, $3, $4, $6, $7))->locate(loc); D($2, $5); };

i_br_uncond: "br" "label" LLVMTOK_PVAR unibangs { $$ = (new BrUncondNode($3, $4))->locate($1); D($1, $2); };

i_br_cond: "br" constant "," label "," label unibangs { $$ = (new BrCondNode($2, $4, $6, $7))->locate($1); D($1, $3, $5); };
label: "label" LLVMTOK_PVAR { $$ = $2; D($1); };

i_call: _result _tail "call" fastmath_flags _cconv _retattrs _addrspace type_nonfn _args conversion_expr "(" _constants ")" call_attrs unibangs
        { auto loc = L({$1, $2, $3}); $$ = (new CallNode($1, $2, $4, $5, $6, $7, $8, $9, $10, $12, $14, $15))->locate(loc); D($3, $11, $13); }
      | _result _tail "call" fastmath_flags _cconv _retattrs _addrspace type_nonfn _args function_name "(" _constants ")" call_attrs unibangs
        { auto loc = L({$1, $2, $3}); $$ = (new CallNode($1, $2, $4, $5, $6, $7, $8, $9, $10, $12, $14, $15))->locate(loc); D($3, $11, $13); }
      | _result _tail "call" _retattrs type_nonfn _args "asm" _sideeffect _alignstack _inteldialect LLVMTOK_STRING "," LLVMTOK_STRING "(" _constants ")" call_attrs _cdebug _srcloc unibangs
        { auto loc = L({$1, $3, $4}); $$ = (new AsmNode($1, $4, $5, $6, $8, $9, $10, $11, $13, $15, $17, $19, $20))->locate(loc)->setDebug($18); D($3, $7, $12, $14, $16); };
_result: result | { $$ = nullptr; };
result: LLVMTOK_PVAR "=" { D($2); };
_args: args | { $$ = nullptr; };
args: "(" types extra_ellipsis ")" { $1->adopt({$2, $3}); D($4); }
    | "("            _ellipsis ")" { $1->adopt($2);       D($3); };
_tail: LLVMTOK_TAIL | { $$ = nullptr; };
function_name: LLVMTOK_GVAR | LLVMTOK_PVAR | any_ident;
_constants: constants | { $$ = new AN(llvmParser, LLVM_CONSTANT_LIST); };
constants: constants "," constant { $1->adopt($3); D($2); }
         | constant               { $$ = (new AN(llvmParser, LLVM_CONSTANT_LIST))->adopt($1); };
call_attrs: call_attrs "#" LLVMTOK_DECIMAL { $1->adopt($3); D($2); } | { $$ = new AN(llvmParser, LLVM_ATTRIBUTE_LIST); };
_sideeffect:   LLVMTOK_SIDEEFFECT   | { $$ = nullptr; };
_alignstack:   LLVMTOK_ALIGNSTACK   | { $$ = nullptr; };
_inteldialect: LLVMTOK_INTELDIALECT | { $$ = nullptr; };
_srcloc: srcloc | { $$ = nullptr; };
srcloc: "," "!srcloc" LLVMTOK_INTBANG { $$ = $3; D($1, $2); };

i_dbg: "call" "void" dbg_type "(" "metadata" constant "," "metadata" LLVMTOK_INTBANG "," "metadata" anybang ")" _fnattrs unibangs
       { $$ = (new DbgIntrinsicNode($3, $6, $9, $12, $15))->locate($1); D($1, $2, $4, $5, $7, $8, $10, $11, $13, $14); }
     | "call" "void" dbg_type "(" "metadata" anybang "," "metadata" LLVMTOK_INTBANG "," "metadata" anybang ")" _fnattrs unibangs
       { $$ = $3; D($1, $2, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15); }
     | "call" "void" "@llvm.dbg.label" "(" "metadata" LLVMTOK_INTBANG ")" _fnattrs unibangs
       { $$ = $3; D($1, $2, $4, $5, $6, $7, $8, $9); }
     | LLVMTOK_TAIL "call" "void" "@llvm.experimental.noalias.scope.decl" "(" "metadata" LLVMTOK_INTBANG ")" _fnattrs unibangs
       { $$ = $4; D($1, $2, $3, $5, $6, $7, $8, $9, $10); }
     | "call" "void" "@llvm.experimental.noalias.scope.decl" "(" "metadata" LLVMTOK_INTBANG ")" _fnattrs unibangs
       { $$ = $3; D($1, $2, $4, $5, $6, $7, $8, $9); };
dbg_type: "@llvm.dbg.value" | "@llvm.dbg.declare";
anybang: LLVMTOK_INTBANG
       | "!" any_ident { $$ = $1->adopt($2); }
       | diexpression
       | diarglist;

// Example: call void @llvm.assume(i1 true) [ "align"(i8* %10, i64 %9) ]
i_assume: "call" "void" "@llvm.assume" "(" LLVMTOK_INTTYPE LLVMTOK_BOOL ")" "[" assume_list "]" _cdebug
          { $$ = $3; D($1, $2, $4, $5, $6, $7, $8, $9, $10, $11); };
assume_list: assume_list "," LLVMTOK_STRING "(" constants ")" { $$ = nullptr; D($1, $2, $3, $4, $5, $6); }
           | LLVMTOK_STRING "(" constants ")"                 { $$ = nullptr; D($1, $2, $3, $4); };

diexpression: "!DIExpression" "(" diexpression_list ")" { $$ = $1->adopt($3); D($2, $4); }
            | "!DIExpression" "(" ")" { $$ = $1; D($2, $3); };
diexpression_list: diexpression_list "," diexpression_item { $$ = $1->adopt($3); D($2); }
                 | diexpression_item { $$ = (new AN(llvmParser, LLVM_DIEXPRESSION_LIST))->adopt($1); };
diexpression_item: any_ident | LLVMTOK_DECIMAL;

diarglist: "!DIArgList" "(" constant "," constant ")" { $$ = $1->adopt({$3, $5}); D($2, $4, $6); };

i_getelementptr: result "getelementptr" _inbounds type_any "," constant gep_indices unibangs
               { auto loc = $1->location; $$ = (new GetelementptrNode($1, $3, $4, $6, $7, $8))->locate(loc); D($2, $5); };
// TODO: vectors. <result> = getelementptr <ty>, <ptr vector> <ptrval>, [inrange] <vector index type> <idx>
gep_indices: { $$ = new AN(llvmParser, LLVM_INDEX_LIST); }
           | gep_indices "," _inrange type_any gep_index { $1->adopt($2->adopt({$4, $5, $3})); };
gep_index: LLVMTOK_DECIMAL | LLVMTOK_PVAR;
_inrange: LLVMTOK_INRANGE | { $$ = nullptr; };

i_ret: "ret" type_nonvoid value unibangs { $$ = (new RetNode($2, $3, $4))->locate($1); D($1); }
     | "ret" "void" unibangs { $$ = new RetNode($3); D($1, $2); };

i_invoke: _result "invoke" _cconv _retattrs _addrspace type_any _args conversion_expr "(" _constants ")" call_attrs unibangs
          /* TODO: operand bundles */ "to" label "unwind" label
          { auto loc = L({$1, $2}); $$ = (new InvokeNode($1, $3, $4, $5, $6, $7, $8, $10, $12, $14, $16, $17))->locate(loc); D($2, $9, $11, $13, $15); };
        | _result "invoke" _cconv _retattrs _addrspace type_any _args function_name "(" _constants ")" call_attrs unibangs
          /* TODO: operand bundles */ "to" label "unwind" label
          { auto loc = L({$1, $2}); $$ = (new InvokeNode($1, $3, $4, $5, $6, $7, $8, $10, $12, $14, $16, $17))->locate(loc); D($2, $9, $11, $13, $15); };

i_landingpad: result "landingpad" type_any clauses            unibangs { auto loc = $1->location; $$ = (new LandingpadNode($1, $3, $4, $5, false))->locate(loc); D($2);     }
            | result "landingpad" type_any "cleanup" _clauses unibangs { auto loc = $1->location; $$ = (new LandingpadNode($1, $3, $5, $6, true))->locate(loc);  D($2, $4); };
_clauses: clauses | { $$ = new AN(llvmParser, LLVM_CLAUSES); };
clauses: clauses clause { $1->adopt($2); } | clause { $$ = (new AN(llvmParser, LLVM_CLAUSES))->adopt($1); };
clause: "catch" type_any value { $1->adopt({$2, $3}); }
      | "filter" array     { $1->adopt($2); };

i_convert: result LLVMTOK_CONV_OP type_any value "to" type_any unibangs
           { auto loc = $1->location; $$ = (new ConversionNode($1, $2, $3, $4, $6, $7))->locate(loc); D($5); };

addsubmulshl: "add" | "sub" | "mul" | "shl";
i_basicmath: result addsubmulshl type_any value "," value             unibangs { auto loc = $1->location; $$ = (new BasicMathNode($1, $2, false, false, $3, $4, $6, $7))->locate(loc); D($5); }
           | result addsubmulshl "nuw" type_any value "," value       unibangs { auto loc = $1->location; $$ = (new BasicMathNode($1, $2, true, false, $4, $5, $7, $8))->locate(loc); D($3, $6); }
           | result addsubmulshl "nsw" type_any value "," value       unibangs { auto loc = $1->location; $$ = (new BasicMathNode($1, $2, false, true, $4, $5, $7, $8))->locate(loc); D($3, $6); }
           | result addsubmulshl "nuw" "nsw" type_any value "," value unibangs { auto loc = $1->location; $$ = (new BasicMathNode($1, $2, true, true, $5, $6, $8, $9))->locate(loc); D($3, $4, $7); }
           | result addsubmulshl "nsw" "nuw" type_any value "," value unibangs { auto loc = $1->location; $$ = (new BasicMathNode($1, $2, true, true, $5, $6, $8, $9))->locate(loc); D($3, $4, $7); };

i_phi: result "phi" fastmath_flags type_any phi_list unibangs
       { auto loc = $1->location; $$ = (new PhiNode($1, $3, $4, $5, $6))->locate(loc); D($2); };
phi_list: phi_list "," phi_pair { $1->adopt($3); D($2); } | phi_pair { $$ = new AN(llvmParser, LLVM_PHI_PAIR, $1); };
phi_pair: "[" value "," LLVMTOK_PVAR "]" { $1->adopt({$2, $4}); D($3, $5); };

i_div: result LLVMTOK_DIV _exact type_any value "," value unibangs
       { $$ = new DivNode($1, $2, $3, $4, $5, $7, $8); D($6); };

i_rem: result LLVMTOK_REM _exact type_any value "," value unibangs
       { $$ = new RemNode($1, $2, $3, $4, $5, $7, $8); D($6); };

i_logic: result LLVMTOK_LOGIC constant "," constant_right unibangs
         { $$ = new LogicNode($1, $2, $3, $5, $6); D($4); };

i_switch: "switch" LLVMTOK_INTTYPE value "," label "[" switch_list "]" unibangs
          { $$ = (new SwitchNode($2, $3, $5, $7, $9))->locate($1); D($1, $4, $6, $8); };
switch_list: switch_list switch_pair { $1->adopt($2); } | switch_pair { $$ = new AN(llvmParser, LLVM_SWITCH_LIST, $1); };
switch_pair: LLVMTOK_INTTYPE value "," label { $$ = $3->adopt({$1, $2, $4}); };

i_shr: result LLVMTOK_SHR _exact type_any value "," value unibangs
       { $$ = new ShrNode($1, $2, $3, $4, $5, $7, $8); D($6); };
_exact: "exact" | { $$ = nullptr; };

i_fmath: result LLVMTOK_FMATH fastmath_flags type_any value "," value unibangs
         { $$ = new FMathNode($1, $2, $3, $4, $5, $7, $8); D($6); };

i_extractvalue: result "extractvalue" type_any value decimals unibangs
                { $$ = new ExtractValueNode($1, $3, $4, $5, $6); D($2); };
decimals: decimals "," LLVMTOK_DECIMAL { $1->adopt($3); D($2); }
        | { $$ = new AN(llvmParser, LLVM_DECIMAL_LIST); }

i_insertvalue: result "insertvalue" type_any value "," type_any value decimals unibangs
               { $$ = new InsertValueNode($1, $3, $4, $6, $7, $8, $9); D($2, $5); };

i_resume: "resume" type_any value unibangs
          { $$ = new ResumeNode($2, $3, $4); D($1); };

i_unreachable: "unreachable" _cdebug
               { $$ = (new UnreachableNode())->setDebug($2); D($1); };

i_freeze: result "freeze" type_any value unibangs { $$ = new FreezeNode($1, $3, $4, $5); D($2); };

// Constants

constant: type_any parattr_list constant_right { $$ = (new AN(llvmParser, LLVM_CONSTANT))->adopt({$1, $3, $2}); }
        | type_any constant_right              { $$ = (new AN(llvmParser, LLVM_CONSTANT))->adopt({$1, $2}); }
        | LLVMTOK_GVAR                         { $$ = (new AN(llvmParser, LLVM_CONSTANT))->adopt($1); };
constant_right: operand | conversion_expr | icmp_expr | logic_expr;
parattr_list: parattr_list parattr { $$ = $1->adopt($2); }
            | parattr              { $$ = (new AN(llvmParser, LLVM_PARATTR_LIST))->adopt($1, true); };
parattr: LLVMTOK_PARATTR
       | parattr_simple                 { $1->symbol = LLVMTOK_PARATTR;  }
       | LLVMTOK_TYPED_PARATTR "(" type_any ")" { $$ = $1->adopt($3); D($2, $4); }
       | "inalloca" "(" type_any ")" { $$ = $1->adopt($3); D($2, $4); }
       | retattr
       | "writeonly";
parattr_simple: LLVMTOK_INALLOCA | LLVMTOK_READONLY | LLVMTOK_READNONE;
retattr: LLVMTOK_RETATTR
       | LLVMTOK_DEREF "(" LLVMTOK_DECIMAL ")" { $$ = $1->adopt($3); D($2, $4); }
       | "align" "(" LLVMTOK_DECIMAL ")"       { $$ = $1->adopt($3); D($2, $4); }
       | "align" LLVMTOK_DECIMAL               { $$ = $1->adopt($2); }
       | "noundef";
operand: LLVMTOK_PVAR | LLVMTOK_DECIMAL | LLVMTOK_HEXADECIMAL | LLVMTOK_GVAR | LLVMTOK_BOOL | LLVMTOK_FLOATING | struct
       | bare_array   | LLVMTOK_CSTRING | getelementptr_expr  | "null" | "zeroinitializer"  | "undef" | "poison";
conversion_expr: LLVMTOK_CONV_OP constant "to" type_any         { $$ = (new AN(llvmParser, LLVM_CONVERSION_EXPR, $1->lexerInfo))->adopt({$2, $4})->locate($1); D($1, $3); }
               | LLVMTOK_CONV_OP "(" constant "to" type_any ")" { $$ = (new AN(llvmParser, LLVM_CONVERSION_EXPR, $1->lexerInfo))->adopt({$3, $5})->locate($1); D($1, $2, $4, $6); };
icmp_expr: "icmp" LLVMTOK_ICMP_COND "(" constant "," constant ")" { $$ = $1->adopt({$2, $4, $6}); D($3, $5, $7); };
logic_expr: LLVMTOK_LOGIC "(" constant "," constant ")" { $$ = $1->adopt({$3, $5}); D($2, $4, $6); };

getelementptr_expr: "getelementptr" _inbounds "(" type_any "," type_ptr gepexpr_operand decimal_pairs ")"
                    { $1->adopt({$4, $6, $7, $8, $2}); D($3, $5, $9); };
_inbounds: LLVMTOK_INBOUNDS | { $$ = nullptr; };
decimal_pairs: decimal_pairs "," _inrange LLVMTOK_INTTYPE LLVMTOK_DECIMAL { $1->adopt($2->adopt({$4, $5, $3})); }
             | { $$ = new AN(llvmParser, LLVM_DECIMAL_PAIR_LIST); };
gepexpr_operand: variable | getelementptr_expr | conversion_expr { $$ = ignoreConversion($1); };

%%

#pragma GCC diagnostic pop

const char * LL2W::Parser::getNameLLVM(int symbol) {
    return yytname[YYTRANSLATE(symbol)];
}
