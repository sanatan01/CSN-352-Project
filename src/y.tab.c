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

#include "helper.h"
void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
// Global variable to hold the current type for declaration
char *currentType = NULL;
int grammarErrorCount = 0;

#line 82 "src/y.tab.c"

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
  YYSYMBOL_MUL_ASSIGN = 18,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 19,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 20,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 21,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 22,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 23,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 24,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 25,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 26,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 27,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 28,                 /* TYPE_NAME  */
  YYSYMBOL_TYPEDEF = 29,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 30,                    /* EXTERN  */
  YYSYMBOL_STATIC = 31,                    /* STATIC  */
  YYSYMBOL_AUTO = 32,                      /* AUTO  */
  YYSYMBOL_REGISTER = 33,                  /* REGISTER  */
  YYSYMBOL_CHAR = 34,                      /* CHAR  */
  YYSYMBOL_SHORT = 35,                     /* SHORT  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_LONG = 37,                      /* LONG  */
  YYSYMBOL_SIGNED = 38,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 39,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 40,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 41,                    /* DOUBLE  */
  YYSYMBOL_CONST = 42,                     /* CONST  */
  YYSYMBOL_VOLATILE = 43,                  /* VOLATILE  */
  YYSYMBOL_VOID = 44,                      /* VOID  */
  YYSYMBOL_STRUCT = 45,                    /* STRUCT  */
  YYSYMBOL_UNION = 46,                     /* UNION  */
  YYSYMBOL_ENUM = 47,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 48,                  /* ELLIPSIS  */
  YYSYMBOL_SEMICOLON = 49,                 /* SEMICOLON  */
  YYSYMBOL_LEFT_BRACE = 50,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 51,               /* RIGHT_BRACE  */
  YYSYMBOL_COMMA = 52,                     /* COMMA  */
  YYSYMBOL_COLON = 53,                     /* COLON  */
  YYSYMBOL_ASSIGN = 54,                    /* ASSIGN  */
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
  YYSYMBOL_primary_expression = 91,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 92,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 93,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 94,          /* unary_expression  */
  YYSYMBOL_unary_operator = 95,            /* unary_operator  */
  YYSYMBOL_cast_expression = 96,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 97, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 98,       /* additive_expression  */
  YYSYMBOL_shift_expression = 99,          /* shift_expression  */
  YYSYMBOL_relational_expression = 100,    /* relational_expression  */
  YYSYMBOL_equality_expression = 101,      /* equality_expression  */
  YYSYMBOL_and_expression = 102,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 103,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 104,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 105,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 106,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 107,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 108,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 109,      /* assignment_operator  */
  YYSYMBOL_expression = 110,               /* expression  */
  YYSYMBOL_constant_expression = 111,      /* constant_expression  */
  YYSYMBOL_declaration = 112,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 113,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 114,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 115,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 116,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 117,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 118, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 119,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 120,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 121,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 122, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 123,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 124,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 125,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 126,          /* enumerator_list  */
  YYSYMBOL_enumerator = 127,               /* enumerator  */
  YYSYMBOL_type_qualifier = 128,           /* type_qualifier  */
  YYSYMBOL_declarator = 129,               /* declarator  */
  YYSYMBOL_direct_declarator = 130,        /* direct_declarator  */
  YYSYMBOL_pointer = 131,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 132,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 133,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 134,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 135,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 136,          /* identifier_list  */
  YYSYMBOL_type_name = 137,                /* type_name  */
  YYSYMBOL_abstract_declarator = 138,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 139, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 140,              /* initializer  */
  YYSYMBOL_initializer_list = 141,         /* initializer_list  */
  YYSYMBOL_statement = 142,                /* statement  */
  YYSYMBOL_labeled_statement = 143,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 144,       /* compound_statement  */
  YYSYMBOL_declaration_list = 145,         /* declaration_list  */
  YYSYMBOL_statement_list = 146,           /* statement_list  */
  YYSYMBOL_expression_statement = 147,     /* expression_statement  */
  YYSYMBOL_selection_statement = 148,      /* selection_statement  */
  YYSYMBOL_declaration_statement = 149,    /* declaration_statement  */
  YYSYMBOL_iteration_statement = 150,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 151,           /* jump_statement  */
  YYSYMBOL_translation_unit = 152,         /* translation_unit  */
  YYSYMBOL_external_declaration = 153,     /* external_declaration  */
  YYSYMBOL_function_definition = 154       /* function_definition  */
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
typedef yytype_int16 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  225
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  378

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
       0,   110,   110,   111,   112,   113,   114,   122,   123,   124,
     125,   126,   127,   128,   129,   134,   135,   140,   141,   142,
     143,   144,   145,   149,   150,   151,   152,   153,   154,   159,
     160,   165,   166,   167,   168,   172,   173,   174,   178,   179,
     180,   185,   186,   187,   188,   189,   193,   194,   195,   200,
     201,   205,   206,   210,   211,   216,   217,   221,   222,   227,
     228,   233,   234,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   253,   254,   255,   259,   266,   271,
     274,   278,   282,   286,   293,   294,   295,   296,   297,   298,
     302,   303,   307,   308,   309,   313,   321,   322,   323,   324,
     325,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   351,   352,   353,   357,   358,   362,
     363,   367,   371,   372,   373,   374,   378,   379,   383,   384,
     385,   390,   391,   392,   396,   397,   401,   402,   407,   408,
     413,   414,   418,   419,   420,   421,   422,   423,   424,   428,
     429,   430,   431,   435,   436,   441,   442,   446,   447,   451,
     452,   453,   457,   458,   462,   463,   467,   468,   469,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   486,   487,
     488,   492,   493,   498,   499,   500,   501,   502,   503,   507,
     508,   509,   513,   514,   515,   516,   520,   521,   525,   526,
     530,   531,   536,   537,   538,   542,   543,   547,   548,   549,
     550,   551,   555,   556,   557,   558,   559,   564,   565,   569,
     570,   574,   577,   580,   583,   586
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
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
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED",
  "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "SEMICOLON", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
  "COLON", "ASSIGN", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET",
  "RIGHT_BRACKET", "DOT", "AMPERSAND", "EXCLAMATION", "TILDE", "MINUS",
  "PLUS", "ASTERISK", "SLASH", "PERCENT", "LESS_THAN", "GREATER_THAN",
  "CARET", "PIPE", "QUESTION", "INVALID_ID", "INVALID_CHAR", "INVALID_OCT",
  "UNTERM_STRING", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "ERROR", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "declaration_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-213)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     786,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,    34,    88,    79,    23,  -213,    45,  1411,  1341,  -213,
      47,  -213,  1411,   724,   159,     9,   300,  -213,  -213,   -36,
      40,     5,  -213,  -213,    79,  -213,   363,    -7,   181,  -213,
      33,  -213,  -213,   -32,   194,  1212,  -213,  -213,  -213,    15,
    1431,  -213,   133,  -213,    45,  -213,   724,  1274,   564,   159,
    -213,  -213,    40,    59,   105,  -213,  -213,  -213,  -213,    74,
    -213,  -213,  1048,  1078,  1078,  -213,  -213,   552,  -213,  -213,
    -213,  -213,  -213,  -213,  1091,    80,    90,   130,   183,   723,
     189,   233,   199,   207,   849,    37,  -213,   192,   357,  1091,
    -213,   221,   210,    44,     8,   268,   201,   196,   205,   275,
      32,  -213,   242,   213,  -213,  -213,  -213,   426,   597,  -213,
    -213,  -213,  -213,   868,  -213,   180,   931,  -213,  -213,  -213,
     724,  1431,  1373,   271,  -213,    28,  1431,  -213,  -213,  -213,
    -213,    82,   245,   246,  -213,    64,  -213,  -213,  -213,  -213,
    -213,   269,   238,  1091,  -213,    40,   723,   552,  -213,  1111,
    -213,  -213,   252,    94,    75,   293,   301,   723,  1111,  1111,
    1111,   243,   489,   311,  -213,  -213,  -213,   219,  1091,   358,
    -213,  -213,   942,  1111,   359,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  1091,  -213,  1091,  1091,
    1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,
    1091,  1091,  1091,  1091,  1091,  1091,  1111,   274,  -213,  1091,
    -213,   660,  -213,  -213,   868,  -213,  -213,  -213,  -213,  -213,
    -213,  1150,  -213,  -213,  -213,  1091,   223,  -213,   317,  -213,
    1174,   961,  -213,   148,  -213,   197,  -213,  1250,   361,  -213,
    -213,  -213,  -213,  -213,  -213,   318,  -213,  1303,   222,  -213,
    1091,   723,  -213,   154,   155,   156,   330,  -213,  -213,   489,
     979,  -213,  -213,  -213,  -213,  -213,   161,  -213,    83,  -213,
    -213,  -213,  -213,  -213,   221,   221,   210,   210,    44,    44,
      44,    44,     8,     8,   268,   201,   196,   205,   275,   267,
    -213,  -213,  -213,  -213,   272,  -213,  -213,  -213,    28,  1091,
    -213,   331,   332,  -213,   315,   197,   661,  1009,  -213,  -213,
    -213,  -213,  -213,  -213,   723,   723,   723,  1111,   334,  1111,
    1111,  1091,  -213,  -213,  1091,  -213,   831,  -213,  -213,  -213,
    -213,  -213,  -213,   360,  -213,   328,   335,  -213,  -213,   173,
     723,   175,   176,  -213,  -213,  -213,  -213,  -213,  -213,   723,
     368,  -213,   723,   723,  -213,  -213,  -213,  -213
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   142,   112,    96,    97,    98,    99,   100,   102,   103,
     104,   105,   108,   109,   106,   107,   138,   139,   101,   117,
     118,     0,     0,   149,     0,   220,     0,    84,    86,   110,
       0,   111,    88,     0,   141,     0,     0,   217,   219,   133,
       0,     0,   153,   151,   150,    81,     0,     0,     0,    90,
      92,   225,    79,     0,     0,    92,    85,    87,   113,   116,
       0,    89,     0,   196,     0,   224,     0,     0,     0,   140,
       1,   218,     0,   136,     0,   134,   143,   154,   152,     2,
       3,     4,     0,     0,     0,   200,   192,     0,    23,    28,
      27,    26,    25,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     7,    17,    29,     0,
      31,    35,    38,    41,    46,    49,    51,    53,    55,    57,
      59,    61,    74,     0,   198,   183,   184,     0,     0,   185,
     186,   187,   188,     0,    82,     0,     0,    83,    80,   222,
       0,     0,   123,     0,   119,     0,   125,   197,   223,   162,
     148,   161,     0,   155,   157,     0,     2,   145,     6,    29,
      78,     0,     0,     0,   131,     0,     0,     0,    21,     0,
      18,    19,     6,     0,   164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,   214,   215,     0,     0,     0,
      13,    14,     0,     0,     0,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    63,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   201,     0,
     194,     0,   193,   199,     0,   178,    94,    91,     6,    93,
     221,     0,   122,   115,   120,     0,     0,   126,   128,   124,
       0,     0,   159,   166,   160,   167,   146,     0,     0,   147,
     144,   132,   137,   135,   189,     0,     5,     0,   166,   165,
       0,     0,   191,     0,     0,     0,     0,   200,   206,     0,
       0,   212,   216,    76,    12,     9,     0,    15,     0,    11,
      62,    32,    33,    34,    37,    36,    39,    40,    44,    45,
      42,    43,    47,    48,    50,    52,    54,    56,    58,     0,
      77,    75,   195,   181,     0,   114,   129,   121,     0,     0,
     174,     0,     0,   170,     0,   168,     0,     0,   156,   158,
     163,    22,    30,   190,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     8,     0,   179,     0,   127,   130,   175,
     169,   171,   176,     0,   172,     0,   202,   204,   207,     0,
       0,     0,     0,    16,    60,   180,   182,   177,   173,     0,
       0,   209,     0,     0,   203,   208,   211,   210
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,  -213,  -213,   -49,  -213,   -91,   141,   143,    24,
     139,   198,   200,   214,   209,   195,  -213,   -64,  -126,  -213,
      11,   -93,     2,     0,   -13,   286,  -213,   -18,  -213,  -213,
     295,  -132,   -71,  -213,   120,  -213,   367,   278,    51,     3,
     -29,    35,  -213,   -62,  -213,   217,  -213,   312,   -92,  -212,
    -127,  -213,   -76,  -213,    -9,    -2,   326,  -174,  -213,   203,
    -213,  -213,  -213,   442,  -213
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   106,   107,   286,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   206,
     123,   161,    63,    64,    48,    49,    27,    28,    29,    30,
     143,   144,   145,   246,   247,    31,    74,    75,    32,    50,
      34,    35,    44,   321,   153,   154,   155,   175,   322,   255,
     236,   314,   124,   125,   126,    66,   128,   129,   130,   280,
     131,   132,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   176,    25,    33,   160,   152,    69,   235,   279,   239,
     235,   244,     1,    54,    72,    51,   174,   137,   207,   159,
     215,   216,   133,   181,    65,    41,     1,    56,    57,    55,
     160,     1,    61,   168,   170,   171,    26,    39,    25,    33,
       1,   325,   142,    73,   127,   159,   139,   133,     1,   225,
      59,    54,   233,   140,   213,   214,   325,   148,    43,   254,
     159,    76,   283,    58,    22,   141,   287,   151,   147,   142,
     262,   242,    45,    46,    42,   249,   217,   218,    22,    78,
     290,   245,   269,    22,    40,     1,    45,   136,    23,   188,
     264,     1,    22,    23,    52,    77,   174,    60,   173,   160,
      22,   272,    23,   311,   226,   338,   340,   313,   235,   244,
      23,   146,    47,   163,   159,   187,   258,   291,   292,   293,
     259,    16,    17,   142,   142,   142,    47,   166,   142,   147,
     267,   240,   251,   177,    53,   229,     1,   250,   146,   251,
      23,   343,   147,    22,    23,   178,   229,    23,   248,   142,
     266,     1,   316,    23,   252,   233,   164,   165,   324,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,    58,   173,   332,
     173,   160,    45,     1,   278,   179,   253,   160,    22,   273,
     274,   275,   146,   146,   146,   333,   159,   146,    23,   189,
     190,   191,   159,   250,   288,   251,   229,   229,   229,   268,
     334,   335,   336,   341,    67,   363,    68,   342,   146,   366,
     235,   159,    47,   142,    69,   229,   348,   229,   229,   370,
     134,   372,   373,   135,   355,    22,   183,   309,   180,   298,
     299,   300,   301,   138,   182,    23,   135,   192,   184,   193,
     151,   194,   326,    41,   327,   160,   185,   151,   356,   357,
     358,   221,   228,   160,   353,   229,   222,   151,   282,    47,
     159,   229,   317,   211,   212,   318,   223,   267,   159,   251,
     364,   278,   219,   220,   371,   253,   208,   209,   210,   261,
     165,   224,   146,   374,   227,   159,   376,   377,   257,     2,
      70,   256,   268,     1,   188,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   229,
     344,   248,   243,   345,   346,   276,   151,   260,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   359,   270,
     361,   362,   294,   295,   271,    22,   296,   297,   302,   303,
     281,   284,   289,   310,   330,    23,    79,    80,    81,    82,
     319,    83,    84,   351,   331,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   337,   368,   349,   350,    24,
     360,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   205,    85,    46,    86,   369,   367,   375,    87,   304,
     308,   237,   305,    88,    89,    90,    91,    92,    93,    79,
      80,    81,    82,   307,    83,    84,   241,   306,   347,   162,
      94,    95,    96,   263,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   231,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   329,    85,    46,   230,    71,   265,
       0,    87,   339,     0,     0,     0,    88,    89,    90,    91,
      92,    93,   156,    80,    81,    82,     0,    83,    84,     0,
       0,     0,     0,    94,    95,    96,     0,    97,    98,    99,
     100,   101,   102,   103,   104,   105,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,   277,     0,
       0,     0,     0,     0,    87,     0,     0,     0,     0,    88,
      89,    90,    91,    92,    93,   156,    80,    81,    82,     0,
      83,    84,     0,     0,     0,     0,     0,   156,    80,    81,
      82,     0,    83,    84,     0,     0,     0,     0,   105,     0,
       2,     0,     0,     0,     0,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      79,    80,    81,    82,     0,    83,    84,    87,     0,     0,
       0,     0,    88,    89,    90,    91,    92,    93,     0,    87,
       0,     0,   157,     0,    88,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   172,     0,     0,     0,     0,    85,    46,   232,     0,
       0,     0,    87,   158,     0,     0,     0,    88,    89,    90,
      91,    92,    93,    79,    80,    81,    82,     0,    83,    84,
       0,     0,     0,     0,    94,    95,    96,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   172,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    85,
      46,   312,     0,     0,     0,    87,     0,   352,     0,     0,
      88,    89,    90,    91,    92,    93,    79,    80,    81,    82,
       0,    83,    84,     0,     0,     0,     0,    94,    95,    96,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   172,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    85,    46,    46,     0,     0,     0,    87,     0,
       0,     0,     0,    88,    89,    90,    91,    92,    93,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   172,    62,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   156,    80,    81,    82,     0,    83,
      84,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,   156,    80,    81,    82,     0,    83,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   156,    80,    81,    82,    24,    83,    84,     0,     0,
       0,   234,   365,     0,     0,     0,    87,     0,     0,     0,
       0,    88,    89,    90,    91,    92,    93,     0,   186,     0,
       0,     0,     0,     0,    87,     0,     0,     0,     0,    88,
      89,    90,    91,    92,    93,     0,     0,     0,   234,     0,
     158,     0,     0,    87,     0,     0,     0,     0,    88,    89,
      90,    91,    92,    93,   156,    80,    81,    82,   172,    83,
      84,     0,     0,     0,     0,   156,    80,    81,    82,     0,
      83,    84,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,     0,     0,   156,    80,    81,    82,     0,    83,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   156,    80,    81,    82,    87,    83,    84,     0,
       0,    88,    89,    90,    91,    92,    93,    87,   285,     0,
       0,     0,    88,    89,    90,    91,    92,    93,     0,     0,
       0,     0,   156,    80,    81,    82,    87,    83,    84,   323,
     238,    88,    89,    90,    91,    92,    93,     0,    85,     0,
       0,   158,     0,     0,    87,     0,     0,     0,     0,    88,
      89,    90,    91,    92,    93,     0,     0,     0,     0,     0,
     158,   156,    80,    81,    82,     0,    83,    84,     0,     0,
       0,     0,     0,     0,    87,     0,     0,   354,   172,    88,
      89,    90,    91,    92,    93,     0,     0,     0,     0,     0,
       0,   156,    80,    81,    82,     0,    83,    84,     0,     0,
       0,     0,     0,     0,   156,    80,    81,    82,   158,    83,
      84,     0,     0,   167,     0,     0,     0,     0,    88,    89,
      90,    91,    92,    93,   156,    80,    81,    82,     0,    83,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   169,     0,     0,     0,   158,    88,    89,
      90,    91,    92,    93,     0,     0,    87,     0,     0,     0,
       0,    88,    89,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,   158,     0,     0,
       0,    88,    89,    90,    91,    92,    93,     1,     2,     0,
     158,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,     0,
     172,   315,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,   250,
     320,   251,     0,     0,     0,     0,     0,     0,     0,    23,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,    46,     0,     0,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   328,     0,
       0,    62,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
     150,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,     0,     0,     0,     0,   267,   320,
     251,     0,     0,     0,     0,     0,     0,     0,    23,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     0,    23,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     2,
       0,     0,     0,     0,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
       0,    94,     0,     0,    68,    67,    35,   133,   182,   136,
     136,   143,     3,    26,    50,    24,    87,    49,   109,    68,
      12,    13,    54,    99,    33,    22,     3,    27,    28,    26,
      94,     3,    32,    82,    83,    84,    36,     3,    36,    36,
       3,   253,    60,     3,    46,    94,    55,    54,     3,    17,
       3,    64,   128,    55,    10,    11,   268,    66,    23,   151,
     109,    56,   188,    28,    55,    50,   192,    67,    66,    87,
     163,   142,    49,    50,    23,   146,    68,    69,    55,    44,
     206,    53,   174,    55,    50,     3,    49,    54,    65,    52,
     166,     3,    55,    65,    49,    44,   167,    50,    87,   163,
      55,   177,    65,   229,    72,   279,   280,   234,   234,   241,
      65,    60,    89,    54,   163,   104,    52,   208,   209,   210,
      56,    42,    43,   141,   142,   143,    89,    53,   146,   127,
      55,   140,    57,    53,    89,    52,     3,    55,    87,    57,
      65,    58,   140,    55,    65,    55,    52,    65,   145,   167,
      56,     3,   245,    65,   151,   231,    51,    52,   251,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   142,   167,   270,
     169,   245,    49,     3,   182,    55,   151,   251,    55,   178,
     179,   180,   141,   142,   143,   271,   245,   146,    65,     7,
       8,     9,   251,    55,   193,    57,    52,    52,    52,   174,
      56,    56,    56,    52,    55,   341,    57,    56,   167,   346,
     346,   270,    89,   241,   253,    52,   319,    52,    52,    56,
      49,    56,    56,    52,   327,    55,     3,   226,    55,   215,
     216,   217,   218,    49,    55,    65,    52,    55,    49,    57,
     250,    59,    55,   250,    57,   319,    49,   257,   334,   335,
     336,    60,    49,   327,   326,    52,    70,   267,    49,    89,
     319,    52,    49,    63,    64,    52,    71,    55,   327,    57,
     344,   279,    14,    15,   360,   250,    65,    66,    67,    51,
      52,    16,   241,   369,    52,   344,   372,   373,    52,    28,
       0,    56,   267,     3,    52,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    52,
      53,   318,    51,    51,    52,    82,   326,    58,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   337,    56,
     339,   340,   211,   212,    53,    55,   213,   214,   219,   220,
      49,     3,     3,    89,     3,    65,     3,     4,     5,     6,
      53,     8,     9,    58,    56,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    55,    58,    56,    56,    89,
      56,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    54,    49,    50,    51,    80,    56,    49,    55,   221,
     225,   135,   222,    60,    61,    62,    63,    64,    65,     3,
       4,     5,     6,   224,     8,     9,   141,   223,   318,    72,
      77,    78,    79,   165,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   127,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,   257,    49,    50,    51,    36,   167,
      -1,    55,   279,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    89,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       3,     4,     5,     6,    -1,     8,     9,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    -1,    55,
      -1,    -1,    58,    -1,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      -1,    -1,    55,    89,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    49,
      50,    51,    -1,    -1,    -1,    55,    -1,    56,    -1,    -1,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    49,    50,    50,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    89,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     3,     4,     5,     6,    -1,     8,
       9,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    89,     8,     9,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    50,    -1,
      89,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,     3,     4,     5,     6,    89,     8,
       9,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,     3,     4,     5,     6,    55,     8,     9,    -1,
      -1,    60,    61,    62,    63,    64,    65,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    55,     8,     9,    58,
      89,    60,    61,    62,    63,    64,    65,    -1,    49,    -1,
      -1,    89,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      89,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    58,    89,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    89,     8,
       9,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    89,    60,    61,
      62,    63,    64,    65,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    89,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,     3,    28,    -1,
      89,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      89,    51,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    89,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    65,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    28,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    55,    65,    89,   112,   113,   116,   117,   118,
     119,   125,   128,   129,   130,   131,   152,   153,   154,     3,
      50,   129,   128,   131,   132,    49,    50,    89,   114,   115,
     129,   144,    49,    89,   114,   129,   113,   113,   131,     3,
      50,   113,    89,   112,   113,   144,   145,    55,    57,   130,
       0,   153,    50,     3,   126,   127,    56,   128,   131,     3,
       4,     5,     6,     8,     9,    49,    51,    55,    60,    61,
      62,    63,    64,    65,    77,    78,    79,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    91,    92,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   110,   142,   143,   144,   145,   146,   147,
     148,   150,   151,    54,    49,    52,    54,    49,    49,   144,
     145,    50,   117,   120,   121,   122,   128,   112,   144,     3,
      56,   113,   133,   134,   135,   136,     3,    58,    89,    94,
     107,   111,   126,    54,    51,    52,    53,    55,    94,    55,
      94,    94,    89,   110,   122,   137,   111,    53,    55,    55,
      55,   142,    55,     3,    49,    49,    49,   110,    52,     7,
       8,     9,    55,    57,    59,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    54,   109,    96,    65,    66,
      67,    63,    64,    10,    11,    12,    13,    68,    69,    14,
      15,    60,    70,    71,    16,    17,    72,    52,    49,    52,
      51,   146,    51,   142,    50,   108,   140,   115,    89,   140,
     144,   120,   122,    51,   121,    53,   123,   124,   129,   122,
      55,    57,   129,   131,   138,   139,    56,    52,    52,    56,
      58,    51,   111,   127,   142,   137,    56,    55,   131,   138,
      56,    53,   142,   110,   110,   110,    82,    49,   112,   147,
     149,    49,    49,   108,     3,    56,    93,   108,   110,     3,
     108,    96,    96,    96,    97,    97,    98,    98,    99,    99,
      99,    99,   100,   100,   101,   102,   103,   104,   105,   110,
      89,   108,    51,   140,   141,    51,   111,    49,    52,    53,
      56,   133,   138,    58,   111,   139,    55,    57,    48,   135,
       3,    56,    96,   142,    56,    56,    56,    55,   147,   149,
     147,    52,    56,    58,    53,    51,    52,   124,   111,    56,
      56,    58,    56,   133,    58,   111,   142,   142,   142,   110,
      56,   110,   110,   108,   107,    51,   140,    56,    58,    80,
      56,   142,    56,    56,   142,    49,   142,   142
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    95,    95,    95,    95,    95,    95,    96,
      96,    97,    97,    97,    97,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   111,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   113,
     114,   114,   115,   115,   115,   115,   116,   116,   116,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   119,   119,   120,
     120,   121,   122,   122,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   140,   140,
     140,   141,   141,   142,   142,   142,   142,   142,   142,   143,
     143,   143,   144,   144,   144,   144,   145,   145,   146,   146,
     147,   147,   148,   148,   148,   149,   149,   150,   150,   150,
     150,   150,   151,   151,   151,   151,   151,   152,   152,   153,
     153,   154,   154,   154,   154,   154
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     4,     3,
       4,     3,     3,     2,     2,     1,     3,     1,     2,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     2,
       3,     2,     3,     3,     1,     2,     1,     2,     1,     2,
       1,     3,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     4,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     3,     1,     2,
       3,     4,     5,     2,     1,     3,     1,     3,     1,     1,
       2,     1,     1,     3,     4,     3,     4,     4,     3,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     2,     1,     1,     2,     3,
       2,     3,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     3,     4,     1,     2,     1,     2,
       1,     2,     5,     7,     5,     1,     1,     5,     7,     6,
       7,     7,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     4,     3,     3,     2,     2
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 6: /* primary_expression: ERROR  */
#line 114 "src/mylang.y"
                {
		yyerror((yyvsp[0].nice));
		yyerrok;
	}
#line 2009 "src/y.tab.c"
    break;

  case 23: /* unary_operator: AMPERSAND  */
#line 149 "src/mylang.y"
                        { (yyval.nice) = "&"; }
#line 2015 "src/y.tab.c"
    break;

  case 24: /* unary_operator: ASTERISK  */
#line 150 "src/mylang.y"
                        { (yyval.nice) = "*"; }
#line 2021 "src/y.tab.c"
    break;

  case 25: /* unary_operator: PLUS  */
#line 151 "src/mylang.y"
                        { (yyval.nice) = "+"; }
#line 2027 "src/y.tab.c"
    break;

  case 26: /* unary_operator: MINUS  */
#line 152 "src/mylang.y"
                        { (yyval.nice) = "-"; }
#line 2033 "src/y.tab.c"
    break;

  case 27: /* unary_operator: TILDE  */
#line 153 "src/mylang.y"
                        { (yyval.nice) = "~"; }
#line 2039 "src/y.tab.c"
    break;

  case 28: /* unary_operator: EXCLAMATION  */
#line 154 "src/mylang.y"
                        { (yyval.nice) = "!"; }
#line 2045 "src/y.tab.c"
    break;

  case 76: /* expression: ERROR COMMA assignment_expression  */
#line 255 "src/mylang.y"
                                            {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2054 "src/y.tab.c"
    break;

  case 77: /* expression: assignment_expression COMMA ERROR  */
#line 259 "src/mylang.y"
                                            {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2063 "src/y.tab.c"
    break;

  case 79: /* declaration: declaration_specifiers SEMICOLON  */
#line 271 "src/mylang.y"
                                           {
		  insertSymbol((yyvsp[-1].nice), "variable", (yyval.nice));
	  }
#line 2071 "src/y.tab.c"
    break;

  case 80: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 274 "src/mylang.y"
                                                                {
		  /* Use the variable name from init_declarator */
		  insertSymbol((yyvsp[-1].nice), "variable", (yyval.nice));
	  }
#line 2080 "src/y.tab.c"
    break;

  case 81: /* declaration: ERROR SEMICOLON  */
#line 278 "src/mylang.y"
                          {
		yyerror((yyvsp[-1].nice));
		yyerrok;
	}
#line 2089 "src/y.tab.c"
    break;

  case 82: /* declaration: ERROR init_declarator_list SEMICOLON  */
#line 282 "src/mylang.y"
                                               {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2098 "src/y.tab.c"
    break;

  case 83: /* declaration: declaration_specifiers ERROR SEMICOLON  */
#line 286 "src/mylang.y"
                                                 {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2107 "src/y.tab.c"
    break;

  case 94: /* init_declarator: ERROR ASSIGN initializer  */
#line 309 "src/mylang.y"
                                   {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2116 "src/y.tab.c"
    break;

  case 95: /* init_declarator: declarator ASSIGN ERROR  */
#line 313 "src/mylang.y"
                                  {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 2125 "src/y.tab.c"
    break;

  case 101: /* type_specifier: VOID  */
#line 330 "src/mylang.y"
                   { (yyval.nice) = strdup("VOID"); }
#line 2131 "src/y.tab.c"
    break;

  case 102: /* type_specifier: CHAR  */
#line 331 "src/mylang.y"
                   { (yyval.nice) = strdup("CHAR");}
#line 2137 "src/y.tab.c"
    break;

  case 103: /* type_specifier: SHORT  */
#line 332 "src/mylang.y"
                   { (yyval.nice) = strdup("SHORT");}
#line 2143 "src/y.tab.c"
    break;

  case 104: /* type_specifier: INT  */
#line 333 "src/mylang.y"
                   { (yyval.nice) = strdup("INT");}
#line 2149 "src/y.tab.c"
    break;

  case 105: /* type_specifier: LONG  */
#line 334 "src/mylang.y"
                   { (yyval.nice) = strdup("LONG");}
#line 2155 "src/y.tab.c"
    break;

  case 106: /* type_specifier: FLOAT  */
#line 335 "src/mylang.y"
                   { (yyval.nice) = strdup("FLOAT");}
#line 2161 "src/y.tab.c"
    break;

  case 107: /* type_specifier: DOUBLE  */
#line 336 "src/mylang.y"
                   { (yyval.nice) = strdup("DOUBLE");}
#line 2167 "src/y.tab.c"
    break;

  case 108: /* type_specifier: SIGNED  */
#line 337 "src/mylang.y"
                   { (yyval.nice) = strdup("SIGNED");}
#line 2173 "src/y.tab.c"
    break;

  case 109: /* type_specifier: UNSIGNED  */
#line 338 "src/mylang.y"
                   { (yyval.nice) = strdup("UNSIGNED");}
#line 2179 "src/y.tab.c"
    break;

  case 110: /* type_specifier: struct_or_union_specifier  */
#line 339 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 2185 "src/y.tab.c"
    break;

  case 111: /* type_specifier: enum_specifier  */
#line 340 "src/mylang.y"
                         { (yyval.nice) = (yyvsp[0].nice); }
#line 2191 "src/y.tab.c"
    break;

  case 112: /* type_specifier: TYPE_NAME  */
#line 341 "src/mylang.y"
                    { (yyval.nice) = strdup("TYPE_NAME");}
#line 2197 "src/y.tab.c"
    break;

  case 113: /* type_specifier: type_specifier pointer  */
#line 342 "src/mylang.y"
                                 {
		char*temp = malloc(strlen((yyvsp[-1].nice)) + 2 );
		sprintf(temp, "%s*", (yyvsp[-1].nice));
		(yyval.nice) = temp;
	}
#line 2207 "src/y.tab.c"
    break;

  case 114: /* struct_or_union_specifier: struct_or_union IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 351 "src/mylang.y"
                                                                                    { (yyval.nice) = (yyvsp[-3].nice); }
#line 2213 "src/y.tab.c"
    break;

  case 116: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 353 "src/mylang.y"
                                     { (yyval.nice) = (yyvsp[0].nice); }
#line 2219 "src/y.tab.c"
    break;

  case 138: /* type_qualifier: CONST  */
#line 407 "src/mylang.y"
                   { (yyval.nice) = strdup("CONST"); }
#line 2225 "src/y.tab.c"
    break;

  case 139: /* type_qualifier: VOLATILE  */
#line 408 "src/mylang.y"
                   { (yyval.nice) = strdup("VOLATILE"); }
#line 2231 "src/y.tab.c"
    break;

  case 140: /* declarator: pointer direct_declarator  */
#line 413 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 2237 "src/y.tab.c"
    break;

  case 141: /* declarator: direct_declarator  */
#line 414 "src/mylang.y"
                            { (yyval.nice) = (yyvsp[0].nice); }
#line 2243 "src/y.tab.c"
    break;

  case 142: /* direct_declarator: IDENTIFIER  */
#line 418 "src/mylang.y"
                     { (yyval.nice) = (yyvsp[0].nice); }
#line 2249 "src/y.tab.c"
    break;

  case 143: /* direct_declarator: LEFT_PAREN declarator RIGHT_PAREN  */
#line 419 "src/mylang.y"
                                            { (yyval.nice) = (yyvsp[-1].nice); }
#line 2255 "src/y.tab.c"
    break;

  case 144: /* direct_declarator: direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET  */
#line 420 "src/mylang.y"
                                                                           { (yyval.nice) = (yyvsp[-3].nice); }
#line 2261 "src/y.tab.c"
    break;

  case 145: /* direct_declarator: direct_declarator LEFT_BRACKET RIGHT_BRACKET  */
#line 421 "src/mylang.y"
                                                       { (yyval.nice) = (yyvsp[-2].nice); }
#line 2267 "src/y.tab.c"
    break;

  case 146: /* direct_declarator: direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN  */
#line 422 "src/mylang.y"
                                                                       { (yyval.nice) = (yyvsp[-3].nice); }
#line 2273 "src/y.tab.c"
    break;

  case 147: /* direct_declarator: direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN  */
#line 423 "src/mylang.y"
                                                                   { (yyval.nice) = (yyvsp[-3].nice); }
#line 2279 "src/y.tab.c"
    break;

  case 148: /* direct_declarator: direct_declarator LEFT_PAREN RIGHT_PAREN  */
#line 424 "src/mylang.y"
                                                   { (yyval.nice) = (yyvsp[-2].nice); }
#line 2285 "src/y.tab.c"
    break;

  case 149: /* pointer: ASTERISK  */
#line 428 "src/mylang.y"
                   { (yyval.nice) = NULL; }
#line 2291 "src/y.tab.c"
    break;

  case 150: /* pointer: ASTERISK type_qualifier_list  */
#line 429 "src/mylang.y"
                                       { (yyval.nice) = NULL; }
#line 2297 "src/y.tab.c"
    break;

  case 151: /* pointer: ASTERISK pointer  */
#line 430 "src/mylang.y"
                           { (yyval.nice) = NULL; }
#line 2303 "src/y.tab.c"
    break;

  case 152: /* pointer: ASTERISK type_qualifier_list pointer  */
#line 431 "src/mylang.y"
                                               { (yyval.nice) = NULL; }
#line 2309 "src/y.tab.c"
    break;

  case 221: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 574 "src/mylang.y"
                                                                                {
		  insertSymbol((yyvsp[-2].nice), "function", (yyvsp[-3].nice)); /* Insert function with its return type */
	  }
#line 2317 "src/y.tab.c"
    break;

  case 222: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 577 "src/mylang.y"
                                                               {
		  insertSymbol((yyvsp[-1].nice), "function", (yyvsp[-2].nice));
	  }
#line 2325 "src/y.tab.c"
    break;

  case 223: /* function_definition: declarator declaration_list compound_statement  */
#line 580 "src/mylang.y"
                                                         {
		  insertSymbol((yyvsp[-2].nice), "function", "auto"); /* Default to auto when return type isn't specified */
	  }
#line 2333 "src/y.tab.c"
    break;

  case 224: /* function_definition: declarator compound_statement  */
#line 583 "src/mylang.y"
                                        {
		  insertSymbol((yyvsp[-1].nice), "function", "auto");
	  }
#line 2341 "src/y.tab.c"
    break;

  case 225: /* function_definition: ERROR compound_statement  */
#line 586 "src/mylang.y"
                                   {
		yyerror((yyvsp[-1].nice));
		yyerrok;
	}
#line 2350 "src/y.tab.c"
    break;


#line 2354 "src/y.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 593 "src/mylang.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
    grammarErrorCount++;
}
