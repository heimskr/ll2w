/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_ROOT = 258,
     TOK_STRING = 259,
     TOK_PERCENTID = 260,
     TOK_INTTYPE = 261,
     TOK_INT_LITERAL = 262,
     TOK_IDENT = 263,
     TOK_DOTIDENT = 264,
     TOK_METADATA_LIST = 265,
     TOK_PARATTR = 266,
     TOK_CONSTANT = 267,
     TOK_SOURCE_FILENAME = 268,
     TOK_BANG = 269,
     TOK_EQUALS = 270,
     TOK_DOT = 271,
     TOK_TARGET = 272,
     TOK_DATALAYOUT = 273,
     TOK_TRIPLE = 274,
     TOK_DISTINCT = 275,
     TOK_METADATA_OPEN = 276,
     TOK_CURLYC = 277,
     TOK_COMMA = 278,
     TOK_NULL = 279
   };
#endif
/* Tokens.  */
#define TOK_ROOT 258
#define TOK_STRING 259
#define TOK_PERCENTID 260
#define TOK_INTTYPE 261
#define TOK_INT_LITERAL 262
#define TOK_IDENT 263
#define TOK_DOTIDENT 264
#define TOK_METADATA_LIST 265
#define TOK_PARATTR 266
#define TOK_CONSTANT 267
#define TOK_SOURCE_FILENAME 268
#define TOK_BANG 269
#define TOK_EQUALS 270
#define TOK_DOT 271
#define TOK_TARGET 272
#define TOK_DATALAYOUT 273
#define TOK_TRIPLE 274
#define TOK_DISTINCT 275
#define TOK_METADATA_OPEN 276
#define TOK_CURLYC 277
#define TOK_COMMA 278
#define TOK_NULL 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

