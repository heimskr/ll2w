/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_WASM_INCLUDE_WASMPARSE_H_INCLUDED
# define YY_WASM_INCLUDE_WASMPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef WASMDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define WASMDEBUG 1
#  else
#   define WASMDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define WASMDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined WASMDEBUG */
#if WASMDEBUG
extern int wasmdebug;
#endif

/* Token kinds.  */
#ifndef WASMTOKENTYPE
# define WASMTOKENTYPE
  enum wasmtokentype
  {
    WASMEMPTY = -2,
    WASMEOF = 0,                   /* "end of file"  */
    WASMerror = 256,               /* error  */
    WASMUNDEF = 257,               /* "invalid token"  */
    WASMTOK_ROOT = 258,            /* WASMTOK_ROOT  */
    WASMTOK_IDENT = 259,           /* WASMTOK_IDENT  */
    WASMTOK_BANG = 260,            /* "!"  */
    WASMTOK_EQUALS = 261,          /* "="  */
    WASMTOK_DOT = 262,             /* "."  */
    WASMTOK_TARGET = 263,          /* "target"  */
    WASMTOK_DATALAYOUT = 264,      /* "datalayout"  */
    WASMTOK_TRIPLE = 265,          /* "triple"  */
    WASMTOK_DISTINCT = 266,        /* "distinct"  */
    WASMTOK_METADATA_OPEN = 267,   /* "!{"  */
    WASMTOK_LCURLY = 268,          /* "{"  */
    WASMTOK_RCURLY = 269,          /* "}"  */
    WASMTOK_COMMA = 270,           /* ","  */
    WASMTOK_NULL = 271,            /* "null"  */
    WASMTOK_PERCENT = 272,         /* "%"  */
    WASMTOK_AT = 273,              /* "@"  */
    WASMTOK_LPAR = 274,            /* "("  */
    WASMTOK_RPAR = 275,            /* ")"  */
    WASMTOK_LSQUARE = 276,         /* "["  */
    WASMTOK_RSQUARE = 277,         /* "]"  */
    WASMTOK_X = 278,               /* "x"  */
    WASMTOK_LANGLE = 279,          /* "<"  */
    WASMTOK_RANGLE = 280,          /* ">"  */
    WASMTOK_VOID = 281,            /* "void"  */
    WASMTOK_ELLIPSIS = 282,        /* "..."  */
    WASMTOK_ASTERISK = 283,        /* "*"  */
    WASMTOK_HASH = 284,            /* "#"  */
    WASMTOK_COLON = 285,           /* ":"  */
    WASMTOK_UNDEF = 286,           /* "undef"  */
    WASMTOK_NEWLINE = 287,         /* WASMTOK_NEWLINE  */
    WASMTOK_TO = 288,              /* "to"  */
    WASMTOK_THREAD_LOCAL = 289,    /* "thread_local"  */
    WASMTOK_THREAD_LOCAL_TYPE = 290, /* WASMTOK_THREAD_LOCAL_TYPE  */
    WASMTOK_LOCALDYNAMIC = 291,    /* "localdynamic"  */
    WASMTOK_INITIALEXEC = 292,     /* "initialexec"  */
    WASMTOK_LOCALEXEC = 293,       /* "localexec"  */
    WASMTOK_ADDRSPACE = 294,       /* "addrspace"  */
    WASMTOK_ZEROINITIALIZER = 295, /* "zeroinitializer"  */
    WASMTOK_EXTERNALLY_INITIALIZED = 296, /* "externally_initialized"  */
    WASMTOK_GLOBAL = 297,          /* "global"  */
    WASMTOK_WASM_CONSTANT = 298,   /* "constant"  */
    WASMTOK_SECTION = 299,         /* "section"  */
    WASMTOK_COMDAT = 300,          /* "comdat"  */
    WASMTOK_ALIGN = 301,           /* "align"  */
    WASMTOK_TYPE = 302,            /* "type"  */
    WASMTOK_OPAQUE = 303,          /* "opaque"  */
    WASMTOK_ATTRIBUTES = 304,      /* "attributes"  */
    WASMTOK_ALIGNSTACK = 305,      /* "alignstack"  */
    WASMTOK_ALLOCSIZE = 306,       /* "allocsize"  */
    WASMTOK_PATCHABLE_PROLOGUE = 307, /* "patchable-function=\"prologue-short-redirect\""  */
    WASMTOK_READONLY = 308,        /* "readonly"  */
    WASMTOK_READNONE = 309,        /* "readnone"  */
    WASMTOK_DECLARE = 310,         /* "declare"  */
    WASMTOK_DEFINE = 311,          /* "define"  */
    WASMTOK_SELECT = 312,          /* "select"  */
    WASMTOK_ALLOCA = 313,          /* "alloca"  */
    WASMTOK_INALLOCA = 314,        /* "inalloca"  */
    WASMTOK_STORE = 315,           /* "store"  */
    WASMTOK_LOAD = 316,            /* "load"  */
    WASMTOK_VOLATILE = 317,        /* "volatile"  */
    WASMTOK_INVARIANT_GROUP = 318, /* "!invariant.group"  */
    WASMTOK_INVARIANT_LOAD = 319,  /* "!invariant.load"  */
    WASMTOK_NONTEMPORAL = 320,     /* "!nontemporal"  */
    WASMTOK_NONNULL = 321,         /* "!nonnull"  */
    WASMTOK_DEREFERENCEABLE = 322, /* "!dereferenceable"  */
    WASMTOK_DEREFERENCEABLE_OR_NULL = 323, /* "!dereferenceable_or_null"  */
    WASMTOK_BANGALIGN = 324,       /* "!align"  */
    WASMTOK_SRCLOC = 325,          /* "!srcloc"  */
    WASMTOK_TBAA = 326,            /* "!tbaa"  */
    WASMTOK_PROF = 327,            /* "!prof"  */
    WASMTOK_CALLEES = 328,         /* "!callees"  */
    WASMTOK_SYNCSCOPE = 329,       /* "syncscope"  */
    WASMTOK_ATOMIC = 330,          /* "atomic"  */
    WASMTOK_ICMP = 331,            /* "icmp"  */
    WASMTOK_BR = 332,              /* "br"  */
    WASMTOK_LABEL = 333,           /* "label"  */
    WASMTOK_CALL = 334,            /* "call"  */
    WASMTOK_GETELEMENTPTR = 335,   /* "getelementptr"  */
    WASMTOK_INBOUNDS = 336,        /* "inbounds"  */
    WASMTOK_INRANGE = 337,         /* "inrange"  */
    WASMTOK_RET = 338,             /* "ret"  */
    WASMTOK_PERSONALITY = 339,     /* "personality"  */
    WASMTOK_INVOKE = 340,          /* "invoke"  */
    WASMTOK_UNWIND = 341,          /* "unwind"  */
    WASMTOK_CLEANUP = 342,         /* "cleanup"  */
    WASMTOK_CATCH = 343,           /* "catch"  */
    WASMTOK_LANDINGPAD = 344,      /* "landingpad"  */
    WASMTOK_EXTRACTVALUE = 345,    /* "extractvalue"  */
    WASMTOK_INSERTVALUE = 346,     /* "insertvalue"  */
    WASMTOK_RESUME = 347,          /* "resume"  */
    WASMTOK_FILTER = 348,          /* "filter"  */
    WASMTOK_BYVAL = 349,           /* "byval"  */
    WASMTOK_WRITEONLY = 350,       /* "writeonly"  */
    WASMTOK_NUW = 351,             /* "nuw"  */
    WASMTOK_NSW = 352,             /* "nsw"  */
    WASMTOK_ADD = 353,             /* "add"  */
    WASMTOK_SUB = 354,             /* "sub"  */
    WASMTOK_MUL = 355,             /* "mul"  */
    WASMTOK_SHL = 356,             /* "shl"  */
    WASMTOK_PHI = 357,             /* "phi"  */
    WASMTOK_SWITCH = 358,          /* "switch"  */
    WASMTOK_UNREACHABLE = 359,     /* "unreachable"  */
    WASMTOK_ASM = 360,             /* "asm"  */
    WASMTOK_SIDEEFFECT = 361,      /* "sideeffect"  */
    WASMTOK_INTELDIALECT = 362,    /* "inteldialect"  */
    WASMTOK_EXACT = 363,           /* "exact"  */
    WASMTOK_DSO_LOCAL = 364,       /* "dso_local"  */
    WASMTOK_DSO_PREEMPTABLE = 365, /* "dso_preemptable"  */
    WASM_CONSTANT = 366,           /* WASM_CONSTANT  */
    WASM_CONVERSION_EXPR = 367,    /* WASM_CONVERSION_EXPR  */
    WASM_INITIAL_VALUE_LIST = 368, /* WASM_INITIAL_VALUE_LIST  */
    WASM_ARRAYTYPE = 369,          /* WASM_ARRAYTYPE  */
    WASM_VECTORTYPE = 370,         /* WASM_VECTORTYPE  */
    WASM_POINTERTYPE = 371,        /* WASM_POINTERTYPE  */
    WASM_TYPE_LIST = 372,          /* WASM_TYPE_LIST  */
    WASM_FUNCTIONTYPE = 373,       /* WASM_FUNCTIONTYPE  */
    WASM_GDEF_EXTRAS = 374,        /* WASM_GDEF_EXTRAS  */
    WASM_STRUCTDEF = 375,          /* WASM_STRUCTDEF  */
    WASM_ATTRIBUTE_LIST = 376,     /* WASM_ATTRIBUTE_LIST  */
    WASM_RETATTR_LIST = 377,       /* WASM_RETATTR_LIST  */
    WASM_FNATTR_LIST = 378,        /* WASM_FNATTR_LIST  */
    WASM_FUNCTION_TYPE_LIST = 379, /* WASM_FUNCTION_TYPE_LIST  */
    WASM_PARATTR_LIST = 380,       /* WASM_PARATTR_LIST  */
    WASM_FUNCTION_HEADER = 381,    /* WASM_FUNCTION_HEADER  */
    WASM_FUNCTION_ARGS = 382,      /* WASM_FUNCTION_ARGS  */
    WASM_FUNCTION_DEF = 383,       /* WASM_FUNCTION_DEF  */
    WASM_STATEMENTS = 384,         /* WASM_STATEMENTS  */
    WASM_LABEL = 385,              /* WASM_LABEL  */
    WASM_INSTRUCTION = 386,        /* WASM_INSTRUCTION  */
    WASM_FASTMATH_FLAGS = 387,     /* WASM_FASTMATH_FLAGS  */
    WASM_VECTOR = 388,             /* WASM_VECTOR  */
    WASM_METADATA_LIST = 389,      /* WASM_METADATA_LIST  */
    WASM_PREDS_LIST = 390,         /* WASM_PREDS_LIST  */
    WASM_FNTYPE = 391,             /* WASM_FNTYPE  */
    WASM_CONSTANT_LIST = 392,      /* WASM_CONSTANT_LIST  */
    WASM_GETELEMENTPTR_EXPR = 393, /* WASM_GETELEMENTPTR_EXPR  */
    WASM_DECIMAL_LIST = 394,       /* WASM_DECIMAL_LIST  */
    WASM_INDEX_LIST = 395,         /* WASM_INDEX_LIST  */
    WASM_STRUCT_VALUE = 396,       /* WASM_STRUCT_VALUE  */
    WASM_VALUE_LIST = 397,         /* WASM_VALUE_LIST  */
    WASM_ARRAY_VALUE = 398,        /* WASM_ARRAY_VALUE  */
    WASM_CLAUSES = 399,            /* WASM_CLAUSES  */
    WASM_GLOBAL_DEF = 400,         /* WASM_GLOBAL_DEF  */
    WASM_PHI_PAIR = 401,           /* WASM_PHI_PAIR  */
    WASM_SWITCH_LIST = 402,        /* WASM_SWITCH_LIST  */
    WASM_BLOCKHEADER = 403,        /* WASM_BLOCKHEADER  */
    WASM_DECIMAL_PAIR_LIST = 404,  /* WASM_DECIMAL_PAIR_LIST  */
    WASM_BANGS = 405               /* WASM_BANGS  */
  };
  typedef enum wasmtokentype wasmtoken_kind_t;
#endif

/* Value type.  */
#if ! defined WASMSTYPE && ! defined WASMSTYPE_IS_DECLARED
typedef int WASMSTYPE;
# define WASMSTYPE_IS_TRIVIAL 1
# define WASMSTYPE_IS_DECLARED 1
#endif


extern WASMSTYPE wasmlval;

int wasmparse (void);

#endif /* !YY_WASM_INCLUDE_WASMPARSE_H_INCLUDED  */
