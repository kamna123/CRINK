/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 16 "cuda.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/cuda_y.h"
/*#include "dependency_abstraction_2.h"
#include "Loop_Normalization.h"
#include "AffineTest.h"
#include "GCD_Banerjee_Test.h"
#include "Dependence_Testing_Interface.h"
#include "Omega_Test.h"
#include "Cycle_Shrinking.h"
#include "ExtendedCS.h"
#include "CodeGen_AffineKernel_Interface.h"
#include "CodeGen_CycleShrinking.h"
#include "CodeGen_ExtendedCycleShrinking.h"
#include "CodeGen_1_only_WAW.h"
#include "fdisplay_2.h"*/
#include <string.h>
#include<getopt.h>
#define LEFT 1;
#define RIGHT 0;
extern int count_loop=0;
int yylex(void);
void yyerror(char *);
//Functions:

void insert_variables(int type, struct StringNode* identifier,struct StringNode* value){
	variables_temp = variables;
	if(variables==NULL) {
		variables = (struct Var*)malloc(sizeof(struct Var));
		variables_temp = variables;
	}
	else {
		variables_temp = variables;
		while(variables_temp->next !=NULL) variables_temp = variables_temp->next;
		variables_temp->next = (struct Var*)malloc(sizeof(struct Var));
		variables_temp = variables_temp->next;
	}
	variables_temp->type = type;
	variables_temp->identifier = identifier;
	variables_temp->var_value=(value!=NULL)?atoi(value->string):-1;
	variables_temp->next = NULL;
}

void merge_StringNode(struct StringNode* sn1, struct StringNode* sn2){ 
	if(sn1==NULL){
		sn1 = sn2;
		return;
	}
	if(sn2==NULL) return;
	while(sn1->next!=NULL) sn1 = sn1->next;
	sn1->next = sn2;
}

void merge_StringNode1(struct StringNode** sn1, struct StringNode* sn2){ 
	if(*sn1==NULL){
		*sn1 = sn2;
		return;
	}
	if(sn2==NULL) return;
	struct StringNode* sn;
	sn = *sn1;
	while(sn->next!=NULL) sn = sn->next;
	sn->next = sn2;
}
/* add_loop_index(struct StringNode* loop_index)
{     struct Count_Loops* temp=(struct Count_Loops*)malloc(sizeof(struct Count_Loops));
      struct Count_Loops* temp1=head;
      if(head==NULL)
       {
         temp->count=loop_index;
          head=temp;
         temp->next=NULL;
        return;
       }
     else
         {
     while(temp1->next!=NULL) temp1=temp1->next;
         }
      temp1->next=temp;
      temp1->next->count=loop_index;
      temp1->next->next=NULL;
}*/
add_loop_index()
{
 count_loop++;
}
void add_into_Count_Loops(struct StatementNode* data)
{            struct Count_Loops* temp=(struct Count_Loops*)malloc(sizeof(struct Count_Loop));
                  temp->count=data;
                   temp->next=NULL;
             if( *head_count_loop==NULL)
                  {
                     *head_count_loop=temp;
                  }  
             else
               {
               temp->next=*head_count_loop;
               *head_count_loop=temp;
               }
                 
}
 add_loop_index_new(struct StringNode* id, struct StringNode* lb, struct StringNode* ub, struct StringNode* d, char op, int relop){
	struct LoopIndexVar_New* liv = (struct LoopIndexVar_New*)malloc(sizeof(struct LoopIndexVar_New));
	liv->loopIndex = id;
	liv->L=lb;
	liv->U=ub;
	liv->D=d;
	liv->op = op;
	liv->relop = relop;
	liv->next = loop_index_new;
	loop_index_new = liv;
       // return (loop_index_new);
     // add_loop_index(loop_index_new);
}

// no use
create_parallel_data(struct ParallelData** pd){
	struct ParallelData* temp;
	temp = (struct ParallelData*)malloc(sizeof(struct ParallelData));
	temp->loop_index = loop_index_new;
	temp->parallel_stmt = parallel_stmt;
	temp->left_var = NULL;
	temp->write_var = NULL;
	temp->read_var = NULL;
	temp->stmt_var = NULL;
	temp->left_stmt_var = NULL;
	temp->write_stmt_var = NULL;
	temp->read_stmt_var = NULL;
	temp->start_num = start_num;
	temp->end_num = end_num;
	temp->next = NULL;
	*pd = temp;
}

reset_parallel(){
	loop_index_new = NULL;
	parallel_stmt = NULL;
}



/* Line 371 of yacc.c  */
#line 212 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     CONSTANT = 259,
     STRING_LITERAL = 260,
     SIZEOF = 261,
     PTR_OP = 262,
     INC_OP = 263,
     DEC_OP = 264,
     LEFT_OP = 265,
     RIGHT_OP = 266,
     LE_OP = 267,
     GE_OP = 268,
     EQ_OP = 269,
     NE_OP = 270,
     AND_OP = 271,
     OR_OP = 272,
     MUL_ASSIGN = 273,
     DIV_ASSIGN = 274,
     MOD_ASSIGN = 275,
     ADD_ASSIGN = 276,
     SUB_ASSIGN = 277,
     LEFT_ASSIGN = 278,
     RIGHT_ASSIGN = 279,
     AND_ASSIGN = 280,
     XOR_ASSIGN = 281,
     OR_ASSIGN = 282,
     TYPE_NAME = 283,
     TYPEDEF = 284,
     EXTERN = 285,
     STATIC = 286,
     AUTO = 287,
     REGISTER = 288,
     CHAR = 289,
     SHORT = 290,
     INT = 291,
     LONG = 292,
     SIGNED = 293,
     UNSIGNED = 294,
     FLOAT = 295,
     DOUBLE = 296,
     CONST = 297,
     VOLATILE = 298,
     VOID = 299,
     STRUCT = 300,
     UNION = 301,
     ENUM = 302,
     ELLIPSIS = 303,
     CASE = 304,
     DEFAULT = 305,
     IF = 306,
     ELSE = 307,
     SWITCH = 308,
     WHILE = 309,
     DO = 310,
     FOR = 311,
     GOTO = 312,
     CONTINUE = 313,
     BREAK = 314,
     RETURN = 315,
     PARALLEL_START = 316,
     PARALLEL_END = 317,
     HASH_INCLUDE = 318,
     HASH_DEFINE = 319,
     PRINTF = 320,
     TYPE_OP = 321
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define SIZEOF 261
#define PTR_OP 262
#define INC_OP 263
#define DEC_OP 264
#define LEFT_OP 265
#define RIGHT_OP 266
#define LE_OP 267
#define GE_OP 268
#define EQ_OP 269
#define NE_OP 270
#define AND_OP 271
#define OR_OP 272
#define MUL_ASSIGN 273
#define DIV_ASSIGN 274
#define MOD_ASSIGN 275
#define ADD_ASSIGN 276
#define SUB_ASSIGN 277
#define LEFT_ASSIGN 278
#define RIGHT_ASSIGN 279
#define AND_ASSIGN 280
#define XOR_ASSIGN 281
#define OR_ASSIGN 282
#define TYPE_NAME 283
#define TYPEDEF 284
#define EXTERN 285
#define STATIC 286
#define AUTO 287
#define REGISTER 288
#define CHAR 289
#define SHORT 290
#define INT 291
#define LONG 292
#define SIGNED 293
#define UNSIGNED 294
#define FLOAT 295
#define DOUBLE 296
#define CONST 297
#define VOLATILE 298
#define VOID 299
#define STRUCT 300
#define UNION 301
#define ENUM 302
#define ELLIPSIS 303
#define CASE 304
#define DEFAULT 305
#define IF 306
#define ELSE 307
#define SWITCH 308
#define WHILE 309
#define DO 310
#define FOR 311
#define GOTO 312
#define CONTINUE 313
#define BREAK 314
#define RETURN 315
#define PARALLEL_START 316
#define PARALLEL_END 317
#define HASH_INCLUDE 318
#define HASH_DEFINE 319
#define PRINTF 320
#define TYPE_OP 321



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 174 "cuda.y"

	int NUM;
	struct SizeNode* Arr_size;
	struct StringNode* stringNode;
	struct StatementNode* stmtNode;
	struct LoopIndexVar* liv;
	struct ParallelData* pd;
        struct LoopIndexVar_New* loop_index;
      //  struct Count_Loops* lov;


/* Line 387 of yacc.c  */
#line 396 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 424 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  54
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1069

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  211

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,     2,     2,    82,    83,     2,
      69,    70,    72,    77,    71,    78,    80,    81,    79,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    87,    67,
      73,    68,    74,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    90,     2,    91,    85,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,    84,    76,    88,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    13,    17,    21,    27,
      33,    37,    40,    45,    50,    52,    54,    57,    61,    65,
      69,    74,    79,    81,    83,    87,    91,    95,    98,   102,
     108,   114,   116,   118,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   138,   140,   142,   145,   147,   150,   154,
     168,   182,   196,   210,   212,   214,   218,   222,   226,   232,
     238,   241,   244,   247,   250,   254,   256,   259,   260,   263,
     265,   269,   273,   277,   280,   283,   287,   289,   291,   293,
     295,   296,   301,   305,   309,   311,   313,   315,   317,   319,
     321,   323,   325,   327,   329,   331,   333,   335,   337,   339,
     341,   343,   345,   347,   349,   351,   353,   355,   357,   359,
     361,   363,   365,   367,   369,   371,   373,   375,   377,   379,
     381,   383,   385,   388,   393
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      93,     0,    -1,   108,    93,    -1,    94,    93,    -1,    -1,
     102,    93,    -1,   100,     3,    67,    -1,   100,   116,    67,
      -1,   100,     3,    68,   110,    67,    -1,   100,   116,    68,
     110,    67,    -1,   100,    99,    67,    -1,    95,    67,    -1,
     100,     3,    69,    70,    -1,   100,     3,    69,    96,    -1,
      97,    -1,    98,    -1,   100,    70,    -1,   100,    71,    97,
      -1,   100,     3,    70,    -1,   100,   116,    70,    -1,   100,
       3,    71,    98,    -1,   100,   116,    71,    98,    -1,     3,
      -1,   116,    -1,     3,    68,   110,    -1,   116,    68,   110,
      -1,     3,    71,    99,    -1,   101,    99,    -1,   116,    71,
      99,    -1,     3,    68,   110,    71,    99,    -1,   116,    68,
     110,    71,    99,    -1,    36,    -1,    34,    -1,    41,    -1,
      37,    -1,    40,    -1,    35,    -1,    38,    -1,    39,    -1,
      42,    -1,    43,    -1,    44,    -1,    31,    -1,    32,    -1,
     101,    -1,   100,   100,    -1,    72,    -1,    72,   101,    -1,
      61,   103,    62,    -1,    56,    69,     3,    68,   110,    67,
       3,    73,   110,    67,   105,    70,   104,    -1,    56,    69,
       3,    68,   110,    67,     3,    74,   110,    67,   105,    70,
     104,    -1,    56,    69,     3,    68,   110,    67,     3,    12,
     110,    67,   105,    70,   104,    -1,    56,    69,     3,    68,
     110,    67,     3,    13,   110,    67,   105,    70,   104,    -1,
     106,    -1,   103,    -1,    75,   103,    76,    -1,     3,    21,
     110,    -1,     3,    22,   110,    -1,     3,    68,     3,    77,
     110,    -1,     3,    68,     3,    78,   110,    -1,     3,     8,
      -1,     3,     9,    -1,     8,     3,    -1,     9,     3,    -1,
      75,   107,    76,    -1,   108,    -1,   108,   107,    -1,    -1,
     110,   109,    -1,    67,    -1,     3,   115,   110,    -1,   116,
     115,   110,    -1,   110,   113,   110,    -1,   110,   114,    -1,
     114,   110,    -1,   111,   110,   112,    -1,     3,    -1,     4,
      -1,    79,    -1,   116,    -1,    -1,     3,   111,   110,   112,
      -1,   110,    71,   110,    -1,   110,    80,   110,    -1,    69,
      -1,    70,    -1,    77,    -1,    78,    -1,    72,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    10,
      -1,    11,    -1,    17,    -1,    16,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    73,    -1,    74,    -1,    86,
      -1,    87,    -1,    88,    -1,     8,    -1,     9,    -1,    89,
      -1,    66,    -1,    68,    -1,    24,    -1,    23,    -1,    21,
      -1,    22,    -1,    18,    -1,    19,    -1,    20,    -1,    25,
      -1,    26,    -1,    27,    -1,     3,   117,    -1,    90,   110,
      91,   117,    -1,    90,   110,    91,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   205,   205,   206,   207,   208,   211,   212,   213,   214,
     215,   216,   219,   220,   223,   224,   227,   228,   231,   232,
     233,   234,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   266,   267,   270,   277,
     281,   283,   285,   289,   290,   291,   294,   295,   296,   297,
     298,   304,   310,   316,   324,   325,   330,   331,   334,   342,
     349,   352,   355,   358,   360,   362,   365,   366,   367,   372,
     373,   374,   378,   386,   397,   404,   411,   416,   421,   426,
     431,   436,   441,   446,   451,   456,   461,   466,   471,   476,
     481,   486,   491,   496,   501,   506,   513,   518,   523,   528,
     533,   536,   541,   546,   551,   556,   560,   565,   570,   575,
     580,   585,   592,   595,   598
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST",
  "VOLATILE", "VOID", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE",
  "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "PARALLEL_START", "PARALLEL_END",
  "HASH_INCLUDE", "HASH_DEFINE", "PRINTF", "TYPE_OP", "';'", "'='", "'('",
  "')'", "','", "'*'", "'<'", "'>'", "'{'", "'}'", "'+'", "'-'", "'0'",
  "'.'", "'/'", "'%'", "'&'", "'|'", "'^'", "'?'", "':'", "'~'", "'!'",
  "'['", "']'", "$accept", "FILE", "DEFINITION", "FUNC_DECL", "ARGUMENTS",
  "ONLY_TYPE", "TYPE_IDENTIFIER", "MANY_DEF", "TYPE", "POINTER",
  "PARALLEL_FOR", "FORLOOP_1", "FORLOOP_1_DEF", "IDENTIFIER_INC", "DEF",
  "BODY", "STATEMENT", "SEMI_COLON", "E", "OPEN_PAREN", "CLOSE_PAREN",
  "OP", "UNARY_OP", "ASSIGN_OP", "ARRAY_IDENTIFIER", "ARRAY_DATA_LIST", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,    59,    61,    40,
      41,    44,    42,    60,    62,   123,   125,    43,    45,    48,
      46,    47,    37,    38,   124,    94,    63,    58,   126,    33,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   101,   101,   102,   103,
     103,   103,   103,   104,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     3,     5,     5,
       3,     2,     4,     4,     1,     1,     2,     3,     3,     3,
       4,     4,     1,     1,     3,     3,     3,     2,     3,     5,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     3,    13,
      13,    13,    13,     1,     1,     3,     3,     3,     5,     5,
       2,     2,     2,     2,     3,     1,     2,     0,     2,     1,
       3,     3,     3,     2,     2,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      80,    76,    77,   107,   108,    42,    43,    32,    36,    31,
      34,    37,    38,    35,    33,    39,    40,    41,     0,   110,
      84,    46,    78,   106,   109,     0,    80,     0,     0,    44,
      80,    80,     0,    80,    80,    79,   116,   117,   118,   114,
     115,   113,   112,   119,   120,   121,   111,    80,    80,    80,
     122,     0,     0,    47,     1,     3,    11,     0,     0,    45,
      44,     0,     5,     2,    94,    95,    98,    99,   100,   101,
      97,    96,    69,    80,    88,   102,   103,    86,    87,    80,
      89,    90,    91,    92,    93,   104,   105,    68,    80,    73,
       0,    74,    80,     0,     0,    70,     0,    48,     6,    80,
       0,     0,    10,    22,    27,     0,    23,     7,    80,     0,
      82,    83,    72,    85,    75,    71,   124,    81,     0,     0,
      12,    13,    14,    15,     0,    26,    80,    80,     0,    28,
     123,    80,     8,    80,     0,    16,     0,     0,    24,    25,
       9,    80,     0,    76,    29,    79,    18,     0,    17,     0,
      19,     0,    30,     0,    80,    80,    20,     0,    21,     0,
      80,    80,    80,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    80,    80,     0,    62,    63,    80,    80,    80,    80,
      56,    57,     0,    80,    54,    51,    53,    65,    52,    49,
      50,    80,    80,     0,     0,    80,    58,    59,    55,    64,
      66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,   121,   122,   123,   104,    59,    29,
      30,   194,   195,   175,   196,   204,    31,    87,    32,    33,
     114,    88,    34,    49,    35,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -154
static const yytype_int16 yypact[] =
{
     186,   711,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,   -47,  -154,
    -154,   -61,  -154,  -154,  -154,    29,   186,     8,   835,  -154,
     186,   186,   344,   236,   236,    20,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,   236,   236,   236,
    -154,     0,     9,  -154,  -154,  -154,  -154,    94,    14,   997,
       5,   -44,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,   236,  -154,  -154,  -154,  -154,  -154,   236,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,   236,  -154,
     426,   734,   236,   318,   426,   734,    79,  -154,  -154,   236,
     978,     5,  -154,   -53,  -154,     5,    24,  -154,   236,     5,
     734,   734,   734,  -154,  -154,   734,     1,  -154,    35,   450,
    -154,  -154,  -154,  -154,   305,  -154,   236,   236,   474,  -154,
    -154,   236,  -154,   201,   -40,  -154,   997,   -49,   816,   840,
    -154,   201,   556,   912,  -154,   940,  -154,   997,  -154,   955,
    -154,   997,  -154,   102,   236,   236,  -154,   913,  -154,    -6,
     236,   236,   236,   236,   580,   604,   686,   710,    11,    11,
      11,    11,     4,   106,   108,    43,    49,    50,    54,  -154,
    -154,   236,   236,   115,  -154,  -154,    48,    48,    48,    48,
     734,   734,    -4,   193,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,   236,   236,    63,    65,   228,   734,   734,  -154,  -154,
    -154
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,    34,  -154,  -154,  -154,   -10,   -81,   -25,     2,   -11,
    -154,   -17,  -153,  -116,  -154,   -77,    90,  -154,    52,     3,
      53,  -154,   -32,   -30,   -12,    26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const yytype_int16 yytable[] =
{
      89,    52,    28,    58,    48,    92,   160,   161,   103,    51,
      53,    21,   179,   180,   172,   126,    61,    60,   101,   173,
     174,   150,   151,   107,   108,   181,   182,   109,    28,    54,
     146,   147,    28,    28,   198,   199,   200,    47,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   106,   105,
      47,     1,     2,   176,   177,   178,     3,     4,    89,    89,
      55,    89,    89,    89,    62,    63,   156,   162,   163,    96,
     158,    97,   183,   201,   202,    56,   125,    21,    89,    89,
      89,   102,   118,    89,   129,    90,    91,    89,    46,   106,
     105,    47,   127,   106,   105,   109,    89,   106,   105,    93,
      94,    95,   124,   131,    51,   159,    89,    89,   144,   184,
      89,   185,   137,   186,    19,    92,   152,    20,   192,   187,
     188,   145,   105,   193,   189,   110,   148,    22,   210,   145,
     105,   111,    89,    89,    89,    89,    23,    24,   149,   208,
     112,   209,   130,     0,   115,   137,    48,   117,     0,   157,
       0,   119,     0,   157,     0,     0,     0,     0,    89,    89,
     128,    98,    99,   100,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    89,   203,     0,   138,   139,
       0,     0,     0,   142,    47,   110,    -4,     0,     0,     1,
       2,     0,     0,   110,     3,     4,     1,     2,     0,     0,
       0,     3,     4,     0,   143,     2,   138,   139,     0,     3,
       4,     0,   164,   165,   166,   167,     0,     5,     6,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     1,     2,   190,   191,     0,     3,     4,     0,     1,
       2,     0,     0,     0,     3,     4,     0,    18,     0,    51,
       0,     0,    19,   206,   207,    20,     0,     0,    21,    19,
       0,     0,    20,     0,     0,    22,     0,    19,     0,   -67,
      20,     0,    22,    21,    23,    24,   197,   197,   197,   197,
      22,    23,    24,   205,     0,     0,     0,     0,     0,    23,
      24,     0,     0,     0,    19,   205,     0,    20,     0,     0,
       0,     0,    19,     0,   -67,    20,     0,    22,   134,     0,
       0,     0,     0,     0,     0,    22,    23,    24,     0,     0,
       0,     0,     0,     0,    23,    24,     3,     4,    64,    65,
      66,    67,    68,    69,    70,    71,     5,     6,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     3,     4,    64,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,    21,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,    73,
      74,    75,    76,     0,     0,    77,    78,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    23,    24,     0,   116,
      19,    72,     0,     0,     0,    73,    74,    75,    76,     0,
       0,    77,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    23,    24,     3,     4,    64,    65,    66,    67,
      68,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,    64,    65,    66,    67,    68,    69,
      70,    71,    19,     0,     0,     0,   113,    73,    74,    75,
      76,     0,     0,    77,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    23,    24,    19,   132,     0,     0,
       0,   133,    74,    75,    76,     0,     0,    77,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    23,    24,
      19,   140,     0,     0,     0,   141,    74,    75,    76,     0,
       0,    77,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    23,    24,     3,     4,    64,    65,    66,    67,
      68,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,    64,    65,    66,    67,    68,    69,
      70,    71,    19,   153,     0,     0,     0,    73,    74,    75,
      76,     0,     0,    77,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    23,    24,    19,   168,     0,     0,
       0,    73,    74,    75,    76,     0,     0,    77,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    23,    24,
      19,   169,     0,     0,     0,    73,    74,    75,    76,     0,
       0,    77,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    23,    24,     3,     4,    64,    65,    66,    67,
      68,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
      64,    65,    66,    67,    68,    69,    70,    71,     0,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,     0,     3,     4,    64,    65,    66,    67,    68,    69,
      70,    71,    19,   170,     0,     0,     0,    73,    74,    75,
      76,     0,     0,    77,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    23,    24,    19,   171,     0,    46,
      20,    73,    74,    75,    76,     0,     0,    77,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    23,    24,
      19,    47,     0,     0,     0,    73,    74,    75,    76,     0,
       0,    77,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    23,    24,     3,     4,    64,    65,    66,    67,
      68,    69,    70,    71,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    19,     0,     0,     0,     0,   133,    74,    75,
      76,     0,     0,    77,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    23,    24,    19,    21,     0,     0,
       0,   141,    74,    75,    76,     0,   134,    77,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    23,    24,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,     0,     0,     5,     6,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -22,
     154,    20,     0,   101,     0,    21,     5,     6,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    47,     0,     0,     0,     0,   -23,   155,     5,
       6,   109,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,   135,   136,    21,     5,     6,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,     0,     0,     0,   120,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-154)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      32,    18,     0,    28,     1,    35,    12,    13,     3,    56,
      21,    72,     8,     9,     3,    68,    28,    28,    71,     8,
       9,    70,    71,    67,    68,    21,    22,    71,    26,     0,
      70,    71,    30,    31,   187,   188,   189,    90,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    60,    60,
      90,     3,     4,   169,   170,   171,     8,     9,    90,    91,
      26,    93,    94,    95,    30,    31,   147,    73,    74,    69,
     151,    62,    68,    77,    78,    67,   101,    72,   110,   111,
     112,    67,     3,   115,   109,    33,    34,   119,    68,   101,
     101,    90,    68,   105,   105,    71,   128,   109,   109,    47,
      48,    49,   100,    68,    56,     3,   138,   139,   133,     3,
     142,     3,   124,    70,    66,   145,   141,    69,     3,    70,
      70,   133,   133,    75,    70,    73,   136,    79,   205,   141,
     141,    79,   164,   165,   166,   167,    88,    89,   136,    76,
      88,    76,   116,    -1,    92,   157,   143,    94,    -1,   147,
      -1,    99,    -1,   151,    -1,    -1,    -1,    -1,   190,   191,
     108,    67,    68,    69,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   206,   207,   193,    -1,   126,   127,
      -1,    -1,    -1,   131,    90,   133,     0,    -1,    -1,     3,
       4,    -1,    -1,   141,     8,     9,     3,     4,    -1,    -1,
      -1,     8,     9,    -1,     3,     4,   154,   155,    -1,     8,
       9,    -1,   160,   161,   162,   163,    -1,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     3,     4,   181,   182,    -1,     8,     9,    -1,     3,
       4,    -1,    -1,    -1,     8,     9,    -1,    61,    -1,    56,
      -1,    -1,    66,   201,   202,    69,    -1,    -1,    72,    66,
      -1,    -1,    69,    -1,    -1,    79,    -1,    66,    -1,    76,
      69,    -1,    79,    72,    88,    89,   186,   187,   188,   189,
      79,    88,    89,   193,    -1,    -1,    -1,    -1,    -1,    88,
      89,    -1,    -1,    -1,    66,   205,    -1,    69,    -1,    -1,
      -1,    -1,    66,    -1,    76,    69,    -1,    79,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    77,    78,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    66,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    66,    67,    -1,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    66,    67,    -1,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    66,    67,    -1,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    66,    67,    -1,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    66,    67,    -1,    68,
      69,    71,    72,    73,    74,    -1,    -1,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      66,    90,    -1,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    66,    72,    -1,    -1,
      -1,    71,    72,    73,    74,    -1,     3,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    -1,    71,    -1,    72,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    67,    68,    31,
      32,    71,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    70,    71,    72,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     8,     9,    31,    32,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    61,    66,
      69,    72,    79,    88,    89,    93,    94,    95,   100,   101,
     102,   108,   110,   111,   114,   116,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    68,    90,   111,   115,
     117,    56,   103,   101,     0,    93,    67,     3,    99,   100,
     101,   116,    93,    93,    10,    11,    12,    13,    14,    15,
      16,    17,    67,    71,    72,    73,    74,    77,    78,    80,
      81,    82,    83,    84,    85,    86,    87,   109,   113,   114,
     110,   110,   115,   110,   110,   110,    69,    62,    67,    68,
      69,    71,    67,     3,    99,   101,   116,    67,    68,    71,
     110,   110,   110,    70,   112,   110,    91,   112,     3,   110,
      70,    96,    97,    98,   100,    99,    68,    68,   110,    99,
     117,    68,    67,    71,     3,    70,    71,   116,   110,   110,
      67,    71,   110,     3,    99,   116,    70,    71,    97,   100,
      70,    71,    99,    67,    68,    68,    98,   100,    98,     3,
      12,    13,    73,    74,   110,   110,   110,   110,    67,    67,
      67,    67,     3,     8,     9,   105,   105,   105,   105,     8,
       9,    21,    22,    68,     3,     3,    70,    70,    70,    70,
     110,   110,     3,    75,   103,   104,   106,   108,   104,   104,
     104,    77,    78,   103,   107,   108,   110,   110,    76,    76,
     107
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
/* Line 1787 of yacc.c  */
#line 208 "cuda.y"
    {(yyvsp[(1) - (2)].pd)->next = parallel_data; parallel_data = (yyvsp[(1) - (2)].pd);}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 211 "cuda.y"
    {insert_variables((yyvsp[(1) - (3)].NUM),(yyvsp[(2) - (3)].stringNode),NULL);}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 212 "cuda.y"
    {insert_variables((yyvsp[(1) - (3)].NUM),(yyvsp[(2) - (3)].stringNode),NULL);}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 213 "cuda.y"
    {insert_variables((yyvsp[(1) - (5)].NUM),(yyvsp[(2) - (5)].stringNode),(yyvsp[(4) - (5)].stringNode));}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 214 "cuda.y"
    {insert_variables((yyvsp[(1) - (5)].NUM),(yyvsp[(2) - (5)].stringNode),(yyvsp[(4) - (5)].stringNode));}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 237 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (1)].stringNode),NULL);}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 238 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (1)].stringNode),NULL);}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 239 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode));}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 240 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode));}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 241 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (3)].stringNode),NULL);}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 243 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (3)].stringNode),NULL);}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 244 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (5)].stringNode),(yyvsp[(3) - (5)].stringNode));}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 245 "cuda.y"
    {insert_variables(type,(yyvsp[(1) - (5)].stringNode),(yyvsp[(3) - (5)].stringNode));}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 248 "cuda.y"
    {(yyval.NUM) = 1; type=(yyval.NUM);}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 249 "cuda.y"
    {(yyval.NUM) = 2; type=(yyval.NUM);}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 250 "cuda.y"
    {(yyval.NUM) = 3; type=(yyval.NUM);}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 251 "cuda.y"
    {(yyval.NUM) = 4; type=(yyval.NUM);}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 252 "cuda.y"
    {(yyval.NUM) = 5; type=(yyval.NUM);}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 253 "cuda.y"
    {(yyval.NUM) = 6; type=(yyval.NUM);}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 254 "cuda.y"
    {(yyval.NUM) = 0; type=(yyval.NUM);}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 255 "cuda.y"
    {(yyval.NUM) = 10; type=(yyval.NUM);}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 256 "cuda.y"
    {(yyval.NUM) = 1000; type=(yyval.NUM);}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 257 "cuda.y"
    {(yyval.NUM) = 0; type=(yyval.NUM);}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 258 "cuda.y"
    {(yyval.NUM) = 0; type=(yyval.NUM);}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 259 "cuda.y"
    {(yyval.NUM) = 100; type=(yyval.NUM);}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 260 "cuda.y"
    {(yyval.NUM) = 0; type=(yyval.NUM);}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 261 "cuda.y"
    {(yyval.NUM) = (yyvsp[(1) - (1)].NUM); type=(yyval.NUM);}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 262 "cuda.y"
    {(yyval.NUM) = (yyvsp[(1) - (2)].NUM)+(yyvsp[(2) - (2)].NUM); type=(yyval.NUM);}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 266 "cuda.y"
    {(yyval.NUM) = 10000;}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 267 "cuda.y"
    {(yyval.NUM) = 10000 + (yyvsp[(2) - (2)].NUM);}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 270 "cuda.y"
    {(yyval.pd)=NULL; 
// no use  
add_loop_index();
create_parallel_data(&(yyval.pd)); /*reset_parallel();*/}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 278 "cuda.y"
    {add_loop_index_new((yyvsp[(3) - (13)].stringNode),(yyvsp[(5) - (13)].stringNode),(yyvsp[(9) - (13)].stringNode),(yyvsp[(11) - (13)].stringNode),'+',1); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 282 "cuda.y"
    {add_loop_index_new((yyvsp[(3) - (13)].stringNode),(yyvsp[(5) - (13)].stringNode),(yyvsp[(9) - (13)].stringNode),(yyvsp[(11) - (13)].stringNode),'-',2);}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 284 "cuda.y"
    {add_loop_index_new((yyvsp[(3) - (13)].stringNode),(yyvsp[(5) - (13)].stringNode),(yyvsp[(9) - (13)].stringNode),(yyvsp[(11) - (13)].stringNode),'+',3);}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 286 "cuda.y"
    {add_loop_index_new((yyvsp[(3) - (13)].stringNode),(yyvsp[(5) - (13)].stringNode),(yyvsp[(9) - (13)].stringNode),(yyvsp[(11) - (13)].stringNode),'-',4);}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 294 "cuda.y"
    {(yyval.stringNode) = (yyvsp[(3) - (3)].stringNode);}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 295 "cuda.y"
    {(yyval.stringNode) = (yyvsp[(3) - (3)].stringNode);}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 296 "cuda.y"
    {(yyval.stringNode) = (yyvsp[(5) - (5)].stringNode);}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 297 "cuda.y"
    {(yyval.stringNode) = (yyvsp[(5) - (5)].stringNode);}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 299 "cuda.y"
    {   (yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                    strcpy((yyval.stringNode)->string,"1"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 305 "cuda.y"
    {     (yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                    strcpy((yyval.stringNode)->string,"1"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 311 "cuda.y"
    {   (yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                    strcpy((yyval.stringNode)->string,"1"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 317 "cuda.y"
    {   (yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                    strcpy((yyval.stringNode)->string,"1"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 324 "cuda.y"
    {(yyval.stmtNode)=(yyvsp[(2) - (3)].stmtNode); /*if(parallel_flag)*/ parallel_stmt=(yyval.stmtNode);}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 325 "cuda.y"
    {(yyval.stmtNode)=(yyvsp[(1) - (1)].stmtNode); /*if(parallel_flag)*/ parallel_stmt=(yyval.stmtNode);}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 330 "cuda.y"
    {(yyvsp[(1) - (2)].stmtNode)->next = (yyvsp[(2) - (2)].stmtNode); (yyval.stmtNode)=(yyvsp[(1) - (2)].stmtNode);}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 331 "cuda.y"
    {(yyval.stmtNode) = NULL;}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 334 "cuda.y"
    {(yyval.stmtNode)=(struct StatementNode*)malloc(sizeof(struct StatementNode)); 
                          (yyval.stmtNode)->next=NULL; 
                          merge_StringNode((yyvsp[(1) - (2)].stringNode),(yyvsp[(2) - (2)].stringNode)); 
                          (yyval.stmtNode)->stringNode=(yyvsp[(1) - (2)].stringNode);
                          add_into_Count_Loops((yyval.stmtNode));                            
                          }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 342 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,";"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 349 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(2) - (3)].stringNode));  //ex: a=E then merge a,=,E
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode); /*if(parallel_flag) {add_parallel_var($1,$2);}*/}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 352 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(2) - (3)].stringNode)); 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode); /*if(parallel_flag) {add_parallel_var($1,$2);}*/}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 355 "cuda.y"
    {merge_StringNode1(&(yyvsp[(1) - (3)].stringNode),(yyvsp[(2) - (3)].stringNode)); 
                                     merge_StringNode1(&(yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode);}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 358 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (2)].stringNode),(yyvsp[(2) - (2)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (2)].stringNode);}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 360 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (2)].stringNode),(yyvsp[(2) - (2)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (2)].stringNode);}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 362 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(2) - (3)].stringNode)); 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode);}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 365 "cuda.y"
    {(yyval.stringNode)=(yyvsp[(1) - (1)].stringNode);}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 366 "cuda.y"
    {(yyval.stringNode)=(yyvsp[(1) - (1)].stringNode);}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 367 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy((yyval.stringNode)->string,"0"); 
                                     (yyval.stringNode)->next = NULL; 
                                     (yyval.stringNode)->size = NULL;}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 372 "cuda.y"
    {(yyval.stringNode)=(yyvsp[(1) - (1)].stringNode);}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 373 "cuda.y"
    {(yyval.stringNode)=NULL;}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 374 "cuda.y"
    {merge_StringNode((yyvsp[(1) - (4)].stringNode),(yyvsp[(2) - (4)].stringNode)); 
                                        merge_StringNode((yyvsp[(1) - (4)].stringNode),(yyvsp[(3) - (4)].stringNode)); 
                                        merge_StringNode((yyvsp[(1) - (4)].stringNode),(yyvsp[(4) - (4)].stringNode)); 
                                        (yyval.stringNode)=(yyvsp[(1) - (4)].stringNode);}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 378 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy((yyval.stringNode)->string,","); 
                                     (yyval.stringNode)->next = NULL; 
                                     (yyval.stringNode)->size = NULL; 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyval.stringNode)); 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode);}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 386 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                                     (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                                     strcpy((yyval.stringNode)->string,"."); 
                                     (yyval.stringNode)->next = NULL; 
                                     (yyval.stringNode)->size = NULL; 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyval.stringNode)); 
                                     merge_StringNode((yyvsp[(1) - (3)].stringNode),(yyvsp[(3) - (3)].stringNode)); 
                                     (yyval.stringNode)=(yyvsp[(1) - (3)].stringNode);}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 397 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"("); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 404 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                  (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                  strcpy((yyval.stringNode)->string,")"); 
                  (yyval.stringNode)->next = NULL; 
                  (yyval.stringNode)->size = NULL;}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 411 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"+"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 416 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"-"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 421 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"*"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 426 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"/"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 431 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"%"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 436 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"&"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 441 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"|"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 446 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"^"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 451 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"<<"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 456 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,">>"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 461 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"||"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 466 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"&&"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 471 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"<="); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 476 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,">="); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 481 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"=="); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 486 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                 strcpy((yyval.stringNode)->string,"!="); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 491 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"<"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 496 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,">"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 501 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,"?"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 506 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                 (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                 strcpy((yyval.stringNode)->string,":"); 
                 (yyval.stringNode)->next = NULL; 
                 (yyval.stringNode)->size = NULL;}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 513 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                     (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                     strcpy((yyval.stringNode)->string,"~"); 
                     (yyval.stringNode)->next = NULL; 
                     (yyval.stringNode)->size = NULL;}
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 518 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                    strcpy((yyval.stringNode)->string,"++"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 523 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                    strcpy((yyval.stringNode)->string,"--"); 
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 528 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                    (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                    strcpy((yyval.stringNode)->string,"!");
                    (yyval.stringNode)->next = NULL; 
                    (yyval.stringNode)->size = NULL;}
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 533 "cuda.y"
    {(yyval.stringNode)=(yyvsp[(1) - (1)].stringNode);}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 536 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*2); 
                             strcpy((yyval.stringNode)->string,"="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 541 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*4); 
                             strcpy((yyval.stringNode)->string,">>="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 546 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*4); 
                             strcpy((yyval.stringNode)->string,"<<="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 551 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"+="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 556 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); strcpy((yyval.stringNode)->string,"-="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 560 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"*="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 565 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"/="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 570 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"%="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 575 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"&="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 580 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"^="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 585 "cuda.y"
    {(yyval.stringNode)=(struct StringNode*)malloc(sizeof(struct StringNode)); 
                             (yyval.stringNode)->string=(char *)malloc(sizeof(char)*3); 
                             strcpy((yyval.stringNode)->string,"|="); 
                             (yyval.stringNode)->next = NULL; 
                             (yyval.stringNode)->size = NULL;}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 592 "cuda.y"
    {(yyval.stringNode)=(yyvsp[(1) - (2)].stringNode); (yyval.stringNode)->size=(yyvsp[(2) - (2)].Arr_size);}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 596 "cuda.y"
    {(yyval.Arr_size)=(struct SizeNode*)malloc(sizeof(struct SizeNode)); 
                            (yyval.Arr_size)->sizeString=(yyvsp[(2) - (4)].stringNode); (yyval.Arr_size)->next=(yyvsp[(4) - (4)].Arr_size);}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 599 "cuda.y"
    {(yyval.Arr_size)=(struct SizeNode*)malloc(sizeof(struct SizeNode)); 
                            (yyval.Arr_size)->sizeString=(yyvsp[(2) - (3)].stringNode); 
                            (yyval.Arr_size)->next=NULL;}
    break;


/* Line 1787 of yacc.c  */
#line 2830 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 605 "cuda.y"

#include "lex.yy.c"
char DependencyExists='n';
int id_max=0;
int line_num=0;
int start_num=0;
int end_num=0;
int Total_Phi=0;
int type=0;
int noOfNestedLoops=0;
int verbosity=0;
char VariableDependenceDist='n';
char AffineKernel='n';

struct Var* variables = NULL;
struct Var* original_variables = NULL;
struct Var* variables_temp = NULL;
struct Stmt_Var* stmt_var = NULL;
struct Stmt_Var* left_stmt_var = NULL;
struct Stmt_Var* write_stmt_var = NULL;
struct Stmt_Var* read_stmt_var = NULL;
struct LoopIndexVar* loop_index=NULL;
struct StatementNode* left_var=NULL;
struct StatementNode* write_var=NULL;
struct StatementNode* read_var=NULL;
struct StatementNode* parallel_stmt=NULL;
struct LoopIndexVar_New* loop_index_new=NULL;
struct LoopIndexVar_New* loopIndex_temp=NULL;
struct LoopIndexVar_New* loop_index_new_start = NULL;
struct LoopIndexVar_New* loop_index_new_end = NULL;
struct Phi_Values* lambda_var=NULL;
struct ReferencePair *RefPair=NULL;
struct DDV *DDVvector=NULL;
struct ParallelData* parallel_data = NULL;// no use
struct  Count_Loops* head=NULL;

void display_SizeNode(int verbosity_no, struct SizeNode* size_node){  // display [3][4]
	while(size_node!=NULL){
		printMessage(verbosity_no,"[");
		display_StringNode(verbosity_no, size_node->sizeString);
		printMessage(verbosity_no,"]");
		size_node = size_node->next;
	}

}

                    

void display_StringNode(int verbosity_no, struct StringNode* str_node){ //display A[B[
	while(str_node!=NULL){
		printMessage(verbosity_no,"%s", str_node->string);
		display_SizeNode(verbosity_no, str_node->size);
		str_node = str_node->next;
	}
}
/*void display_No_of_loops(int verbosity_no,struct Count_Loops* loop)
 {
             while(loop!=NULL)
                   {
                    display_StringNode(verbosity_no,loop->count);
                     printMessage(verbosity_no, "\n");
                     loop=loop->next;
                   }
}*/
void display_No_of_loops()
{
                 int temp=count_loop;
                  int start=1;
                    while(start!=temp+1)
                        {
                         printf("%d\n",start);
                           start++;
                        }
                           
}


void display_StatementNode(int verbosity_no, struct StatementNode* stmt){
	while(stmt!=NULL){
		display_StringNode(verbosity_no, stmt->stringNode);
		printMessage(verbosity_no, "\n");
		stmt = stmt->next;
	}
}

void display_LoopIndexVar(int verbosity_no, struct LoopIndexVar* loop_id){
	while(loop_id!=NULL){
		display_StringNode(verbosity_no, loop_id->loopIndex);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, loop_id->size);
		printMessage(verbosity_no, "\n");
		loop_id = loop_id->next;
	}
}


void display_LoopIndexVar_New(int verbosity_no, struct LoopIndexVar_New* loop_id){
	while(loop_id!=NULL){
		display_StringNode(verbosity_no, loop_id->loopIndex);
		printMessage(verbosity_no, ": [");
		display_StringNode(verbosity_no, loop_id->L);
		printMessage(verbosity_no, ",");
		display_StringNode(verbosity_no, loop_id->U);
		printMessage(verbosity_no, (loop_id->relop==1) ? ")" : "]");
		printMessage(verbosity_no, "%c",loop_id->op);
		display_StringNode(verbosity_no, loop_id->D);
		printMessage(verbosity_no, "\n");
		loop_id = loop_id->next;
	}
}

                      
       
void display_type(int verbosity_no, int t){
	int n = (t/1000)%10;
	//t=t%1000;
	switch(n){
		case 1 : printMessage(verbosity_no, "const"); break;
	}
	n=(t/100)%10;
	switch(n){
		case 1 : printMessage(verbosity_no, "static");break;
	}
	n = (t/10)%10;
	switch(n){
		case 1 : printMessage(verbosity_no, "unsigned");break;
	}
	n = t%10;
	switch(n){
		case 0 : printMessage(verbosity_no, "void");break;
		case 1 : printMessage(verbosity_no, "int");break;
		case 2 : printMessage(verbosity_no, "char");break;
		case 3 : printMessage(verbosity_no, "double");break;
		case 4 : printMessage(verbosity_no, "long");break;
		case 5 : printMessage(verbosity_no, "float");break;
		case 6 : printMessage(verbosity_no, "short");break;
	}
}

void display_Var(int verbosity_no, struct Var* var){
	while(var!=NULL){
		display_type(verbosity_no, var->type);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, var->identifier);
		printMessage(verbosity_no, "\n");
		var = var->next;
	}
}

void display_Stmt_Var(int verbosity_no, struct Stmt_Var* var){
	while(var!=NULL){
		display_type(verbosity_no, var->var->type);
		printMessage(verbosity_no, ":");
		display_StringNode(verbosity_no, var->var->identifier);
		printMessage(verbosity_no, "\n");
		var = var->next;
	}
}

void yyerror(char *s) {
	printMessage(10, "ERROR:  %s \n",s);
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

void printMessage(int verbosity_no, char *format, ...)
{
   va_list args;
   if(verbosity_no>=verbosity){
       va_start(args, format);
       vprintf(format, args);
       va_end(args);
   }
}

void main(int argc, char* argv[]){
	char* outfile;
	char* infile, *fileName;
	char* dependence_test,*shrinking,*verbosity_no;
	
	extern FILE *yyin, *yyout;
	
	dependence_test = (char*)malloc(sizeof(char)*20);
	verbosity_no = (char*)malloc(sizeof(char)*20);
	shrinking = (char*)malloc(sizeof(char)*20);
	infile = (char*)malloc(sizeof(char)*50);
	fileName = (char*)malloc(sizeof(char)*50);
	strcpy(infile,"input/");
	outfile = (char*)malloc(sizeof(char)*50);
	strcpy(outfile,"output/");
	
	verbosity=10;
	strcpy(dependence_test, "gcd");
	strcpy(shrinking, "simple");
	
	static struct option long_options[] = {
        {"verbosityLevel",      required_argument,       0,  'v' },
        {"fileName", required_argument,       0,  'f' },
        {"depTest",    required_argument, 0,  'd' },
        {"cycleShrink",   required_argument, 0,  'c' },
        {0,           0,                 0,  0   }
        };
        
    int long_index =0, opt;
    while ((opt = getopt_long(argc, argv,"v:f:d:c:", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
             case 'v' : 
                   verbosity = atoi(optarg);
                   break;
             case 'f' : 
                   strcpy(fileName, optarg);
                   strcat(infile, optarg);
                   strcat(outfile, optarg);
            	   strcat(outfile, "u");
                   break;
             case 'd' : 
                   strcpy(dependence_test, optarg);
                   break;
             case 'c' : 
                   strcpy(shrinking, optarg);
                   break;
             default: 
                    fprintf(stderr, "Usage: %s [--verbosityLevel=value] [--fileName=name.c] [--depTest=gcd/banerjee/omega] [--cycleShrink=simple/selective/true_dependence/extShrinking1/extShrinking2]\n", argv[0]);
                   exit(EXIT_FAILURE);
            }
        }
	
	if(strcmp(fileName,"")==0)
	{
	    strcat(infile, "input.c");
	    strcat(outfile, "input.cu");
	}
	if(strcmp(dependence_test,"")==0)
            strcpy(dependence_test,"gcd");
    if(strcmp(shrinking,"")==0)
            strcpy(shrinking,"simple");
	
	in = fopen(infile, "r");
	out = fopen(outfile, "w");
	yyin = fopen(infile, "r");
	//verbosity=atoi(verbosity_no+1);
	if(yyin==NULL) {
		printMessage(10,"%s : FILE NOT FOUND\n", infile);
		return;
	}
	yyparse();
	
	// now we have loop index variables and parallel statement
	/*parallel_stmt = parallel_data->parallel_stmt;
	loop_index_new = parallel_data->loop_index;
	*/
        printMessage(10,"\n-------------------- number of Loops: \n");
        display_No_of_loops();
	printMessage(8,"\n-------------------- Loop statements: \n");
	display_StatementNode(8,parallel_stmt);
	loop_normalization(5,parallel_stmt,variables,loop_index_new);
	printMessage(8,"\n-------------------- Loop statements after Loop Normalization: \n");
	display_StatementNode(8,parallel_stmt);
	printMessage(8,"\n-------------------- Loop index variables: \n");
	display_LoopIndexVar(8,loop_index); // no use
	//printMessage(8,"======\n");
	display_LoopIndexVar_New(8,loop_index_new);
	printMessage(8,"\n-------------------- Original variables: \n");
	display_Var(8,variables);
	
	remove_LoopIndexVar();// no use
	remove_LoopIndexVar_New();
	printMessage(8,"\n-------------------- Variables excluding Loop index variables: \n"); // excluding loop index variables
	display_Var(8,variables);
	
	// No need as it reprints the loop statement variables
	/*printMessage(8,"---HERE---\n");
	display_StatementNode(8,parallel_stmt);*/
	
	// calculate left_var, read_var, write_var
	get_dependency_var();
	
	/*  NO NEED
	printMessage(8,"left variables\n");
	display_StatementNode(8,left_var);*/
	
	printMessage(8,"\n-------------------- Array References involved in RAW dependence\n");
	printMessage(8,"read dep variables\n");
	display_StatementNode(8,read_var);
	printMessage(8,"\n-------------------- Array References involved in WAW dependence\n");
	printMessage(8,"write dep variables\n");
	display_StatementNode(8,write_var);
	printMessage(8,"\n-------------------- List of Loop Statement Variables\n");
	display_Stmt_Var(8,stmt_var);
	
	// calculate left_stmt_var, read_stmt_var, write_stmt_var 
	get_left_read_write_stmt_var();
	
	/* NO NEED
	printMessage(8,"left statement variables\n");
	display_Stmt_Var(8,left_stmt_var);*/
	
	printMessage(8,"\n-------------------- List of Loop Statement Variables involved in RAW dependence\n");
	display_Stmt_Var(8,read_stmt_var);
	printMessage(8,"\n-------------------- List of Loop Statement Variables involved in WAW dependence\n");
	display_Stmt_Var(8,write_stmt_var);

	printMessage(5,"\n-------------------- Pragma starts at line number %d and ends at line number %d\n", start_num, end_num);
	// Identifying Affine/Non-Affine kernel
	AffineKernel='y';
	Affine_NonAffine_Test();
	if(AffineKernel=='n')
    { 
        printMessage(8,"\n-------------------- Input program contains a non-affine loop\n");
        if(parallel_stmt!=NULL)
	    cuda_function_DEF();
	    fdisplay_part1();
	    if(parallel_stmt!=NULL)
	    cuda_loop();
	    if(parallel_stmt!=NULL)
	    cuda_postloop();
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    if(parallel_stmt!=NULL)
	    cuda_function();
    }
	else
	{
	    printMessage(8,"\n-------------------- Input program contains an affine loop\n");
	    // DEPENDENCE TESTING
	    Dependence_Testing_Interface(5,dependence_test,read_var,write_var,loop_index_new);
	    CycleShrinking(5,shrinking,read_var,write_var,loop_index_new,stmt_var);
	    //Code Generation
	    cuda_kernel_declaration_AFFINE(shrinking);
	    fdisplay_part1();
	    cuda_kernel_call_AFFINE(shrinking);
	    in = fopen(infile, "r");
	    fdisplay_part2();
	    cuda_kernel_definition_AFFINE(shrinking);
	}
}
