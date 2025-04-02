/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/mylang.y"

#include <helper.h>
#include <types.h>
#include <symtab.h>

// #include <statementh>
// #include <expression.h>
// #include <ast.h>
// #include <3ach>

void yyerror(const char *s);
 extern int yylex();
 extern int yylineno;
 extern FILE *yyin;
// // Global variable to hold the current type for declaration
// char *currentType = NULL;
// int grammarErrorCount = 0;
 

#line 91 "src/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "y.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_SIZEOF = 6,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 7,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 8,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 9,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 10,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 11,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 12,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 13,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 14,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 15,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 16,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 17,                     /* OR_OP  */
  YYSYMBOL_TYPE_NAME = 18,                 /* TYPE_NAME  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 22,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 23,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 24,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 25,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 26,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 27,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 28,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 29,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPEDEF = 30,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 31,                    /* EXTERN  */
  YYSYMBOL_STATIC = 32,                    /* STATIC  */
  YYSYMBOL_AUTO = 33,                      /* AUTO  */
  YYSYMBOL_REGISTER = 34,                  /* REGISTER  */
  YYSYMBOL_CHAR = 35,                      /* CHAR  */
  YYSYMBOL_SHORT = 36,                     /* SHORT  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_LONG = 38,                      /* LONG  */
  YYSYMBOL_SIGNED = 39,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 40,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 41,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 42,                    /* DOUBLE  */
  YYSYMBOL_CONST = 43,                     /* CONST  */
  YYSYMBOL_VOLATILE = 44,                  /* VOLATILE  */
  YYSYMBOL_VOID = 45,                      /* VOID  */
  YYSYMBOL_STRUCT = 46,                    /* STRUCT  */
  YYSYMBOL_UNION = 47,                     /* UNION  */
  YYSYMBOL_ENUM = 48,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 49,                  /* ELLIPSIS  */
  YYSYMBOL_SEMICOLON = 50,                 /* SEMICOLON  */
  YYSYMBOL_LEFT_BRACE = 51,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 52,               /* RIGHT_BRACE  */
  YYSYMBOL_COMMA = 53,                     /* COMMA  */
  YYSYMBOL_COLON = 54,                     /* COLON  */
  YYSYMBOL_LEFT_PAREN = 55,                /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 56,               /* RIGHT_PAREN  */
  YYSYMBOL_LEFT_BRACKET = 57,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 58,             /* RIGHT_BRACKET  */
  YYSYMBOL_DOT = 59,                       /* DOT  */
  YYSYMBOL_AMPERSAND = 60,                 /* AMPERSAND  */
  YYSYMBOL_EXCLAMATION = 61,               /* EXCLAMATION  */
  YYSYMBOL_TILDE = 62,                     /* TILDE  */
  YYSYMBOL_MINUS = 63,                     /* MINUS  */
  YYSYMBOL_PLUS = 64,                      /* PLUS  */
  YYSYMBOL_ASTERISK = 65,                  /* ASTERISK  */
  YYSYMBOL_SLASH = 66,                     /* SLASH  */
  YYSYMBOL_PERCENT = 67,                   /* PERCENT  */
  YYSYMBOL_LESS_THAN = 68,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 69,              /* GREATER_THAN  */
  YYSYMBOL_CARET = 70,                     /* CARET  */
  YYSYMBOL_PIPE = 71,                      /* PIPE  */
  YYSYMBOL_QUESTION = 72,                  /* QUESTION  */
  YYSYMBOL_INVALID_ID = 73,                /* INVALID_ID  */
  YYSYMBOL_INVALID_CHAR = 74,              /* INVALID_CHAR  */
  YYSYMBOL_INVALID_OCT = 75,               /* INVALID_OCT  */
  YYSYMBOL_UNTERM_STRING = 76,             /* UNTERM_STRING  */
  YYSYMBOL_CASE = 77,                      /* CASE  */
  YYSYMBOL_DEFAULT = 78,                   /* DEFAULT  */
  YYSYMBOL_IF = 79,                        /* IF  */
  YYSYMBOL_ELSE = 80,                      /* ELSE  */
  YYSYMBOL_SWITCH = 81,                    /* SWITCH  */
  YYSYMBOL_WHILE = 82,                     /* WHILE  */
  YYSYMBOL_DO = 83,                        /* DO  */
  YYSYMBOL_FOR = 84,                       /* FOR  */
  YYSYMBOL_GOTO = 85,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 86,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 87,                     /* BREAK  */
  YYSYMBOL_RETURN = 88,                    /* RETURN  */
  YYSYMBOL_ERROR = 89,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 90,                  /* $accept  */
  YYSYMBOL_declaration = 91,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 92,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 93,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 94,           /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 95,   /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 96,            /* type_specifier  */
  YYSYMBOL_struct_specifier = 97,          /* struct_specifier  */
  YYSYMBOL_union_specifier = 98,           /* union_specifier  */
  YYSYMBOL_struct_declaration_list = 99,   /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 100,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 101,   /* struct_declarator_list  */
  YYSYMBOL_specifier_qualifier_list = 102, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator = 103,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 104,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 105,          /* enumerator_list  */
  YYSYMBOL_enumerator = 106,               /* enumerator  */
  YYSYMBOL_type_qualifier = 107,           /* type_qualifier  */
  YYSYMBOL_declarator = 108,               /* declarator  */
  YYSYMBOL_direct_declarator = 109,        /* direct_declarator  */
  YYSYMBOL_pointer = 110,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 111,      /* type_qualifier_list  */
  YYSYMBOL_parameter_list = 112,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 113,    /* parameter_declaration  */
  YYSYMBOL_compound_statement = 114,       /* compound_statement  */
  YYSYMBOL_declaration_list = 115,         /* declaration_list  */
  YYSYMBOL_translation_unit = 116,         /* translation_unit  */
  YYSYMBOL_external_declaration = 117,     /* external_declaration  */
  YYSYMBOL_function_identifier = 118,      /* function_identifier  */
  YYSYMBOL_function_declaration = 119,     /* function_declaration  */
  YYSYMBOL_function_definition = 120,      /* function_definition  */
  YYSYMBOL_121_1 = 121,                    /* $@1  */
  YYSYMBOL_INC_SCOPE = 122                 /* INC_SCOPE  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   302,   327,   332,   371,   372,   376,   379,   390,   394,
     401,   412,   413,   414,   415,   416,   421,   422,   423,   424,
     425,   426,   427,   430,   431,   432,   443,   444,   445,   450,
     451,   452,   456,   457,   464,   474,   478,   485,   489,   492,
     506,   519,   522,   525,   531,   535,   542,   552,   553,   558,
     559,   572,   573,   612,   613,   620,   624,   635,   638,   655,
     656,   660,   735,   737,   742,   743,   789,   790,   795,   796,
     797,   801,   802,   814,   823,   835,   835,   847
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "TYPE_NAME", "ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN",
  "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED",
  "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "SEMICOLON", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
  "COLON", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET",
  "DOT", "AMPERSAND", "EXCLAMATION", "TILDE", "MINUS", "PLUS", "ASTERISK",
  "SLASH", "PERCENT", "LESS_THAN", "GREATER_THAN", "CARET", "PIPE",
  "QUESTION", "INVALID_ID", "INVALID_CHAR", "INVALID_OCT", "UNTERM_STRING",
  "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "ERROR", "$accept", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_specifier",
  "union_specifier", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "specifier_qualifier_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_list", "parameter_declaration",
  "compound_statement", "declaration_list", "translation_unit",
  "external_declaration", "function_identifier", "function_declaration",
  "function_definition", "$@1", "INC_SCOPE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     182,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,     1,    10,    13,   -81,     5,
     182,   182,   -81,   -81,   -81,   182,    90,   -81,   -46,   -81,
      17,   250,    30,   250,    31,    19,   -23,   -81,     8,     6,
      -8,   -81,   -81,   -81,    11,    -1,   -81,   -81,   -81,   -81,
     -81,   -81,   250,   250,    57,   -81,     8,   250,   250,   196,
      19,   -81,    -6,   -81,   -81,     9,     4,   -81,   -81,     6,
     -81,     8,   -81,    12,   -81,   109,   -81,   214,   -81,   -81,
     -81,    -2,   -81,   -81,   -81,   232,   -81,    27,   -81,    19,
     -81,   -81,   -81,   -81,   -81,   -81,     8,   -22,   -81,   -81,
      33,   -81,   -81,     8,   -81,   -81,   -81,   -81,   182,   -81,
     136,   -81,   -81,   -81,   -81,     7,   159,   -81,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,    13,    14,    15,    18,    19,    16,    20,
      21,    22,    47,    48,    17,     0,     0,     0,    70,     0,
       0,     4,    23,    24,    25,     0,     0,    66,    68,    69,
      26,     0,    29,     0,    43,     0,    51,     2,     0,    53,
       0,     8,    10,    49,     0,     0,     5,     6,     7,     1,
      67,    75,     0,    38,     0,    32,     0,     0,     0,     0,
       0,    46,     0,    44,    51,     0,     0,    57,    55,    54,
       3,     0,    50,     0,    72,     0,    77,     0,    37,    28,
      33,     0,    35,    40,    39,     0,    31,     0,    41,     0,
      52,    58,    56,     9,    71,    73,     0,     0,    59,    76,
       0,    27,    34,     0,    30,    42,    45,    61,     0,    74,
       0,    36,    60,    62,    64,     0,     0,    63,    65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -80,   -19,   -81,    15,   -81,     3,   -81,   -81,   -14,
     -42,   -81,   -16,   -18,   -81,    28,    18,     0,   -29,   -26,
      14,   -81,   -81,   -12,   -81,   -81,   -81,    80,    93,   -81,
     -81,   -81,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    18,    19,    40,    41,    20,    53,    22,    23,    54,
      55,    81,    56,    82,    24,    62,    63,    57,    42,    43,
      66,    69,    97,    98,    99,   116,    26,    27,    74,    28,
      29,    76,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      25,    46,    47,    21,    30,   -77,    48,    64,    36,    65,
      64,    64,    80,    32,    36,    94,    34,    80,    72,    59,
      25,    25,    61,    21,    21,    25,    25,    83,    21,    21,
     114,   108,   -71,    44,   109,    80,   118,    78,    77,    67,
      72,    84,    70,    80,    85,    71,    88,    89,   102,    12,
      13,   103,    31,    68,    75,    37,    96,    37,    73,    38,
      38,    33,    38,    38,    35,    90,    38,   107,    52,    91,
      39,    39,    39,    39,    83,    25,    39,    39,    21,   105,
      89,    58,    60,    92,   110,   111,    93,    73,    87,    96,
      49,   115,     6,     7,     8,     9,   112,   115,    10,    11,
      12,    13,    14,    15,    16,    17,    50,   106,    25,    79,
      25,    21,    45,    21,   100,     0,    25,     0,     0,    21,
       1,     2,     3,     4,     5,     6,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,     1,
       2,     3,     4,     5,     6,     7,     8,     9,     0,     0,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,    95,     1,     2,     3,     4,
       5,     6,     7,     8,     9,     0,     0,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,   113,     1,
       2,     3,     4,     5,     6,     7,     8,     9,     0,     0,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,   117,     1,     2,     3,     4,     5,     6,     7,     8,
       9,     0,     0,    10,    11,    12,    13,    14,    15,    16,
      17,     6,     7,     8,     9,     0,     0,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,    86,     6,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     0,   101,     6,     7,     8,
       9,     0,     0,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,   104,     6,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17
};

static const yytype_int8 yycheck[] =
{
       0,    20,    21,     0,     3,    51,    25,     3,     3,    38,
       3,     3,    54,     3,     3,     3,     3,    59,    44,    33,
      20,    21,     3,    20,    21,    25,    26,    56,    25,    26,
     110,    53,    55,    19,    56,    77,   116,    53,    52,    39,
      66,    57,    50,    85,    58,    53,    52,    53,    50,    43,
      44,    53,    51,    39,    55,    50,    75,    50,    44,    55,
      55,    51,    55,    55,    51,    56,    55,    96,    51,    69,
      65,    65,    65,    65,   103,    75,    65,    65,    75,    52,
      53,    51,    51,    69,    51,   103,    71,    73,    60,   108,
       0,   110,    35,    36,    37,    38,   108,   116,    41,    42,
      43,    44,    45,    46,    47,    48,    26,    89,   108,    52,
     110,   108,    19,   110,    76,    -1,   116,    -1,    -1,   116,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    52,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    52,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    35,    36,    37,    38,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    52,    35,
      36,    37,    38,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    52,    35,    36,    37,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    35,    36,    37,    38,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      41,    42,    43,    44,    45,    46,    47,    48,    91,    92,
      95,    96,    97,    98,   104,   107,   116,   117,   119,   120,
       3,    51,     3,    51,     3,    51,     3,    50,    55,    65,
      93,    94,   108,   109,   110,   118,    92,    92,    92,     0,
     117,   122,    51,    96,    99,   100,   102,   107,    51,    99,
      51,     3,   105,   106,     3,   108,   110,   107,   110,   111,
      50,    53,   109,   110,   118,    55,   121,    99,   102,    52,
     100,   101,   103,   108,   102,    99,    52,   105,    52,    53,
      56,   107,   110,    94,     3,    56,    92,   112,   113,   114,
     122,    52,    50,    53,    52,    52,   106,   108,    53,    56,
      51,   103,   113,    52,    91,    92,   115,    52,    91
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    90,    91,    91,    92,    92,    92,    92,    93,    93,
      94,    95,    95,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    98,    99,    99,   100,   101,   101,   102,   102,   102,
     103,   104,   104,   104,   105,   105,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   110,   110,   111,   111,   112,
     112,   113,   114,   114,   115,   115,   116,   116,   117,   117,
     117,   118,   118,   119,   119,   121,   120,   122
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     2,     2,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     5,     4,     2,
       5,     4,     1,     2,     3,     1,     3,     2,     1,     2,
       1,     4,     5,     2,     1,     3,     1,     1,     1,     1,
       2,     1,     3,     1,     2,     2,     3,     1,     2,     1,
       3,     2,     3,     4,     1,     2,     1,     2,     1,     1,
       1,     1,     2,     4,     5,     0,     4,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* declaration: declaration_specifiers SEMICOLON  */
#line 327 "src/mylang.y"
                                           {
 		  (yyval.vector_identifiers) = new VectorIdentifiers();
 		  (yyval.vector_identifiers)->add_identifier(new Identifier((yyvsp[-1].global_type)));
 		  SymbolTable::add_symbols((yyval.vector_identifiers));
 	  }
#line 1340 "src/y.tab.c"
    break;

  case 3: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 332 "src/mylang.y"
                                                                {
 		  /* Use the variable name from init_declarator */
 		  for(auto &element : (yyvsp[-1].vector_identifiers)->identifiers) {
 			  element.type = (yyvsp[-2].global_type);
 		  }
		  (yyval.vector_identifiers)=(yyvsp[-1].vector_identifiers);
		  SymbolTable::add_symbols((yyval.vector_identifiers));
 	  }
#line 1353 "src/y.tab.c"
    break;

  case 4: /* declaration_specifiers: type_specifier  */
#line 371 "src/mylang.y"
                         { (yyval.global_type) = (yyvsp[0].global_type); }
#line 1359 "src/y.tab.c"
    break;

  case 5: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 372 "src/mylang.y"
                                                         {
		(yyval.global_type) = (yyvsp[0].global_type);
		(yyval.global_type)->setSpecifiers(combine_specs((yyval.global_type)->getSpecifiers(), (yyvsp[-1].specifiers)));
 	}
#line 1368 "src/y.tab.c"
    break;

  case 6: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 376 "src/mylang.y"
                                                { 
 		/* $$ = combine_global_type($1, $2); */
 	}
#line 1376 "src/y.tab.c"
    break;

  case 7: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 379 "src/mylang.y"
                                                {
 		(yyval.global_type) = (yyvsp[0].global_type);
 		(yyval.global_type)->setSpecifiers(combine_specs((yyval.global_type)->getSpecifiers(), (yyvsp[-1].specifiers)));
 	}
#line 1385 "src/y.tab.c"
    break;

  case 8: /* init_declarator_list: init_declarator  */
#line 390 "src/mylang.y"
                         {
 		(yyval.vector_identifiers) = new VectorIdentifiers();
 		(yyval.vector_identifiers)->add_identifier((yyvsp[0].identifier));
 	}
#line 1394 "src/y.tab.c"
    break;

  case 9: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 394 "src/mylang.y"
                                                    {
 		(yyval.vector_identifiers) = (yyvsp[-2].vector_identifiers);
 		(yyval.vector_identifiers)->add_identifier((yyvsp[0].identifier));
 	}
#line 1403 "src/y.tab.c"
    break;

  case 10: /* init_declarator: declarator  */
#line 401 "src/mylang.y"
                    {
 		(yyval.identifier) = (yyvsp[0].identifier);
 	}
#line 1411 "src/y.tab.c"
    break;

  case 11: /* storage_class_specifier: TYPEDEF  */
#line 412 "src/mylang.y"
                  { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_typedef = true; }
#line 1417 "src/y.tab.c"
    break;

  case 12: /* storage_class_specifier: EXTERN  */
#line 413 "src/mylang.y"
                 { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_extern = true; }
#line 1423 "src/y.tab.c"
    break;

  case 13: /* storage_class_specifier: STATIC  */
#line 414 "src/mylang.y"
                 { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_static = true; }
#line 1429 "src/y.tab.c"
    break;

  case 14: /* storage_class_specifier: AUTO  */
#line 415 "src/mylang.y"
               { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_auto = true; }
#line 1435 "src/y.tab.c"
    break;

  case 15: /* storage_class_specifier: REGISTER  */
#line 416 "src/mylang.y"
                   { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_register = true; }
#line 1441 "src/y.tab.c"
    break;

  case 16: /* type_specifier: INT  */
#line 421 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(INT_T); }
#line 1447 "src/y.tab.c"
    break;

  case 17: /* type_specifier: VOID  */
#line 422 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(VOID_T); }
#line 1453 "src/y.tab.c"
    break;

  case 18: /* type_specifier: CHAR  */
#line 423 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(CHAR_T); }
#line 1459 "src/y.tab.c"
    break;

  case 19: /* type_specifier: SHORT  */
#line 424 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(SHORT_T); }
#line 1465 "src/y.tab.c"
    break;

  case 20: /* type_specifier: LONG  */
#line 425 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(LONG_T); }
#line 1471 "src/y.tab.c"
    break;

  case 21: /* type_specifier: FLOAT  */
#line 426 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(FLOAT_T); }
#line 1477 "src/y.tab.c"
    break;

  case 22: /* type_specifier: DOUBLE  */
#line 427 "src/mylang.y"
                   { (yyval.global_type) = create_primitive_type(DOUBLE_T); }
#line 1483 "src/y.tab.c"
    break;

  case 23: /* type_specifier: struct_specifier  */
#line 430 "src/mylang.y"
                           { (yyval.global_type) = create_struct_type((yyvsp[0].struct_type)); }
#line 1489 "src/y.tab.c"
    break;

  case 24: /* type_specifier: union_specifier  */
#line 431 "src/mylang.y"
                          { (yyval.global_type) = create_union_type((yyvsp[0].union_type)); }
#line 1495 "src/y.tab.c"
    break;

  case 25: /* type_specifier: enum_specifier  */
#line 432 "src/mylang.y"
                         { (yyval.global_type) = create_enum_type((yyvsp[0].enum_type)); }
#line 1501 "src/y.tab.c"
    break;

  case 26: /* struct_specifier: STRUCT IDENTIFIER  */
#line 443 "src/mylang.y"
                            { (yyval.struct_type) = new Struct(std::string((yyvsp[0].nice))); }
#line 1507 "src/y.tab.c"
    break;

  case 27: /* struct_specifier: STRUCT IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 444 "src/mylang.y"
                                                                           { (yyval.struct_type) = new Struct(std::string((yyvsp[-3].nice)), (yyvsp[-1].struct_element_list)); }
#line 1513 "src/y.tab.c"
    break;

  case 28: /* struct_specifier: STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 445 "src/mylang.y"
                                                                { (yyval.struct_type) = new Struct((yyvsp[-1].struct_element_list)); }
#line 1519 "src/y.tab.c"
    break;

  case 29: /* union_specifier: UNION IDENTIFIER  */
#line 450 "src/mylang.y"
                           { (yyval.union_type) = new Union(std::string((yyvsp[0].nice))); }
#line 1525 "src/y.tab.c"
    break;

  case 30: /* union_specifier: UNION IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 451 "src/mylang.y"
                                                                          { (yyval.union_type) = new Union(std::string((yyvsp[-3].nice)), (yyvsp[-1].struct_element_list)); }
#line 1531 "src/y.tab.c"
    break;

  case 31: /* union_specifier: UNION LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 452 "src/mylang.y"
                                                               { (yyval.union_type) = new Union((yyvsp[-1].struct_element_list)); }
#line 1537 "src/y.tab.c"
    break;

  case 32: /* struct_declaration_list: struct_declaration  */
#line 456 "src/mylang.y"
                             { (yyval.struct_element_list) = (yyvsp[0].struct_element_list); }
#line 1543 "src/y.tab.c"
    break;

  case 33: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 457 "src/mylang.y"
                                                     {
 		(yyval.struct_element_list) = (yyvsp[-1].struct_element_list);
 		(yyval.struct_element_list)->add_elements((yyvsp[0].struct_element_list));
 	}
#line 1552 "src/y.tab.c"
    break;

  case 34: /* struct_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 464 "src/mylang.y"
                                                                    {
 		(yyval.struct_element_list) = new VectorStructElement();
 		for (auto &declarator : (yyvsp[-1].struct_element_list)->elements) {
 			declarator.id->type = (yyvsp[-2].global_type);
 		}
		(yyval.struct_element_list)->add_elements((yyvsp[-1].struct_element_list));
 	}
#line 1564 "src/y.tab.c"
    break;

  case 35: /* struct_declarator_list: struct_declarator  */
#line 474 "src/mylang.y"
                            {
 		(yyval.struct_element_list) = new VectorStructElement();
 		(yyval.struct_element_list)->add_element((yyvsp[0].struct_element));
 	}
#line 1573 "src/y.tab.c"
    break;

  case 36: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 478 "src/mylang.y"
                                                         {
 		(yyval.struct_element_list) = (yyvsp[-2].struct_element_list);
 		(yyval.struct_element_list)->add_element((yyvsp[0].struct_element));
 	}
#line 1582 "src/y.tab.c"
    break;

  case 37: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 485 "src/mylang.y"
                                                  {
 		// TODO: 
		(yyval.global_type) = combine_global_type((yyvsp[-1].global_type), (yyvsp[0].global_type));
 	}
#line 1591 "src/y.tab.c"
    break;

  case 38: /* specifier_qualifier_list: type_specifier  */
#line 489 "src/mylang.y"
                        {
			(yyval.global_type) = (yyvsp[0].global_type);
	}
#line 1599 "src/y.tab.c"
    break;

  case 39: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 492 "src/mylang.y"
                                                 {
		(yyval.global_type)=(yyvsp[0].global_type);
		(yyval.global_type)->setSpecifiers(combine_specs((yyval.global_type)->getSpecifiers(), (yyvsp[-1].specifiers)));
	}
#line 1608 "src/y.tab.c"
    break;

  case 40: /* struct_declarator: declarator  */
#line 506 "src/mylang.y"
                     {
 		(yyval.struct_element) = new StructElement((yyvsp[0].identifier), (yyvsp[0].identifier)->type->getSize()); 
	}
#line 1616 "src/y.tab.c"
    break;

  case 41: /* enum_specifier: ENUM LEFT_BRACE enumerator_list RIGHT_BRACE  */
#line 519 "src/mylang.y"
                                                      {
 		(yyval.enum_type) = new EnumType((yyvsp[-1].vector_enum_element));
 	}
#line 1624 "src/y.tab.c"
    break;

  case 42: /* enum_specifier: ENUM IDENTIFIER LEFT_BRACE enumerator_list RIGHT_BRACE  */
#line 522 "src/mylang.y"
                                                                {
 		(yyval.enum_type) = new EnumType(std::string((yyvsp[-3].nice)),(yyvsp[-1].vector_enum_element));
 	}
#line 1632 "src/y.tab.c"
    break;

  case 43: /* enum_specifier: ENUM IDENTIFIER  */
#line 525 "src/mylang.y"
                         {
 		(yyval.enum_type) = new EnumType(std::string((yyvsp[0].nice)));
 	}
#line 1640 "src/y.tab.c"
    break;

  case 44: /* enumerator_list: enumerator  */
#line 531 "src/mylang.y"
                     { 
 		(yyval.vector_enum_element) = new VectorEnumElement();
 		(yyval.vector_enum_element)->add_element((yyvsp[0].enum_element));
 	}
#line 1649 "src/y.tab.c"
    break;

  case 45: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 535 "src/mylang.y"
                                          {
 		(yyval.vector_enum_element) = (yyvsp[-2].vector_enum_element);
 		(yyval.vector_enum_element)->add_element((yyvsp[0].enum_element));
 	}
#line 1658 "src/y.tab.c"
    break;

  case 46: /* enumerator: IDENTIFIER  */
#line 542 "src/mylang.y"
                    {
 		(yyval.enum_element) = new EnumElement(std::string((yyvsp[0].nice)));
 	}
#line 1666 "src/y.tab.c"
    break;

  case 47: /* type_qualifier: CONST  */
#line 552 "src/mylang.y"
                   { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_const = true; }
#line 1672 "src/y.tab.c"
    break;

  case 48: /* type_qualifier: VOLATILE  */
#line 553 "src/mylang.y"
                   { (yyval.specifiers) = new Specifiers(); (yyval.specifiers)->is_volatile = true; }
#line 1678 "src/y.tab.c"
    break;

  case 49: /* declarator: direct_declarator  */
#line 558 "src/mylang.y"
                            { (yyval.identifier) = (yyvsp[0].identifier); }
#line 1684 "src/y.tab.c"
    break;

  case 50: /* declarator: pointer direct_declarator  */
#line 559 "src/mylang.y"
                                    { 
 		(yyval.identifier) = (yyvsp[0].identifier); 
 		if((yyval.identifier)->type->type_tag == NONE) {
 			(yyval.identifier)->type = create_pointer_type(new GlobalType(), (yyvsp[-1].pointer_type)->ptr_level, (yyvsp[-1].pointer_type)->specifiers);

 		} else{
 			(yyval.identifier)->type->pointer_type->ptr_level = (yyvsp[-1].pointer_type)->ptr_level;
 		}
 	}
#line 1698 "src/y.tab.c"
    break;

  case 51: /* direct_declarator: IDENTIFIER  */
#line 572 "src/mylang.y"
                     { (yyval.identifier) = new Identifier(std::string((yyvsp[0].nice))); }
#line 1704 "src/y.tab.c"
    break;

  case 52: /* direct_declarator: LEFT_PAREN declarator RIGHT_PAREN  */
#line 573 "src/mylang.y"
                                            { (yyval.identifier) = (yyvsp[-1].identifier); }
#line 1710 "src/y.tab.c"
    break;

  case 53: /* pointer: ASTERISK  */
#line 612 "src/mylang.y"
                   { (yyval.pointer_type) = new PointerType(); }
#line 1716 "src/y.tab.c"
    break;

  case 54: /* pointer: ASTERISK type_qualifier_list  */
#line 613 "src/mylang.y"
                                       { 
 		(yyval.pointer_type) = new PointerType();
 		if ((yyval.pointer_type)->specifiers == NULL) {
			(yyval.pointer_type)->specifiers = new Specifiers();
		}
 		(yyval.pointer_type)->specifiers = combine_specs((yyval.pointer_type)->specifiers, (yyvsp[0].specifiers));
 	 }
#line 1728 "src/y.tab.c"
    break;

  case 55: /* pointer: ASTERISK pointer  */
#line 620 "src/mylang.y"
                           { 
 		(yyval.pointer_type) = (yyvsp[0].pointer_type);
 		(yyval.pointer_type)->ptr_level++;
 	}
#line 1737 "src/y.tab.c"
    break;

  case 56: /* pointer: ASTERISK type_qualifier_list pointer  */
#line 624 "src/mylang.y"
                                               { 
 		(yyval.pointer_type) = (yyvsp[0].pointer_type);
 		(yyval.pointer_type)->ptr_level++;
		if ((yyval.pointer_type)->specifiers == NULL) {
			(yyval.pointer_type)->specifiers = new Specifiers();
		}
 		(yyval.pointer_type)->specifiers = combine_specs((yyval.pointer_type)->specifiers, (yyvsp[-1].specifiers));
	}
#line 1750 "src/y.tab.c"
    break;

  case 57: /* type_qualifier_list: type_qualifier  */
#line 635 "src/mylang.y"
                         { 
 		(yyval.specifiers) = (yyvsp[0].specifiers);
 	}
#line 1758 "src/y.tab.c"
    break;

  case 58: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 638 "src/mylang.y"
                                            {
 		(yyval.specifiers) = combine_specs((yyvsp[-1].specifiers), (yyvsp[0].specifiers));
 	}
#line 1766 "src/y.tab.c"
    break;

  case 59: /* parameter_list: parameter_declaration  */
#line 655 "src/mylang.y"
                                { (yyval.vector_identifiers) = new VectorIdentifiers(); (yyval.vector_identifiers)->add_identifier((yyvsp[0].identifier)); }
#line 1772 "src/y.tab.c"
    break;

  case 60: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 656 "src/mylang.y"
                                                     { (yyval.vector_identifiers) = (yyvsp[-2].vector_identifiers); (yyval.vector_identifiers)->add_identifier((yyvsp[0].identifier)); }
#line 1778 "src/y.tab.c"
    break;

  case 61: /* parameter_declaration: declaration_specifiers declarator  */
#line 660 "src/mylang.y"
                                            {
 		(yyval.identifier) = (yyvsp[0].identifier);
		if ((yyval.identifier)->type->type_tag == NONE) {
			(yyval.identifier)->type = (yyvsp[-1].global_type);
		} else {
			(yyval.identifier)->type = create_pointer_type((yyvsp[-1].global_type), (yyval.identifier)->type->pointer_type->ptr_level, (yyvsp[-1].global_type)->getSpecifiers());
		}
		// TODO: Add combine_global_type function here depending on what type is the function
 	}
#line 1792 "src/y.tab.c"
    break;

  case 62: /* compound_statement: INC_SCOPE LEFT_BRACE RIGHT_BRACE  */
#line 735 "src/mylang.y"
                                           { SymbolTable::exit_scope(); }
#line 1798 "src/y.tab.c"
    break;

  case 63: /* compound_statement: INC_SCOPE LEFT_BRACE declaration_list RIGHT_BRACE  */
#line 737 "src/mylang.y"
                                                            { SymbolTable::exit_scope(); }
#line 1804 "src/y.tab.c"
    break;

  case 64: /* declaration_list: declaration  */
#line 742 "src/mylang.y"
                      { (yyval.vector_identifiers) = (yyvsp[0].vector_identifiers); }
#line 1810 "src/y.tab.c"
    break;

  case 65: /* declaration_list: declaration_list declaration  */
#line 743 "src/mylang.y"
                                      {
		(yyval.vector_identifiers) = (yyvsp[-1].vector_identifiers);
		(yyval.vector_identifiers)->add_identifiers((yyvsp[0].vector_identifiers));
	}
#line 1819 "src/y.tab.c"
    break;

  case 71: /* function_identifier: IDENTIFIER  */
#line 801 "src/mylang.y"
                     { (yyval.identifier) = new Identifier((yyvsp[0].nice)); }
#line 1825 "src/y.tab.c"
    break;

  case 72: /* function_identifier: pointer function_identifier  */
#line 802 "src/mylang.y"
                                     { 
 		(yyval.identifier) = (yyvsp[0].identifier); 
 		if((yyval.identifier)->type->type_tag == NONE) {
 			(yyval.identifier)->type = create_pointer_type(new GlobalType(), (yyvsp[-1].pointer_type)->ptr_level, (yyvsp[-1].pointer_type)->specifiers);
 		} else{
 			(yyval.identifier)->type->pointer_type->ptr_level = (yyvsp[-1].pointer_type)->ptr_level;
 		}
		
 	}
#line 1839 "src/y.tab.c"
    break;

  case 73: /* function_declaration: declaration_specifiers function_identifier LEFT_PAREN RIGHT_PAREN  */
#line 814 "src/mylang.y"
                                                                            {
		(yyval.identifier) = (yyvsp[-2].identifier);
		if((yyval.identifier)->type->type_tag == NONE) {
			(yyval.identifier)->type = create_function_type((yyvsp[-3].global_type), new VectorIdentifiers(), (yyvsp[-2].identifier)->type->getSpecifiers());
		} else {
			class GlobalType* temp = create_pointer_type((yyvsp[-3].global_type), (yyval.identifier)->type->pointer_type->ptr_level);
			(yyval.identifier)->type = create_function_type(temp, new VectorIdentifiers(), (yyvsp[-2].identifier)->type->getSpecifiers());
		}
	}
#line 1853 "src/y.tab.c"
    break;

  case 74: /* function_declaration: declaration_specifiers function_identifier LEFT_PAREN parameter_list RIGHT_PAREN  */
#line 823 "src/mylang.y"
                                                                                          {
		(yyval.identifier) = (yyvsp[-3].identifier);
		if((yyval.identifier)->type->type_tag == NONE) {
			(yyval.identifier)->type = create_function_type((yyvsp[-4].global_type), (yyvsp[-1].vector_identifiers), (yyvsp[-3].identifier)->type->getSpecifiers());
		} else {
			class GlobalType* temp = create_pointer_type((yyvsp[-4].global_type), (yyval.identifier)->type->pointer_type->ptr_level);
			(yyval.identifier)->type = create_function_type(temp, (yyvsp[-1].vector_identifiers), (yyvsp[-3].identifier)->type->getSpecifiers());
		}
	}
#line 1867 "src/y.tab.c"
    break;

  case 75: /* $@1: %empty  */
#line 835 "src/mylang.y"
                                          { SymbolTable::add_symbols(&((yyvsp[-1].identifier)->type->function_type->args));}
#line 1873 "src/y.tab.c"
    break;

  case 76: /* function_definition: function_declaration INC_SCOPE $@1 compound_statement  */
#line 835 "src/mylang.y"
                                                                                                                                 { 
 		(yyval.identifier) = (yyvsp[-3].identifier);
		SymbolTable::exit_scope();
 		SymbolTable::add_symbol((yyval.identifier));
 		}
#line 1883 "src/y.tab.c"
    break;

  case 77: /* INC_SCOPE: %empty  */
#line 847 "src/mylang.y"
            { SymbolTable::enter_scope(); }
#line 1889 "src/y.tab.c"
    break;


#line 1893 "src/y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 848 "src/mylang.y"


void yyerror(const char *s) {
 	fprintf(stderr, "Syntax Error: %s at line %d\n", s, yylineno);
}
