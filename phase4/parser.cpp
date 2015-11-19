/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "phase4/parser.yy" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "hash.h"
#include "intermediate.h"
#include "target.h"
#include <fstream>

#include "parser.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

/****************/
extern string blvr;
/****************/	
int Lval_used=0;     	
int is_function=0;	 	
int is_call=0;			
int is_funcall=0;		
int is_funcdef=0; 		// otan pianw funcdef prosoxi stou pou epsitrefei se zero san tin coca cola zero 
string functionName; 	//to function name 8a einai eite yytext eite to paragomeno apo tin sunartisi y=x;
///
string defaultName="_sysfuncName_"; //default pro8ema
int prefix_count=0; 	
bool autoName=false; 	//on when we need autoname (id_tmp = keno )
int illcount=0;
int idcount=0;
int templast=0;
int here=0;
extern string buff; 	// nomizw de to usarw
Symbol toAdd;
Symbol *s, *func1, *argcheck, *localcheck;
bool lvalfunc=false; 	// on when func is found as ID in  lval ID edw 8elei ligo debug
//std::ofstream outfile;

int yylex();
extern char *yytext;
extern int yylineno;
extern FILE* yyin;

extern vector<quad>		quadhead ;
extern unsigned int	total;
extern unsigned int 	currQuad;
extern string tempname;
extern unsigned int tempcounter;

extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset ;
extern unsigned int formalArgOffset ;
extern unsigned int scopeSpaceCounter;

extern vector <vector<Symbol>> Scopelist;
extern unordered_multimap<int,Symbol> Syriza;
list<int> assignParts;
list<string> functions;
vector<expr*> expr_list;
vector<int> breakvector;
vector<int> contvector;
stack <int> aerials;
stack <int> ownage;
vector <vector<int>> contMultiVector;
vector <vector<int>> breakMultiVector;
vector <vector<int>> trueMultiVector;
vector <vector<int>> falseMultiVector;
int vc=0;
int bc=0;
int cc=0;

//
int tracktrue,trackfalse;
//

typedef struct forstruct{
	int test;
	int enter;
}forstr;


typedef struct bc_indexes{
	int break_index=-1;
	int cont_index=-1;
}tf;

bool isLocalVar = nullptr;							//isLocalVar
expr *tmpsym;
expr * tmp, *tmpexpr;
bool uminusValid;

int maxFScope=0;								//might be boolean	deepestFunctionScope
int maxScope=0;									//deepestScope
int isLoop=0;									//might be boolean
int elist_start=0;

bool clearList= false;
bool isValid= true;

int yyerror(const char * yaccProvidedMessage);
struct forstruct *fortmp;
struct true_false_indexes *tftmp;
char* staurosDota;


#line 177 "phase4/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 117 "phase4/parser.yy" /* yacc.c:355  */


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
	

#line 348 "phase4/parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PHASE4_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 363 "phase4/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   680

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   165,   165,   166,   170,   206,   216,   224,   231,   243,
     266,   284,   298,   305,   312,   319,   358,   371,   383,   395,
     407,   419,   436,   455,   472,   489,   506,   524,   555,   635,
     653,   670,   691,   754,   788,   821,   854,   886,   895,  1007,
    1013,  1039,  1045,  1052,  1061,  1091,  1108,  1125,  1136,  1142,
    1148,  1150,  1155,  1164,  1177,  1193,  1201,  1211,  1220,  1227,
    1233,  1237,  1242,  1245,  1255,  1263,  1272,  1280,  1283,  1293,
    1297,  1292,  1320,  1362,  1371,  1378,  1388,  1411,  1434,  1437,
    1465,  1465,  1474,  1485,  1585,  1589,  1593,  1597,  1602,  1606,
    1617,  1655,  1667,  1680,  1698,  1710,  1727,  1744,  1769,  1778,
    1786,  1840,  1883,  1890,  1897,  1902
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "STRING", "IDENTIFIER",
  "REALNUMBER", "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_WHILE",
  "KEYWORD_FOR", "KEYWORD_FUNCTION", "KEYWORD_RETURN", "KEYWORD_BREAK",
  "KEYWORD_CONTINUE", "KEYWORD_AND", "KEYWORD_NOT", "KEYWORD_OR",
  "KEYWORD_LOCAL", "KEYWORD_TRUE", "KEYWORD_FALSE", "KEYWORD_NIL", "NOKEY",
  "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "EQUAL",
  "NOT_EQUAL", "INCREMENT", "DECREMENT", "LESS_THAN", "GREATER_THAN",
  "LESS_EQUAL", "GREATER_EQUAL", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS",
  "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT",
  "INTCONST", "REALCONST", "ID", "LINECOMMENT", "COMMENT",
  "NESTED_COMMENT", "CLOSE_COMMENT", "UNDEFINED", "UMINUS", "$accept",
  "program", "stmt", "expr", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "elist_tmp", "objectdef", "indexed", "indexedelemtmp", "indexedelem",
  "block", "$@1", "$@2", "block_stmt", "id_tmp", "idlist",
  "functionprefix", "funcargs", "$@3", "funcbody", "funcdef", "const",
  "ifprefix", "elseprefix", "ifstmt", "whilestart", "whilecond",
  "whileblock", "whilestmt", "Q", "R", "forstmt", "forprefix", "S", "L",
  "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

#define YYPACT_NINF -183

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-183)))

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-71)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     119,   -37,  -183,    -5,  -183,    -4,   -26,     3,     5,     8,
     332,   -12,  -183,  -183,  -183,   332,    -1,    -1,  -183,   260,
     296,  -183,     4,  -183,  -183,  -183,    60,   119,   404,  -183,
    -183,  -183,   -21,  -183,    20,  -183,  -183,    21,  -183,  -183,
     224,  -183,    22,  -183,  -183,  -183,  -183,  -183,   332,  -183,
    -183,  -183,  -183,   426,  -183,  -183,   631,  -183,  -183,    55,
      17,    20,    17,  -183,   332,   382,    28,    42,    39,   470,
      45,  -183,  -183,  -183,  -183,  -183,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,  -183,   332,  -183,
    -183,   332,   332,    37,    48,  -183,  -183,  -183,   332,   332,
      49,  -183,    53,    88,   332,   224,  -183,   492,   332,  -183,
      62,   173,   360,   332,  -183,  -183,  -183,    65,  -183,  -183,
      64,   332,   332,    67,    67,  -183,  -183,  -183,   644,   644,
     644,   644,   644,   644,   602,   536,    68,  -183,    66,   558,
      69,  -183,    58,  -183,  -183,  -183,   224,   514,  -183,  -183,
     332,  -183,  -183,    64,  -183,    74,   332,   382,    39,   332,
     631,   618,  -183,  -183,   332,  -183,  -183,  -183,   -28,  -183,
    -183,  -183,    70,  -183,   580,  -183,  -183,    75,    76,  -183,
      71,    82,  -183,  -183,  -183,  -183,  -183,  -183,   332,   224,
     448,  -183,  -183,  -183
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    86,     0,    94,     0,    75,     0,     0,     0,
       0,     0,    88,    89,    87,     0,     0,     0,    69,    60,
       0,    13,     0,    84,    85,    44,     0,     0,     0,    29,
      15,    37,    39,    47,    40,    41,    11,     0,    12,    43,
       0,     5,     0,     6,     7,   102,     8,    14,     0,    98,
      74,    79,   104,     0,     9,    10,    32,    45,    31,     0,
      33,     0,    35,    73,     0,    62,     0,     0,    67,     0,
       0,    46,     1,     2,   103,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,    34,
      36,     0,    60,     0,     0,    53,    55,    56,     0,    60,
       0,    80,     0,    92,     0,     0,    98,     0,    60,   105,
       0,     0,     0,     0,    59,    63,    64,     0,    65,    30,
      42,     0,     0,    16,    17,    18,    19,    20,    25,    26,
      23,    21,    24,    22,    38,     0,     0,    48,     0,     0,
       0,    50,    78,    82,    83,    91,     0,     0,    96,    97,
      60,    90,    99,     0,    72,     0,     0,    62,    67,    60,
      27,    28,    49,    57,    60,    51,    52,    76,     0,    93,
      95,    99,     0,    71,     0,    61,    66,     0,     0,    81,
       0,     0,   103,    68,    54,    58,    77,   102,     0,     0,
       0,   102,   101,   100
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,    89,   -25,    -7,  -183,  -183,  -183,    13,  -183,    16,
    -183,  -183,  -183,   -61,   -32,  -183,  -183,   -31,    19,    32,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,   -16,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,    35,   -29,
    -183,  -183,  -182,   -74,  -183
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      95,    96,    97,    66,   114,    35,    67,   118,    68,    36,
      63,   155,   111,    51,   168,    37,   102,   142,   144,    38,
      39,    40,   146,    41,    42,   105,   149,    43,   108,   172,
      44,    45,   106,   121,    46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   122,    88,    56,    70,   189,    47,     2,    58,   193,
      89,    90,    65,    69,   179,   103,   180,    11,    91,    10,
      92,    11,    12,    13,    14,    50,    93,    94,    15,    60,
      62,   136,    61,    61,    16,    17,    48,    49,   140,    57,
      59,   107,    19,   110,    20,    22,    52,   152,    54,    22,
      25,    55,    23,    24,    25,    71,    91,   112,    92,    98,
      72,    99,   101,   104,    93,    94,     6,   100,   115,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     148,   134,   116,   117,   135,    65,   154,   120,   137,   171,
      18,   139,    65,    78,    79,    80,   145,   147,   177,   138,
     141,    65,    64,   178,   153,   159,   157,   164,   188,   167,
     163,   166,   173,   182,   160,   161,    73,   184,   185,    -3,
       1,   169,   186,     2,   187,   175,     3,   176,     4,     5,
       6,     7,     8,     9,   143,    10,   158,    11,    12,    13,
      14,   150,   181,    65,    15,     0,     0,     0,     0,   174,
      16,    17,    65,     0,     0,     0,    18,    65,    19,     0,
      20,     0,    21,     0,   191,    22,     0,     0,    23,    24,
      25,     0,     0,     0,     1,     0,     0,     2,     0,     0,
       3,   190,     4,     5,     6,     7,     8,     9,     0,    10,
       0,    11,    12,    13,    14,     0,     0,     0,    15,     0,
       0,     0,     0,     0,    16,    17,     0,     0,     0,     0,
      18,   -70,    19,     0,    20,     0,    21,     0,     0,    22,
       0,     0,    23,    24,    25,     1,     0,     0,     2,     0,
       0,     3,     0,     4,     5,     6,     7,     8,     9,     0,
      10,     0,    11,    12,    13,    14,     0,     0,     0,    15,
       0,     0,     0,     0,     0,    16,    17,     0,     0,     0,
       0,    18,     0,    19,     2,    20,     0,    21,     0,     0,
      22,     0,     0,    23,    24,    25,    10,     0,    11,    12,
      13,    14,     0,     0,     0,    15,     0,     0,     0,     0,
       0,    16,    17,     0,     0,     0,     0,    64,     0,    19,
       2,    20,     0,     0,     0,     0,    22,     6,     0,    23,
      24,    25,    10,     0,    11,    12,    13,    14,     0,     0,
       0,    15,     0,     0,     0,     0,     0,    16,    17,     0,
       0,     0,     0,     0,     0,    19,     2,    20,     0,     0,
       0,     0,    22,     0,     0,    23,    24,    25,    10,     0,
      11,    12,    13,    14,     0,     0,     0,    15,     0,     0,
       0,     0,     0,    16,    17,     0,     0,     0,     0,     0,
       0,    19,     0,    20,     0,    74,     0,    75,    22,     0,
       0,    23,    24,    25,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,    74,     0,    75,
       0,     0,     0,     0,     0,   156,    76,    77,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,    74,
       0,    75,     0,     0,     0,     0,   113,     0,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,    84,    85,
      86,    74,     0,    75,     0,     0,     0,    87,     0,     0,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    83,
      84,    85,    86,    74,     0,    75,     0,     0,     0,   109,
       0,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    74,     0,    75,     0,     0,
       0,   192,     0,     0,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,    74,     0,    75,
       0,     0,   119,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,    74,
       0,    75,     0,     0,   151,     0,     0,     0,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,    84,    85,
      86,    74,     0,    75,     0,     0,   170,     0,     0,     0,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    83,
      84,    85,    86,    74,     0,    75,   162,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    74,     0,    75,   165,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,    74,   183,    75,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,    74,     0,    83,    84,    85,    86,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    76,    77,
      78,    79,    80,   -71,   -71,     0,     0,   -71,   -71,   -71,
     -71
};

static const yytype_int16 yycheck[] =
{
       7,    75,    23,    10,    20,   187,    43,     4,    15,   191,
      31,    32,    19,    20,    42,    40,    44,    18,    39,    16,
      41,    18,    19,    20,    21,    51,    47,    48,    25,    16,
      17,    92,    16,    17,    31,    32,    41,    41,    99,    51,
      41,    48,    39,    59,    41,    46,    43,   108,    43,    46,
      51,    43,    49,    50,    51,    51,    39,    64,    41,    39,
       0,    41,    41,    41,    47,    48,    11,    47,    40,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
     105,    88,    40,    44,    91,    92,   111,    42,    51,   150,
      37,    98,    99,    26,    27,    28,     8,   104,   159,    51,
      51,   108,    37,   164,    42,    41,   113,    41,   182,    51,
      42,    42,    38,    43,   121,   122,    27,    42,    42,     0,
       1,   146,    51,     4,    42,   157,     7,   158,     9,    10,
      11,    12,    13,    14,   102,    16,   117,    18,    19,    20,
      21,   106,   171,   150,    25,    -1,    -1,    -1,    -1,   156,
      31,    32,   159,    -1,    -1,    -1,    37,   164,    39,    -1,
      41,    -1,    43,    -1,   189,    46,    -1,    -1,    49,    50,
      51,    -1,    -1,    -1,     1,    -1,    -1,     4,    -1,    -1,
       7,   188,     9,    10,    11,    12,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    39,    -1,    41,    -1,    43,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,     1,    -1,    -1,     4,    -1,
      -1,     7,    -1,     9,    10,    11,    12,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,
      -1,    37,    -1,    39,     4,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    31,    32,    -1,    -1,    -1,    -1,    37,    -1,    39,
       4,    41,    -1,    -1,    -1,    -1,    46,    11,    -1,    49,
      50,    51,    16,    -1,    18,    19,    20,    21,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    39,     4,    41,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    -1,    15,    -1,    17,    46,    -1,
      -1,    49,    50,    51,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    15,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    45,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    15,
      -1,    17,    -1,    -1,    -1,    -1,    44,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    15,    -1,    17,    -1,    -1,    -1,    43,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    15,    -1,    17,    -1,    -1,    -1,    43,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    15,    -1,    17,    -1,    -1,
      -1,    43,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    15,    -1,    17,
      -1,    -1,    42,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    15,
      -1,    17,    -1,    -1,    42,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    15,    -1,    17,    -1,    -1,    42,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    15,    -1,    17,    40,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    15,    -1,    17,    40,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    15,    38,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    15,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     7,     9,    10,    11,    12,    13,    14,
      16,    18,    19,    20,    21,    25,    31,    32,    37,    39,
      41,    43,    46,    49,    50,    51,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    73,    77,    83,    87,    88,
      89,    91,    92,    95,    98,    99,   102,    43,    41,    41,
      51,    81,    43,    61,    43,    43,    61,    51,    61,    41,
      65,    67,    65,    78,    37,    61,    71,    74,    76,    61,
      87,    51,     0,    59,    15,    17,    24,    25,    26,    27,
      28,    29,    30,    33,    34,    35,    36,    43,    23,    31,
      32,    39,    41,    47,    48,    68,    69,    70,    39,    41,
      47,    41,    84,    60,    41,    93,   100,    61,    96,    43,
      87,    80,    61,    44,    72,    40,    40,    44,    75,    42,
      42,   101,   101,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    71,    51,    51,    61,
      71,    51,    85,    77,    86,     8,    90,    61,    60,    94,
      96,    42,    71,    42,    60,    79,    45,    61,    76,    41,
      61,    61,    40,    42,    41,    40,    42,    51,    82,    60,
      42,    71,    97,    38,    61,    72,    75,    71,    71,    42,
      44,    97,    43,    38,    42,    42,    51,    42,   101,   100,
      61,    60,    43,   100
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    69,    70,    71,
      71,    72,    72,    73,    73,    74,    75,    75,    76,    78,
      79,    77,    80,    80,    81,    81,    82,    82,    82,    83,
      85,    84,    86,    87,    88,    88,    88,    88,    88,    88,
      89,    90,    91,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     2,
       0,     3,     0,     3,     3,     2,     3,     0,     5,     0,
       0,     5,     2,     0,     1,     0,     1,     3,     0,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       4,     1,     2,     4,     1,     3,     1,     3,     0,     0,
       9,     9,     0,     0,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 166 "phase4/parser.yy" /* yacc.c:1646  */
    {
			cout<<yylineno<<": |" << "Program "<< endl;
		}
#line 1690 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 171 "phase4/parser.yy" /* yacc.c:1646  */
    {
			
			if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			illcount=0;
			assignParts.clear();
			//cout<<yylineno<<": |"<< "Expr Semicolon detected. "<< endl;
			idcount=0;
			if(!((yyvsp[-1].isNormalcall))){
				if((yyvsp[-1].exprvalue)->type==boolexpr_e){
					false_backpatch((yyvsp[-1].exprvalue)->false_index,0,currQuad);
					emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, (yyvsp[-1].exprvalue), -1, yylineno);
					emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
					true_backpatch((yyvsp[-1].exprvalue)->true_index,0,currQuad);
					emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, (yyvsp[-1].exprvalue), -1, yylineno);
					emit(if_eq,(yyvsp[-1].exprvalue),insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
					emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
				}
			}
			if ((yyvsp[-1].exprvalue)->type==boolexpr_e){
				if(DEBUG){cout<<"kane backpatch"<<endl;}
				false_backpatch((yyvsp[-1].exprvalue)->false_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, (yyvsp[-1].exprvalue), -1, yylineno);
				emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
				true_backpatch((yyvsp[-1].exprvalue)->true_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, (yyvsp[-1].exprvalue), -1, yylineno);
				//emit(if_eq,$<exprvalue>1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
				//$<intvalue>$ =  currQuad-1;
			}
			resettemp();
			bc_indexes * bc= new bc_indexes;
			(yyval.indexes)=bc;
			//$<break_index>$=-1;

		}
#line 1730 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 207 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "Expr ifstmt detected. "<< endl;
			//$<break_index>$=$<break_index>1;
  			//$<cont_index>$=$<cont_index>1;
  			bc_indexes * bc= new bc_indexes;
  			bc->break_index=(yyvsp[0].indexes)->break_index;
			bc->cont_index=(yyvsp[0].indexes)->cont_index;
			(yyval.indexes)=bc;
		}
#line 1744 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 217 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "Expr whilestmt detected. "<< endl;
			//
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			(yyval.indexes)=bc;
		}
#line 1756 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 225 "phase4/parser.yy" /* yacc.c:1646  */
    {
		//cout<<yylineno<<": |" << "Expr forstmt detected. "<< endl;
		//$<break_index>$=-1;
		bc_indexes * bc= new bc_indexes;
		(yyval.indexes)=bc;
		}
#line 1767 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 232 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			if(maxFScope==0){
				cout << "Syntax Error in line :"<< yylineno << "Return out of function ."<<endl;
				isValid=false;

			}
			//cout<<yylineno<<": |" << "Expr Returnstmt  detected. "<< endl;
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			(yyval.indexes)=bc;
		}
#line 1783 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 244 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			//cout << "ISLOOP: "<< isLoop << endl;
			if(isLoop==0){
				cout << "Syntax Error in line :"<<yylineno <<" Break outside loop." << endl;
				isValid=false;
			}
			//cout<<yylineno<<": |" << "Expr Break  detected. "<< endl;

			bc_indexes * bc= new bc_indexes;
			bc->break_index=load_b(1);
			//break handle
			//breakvector.size();
			breakvector.push_back(quadhead.size());
			///printbreak();
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			if(DEBUG){cout<<"            inserting into break <<<<<<<<"	<<endl;
			cout<<" passing break; -> stmt"<<(yyval.break_index)<<endl;
			cout<<" passing break; cont -> stmt"<<(yyval.cont_index)<<endl;}
			//printbreak();
			(yyval.indexes)=bc;

		}
#line 1810 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 267 "phase4/parser.yy" /* yacc.c:1646  */
    {
			if(isLoop==0){
				cout << "Syntax Error in line :"<<yylineno <<" Continue outside loop." << endl;
				isValid=false;
			}
			//cout<<yylineno<<": |" << "Expr Continue  detected. "<< endl;
			bc_indexes * bc= new bc_indexes;
			bc->cont_index=load_c(1);
			contvector.push_back(quadhead.size());
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			if(DEBUG){cout<<" passing cont; -> stmt"<<(yyvsp[-1].break_index)<<endl;
			cout<<" passing cont; -> stmt"<<(yyval.cont_index)<<endl;}

			(yyval.indexes)=bc;
			

		}
#line 1832 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 285 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//$<break_index>$=$<break_index>1;
						///contvector cont_index
			//$<cont_index>$=$<cont_index>1;
			if(DEBUG){cout<<yylineno<<": |" << "Expr block  detected. "<< (yyval.break_index)<<endl;	
			cout<<yylineno<<": |" << "Expr block  detected. "<< (yyval.cont_index)<<endl;	}
			bc_indexes * bc= new bc_indexes;
			bc->break_index=(yyvsp[0].indexes)->break_index;
			bc->cont_index=(yyvsp[0].indexes)->cont_index;
			(yyval.indexes)=bc;


		}
#line 1850 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 299 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "Expr funcdef detected. "<< endl;
			bc_indexes * bc= new bc_indexes;
			(yyval.indexes)=bc;
			//$<break_index>$=-1;
		}
#line 1861 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 306 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			//cout<<yylineno<<": |" << "Expr Semicolon detected. "<< endl;
			(yyval.indexes)=bc;
		}
#line 1872 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 312 "phase4/parser.yy" /* yacc.c:1646  */
    {yyerrok; cout<<"Major Grammar Error in line :"<<yylineno<<endl;
			assignParts.clear();
			bc_indexes * bc= new bc_indexes;
			(yyval.indexes)=bc;
			//cout<<"ADEIAZW ASSIGN PARTS"<<endl;
			}
#line 1883 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 320 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//$<exprvalue>$=newexpr(assignexpr_e);
			if(DEBUG)cout<<(yyvsp[0].exprvalue)->type<<" "<<endl;//printexpr($<exprvalue>1->index)<<end;
			//$<exprvalue>$->sym=newtemp();
			//emit(assign,$<exprvalue>1,NULL,$<exprvalue>$,-1,yylineno);
			//resettemp();
			//from here

			//cout<<$<exprvalue>1->sym->name<<" "<<$<exprvalue>1->index->sym->name<<endl;
			expr* result = new expr;
			result = newexpr(assignexpr_e);
			result->sym=newtemp();
			//$<exprvalue>$=newexpr(assignexpr_e);
			//$<exprvalue>$->sym=newtemp();
			
			if ((yyvsp[0].exprvalue)->type==1){
				// eksetasi an stekei!
				emit(tablegetelem,(yyvsp[0].exprvalue),(yyvsp[0].exprvalue)->index, result ,-1,yylineno);
			}
			else{
				emit(assign,(yyvsp[0].exprvalue),NULL,result,-1,yylineno);	
			}
			//tohere
			(yyval.exprvalue)=result;
			//cout<<yylineno<<": |" << "Expr assignexpr  detected. idc: "<<idcount<<" TYPE: " << $<exprvalue>$->type << $<exprvalue>$->sym->offset << endl;
			//$<exprvalue>$ = $<exprvalue>1;
			idcount--;
			//tablegetelem t0 pinakas  
			/*
			[5/9/15, 13:28:15] stayros dag: Αν εννοείς την extra εντολή μετά το tablesetelem, αυτή είναι μια tablegetelem με την οποία κρατάμε την τιμή που μόλις κάναμε assign σε ένα temp ώστε να μπορεί να χρησιμοποιηθεί αργότερα. Συνολικά λοιπόν, 
			το a.b = 3 παράγει τα quads:
			1. tablesetelem a b 3
			2. tablegetelem _t0 a b
			[5/9/15, 13:28:53] stayros dag: ara den 8elei assign
			*/
		}
#line 1924 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 358 "phase4/parser.yy" /* yacc.c:1646  */
    {
									if(DEBUG){cout<<yylineno<<": |" << "Expr + expr => "<<endl;}
									//cout << "TYPE OF 1st EXPR: "<< $<exprvalue>1->type <<  "TYPE OF 2st EXPR: "<< $<exprvalue>3=x->type << endl;
									if(validForOp((yyvsp[-2].exprvalue)) && validForOp((yyvsp[0].exprvalue))){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in addition operation" << endl;
									}
							   		(yyval.exprvalue) = op_emit(add,(yyvsp[-2].exprvalue),(yyvsp[0].exprvalue),yylineno);
							   }
#line 1941 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 371 "phase4/parser.yy" /* yacc.c:1646  */
    {
									if(DEBUG){cout<<yylineno<<": |" << "Expr - expr => "<<endl;}
									if(validForOp((yyvsp[-2].exprvalue)) && validForOp((yyvsp[0].exprvalue))){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in subtraction operation" << endl;
									}
								 (yyval.exprvalue) = op_emit(sub,(yyvsp[-2].exprvalue),(yyvsp[0].exprvalue),yylineno);
								}
#line 1957 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 383 "phase4/parser.yy" /* yacc.c:1646  */
    {
									if(DEBUG){cout<<yylineno<<": |" << "Expr * expr => "<<endl; }
									if(validForOp((yyvsp[-2].exprvalue)) && validForOp((yyvsp[0].exprvalue))){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in multiplication  operation" << endl;
									}
								 	(yyval.exprvalue) = op_emit(mul,(yyvsp[-2].exprvalue),(yyvsp[0].exprvalue),yylineno);
								 }
#line 1973 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 395 "phase4/parser.yy" /* yacc.c:1646  */
    {
									if(DEBUG){cout<<yylineno<<": |" << "Expr / expr => "<<endl;}
									if(validForOp((yyvsp[-2].exprvalue)) && validForOp((yyvsp[0].exprvalue))){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in division operation" << endl;
									}
								 	(yyval.exprvalue) = op_emit(divide,(yyvsp[-2].exprvalue),(yyvsp[0].exprvalue),yylineno);
								}
#line 1989 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 407 "phase4/parser.yy" /* yacc.c:1646  */
    {
									if(DEBUG){cout<<yylineno<<": |" << "Expr %% (mod) => "<<endl;}
									if(validForOp((yyvsp[-2].exprvalue)) && validForOp((yyvsp[0].exprvalue))){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in modulo operation" << endl;
									}
								 	(yyval.exprvalue) = op_emit(mod,(yyvsp[-2].exprvalue),(yyvsp[0].exprvalue),yylineno);
								}
#line 2005 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 419 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr > expr => "<< endl; 
			
			emit(if_greater,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;
			//cout<<"efuga"<<endl;;

			}
#line 2027 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 436 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
		lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr >= expr => "<< endl; 
			
			emit(if_greatereq,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;

			
			
			//cout <<" in greater eq "<< $<exprvalue>$->true_index << " | "<<$<exprvalue>$->false_index<<endl;
			}
#line 2051 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 455 "phase4/parser.yy" /* yacc.c:1646  */
    {

		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
		lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr < expr => "<<endl;
			emit(if_less,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;


			}
#line 2073 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 472 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr <= expr => "<<endl;
			
			emit(if_lesseq,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;


			}
#line 2095 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 489 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr == expr => "<<endl;

			emit(if_eq,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;


			}
#line 2117 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 506 "phase4/parser.yy" /* yacc.c:1646  */
    {

		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr != expr => "<<endl; 

			emit(if_not_eq,(yyvsp[-2].exprvalue), (yyvsp[0].exprvalue), NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			(yyval.exprvalue) = result;


			}
#line 2140 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 524 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){/*cout<<"kleinw lvalfunc"<<endl;*/lvalfunc=0;}
			//true_backpatch($<exprvalue>1->true_index, $<exprvalue>1->true_index,currQuad);

			//cout<<yylineno<<": |" << "!!!!!!!!!!!!!Expr && expr => "<<$<intvalue>3<< "VS"<<currQuad<<endl; 
	
			////

			expr * arg1= new expr;
			expr * arg2= new expr;
			expr * result = new expr;
			result = newexpr(boolexpr_e);
			result->sym=newtemp();

			arg1 = true_test((yyvsp[-3].exprvalue),arg1,(yyvsp[-1].intvalue));
			if (arg1->changeLabel) (yyvsp[-1].intvalue)=currQuad;
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			arg2 = true_test((yyvsp[0].exprvalue),arg1,(yyvsp[-1].intvalue));

			true_backpatch(arg1->true_index, arg1->true_end ,(yyvsp[-1].intvalue));
			//cout<<"edw!!!"<<endl;
			result->true_index=arg2->true_index;
			result->false_index=merge_false(arg1->false_index,arg2->false_index);
			result->isAnd = false;
			(yyval.exprvalue)=result;


			//cout<<"efuga apo to and"<<endl;
			}
#line 2176 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 555 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if (lvalfunc){/*cout<<"kleinw lvalfunc"<<endl;*/lvalfunc=0;}
			//cout<<yylineno<<": |" << "!!!!!!!!!!!!!!Expr || expr => " << $<intvalue>3 << "VS"<<currQuad <<endl; 
			expr * arg1= new expr;
			expr * arg2= new expr;
			expr * result = new expr;
			expr *temp = new expr;
			result = newexpr(boolexpr_e);
			result->sym=newtemp();
			
			/*
			auto it = myvector.emplace ( myvector.begin()+1, 100 );
 			myvector.emplace ( it, 200 );
  			myvector.emplace ( myvector.end(), 300 )
		
		
			*/
			arg1 = true_test_or((yyvsp[-3].exprvalue),arg1,(yyvsp[0].exprvalue),(yyvsp[-1].intvalue));
			//arg1 = true_test($<exprvalue>1,arg1,$<intvalue>3);
			//expr *temp = new expr;
			if (arg1->changeLabel){ 

				//$<intvalue>3=arg1->false_index;

			}
			

			if(DEBUG){cout<<"============================ indexes :"<<arg1->true_index<<"  |  "<<arg1->false_index<<endl;
			print_true();
	 		print_false();}
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			arg2 = true_test((yyvsp[0].exprvalue),arg1,(yyvsp[-1].intvalue));
			/*if (arg1->changeLabel){ 
				temp= arg1;
				arg1=arg2;
				arg2= temp;

			}*/
			if (arg1->changeLabel){ 

				//$<intvalue>3=currQuad;
				//$<intvalue>3=currQuad;
				(yyvsp[-1].intvalue)=falseMultiVector[arg1->false_index][0]+1;
				if(DEBUG){cout<<"NEW L"<<(yyvsp[-1].intvalue)<<endl;}
				if(DEBUG)cout<<falseMultiVector[arg1->false_index][0]<<endl;
				if(quadhead.size()>falseMultiVector[arg1->false_index][0]){
				if(DEBUG){cout<<"changelabel"<<endl;}
			  	vector<quad>  :: iterator it;
			  	if(!(arg2->changeLabel)) fix_quads(arg2->true_index, arg2->false_index);


				}
			}

			if(DEBUG)cout<<arg1->false_index<<endl;
			if(DEBUG)cout<<arg2->false_index<<endl;
			print_false();
			if(DEBUG)cout<<arg1->true_index<<endl;
			if(DEBUG)cout<<arg2->true_index<<endl;
			print_true();




			false_backpatch(arg1->false_index, arg1->false_end ,(yyvsp[-1].intvalue));
			//cout<<"telos false"<<endl;;
			result->true_index=merge_true(arg1->true_index,arg2->true_index);
			result->false_index=arg2->false_index;
			result->isAnd = false;
			(yyval.exprvalue)=result;
			


			}
#line 2257 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 635 "phase4/parser.yy" /* yacc.c:1646  */
    {
								//cout<<yylineno<<": |" << "Terminal " <<$<isNormalcall>1<< endl;
								expr *tmp = new expr;
								tmp= (yyvsp[0].exprvalue);
								//if ()
								int normal=(yyvsp[0].isNormalcall);

								
								//$<true_index>$=tracktrue;
								//$<false_index>$=trackfalse;
								(yyval.exprvalue) = tmp;
								(yyval.isNormalcall)=normal;
								//cout<<"term efuga"<<endl;

								}
#line 2277 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 653 "phase4/parser.yy" /* yacc.c:1646  */
    {
				
					if(lvalfunc){
							lvalfunc =0;
					}
					//cout<<yylineno<<": |" << "L_parent Expr R_parent "<< endl;

					expr *tmp = new expr;
					tmp= (yyvsp[-1].exprvalue);


					(yyval.exprvalue) = tmp;

					//cout<<"efuga"<<$<exprvalue>$->true_index<<endl;

					//$<exprvalue>$ = $<exprvalue>2;
					}
#line 2299 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 671 "phase4/parser.yy" /* yacc.c:1646  */
    {

			if(validForOp((yyvsp[0].exprvalue))) {
										isValid=true;
										lvalfunc=0;
									}
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. MINUS EXPR"<<endl;
				lvalfunc = 0;
				isValid=false;
			}
			uminusValid = uminus_validity((yyvsp[0].exprvalue));
			if(uminusValid){
				cout << "Invalid assignment to uminus operator" << endl;
			}
			(yyval.exprvalue) = newexpr(arithexpr_e);
			(yyval.exprvalue)->sym = newtemp();
			emit(uminus ,(yyvsp[0].exprvalue), NULL, (yyval.exprvalue), -1, yylineno);
			//cout<<yylineno<<": |" << "Mnus Expr "<< endl;
		}
#line 2324 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 693 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			lvalfunc = 0;
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. NOT EXPR"<<endl;
				lvalfunc = 0;
				isValid=false;
			}
			expr *result = new expr;
			//result = newexpr(boolexpr_e);
			//result->sym = newtemp();

			if((yyvsp[0].exprvalue)->type!=boolexpr_e){
				//emit(if_eq,$<exprvalue>1, , NULL, (int)(currQuad +2), yylineno);
				//emit(if_eq,$<exprvalue>2,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
				//emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				//expr *result = new expr;
				//result = newexpr(boolexpr_e);
				//result->sym = newtemp();
				result =(yyvsp[0].exprvalue);
				result->true_index= load_t();
				result->false_index= load_f();
				result -> fromNot=true;
				//cout<<"this that?"<<arg1->sym->name<<endl;
				//$<intvalue>3=currQuad;



				/*

				emit(if_not_eq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
				emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				expr *result = new expr;
				result = newexpr(boolexpr_e);
				result->sym = newtemp();
				result->true_index= load_t();
				result->false_index= load_f();	
				$<exprvalue>$ = result;

				*/
			}
			else{

					result->type=boolexpr_e;
					result->true_index=(yyvsp[0].exprvalue)->true_index;
					result->false_index=(yyvsp[0].exprvalue)->false_index;
					result = (yyvsp[0].exprvalue);
					swap(result->true_index,result->false_index);
			}


			
			//cout<<" indexes "<<result->true_index<<" "<<result->false_index<<endl;
			
			//result->true_index= $<exprvalue>2->true_index;
			//result->false_index= $<exprvalue>2->false_index;
			(yyval.exprvalue)=result;
			//$<exprvalue$=$<exprvalue>2;
			//$<exprvalue>$->type=  boolexpr_e;
			//cout<<yylineno<<": |" << "Not expr aaaaaaaaaaaaa "<< endl;
		}
#line 2389 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 755 "phase4/parser.yy" /* yacc.c:1646  */
    {	if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. INCR LVL"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "++ LValue "<< endl;

			//$<exprvalue>$ = $<exprvalue>2;

			if ((yyvsp[0].exprvalue)->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				(yyval.exprvalue)=emit_iftableitem((yyvsp[0].exprvalue), yylineno);
				(yyval.exprvalue)=op_emit(add,(yyval.exprvalue),insertVal(1,-1,"INTCONST"),yylineno);
				emit(tablesetelem,(yyvsp[0].exprvalue),(yyvsp[0].exprvalue)->index, (yyval.exprvalue),-1,yylineno);			
			}
			else 
			{

				(yyval.exprvalue)=newexpr(var_e);
				emit(add,insertVal(1,-1,"INTCONST"),(yyvsp[0].exprvalue),(yyvsp[0].exprvalue),-1,yylineno);
				if(istempname((yyvsp[0].exprvalue)->sym->name))
				{
					(yyval.exprvalue)->sym = (yyvsp[0].exprvalue)->sym;
				}
				else
				{
					(yyval.exprvalue)->sym=newtemp();
					emit(assign,(yyvsp[0].exprvalue),NULL,(yyval.exprvalue),-1,yylineno);
				}
			}				
		}
#line 2427 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 789 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. LVL INCR"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "Lval ++ "<< endl;

			//$<exprvalue>$ = $<exprvalue>1;
			(yyval.exprvalue)=newexpr(var_e);
			(yyval.exprvalue)->sym= newtemp();
			
			if ((yyvsp[-1].exprvalue)->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				expr * temp;
				temp=emit_iftableitem((yyvsp[-1].exprvalue), yylineno);
				emit(assign,temp,NULL,(yyval.exprvalue),-1,yylineno);
				emit(add,temp,insertVal(1,-1,"INTCONST"),temp,-1,yylineno);
				emit(tablesetelem,(yyvsp[-1].exprvalue),(yyvsp[-1].exprvalue)->index, temp,-1,yylineno);
							
			}
			else 
			{
				emit(assign,(yyvsp[-1].exprvalue),NULL,(yyval.exprvalue),-1,yylineno);
				emit(add,insertVal(1,-1,"INTCONST"),(yyvsp[-1].exprvalue),(yyvsp[-1].exprvalue),-1,yylineno);

			}				

		}
#line 2463 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 822 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. DECR LVL"<<endl;
				lvalfunc = 0;
				isValid=false;
			
			}
			//cout<<yylineno<<": |" << "--Lval "<< endl;
			//$<exprvalue>$ = $<exprvalue>2;

			if ((yyvsp[0].exprvalue)->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				(yyvsp[-1].exprvalue)=emit_iftableitem((yyvsp[0].exprvalue), yylineno);
				(yyval.exprvalue)=op_emit(sub,(yyvsp[-1].exprvalue),insertVal(1,-1,"INTCONST"),yylineno);			
			}
			else 
			{
				emit(sub,(yyvsp[0].exprvalue),insertVal(1,-1,"INTCONST"),(yyvsp[0].exprvalue),-1,yylineno);
				(yyval.exprvalue)=newexpr(arithexpr_e);
				if(istempname((yyvsp[0].exprvalue)->sym->name))
				{
					(yyval.exprvalue)->sym = (yyvsp[0].exprvalue)->sym;
				}
				else
				{
					(yyval.exprvalue)->sym=newtemp();
					emit(assign,(yyvsp[0].exprvalue),NULL,(yyval.exprvalue),-1,yylineno);
				}
			}	
					

		}
#line 2500 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 855 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. LVL DECR"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "Lval-- "<< endl;

			//$<exprvalue>$ = $<exprvalue>1;
			(yyval.exprvalue)=newexpr(var_e);
			(yyval.exprvalue)->sym= newtemp();
			
			if ((yyvsp[-1].exprvalue)->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				expr * temp;
				temp=emit_iftableitem((yyvsp[-1].exprvalue), yylineno);
				emit(assign,temp,NULL,(yyval.exprvalue),-1,yylineno);
				emit(sub,temp,insertVal(1,-1,"INTCONST"),temp,-1,yylineno);
				emit(tablesetelem,(yyvsp[-1].exprvalue),(yyvsp[-1].exprvalue)->index, temp,-1,yylineno);
							
			}
			else 
			{
				emit(assign,(yyvsp[-1].exprvalue),NULL,(yyval.exprvalue),-1,yylineno);
				emit(sub,(yyvsp[-1].exprvalue),insertVal(1,-1,"INTCONST"),(yyvsp[-1].exprvalue),-1,yylineno);

			}					

		}
#line 2536 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 887 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			(yyval.exprvalue)=(yyvsp[0].exprvalue);
			//cout<<yylineno<<": |" << "Primary "<< endl;
		}
#line 2545 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 896 "phase4/parser.yy" /* yacc.c:1646  */
    {



			///meriki
			//if($<exprvalue>1->sym->type<2){cout<<"^^^^^^^^^^^print error?^^^^^^^^^^^^ "<<endl;}
			
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->type << endl;
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->sym->name << endl;
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->sym->type << endl;

			///
			//cout<<yylineno<<": |" << "IN ASSIGNEXPR idc: "<<idcount<<endl;
			illcount=0;
			for (list<int>::iterator it = assignParts.begin(); it != assignParts.end(); it++){
				if(DEBUG)cout<<(*it)<<endl;
					if ((*it < 2 )&& (*it!=5)) {
								illcount++;
 							 	//cout<<" ASSIGNPART FOUND FUNC OR LIBFUNC succeded :"<<yylineno<<" illcount :"<<illcount<<" |:"<<*it<<endl;

									}
					}

			//provlima me ta temp pou eisagontai meta
			//cout<<" assignparts front :"<<assignParts.front()<<" "<<assignParts(1)<<" "<<assignParts(2)<<" back"<< assignParts.back()<<"  size :"<< assignParts.size()<<endl;

			//cout<<" assignparts front :"<<assignParts.front()<<" back"<< assignParts.back()<<"  size :"<< assignParts.size()<<endl;
			
			/*if((illcount>1)||((illcount==1)&&((assignParts.back()!=5)&&assignParts.back()>1)&&(assignParts.size()>1))||((illcount==1)&&(assignParts.front()<2)&&(assignParts.size()==1))||(assignParts.front()<2)) {
					cout<<"SYNTAX ERROR LVAL ON FUNCTION FROM ASSIGNPARTS :"<<yylineno<<endl;
					isValid=false;
					assignParts.pop_back();
					//cout<<"back pop here"<<endl;
					illcount--;

			}*/

			if((yyvsp[0].exprvalue)->fromNot){
					//cout<<"in not "<<endl;

					expr *temp = new expr;
					expr *result = new expr;
					result= newexpr(boolexpr_e);
					result->sym=newtemp();
					temp = newexpr(boolexpr_e);
					temp->sym = (yyvsp[0].exprvalue) ->sym;
					//$<exprvalue>3->sym = newtemp();
					emit(if_eq,temp,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
					emit(jump, NULL, NULL, NULL, (int)(currQuad +3), yylineno);
					emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL,result, -1, yylineno);
					emit(jump, NULL, NULL, NULL, (int)(currQuad +2), yylineno);
					emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, result, -1, yylineno);
					(yyvsp[0].exprvalue)->sym= result->sym;


				}

			
			
			else if((yyvsp[0].exprvalue)->type==boolexpr_e){
				//cout<<"in bool "<<endl;
				//cout<<"efatsa sta type check"<<$<exprvalue>3->type<<endl;
				
				if(DEBUG){cout<<  (yyvsp[0].exprvalue)->sym->name<< " indexes :"<< (yyvsp[0].exprvalue)->true_index <<"  |  "<<(yyvsp[0].exprvalue)->false_index<<endl;}

				/*
				true_backpatch($<exprvalue>3->true_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>3, -1, yylineno);
			
				emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
				false_backpatch($<exprvalue>3->false_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>3, -1, yylineno);
				*/
				bool_assign((yyvsp[-2].exprvalue), (yyvsp[0].exprvalue));
				(yyval.exprvalue)=newexpr(assignexpr_e);
			
			/*----------------------stayros!!!!!!!!!!!!----------------//*/
			}
			else if((yyvsp[0].exprvalue)->type==tableitem_e){
				(yyvsp[0].exprvalue)=emit_iftableitem((yyvsp[0].exprvalue),yylineno);
			}
			



			if((yyvsp[-2].exprvalue)->type==tableitem_e){
				//$<exprvalue>1=emit_iftableitem($<exprvalue>1,yylineno);
				emit(tablesetelem,(yyvsp[-2].exprvalue),(yyvsp[-2].exprvalue)->index, (yyvsp[0].exprvalue),-1,yylineno);
				(yyval.exprvalue)=(yyvsp[-2].exprvalue);	

			}
			else{
				//cout<<"bika sto else"<<endl;
				emit(assign,(yyvsp[0].exprvalue),NULL,(yyvsp[-2].exprvalue),-1,yylineno);
				(yyval.exprvalue)=newexpr(assignexpr_e);
				//cout << $<exprvalue>1->sym->name<< endl;

					if(	istempname((yyvsp[-2].exprvalue)->sym->name)){

						(yyval.exprvalue)->sym=newtemp();
						emit(assign,(yyvsp[-2].exprvalue),NULL,(yyval.exprvalue),-1,yylineno);

					}
					else{
						(yyval.exprvalue)->sym = (yyvsp[-2].exprvalue)->sym;
					}
			}
		}
#line 2658 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 1008 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			(yyval.exprvalue) =emit_iftableitem((yyvsp[0].exprvalue),yylineno);
			Lval_used = 1;
			if(DEBUG){cout<<yylineno<<": |" << "Lval primary "<< endl;}
		}
#line 2668 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 1014 "phase4/parser.yy" /* yacc.c:1646  */
    {
			is_call = 1;
			int temp=1;
			expr * calltemp = new expr;
			calltemp= (yyvsp[0].exprvalue);			
			//cout<<$<exprvalue>1->sym->name<<endl;
			(yyval.isNormalcall)=temp;
			if(DEBUG){cout<<yylineno<<": |" << "Call "<< (yyval.isNormalcall)<< endl;}
			(yyval.exprvalue) = calltemp;


			/*
			is_call = 1;
			int temp=1;
			expr * calltemp = new expr;
			calltemp= $<exprvalue>1;			
			//cout<<$<exprvalue>1->sym->name<<endl;
			$<isNormalcall>$=temp;
			cout<<yylineno<<": |" << "Call "<< $<isNormalcall>$<< endl;
			$<exprvalue>$ = calltemp;
			//cout<<"''''''''''''''''''''''call "<<$<exprvalue>$->sym->name<<endl;
		

			*/
		}
#line 2698 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 1040 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "Object def "<< endl;
			(yyval.exprvalue) = newexpr(newtable_e);
			(yyval.exprvalue) = (yyvsp[0].exprvalue);
		}
#line 2708 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 1046 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "Function Def "<< endl;
			(yyval.exprvalue) = newexpr(programfunc_e);
			(yyval.exprvalue)->sym = (yyvsp[-1].symvalue);

		}
#line 2719 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 1052 "phase4/parser.yy" /* yacc.c:1646  */
    {
			tmpsym = new expr;
			tmpsym=(yyvsp[0].exprvalue);
			//cout<<yylineno<<": |" << "Constant :"<<endl;
			(yyval.exprvalue) = (yyvsp[0].exprvalue);
		}
#line 2730 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 1063 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			if(DEBUG){cout<<"IN LVALUE: ID"<<(yyvsp[0].strvalue)<<endl;}
			localcheck =createFSymbol((yyvsp[0].strvalue),maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   
			if(DEBUG){cout<<"is_funcall :"<<is_funcall<<" || is_call :"<<is_call<<" ||is_funcdef :"<<is_funcdef<<endl;}
			Symbol *kati;
			/*kati=LookupforRef($1,maxScope);
			if(kati==NULL){
				insertPt(localcheck);
				cout<< "CURRENT SCOPE SPACE  " << currentscopeoffset() <<endl;
			}*/
			kati=Lookup(*localcheck,LVAL_ID);
			//cout << "=========NAME===============" << localcheck->name << endl;
			//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
			//inccurrscopeoffset();
			//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
			//cout<<yylineno<<": " << "Identifier "<<endl;

			//cout<<yylineno<<": " << "Identifier "<< kati->name <<endl;
			idcount++;
   			//$<exprvalue>$= lvalue_expr($<strvalue>1);
   			///$<exprvalue>$->sym=kati;
			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			(yyval.exprvalue) = passme;
			//cout<<yylineno<<": |" << "id :"<< ($<exprvalue>$->sym->name) <<endl;										 
		

		}
#line 2763 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 1092 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			Symbol *kati;
			if(DEBUG)cout<<yylineno<<": " << "Local Identifier "<< (yyvsp[0].strvalue) << endl;
			idcount++;
			//toAdd =fill($2,maxScope,yylineno,"none",maxFScope,0,VAR,true);   //missing check
			if(DEBUG)cout<<" prin create"<<endl;
			localcheck =createFSymbol((yyvsp[0].strvalue),maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   
			if(DEBUG)cout<<" after create"<<endl;	
			kati=Lookup(*localcheck,LVAL_LOCAL);
			if(DEBUG)cout<<" after lookup"<<endl;
   			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			(yyval.exprvalue) = passme;


		}
#line 2784 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 1109 "phase4/parser.yy" /* yacc.c:1646  */
    { 	
			Symbol *kati;

			localcheck =createFSymbol((yyvsp[0].strvalue),maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   

			kati=Lookup(*localcheck,LVAL_GLOBAL);
			if(DEBUG)cout<<yylineno<<": " << "Global Identifier "<< (yyvsp[0].strvalue) << endl;
			idcount++;
			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			(yyval.exprvalue) = passme;
   			//$<exprvalue>$= lvalue_expr($<strvalue>2);

		}
#line 2803 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 1126 "phase4/parser.yy" /* yacc.c:1646  */
    {	

			templast=assignParts.back();
			while ((assignParts.back()!=5)&&assignParts.size()){ assignParts.pop_back();}
			assignParts.push_back(2);
			if(DEBUG){cout<<yylineno<<": " << "Member "<< (yyvsp[0].strvalue) << endl;}
			(yyval.exprvalue)=(yyvsp[0].exprvalue);
		}
#line 2816 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 1137 "phase4/parser.yy" /* yacc.c:1646  */
    { 
						if(DEBUG){cout<<yylineno<<": |" << "Lval.ID "<< endl;
						cout<<yylineno<<": " << "Member lval.ID "<< (yyvsp[0].strvalue) << endl;}
						(yyval.exprvalue)=emit_table((yyvsp[-2].exprvalue),constString_expr((yyvsp[0].strvalue)),yylineno);
					}
#line 2826 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 1142 "phase4/parser.yy" /* yacc.c:1646  */
    {

						//cout<<yylineno<<": |" << "Lval[expr] "<< endl;

						(yyval.exprvalue)=emit_table((yyvsp[-3].exprvalue),(yyvsp[-1].exprvalue),yylineno);
					}
#line 2837 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 1148 "phase4/parser.yy" /* yacc.c:1646  */
    {//cout<<yylineno<<": |" << "Call ID "<< endl;
							}
#line 2844 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 1150 "phase4/parser.yy" /* yacc.c:1646  */
    {//cout<<yylineno<<": |" << "Cal[expr] "<< endl;
												}
#line 2851 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 1156 "phase4/parser.yy" /* yacc.c:1646  */
    {
		if(DEBUG){cout<<yylineno<<": |" << "Call(Elist) "<< endl;}
		if(lvalfunc){
					lvalfunc=0;
					}
		
		(yyval.exprvalue) = (expr *) func_call((yyvsp[-3].exprvalue), (yyvsp[-1].exprvalue), yylineno , (yyvsp[-2].startHere));
		}
#line 2864 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 1164 "phase4/parser.yy" /* yacc.c:1646  */
    {		
							if(DEBUG){cout<<"######IS NORMALCALL? : "<<(yyvsp[0].isNormalcall)<<" elist value "<<expr_list.size()<<endl;}

							if (!((yyvsp[0].isNormalcall))) {
							(yyval.exprvalue) = (expr *) func_call((yyvsp[-1].exprvalue), (yyvsp[0].exprvalue), yylineno, (yyvsp[0].startHere));
							}
							else {
							(yyval.exprvalue) = (expr *) func_methodcall((yyvsp[-1].exprvalue), (yyvsp[0].strvalue), yylineno,(yyvsp[0].startHere));

							}
									

								}
#line 2882 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 1178 "phase4/parser.yy" /* yacc.c:1646  */
    {//cout<<yylineno<<": |" << "Fundef(Elist) "<< endl;
		expr* callfunc = new expr;
		callfunc= newexpr(programfunc_e);
		callfunc ->sym = (yyvsp[-4].symvalue);
		if(DEBUG){cout<<"name of func is "<<callfunc->sym->name<<endl;
		printList();
		cout<<"########"<<endl;}
		//cout<<$<startHere>5<<"   "<<$<startHere>6<<endl;
		(yyval.exprvalue) = (expr *) func_call(callfunc, (yyvsp[-1].exprvalue), yylineno, (yyvsp[-2].startHere));


	}
#line 2899 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 1193 "phase4/parser.yy" /* yacc.c:1646  */
    {
							//cout<<yylineno<<": |" << "Normalcall "<< endl;
							(yyval.exprvalue) = (yyvsp[0].exprvalue);
							(yyval.startHere)=(yyvsp[0].startHere);
							(yyval.isNormalcall)=0;


						}
#line 2912 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 1201 "phase4/parser.yy" /* yacc.c:1646  */
    {
								//cout<<yylineno<<": |" << "Method call "<< $<strvalue>1 <<endl;
								(yyval.isNormalcall)=1;
								(yyval.strvalue)= (yyvsp[0].strvalue);
								//cout<<yylineno<<": |" << "Method call "<< $<isNormalcall>$ <<endl;

						}
#line 2924 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 1211 "phase4/parser.yy" /* yacc.c:1646  */
    {
											is_call=1;
											//cout<<yylineno<<": |" << "(Elist) "<< endl;
											(yyval.exprvalue) = (yyvsp[-2].exprvalue);
											(yyval.startHere)=(yyvsp[-2].startHere);
											}
#line 2935 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 1221 "phase4/parser.yy" /* yacc.c:1646  */
    {
							if(DEBUG){cout<<yylineno<<": |" << "|..ID(Elist) "<<(yyvsp[-3].strvalue) << endl;}
							(yyval.strvalue)= (yyvsp[-3].strvalue);
						}
#line 2944 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 1227 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "Expr "<< endl;}
								(yyval.exprvalue) = (yyvsp[-1].exprvalue);
								expr_list.push_back((yyvsp[-1].exprvalue));
						}
#line 2954 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 1233 "phase4/parser.yy" /* yacc.c:1646  */
    {
							if(DEBUG){cout << "Empty elist given" << endl;}
						}
#line 2962 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 1237 "phase4/parser.yy" /* yacc.c:1646  */
    {
							if(DEBUG){cout<<yylineno<<": |" << "Expr .. Expr"<< endl;}
							(yyval.exprvalue)=(yyvsp[-1].exprvalue);
							expr_list.push_back((yyvsp[-1].exprvalue));							
						}
#line 2972 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 1242 "phase4/parser.yy" /* yacc.c:1646  */
    {}
#line 2978 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 1245 "phase4/parser.yy" /* yacc.c:1646  */
    {

						if(DEBUG){cout<<"[ Elist ]"<<endl;}
						expr * table = newexpr(newtable_e);
						elist_start++;
						
    					(yyval.exprvalue) = obj_manage((yyvsp[-2].startHere));


}
#line 2993 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 1255 "phase4/parser.yy" /* yacc.c:1646  */
    {
												expr * table = newexpr(newtable_e);
												elist_start++;
    											(yyval.exprvalue) = obj_manage((yyvsp[-2].startHere));
												//cout<<yylineno<<": |" << "[Indexed]"<< endl;
    										}
#line 3004 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 1263 "phase4/parser.yy" /* yacc.c:1646  */
    {
							if(DEBUG){cout<<yylineno<<": |" << "Expr "<< endl;}
								(yyval.exprvalue) = (yyvsp[-1].exprvalue);
								expr_list.push_back((yyvsp[-1].exprvalue));
						}
#line 3014 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 1272 "phase4/parser.yy" /* yacc.c:1646  */
    {

			if(DEBUG){cout<<yylineno<<": |" << "Expr .. Expr"<< endl;}
			(yyval.exprvalue)=(yyvsp[-1].exprvalue);
			expr_list.push_back((yyval.exprvalue));


}
#line 3027 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 1280 "phase4/parser.yy" /* yacc.c:1646  */
    {}
#line 3033 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 1283 "phase4/parser.yy" /* yacc.c:1646  */
    {
														//cout<<yylineno<<": |" << "{ expr : expr } "<< endl;
														(yyval.exprvalue) = (yyvsp[-3].exprvalue);
														(yyval.exprvalue)->iskey = true;
														(yyval.exprvalue)->keyval = (yyvsp[-1].exprvalue);
															}
#line 3044 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 1293 "phase4/parser.yy" /* yacc.c:1646  */
    {
			maxScope++;
			if(DEBUG){cout<<yylineno<<": |" << "L_brace "<< endl;}
		}
#line 3053 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 1297 "phase4/parser.yy" /* yacc.c:1646  */
    {}
#line 3059 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 1298 "phase4/parser.yy" /* yacc.c:1646  */
    {
			hideTheScope(maxScope); 
			maxScope--;
			if(DEBUG){cout<<yylineno<<": |" << "R_brace "<< endl;}

			//both
			//$<break_index>$=$<break_index>3; 
			//$<cont_index>$=$<cont_index>3;
	
			bc_indexes * bc= new bc_indexes;
  			bc->break_index=(yyvsp[-2].indexes)->break_index;
			bc->cont_index=(yyvsp[-2].indexes)->cont_index;
			(yyval.indexes)=bc;
			if(DEBUG){
	 		cout<<" passing block_stmt; -> block"<<(yyval.break_index)<<endl;
			cout<<" passing block_stmt;"<<(yyval.cont_index)<<endl;
			
			}

		}
#line 3084 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 1320 "phase4/parser.yy" /* yacc.c:1646  */
    {
			if(DEBUG){cout<<" in block_stmt"<<" blockstmt :"<< (yyvsp[-1].break_index)<<" stmt: "<<(yyvsp[0].break_index)<<endl;}
			/*if($<break_index>1>-1){

				if($<break_index>2>-1){

				$<break_index>$=min($<break_index>2,$<break_index>1);

				cout<<" passing block stmt stmt in if -> block_stmt "<<$<break_index>$<<endl;
				}
				else{
						$<break_index>$=$<break_index>1;
				}

			}

			else{
					$<break_index>$=$<break_index>2;	
					cout<<" passing block stmt stmt else -> block_stmt "<<$<break_index>$<<endl;
			}


			if($<cont_index>1>-1){

				$<cont_index>$=min($<cont_index>2,$<cont_index>1);

				cout<<" passing block stmt stmt in if -> block_stmt "<<$<cont_index>$<<endl;

			}
			else{
					$<cont_index>$=$<cont_index>2;
					cout<<" passing block stmt stmt else -> block_stmt "<<$<cont_index>$<<endl;
			}*/
			
			

			bc_indexes * bc= new bc_indexes;
  			bc->break_index=merge_break((yyvsp[0].indexes)->break_index,(yyvsp[-1].indexes)->break_index);
			bc->cont_index=merge_break((yyvsp[0].indexes)->cont_index,(yyvsp[-1].indexes)->cont_index);
			(yyval.indexes)=bc;

			}
#line 3131 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 1362 "phase4/parser.yy" /* yacc.c:1646  */
    {
					
					bc_indexes * bc= new bc_indexes;
					(yyval.indexes)=bc;
				}
#line 3141 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 1371 "phase4/parser.yy" /* yacc.c:1646  */
    {
				if(DEBUG){cout<<yylineno<<": " << "Identifier "<<(yyvsp[0].strvalue)<<endl;idcount++;/*cout<<"id++ here"<<endl*/;}

				staurosDota=strdup((yyvsp[0].strvalue));
				(yyval.strvalue)=staurosDota;
			}
#line 3152 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 1378 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			//klisi sunartisis edw?

			prefix_count = 1;autoName=true;
			if(DEBUG){cout<<yylineno<<": " << "Identifier {} setting custom name... "<<yytext<< endl;}
			idcount++;

			}
#line 3165 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 1389 "phase4/parser.yy" /* yacc.c:1646  */
    {	//maxScope++;
			//maxFScope++;
			//LookupName($1,maxScope);
			//argcheck = LookupforRef($1,maxScope);
			toAdd =fill3((yyvsp[0].strvalue),maxScope,yylineno,"none",maxFScope,0,ARGUMENT,true,currentscopeoffset(),currentscopespace());   //missing
			//cout << "FORMAL ARG OFFSET: " << endl << formalArgOffset << endl;
			if(!((isActive(toAdd))&&((isArgument(toAdd))))){
				insertH(toAdd);
				//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
				//inccurrscopeoffset();
				//cout << "EGINE INCREASE TO currentscopeoffset se: " << currentscopeoffset() << endl;
				if(DEBUG){cout<<"inserting  id"<<endl;}
			}
			else{ 
				cout<<yylineno<<": " <<"Syntax error : redefining argument "<<(yyvsp[0].strvalue)<<endl;
				isValid=false;
			}
			idcount++;
			if(DEBUG){cout<<yylineno<<": " << "Idlist ID "<<(yyvsp[0].strvalue)<< endl;}
			//maxScope--;
			//maxFScope--;
		}
#line 3192 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 1412 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//maxScope++;
			//maxFScope++;
			if(DEBUG){cout << "FORMAL ARG OFFSET: " << endl << formalArgOffset << endl;}
			toAdd =fill3((yyvsp[0].strvalue),maxScope,yylineno,"none",maxFScope,0,ARGUMENT,true,currentscopeoffset(),currentscopespace());   //missing
			if(!((isActive(toAdd))&&((isArgument(toAdd))))){
				//cout<<"inserting idlist comma id"<<" isactive:"<<isActive(toAdd)<<" , isrgument:"<<isArgument(toAdd)<<endl;
				insertH(toAdd);
				//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
				//inccurrscopeoffset();
				//cout << "EGINE INCREASE TO currentscopeoffset se: " << currentscopeoffset() << endl;

			}
			else{ 

				if(DEBUG){cout<<yylineno<<": " <<"Syntax error : redefining argument "<<(yyvsp[0].strvalue)<<endl;}
				isValid=false;
			}
			if(DEBUG){cout<<yylineno<<": " << "COMMA Argument "<<(yyvsp[0].strvalue)<< endl;}
			//maxScope--;
			//maxFScope--;
		}
#line 3219 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 1434 "phase4/parser.yy" /* yacc.c:1646  */
    {;}
#line 3225 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 1438 "phase4/parser.yy" /* yacc.c:1646  */
    {

				Symbol *kati= new Symbol;
				is_funcdef=1;
				if(autoName){
					autoName=false;
					functionName=setFunctionName();
				}
				else functionName=(yyvsp[0].strvalue);
				//i address -> krata to sto  line Function tou Symbol
				toAdd =fill3(functionName,maxScope,yylineno,functionName,maxFScope,currQuad,FUNC,true,-1,currentscopespace());
				Lookup(toAdd,FUNCDEF_MODE);
				localcheck =createFSymbol(functionName,maxScope,yylineno,functionName,maxFScope,currQuad,FUNC,true,-1,currentscopespace());   
				kati=Lookup(*localcheck,LVAL_LOCAL);

				aerials.push(currentscopeoffset());
				ownage.push(isLoop);
				isLoop=0;
				enterscopespace();
				resetformalargoffset();
				//Symbol *temp= new Symbol;
				//temp->name = functionName;
				(yyval.symvalue) = kati;

			}
#line 3255 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 1465 "phase4/parser.yy" /* yacc.c:1646  */
    { maxFScope++; maxScope++; }
#line 3261 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 1466 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout << "----BIKA FuncArgs-----" << endl;
			maxScope--;
			enterscopespace();
			resetfunctionlocaloffset();
		}
#line 3272 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 1475 "phase4/parser.yy" /* yacc.c:1646  */
    {	
			is_funcdef=0;
			//$<intvalue>$=currentscopeoffset();
			exitscopespace();
			hideThem(maxFScope);
			maxFScope--;
			
		}
#line 3285 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 1486 "phase4/parser.yy" /* yacc.c:1646  */
    {
			
			exitscopespace();
			Symbol *temp= new Symbol;
			temp = (yyvsp[-2].symvalue);
			temp->dotalocal = functionLocalOffset;//$<intvalue>3;
			if(DEBUG){cout<<(yyvsp[-2].symvalue)->name <<"  has dotalocal" <<functionLocalOffset<<endl;}
			temp->name = (yyvsp[-2].symvalue)->name;
			temp->type = FUNC;

			//$<symvalue>1->dotalocal=$<intvalue>3;
			unsigned oldoffset= aerials.top();
			aerials.pop();
			restorecurrscopeoffset(oldoffset);
			isLoop=ownage.top();
			ownage.pop();
			(yyval.symvalue)=temp;
			if(DEBUG){cout<<" $$ type"<<(yyval.symvalue)->type<<endl;}
			expr *ack = new expr;
			ack = lvalue_symbol(ack,temp);
			emit(funcend,nullptr,nullptr,ack,-1,yylineno);
			//cout << "FUNC: "<< $<symvalue>$->name<< "ME ARITHMO locals" << $<symvalue>$->dotalocal << endl;
		}
#line 3313 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 1585 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "INTCONST :"<< (yyvsp[0].intvalue) <<endl;}
								(yyval.exprvalue) = insertVal(yylval.intvalue,-1,"INTCONST");
								}
#line 3322 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 1589 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "Realconst "<< endl;}
								(yyval.exprvalue) = insertVal(-1,yylval.dvalue,"REALCONST");
							}
#line 3331 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 1593 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "String \""<<(yyvsp[0].strvalue)<<"\""<< endl;}
								(yyval.exprvalue) = constString_expr(yylval.strvalue);
							}
#line 3340 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 1597 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "Nil "<< endl;}
								(yyval.exprvalue) = insertVal(-1,-1,"KEYWORD_NIL");

							}
#line 3350 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 1602 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "True "<< endl;}
								(yyval.exprvalue) = insertVal(-1,-1,"KEYWORD_TRUE");
							}
#line 3359 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 1606 "phase4/parser.yy" /* yacc.c:1646  */
    {
								if(DEBUG){cout<<yylineno<<": |" << "False "<< endl;}
								(yyval.exprvalue) = insertVal(-1,-1,"KEYWORD_FALSE");
							}
#line 3368 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 1618 "phase4/parser.yy" /* yacc.c:1646  */
    {

			//cout<<yylineno<<": |" << "Lparent expr R_parent "<< endl;
			if(lvalfunc)
			{
				lvalfunc=0;
				assignParts.clear();
			}
			expr* cond = new expr;
			cond = true_test((yyvsp[-1].exprvalue), cond,-1);
			//if (arg1->changeLabel) $<intvalue>3=currQuad;

			//expr * cond = new expr;
			//true_test($<exprvalue>3,cond,0);

			//
			//arg1 = true_test($<exprvalue>1,arg1,$<intvalue>3);
			//if (arg1->changeLabel) $<intvalue>3=currQuad;
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			/////arg2 = true_test($<exprvalue>4,arg1,$<intvalue>3);
			//

			//apo edw
			false_backpatch(cond->false_index,0,currQuad);
			//OI MALAKIES EINAI EDW
			emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
			emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
			true_backpatch(cond->true_index,0,currQuad);
			emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
			emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			(yyval.intvalue) =  currQuad-1;
		}
#line 3408 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 1655 "phase4/parser.yy" /* yacc.c:1646  */
    {
			if(DEBUG){cout<<yylineno<<": |" << "Else "<< endl;}
			(yyval.intvalue)=currQuad;
			if(DEBUG){cout<<" key else int val ### "<<(yyval.intvalue)<<endl;}
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);


		}
#line 3421 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 1667 "phase4/parser.yy" /* yacc.c:1646  */
    {
				if(DEBUG){cout<<"EGW BACKPATCHARW TWRA"<<endl;}
				backpatch((yyvsp[-1].intvalue),currQuad);
				//$<break_index>$=$<break_index>2;
  				//$<cont_index>$=$<cont_index>2;
  				bc_indexes * bc= new bc_indexes;
  				bc->break_index=(yyvsp[0].indexes)->break_index;
				bc->cont_index=(yyvsp[0].indexes)->cont_index;
				(yyval.indexes)=bc;



			}
#line 3439 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 1681 "phase4/parser.yy" /* yacc.c:1646  */
    {
			if(DEBUG){cout<<yylineno<<": |" << "stmt  "<< endl;}
			backpatch((yyvsp[-3].intvalue),(yyvsp[-1].intvalue)+1);
			if(DEBUG){cout<<" key else int val apokatw ### "<<(yyvsp[-1].intvalue)<<endl;}
			backpatch((yyvsp[-1].intvalue),currQuad);
			//$<break_index>$=min($<break_index>2,$<break_index>4);
  			//$<cont_index>$=min($<cont_index>2,$<cont_index>4);
  			//$<break_index>$=merge_break($<break_index>2,$<break_index>4);
			//$<cont_index>$=merge_cont($<cont_index>2,$<cont_index>4);

			bc_indexes * bc= new bc_indexes;
  			bc->break_index=merge_break((yyvsp[-2].indexes)->break_index,(yyvsp[0].indexes)->break_index);
			bc->cont_index=merge_break((yyvsp[-2].indexes)->cont_index,(yyvsp[0].indexes)->cont_index);
			(yyval.indexes)=bc;
		}
#line 3459 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 1698 "phase4/parser.yy" /* yacc.c:1646  */
    {
    //cout << "BIKA WHILESTART" << endl;
    (yyval.intvalue) = currQuad;
    if(DEBUG)cout << (yyval.intvalue) << endl ;

    isLoop++;
    //


   }
#line 3474 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 1710 "phase4/parser.yy" /* yacc.c:1646  */
    {
    maxScope++;

    expr* cond = new expr;
	cond = true_test((yyvsp[-1].exprvalue), cond,-1);
    false_backpatch(cond->false_index,0,currQuad);
     //KAI EDW EXEI MALAKIES
	emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
	emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
	true_backpatch(cond->true_index,0,currQuad);
	emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
	emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
	(yyval.intvalue) =  currQuad-1;
  }
#line 3494 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 1727 "phase4/parser.yy" /* yacc.c:1646  */
    {
  //$<intvalue>1=currQuad+1;
  isLoop--;
  maxScope--;
  if(DEBUG){cout<<yylineno<<": |" << " While(expr)stmt"<< endl;}

  //both
   	//$<break_index>$=$<break_index>1;
  	//$<cont_index>$=$<cont_index>1;
  	bc_indexes * bc= new bc_indexes;
	bc->break_index=(yyvsp[0].indexes)->break_index;
	bc->cont_index=(yyvsp[0].indexes)->cont_index;
	(yyval.indexes)=bc;

}
#line 3514 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 1744 "phase4/parser.yy" /* yacc.c:1646  */
    {
   emit(jump,nullptr,nullptr,nullptr,(yyvsp[-2].intvalue),yylineno);
   if(DEBUG){cout<<yylineno<<": |" << " while "<< endl;}
   backpatch((yyvsp[-1].intvalue),currQuad);

   break_backpatch((yyvsp[0].indexes)->break_index,0,currQuad);
   cont_backpatch((yyvsp[0].indexes)->cont_index,0,(yyvsp[-2].intvalue));
   /*
   if(($<break_index>3>-1) && (breakvector.size())){
  						 break_manage($<break_index>3);
   				}
 	if(($<cont_index>3>-1) && (contvector.size())){
  						 continue_manage($<cont_index>3,$<intvalue>1);
   				}

	*/
   
  }
#line 3537 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 1769 "phase4/parser.yy" /* yacc.c:1646  */
    { 
 		(yyval.intvalue) = expr_list.size();
 		here=expr_list.size(); 
 		clearList = true;
		//cout<<yylineno<<":|"<<"*****L*****"<<endl;
		}
#line 3548 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 1778 "phase4/parser.yy" /* yacc.c:1646  */
    {

	if (clearList) { 
		expr_list.resize(here);
		clearList=false;

	}
}
#line 3561 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 1787 "phase4/parser.yy" /* yacc.c:1646  */
    {
		//printbreak() ;
			/*
		cout<"from "<<
		backpatch($<fordata>1->enter,$<intvalue>5+1);
		backpatch($<intvalue>2,currQuad);
		backpatch($<intvalue>5,$<fordata>1->test);
		backpatch($<intvalue>7,$<intvalue>2+1);
		cout<<yylineno<<": |" << "Forstmt"<< endl;
		isLoop++;
		
		// 				6765776 			2 						6766656 				0 
		cout<<" "<<$<break_index>1<<" "<<$<break_index>2<<" "<<$<break_index>3<<" "<<$<break_index>4<<" "<<$<break_index>5<<" "<<$<break_index>6<<" "<<$<break_index>7<<endl;
		// 4 						0 					10

		if(($<break_index>6>-1) && (breakvector.size())){
  						 break_manage($<break_index>6);
   				}
 		if(($<cont_index>6>-1) && (contvector.size())){
  						 continue_manage($<cont_index>6,$<intvalue>2+1);
   				}


		}
		*/
		backpatch((yyvsp[-8].fordata)->enter,(yyvsp[-2].intvalue)+1);
		backpatch((yyvsp[-7].intvalue),currQuad);
		backpatch((yyvsp[-2].intvalue),(yyvsp[-8].fordata)->test);
		backpatch((yyvsp[0].intvalue),(yyvsp[-7].intvalue)+1);
		if(DEBUG){cout<<yylineno<<": |" << "Forstmt"<< endl;}
		isLoop--;
		if(DEBUG){cout<<"from "<< (yyvsp[-6].intvalue) <<" to "<< (yyvsp[-4].intvalue) <<endl;}
		// 				6765776 			2 						6766656 				0 
		//cout<<" "<<$<break_index>1<<" "<<$<break_index>2<<" "<<$<break_index>3<<" "<<$<break_index>4<<" "<<$<break_index>5<<" "<<$<break_index>6<<" "<<$<break_index>7<<endl;
		// 4 						0 					10

		break_backpatch((yyvsp[-1].indexes)->break_index,0,currQuad);
   		cont_backpatch((yyvsp[-1].indexes)->cont_index,0,(yyvsp[-7].intvalue)+1);	
   		/*
		if(($<break_index>8>-1) && (breakvector.size())){
  						 break_manage($<break_index>8);
   				}
 		if(($<cont_index>8>-1) && (contvector.size())){
  						 continue_manage($<cont_index>8,$<intvalue>2+1);
   				}

		*/
		}
#line 3614 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 1841 "phase4/parser.yy" /* yacc.c:1646  */
    {
		fortmp=new forstr;
		expr * cond = new expr;
		//cout << "$5: "<<$<intvalue>5<<"\tcurrQuad: "<<currQuad<<endl;
		fortmp->test = (yyvsp[-2].intvalue);
		if(DEBUG)
		{
		cout<<"//////////////////////////////////////////////////"<<endl;
		cout<<"from "<< (yyvsp[-6].intvalue) <<" to "<< (yyvsp[-4].intvalue) <<endl;
		}	
		fix_elist( (yyvsp[-6].intvalue), (yyvsp[-4].intvalue));
		cond = true_test((yyvsp[-1].exprvalue), cond,-1);
		false_backpatch(cond->false_index,0,currQuad);
		emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
		emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
		true_backpatch(cond->true_index,0,currQuad);
		emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
		fortmp->enter= currQuad;
		emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,-1,yylineno);
		
		isLoop++;
		(yyval.fordata)=fortmp;

		//true_backpatch($<exprvalue>2->true_index,0,currQuad);

		//cout << "test: " << fortmp->test <<"\tenter: " <<fortmp->enter<<endl;
		//cout<<yylineno<<":|" <<"---forprefix---"<<endl;
		/*
		false_backpatch($<exprvalue>2->false_index,0,currQuad);
     //KAI EDW EXEI MALAKIES
	//emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>2, -1, yylineno);
	//emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
	true_backpatch($<exprvalue>2->true_index,0,currQuad);
	//emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>2, -1, yylineno);
	emit(if_eq,$<exprvalue>2,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
	$<intvalue>$ =  currQuad-1;*/


	  	}
#line 3659 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 1883 "phase4/parser.yy" /* yacc.c:1646  */
    { 
 	 	(yyval.intvalue) = currQuad;
		//cout<<yylineno<<":|"<<"*****S*****"<<endl;
 	  	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
   		}
#line 3669 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1890 "phase4/parser.yy" /* yacc.c:1646  */
    { 
 		(yyval.intvalue) = currQuad; 
		//cout<<yylineno<<":|"<<"*****L*****"<<endl;
		}
#line 3678 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1898 "phase4/parser.yy" /* yacc.c:1646  */
    {
		//cout<<yylineno<<": |" << "return ;"<< endl;
			emit(ret, nullptr, nullptr, nullptr, -1, yylineno);
		}
#line 3687 "phase4/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1903 "phase4/parser.yy" /* yacc.c:1646  */
    {
			//cout<<yylineno<<": |" << "return ;"<< endl;
			emit(ret, nullptr, nullptr, (yyvsp[-1].exprvalue), -1, yylineno);

		}
#line 3697 "phase4/parser.cpp" /* yacc.c:1646  */
    break;


#line 3701 "phase4/parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1910 "phase4/parser.yy" /* yacc.c:1906  */


int yyerror (const char * YaccProvidedMessage)
{	
	isValid=false;
	if ((strstr(YaccProvidedMessage,"$end")))
		cout<<yylineno<<": |"<<"Unexpected reach of the EOF."<<endl;
		//printf("Unexpected reach of the EOF.\n");
	else
		cout<<yylineno<<": |"<<" in line "<<yylineno<<", token "<<yytext<<endl;
		//printf("%s -- in line %d , token %s \n ",YaccProvidedMessage,yylineno,yytext);
	return 0;
}

int main(int argc,char **argv)
{	

	if(DEBUG){
		cout << "KANW DEBUG TWRA KAI KALA" << endl;
	}
	//breakvector.resize(1000);
	Scopelist.resize(100);
	breakMultiVector.resize(20);
	contMultiVector.resize(20);
	trueMultiVector.resize(20);
	falseMultiVector.resize(20);
	FILE *fp1, *fp2;
	streambuf *psbuf, *backup;
  	ofstream filestr;
	ofstream kalaitzos,binarw;
	kalaitzos.open(argv[20]);
  	filestr.open ("quads.txt");
  	ofstream instr;
  	instr.open ("binary.abc");
  	binarw.open("binary.abin", ios::out | ios::binary);
  	      // restore cout's original streambuf
	if(argc>1){
		fp1=freopen(argv[1],"r",stdin);
		if(fp1==NULL) {
			cout << "INPUT FILE NOT FOUND" << endl;
		}
		if(argc>2){
			fp2=freopen(argv[2],"w",stdout);
		}
	}
	//outfile.open("quads.txt");
	yyin=stdin;
	initializeHash();

	//cout<<endl;
	yyparse();
	//cout << "vlakas" << endl;
	//printSymbols();
	//printAll();
	if(DEBUG){printQuads();}
	//printStack();
	if (isValid){
		//cout<<"is valid so printing quads"<<endl;
		//validPrints();
		if(DEBUG){printAll();}
		
		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = filestr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
  		printQuads();
  		cout.rdbuf(backup);

  		//
  		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = kalaitzos.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf); 
  		//

		generate_binary();
		//backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = instr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
  		generate_abc();
  		psbuf = binarw.rdbuf();
  		cout.rdbuf(psbuf);
  		generate_o(binarw);
  		cout.rdbuf(backup);
  		
	} 

	else {
		//cout<<"is not valid, mpaaa"<<endl;
		if(DEBUG)
		{
			printAll();
			printQuads();
		}	
		cout<<"-ggs ownage failed."<<endl;
		
		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = filestr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
		cout<<"-ggs ownage failed."<<endl;
  		cout.rdbuf(backup);  
  		
	}
	if(DEBUG)
	{
		print_true();
		print_false();
	}

	//printtruelist();
	if(argc>1){
		fclose(fp1);
		if(argc>2){
			fclose(fp2);
		}
	}
	filestr.close();

	//outfile.close();
	return 0;
}
