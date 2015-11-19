/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_PHASE4_PARSER_HPP_INCLUDED
# define YY_YY_PHASE4_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    STRING = 259,
    IDENTIFIER = 260,
    REALNUMBER = 261,
    KEYWORD_IF = 262,
    KEYWORD_ELSE = 263,
    KEYWORD_WHILE = 264,
    KEYWORD_FOR = 265,
    KEYWORD_FUNCTION = 266,
    KEYWORD_RETURN = 267,
    KEYWORD_BREAK = 268,
    KEYWORD_CONTINUE = 269,
    KEYWORD_AND = 270,
    KEYWORD_NOT = 271,
    KEYWORD_OR = 272,
    KEYWORD_LOCAL = 273,
    KEYWORD_TRUE = 274,
    KEYWORD_FALSE = 275,
    KEYWORD_NIL = 276,
    NOKEY = 277,
    ASSIGN = 278,
    PLUS = 279,
    MINUS = 280,
    MULTIPLY = 281,
    DIVIDE = 282,
    MODULO = 283,
    EQUAL = 284,
    NOT_EQUAL = 285,
    INCREMENT = 286,
    DECREMENT = 287,
    LESS_THAN = 288,
    GREATER_THAN = 289,
    LESS_EQUAL = 290,
    GREATER_EQUAL = 291,
    LEFT_BRACE = 292,
    RIGHT_BRACE = 293,
    LEFT_BRACKET = 294,
    RIGHT_BRACKET = 295,
    LEFT_PARENTHESIS = 296,
    RIGHT_PARENTHESIS = 297,
    SEMICOLON = 298,
    COMMA = 299,
    COLON = 300,
    DOUBLE_COLON = 301,
    DOT = 302,
    DOUBLE_DOT = 303,
    INTCONST = 304,
    REALCONST = 305,
    ID = 306,
    LINECOMMENT = 307,
    COMMENT = 308,
    NESTED_COMMENT = 309,
    CLOSE_COMMENT = 310,
    UNDEFINED = 311,
    UMINUS = 312
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define STRING 259
#define IDENTIFIER 260
#define REALNUMBER 261
#define KEYWORD_IF 262
#define KEYWORD_ELSE 263
#define KEYWORD_WHILE 264
#define KEYWORD_FOR 265
#define KEYWORD_FUNCTION 266
#define KEYWORD_RETURN 267
#define KEYWORD_BREAK 268
#define KEYWORD_CONTINUE 269
#define KEYWORD_AND 270
#define KEYWORD_NOT 271
#define KEYWORD_OR 272
#define KEYWORD_LOCAL 273
#define KEYWORD_TRUE 274
#define KEYWORD_FALSE 275
#define KEYWORD_NIL 276
#define NOKEY 277
#define ASSIGN 278
#define PLUS 279
#define MINUS 280
#define MULTIPLY 281
#define DIVIDE 282
#define MODULO 283
#define EQUAL 284
#define NOT_EQUAL 285
#define INCREMENT 286
#define DECREMENT 287
#define LESS_THAN 288
#define GREATER_THAN 289
#define LESS_EQUAL 290
#define GREATER_EQUAL 291
#define LEFT_BRACE 292
#define RIGHT_BRACE 293
#define LEFT_BRACKET 294
#define RIGHT_BRACKET 295
#define LEFT_PARENTHESIS 296
#define RIGHT_PARENTHESIS 297
#define SEMICOLON 298
#define COMMA 299
#define COLON 300
#define DOUBLE_COLON 301
#define DOT 302
#define DOUBLE_DOT 303
#define INTCONST 304
#define REALCONST 305
#define ID 306
#define LINECOMMENT 307
#define COMMENT 308
#define NESTED_COMMENT 309
#define CLOSE_COMMENT 310
#define UNDEFINED 311
#define UMINUS 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 117 "phase4/parser.yy" /* yacc.c:1909  */


	int intvalue;
	double dvalue;
	char* strvalue;
	struct expre* exprvalue;
	struct symT * symvalue;
	int isNormalcall=0;
	struct expre* start;
	int startHere;
	int break_index;
	int cont_index;
	struct forstruct* fordata;
	struct bc_indexes * indexes;
	

#line 185 "phase4/parser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PHASE4_PARSER_HPP_INCLUDED  */
