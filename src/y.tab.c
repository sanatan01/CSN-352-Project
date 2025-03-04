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
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_primary_expression = 90,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 91,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 92,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 93,          /* unary_expression  */
  YYSYMBOL_unary_operator = 94,            /* unary_operator  */
  YYSYMBOL_cast_expression = 95,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 96, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 97,       /* additive_expression  */
  YYSYMBOL_shift_expression = 98,          /* shift_expression  */
  YYSYMBOL_relational_expression = 99,     /* relational_expression  */
  YYSYMBOL_equality_expression = 100,      /* equality_expression  */
  YYSYMBOL_and_expression = 101,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 102,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 103,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 104,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 105,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 106,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 107,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 108,      /* assignment_operator  */
  YYSYMBOL_expression = 109,               /* expression  */
  YYSYMBOL_constant_expression = 110,      /* constant_expression  */
  YYSYMBOL_declaration = 111,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 112,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 113,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 114,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 115,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 116,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 117, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 118,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 119,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 120,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 121, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 122,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 123,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 124,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 125,          /* enumerator_list  */
  YYSYMBOL_enumerator = 126,               /* enumerator  */
  YYSYMBOL_type_qualifier = 127,           /* type_qualifier  */
  YYSYMBOL_declarator = 128,               /* declarator  */
  YYSYMBOL_direct_declarator = 129,        /* direct_declarator  */
  YYSYMBOL_pointer = 130,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 131,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 132,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 133,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 134,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 135,          /* identifier_list  */
  YYSYMBOL_type_name = 136,                /* type_name  */
  YYSYMBOL_abstract_declarator = 137,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 138, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 139,              /* initializer  */
  YYSYMBOL_initializer_list = 140,         /* initializer_list  */
  YYSYMBOL_statement = 141,                /* statement  */
  YYSYMBOL_labeled_statement = 142,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 143,       /* compound_statement  */
  YYSYMBOL_declaration_list = 144,         /* declaration_list  */
  YYSYMBOL_statement_list = 145,           /* statement_list  */
  YYSYMBOL_expression_statement = 146,     /* expression_statement  */
  YYSYMBOL_selection_statement = 147,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 148,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 149,           /* jump_statement  */
  YYSYMBOL_translation_unit = 150,         /* translation_unit  */
  YYSYMBOL_external_declaration = 151,     /* external_declaration  */
  YYSYMBOL_function_definition = 152       /* function_definition  */
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
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  216
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  354

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   343


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
      85,    86,    87,    88
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   105,   106,   107,   108,   112,   116,   120,
     128,   129,   130,   131,   132,   133,   134,   135,   140,   141,
     146,   147,   148,   149,   150,   151,   155,   156,   157,   158,
     159,   160,   165,   166,   171,   172,   173,   174,   178,   179,
     180,   184,   185,   186,   191,   192,   193,   194,   195,   199,
     200,   201,   206,   207,   211,   212,   216,   217,   222,   223,
     227,   228,   233,   234,   239,   240,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   259,   260,   264,
     269,   272,   279,   280,   281,   282,   283,   284,   288,   289,
     293,   294,   299,   300,   301,   302,   303,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   324,
     325,   326,   330,   331,   335,   336,   340,   344,   345,   346,
     347,   351,   352,   356,   357,   358,   363,   364,   365,   369,
     370,   374,   375,   380,   381,   386,   387,   391,   392,   393,
     394,   395,   396,   397,   401,   402,   403,   404,   408,   409,
     414,   415,   419,   420,   424,   425,   426,   430,   431,   435,
     436,   440,   441,   442,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   459,   460,   461,   465,   466,   471,   472,
     473,   474,   475,   476,   480,   481,   482,   486,   487,   488,
     489,   493,   494,   498,   499,   503,   504,   509,   510,   511,
     515,   516,   517,   518,   522,   523,   524,   525,   526,   531,
     532,   536,   537,   541,   544,   547,   550
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
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "$accept",
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
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-210)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1060,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,    21,     9,   -21,  -210,    11,  1310,  1310,  -210,    34,
    -210,  1310,  1266,    99,    38,   970,  -210,  -210,   -10,    51,
      35,  -210,  -210,   -21,  -210,    23,  -210,  1201,  -210,  -210,
      36,  1330,  -210,   280,  -210,    11,  -210,  1266,  1105,   440,
      99,  -210,  -210,    51,    47,   156,  -210,  -210,  -210,  -210,
    -210,     9,   669,  -210,  1266,  1330,  1330,  1222,  -210,    14,
    1330,    73,  -210,  -210,   858,   892,   892,  -210,  -210,   595,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
     921,    92,     4,   127,   133,   532,   136,   117,   146,   151,
     703,  -210,   142,   274,   921,  -210,   152,   158,   221,    65,
     227,   155,   139,   181,   213,    -4,  -210,  -210,    31,  -210,
    -210,  -210,   343,   406,  -210,  -210,  -210,  -210,   204,  -210,
    -210,  -210,  -210,    67,   211,   216,  -210,     5,  -210,  -210,
    -210,  -210,   214,   193,   921,  -210,    51,  -210,   669,  -210,
    -210,  -210,  1242,  -210,  -210,  -210,   921,    76,  -210,   218,
    -210,   532,   595,  -210,   921,  -210,  -210,    57,    74,   217,
     223,   532,   921,   921,   921,   192,   732,   228,  -210,  -210,
    -210,    94,   275,  -210,  -210,   503,   921,   276,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,   921,
    -210,   921,   921,   921,   921,   921,   921,   921,   921,   921,
     921,   921,   921,   921,   921,   921,   921,   921,   921,   921,
    -210,   921,  -210,   469,  -210,  -210,  1015,   766,  -210,    33,
    -210,   157,  -210,  1289,   277,  -210,  -210,  -210,  -210,  -210,
    -210,   195,  -210,  -210,  -210,    14,   921,  -210,   225,  -210,
    1134,   173,  -210,   921,   532,  -210,    86,    96,   101,   232,
     732,  -210,  -210,  -210,  -210,   128,  -210,    -7,  -210,  -210,
    -210,  -210,  -210,   152,   152,   158,   158,   221,   221,   221,
     221,    65,    65,   227,   155,   139,   181,   213,   196,  -210,
    -210,  -210,   226,   234,  -210,   233,   157,  1172,   795,  -210,
    -210,  -210,  -210,   640,  -210,  -210,  -210,  -210,  -210,   532,
     532,   532,   921,   829,   921,  -210,  -210,   921,  -210,  -210,
    -210,  -210,   246,  -210,   245,  -210,  -210,   224,  -210,  -210,
     137,   532,   138,  -210,  -210,  -210,  -210,   532,   256,  -210,
     532,  -210,  -210,  -210
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   137,   108,    92,    93,    94,    95,    96,    98,    99,
     100,   101,   104,   105,   102,   103,   133,   134,    97,   112,
     113,     0,     0,   144,   212,     0,    82,    84,   106,     0,
     107,    86,     0,   136,     0,     0,   209,   211,   128,     0,
       0,   148,   146,   145,    80,     0,    88,    90,    83,    85,
     111,     0,    87,     0,   191,     0,   216,     0,     0,     0,
     135,     1,   210,     0,   131,     0,   129,   138,   149,   147,
      81,     0,     0,   214,     0,     0,   118,     0,   114,     0,
     120,     2,     3,     4,     0,     0,     0,   195,   187,     0,
      26,    31,    30,    29,    28,    27,     6,     7,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,    20,    32,     0,    34,    38,    41,    44,    49,
      52,    54,    56,    58,    60,    62,    64,    77,     0,   193,
     178,   179,     0,     0,   180,   181,   182,   183,    90,   192,
     215,   157,   143,   156,     0,   150,   152,     0,     2,   140,
      32,    79,     0,     0,     0,   126,     0,    89,     0,   173,
      91,   213,     0,   117,   110,   115,     0,     0,   121,   123,
     119,     0,     0,    24,     0,    21,    22,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,   206,
     207,     0,     0,    16,    17,     0,     0,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    66,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     196,     0,   189,     0,   188,   194,     0,     0,   154,   161,
     155,   162,   141,     0,     0,   142,   139,   127,   132,   130,
     176,     0,   109,   124,   116,     0,     0,   184,     0,     5,
       0,   161,   160,     0,     0,   186,     0,     0,     0,     0,
       0,   204,   208,    15,    12,     0,    18,     0,    14,    65,
      35,    36,    37,    40,    39,    42,    43,    47,    48,    45,
      46,    50,    51,    53,    55,    57,    59,    61,     0,    78,
     190,   169,     0,     0,   165,     0,   163,     0,     0,   151,
     153,   158,   174,     0,   122,   125,    25,    33,   185,     0,
       0,     0,     0,     0,     0,    13,    11,     0,   170,   164,
     166,   171,     0,   167,     0,   175,   177,   197,   199,   200,
       0,     0,     0,    19,    63,   172,   168,     0,     0,   202,
       0,   198,   201,   203
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -210,  -210,  -210,  -210,   -52,  -210,   -76,    39,    46,     6,
      43,    82,   107,   108,   106,   109,  -210,   -58,   -54,  -210,
     -85,   -51,     8,     0,  -210,   265,  -210,    41,  -210,  -210,
     263,   -62,   -60,  -210,    84,  -210,   287,   235,    30,   -16,
     -29,   -20,  -210,   -56,  -210,   126,  -210,   188,  -132,  -209,
    -130,  -210,   -86,  -210,   149,     3,   238,  -176,  -210,  -210,
    -210,  -210,   360,  -210
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   111,   112,   275,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   209,
     128,   152,    54,    55,    45,    46,    26,    27,    28,    29,
      77,    78,    79,   167,   168,    30,    65,    66,    31,    32,
      33,    34,    43,   302,   145,   146,   147,   179,   303,   241,
     160,   251,   129,   130,   131,    57,   133,   134,   135,   136,
     137,    35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   151,   144,    42,   177,    60,    40,   150,    24,    47,
     270,   240,     1,   228,     1,   165,   163,     1,   159,   185,
     170,    16,    17,    69,    38,   191,    48,    49,   250,   178,
     306,    52,   173,   175,   176,    25,     1,    50,   210,   138,
      63,     1,   151,    24,    23,   231,   262,   235,   150,   180,
      74,   326,   306,    41,    64,   138,   132,   244,   143,   182,
      44,   245,   150,   169,    22,   139,    22,   166,   229,    22,
       1,    39,    70,    68,    23,    71,    23,   218,   219,    23,
     230,    80,   139,   231,    51,   257,    75,   177,   236,   177,
     237,    67,    76,    22,   323,   265,   151,   266,   267,   268,
     165,   154,   150,   248,   159,    80,    80,    80,   151,   231,
      80,   277,   178,   259,   150,   253,    76,    76,    76,    80,
     187,    76,   236,   239,   237,   254,   171,   238,   255,   260,
      76,   237,    23,   220,   221,   280,   281,   282,   231,    23,
     139,   276,   319,   272,   298,   181,   231,   235,   231,   192,
     193,   194,   320,   231,    58,   279,    59,   321,   261,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   299,   318,   151,
     324,    56,   183,   336,   325,   150,   305,   317,   184,   231,
     231,   186,    80,   348,   350,   188,    73,   195,   151,   196,
     189,   197,    80,    76,   150,   315,   140,   155,   156,   225,
      60,   150,   307,    76,   308,   224,   239,   211,   212,   213,
      40,   214,   215,   161,   287,   288,   289,   290,   260,   227,
     237,   216,   217,   337,   338,   339,   143,   340,   342,   169,
     261,   222,   223,   143,   247,   156,   312,   313,   231,   327,
     151,   332,   226,   283,   284,   349,   150,   334,    72,   159,
     143,   351,   285,   286,   353,   291,   292,   242,   243,   344,
     343,   256,   246,   263,   269,   150,   264,   271,   273,   278,
     311,   316,   328,    81,    82,    83,    84,   322,    85,    86,
     329,   330,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   345,   346,   347,   352,   293,   143,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   208,    87,
      53,    88,   294,   296,   295,    89,   157,   297,   162,   314,
      90,    91,    92,    93,    94,    95,    81,    82,    83,    84,
     153,    85,    86,    96,    97,    98,    99,   100,   101,   102,
     258,   103,   104,   105,   106,   107,   108,   109,   110,   310,
     233,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   249,    87,    53,   232,    62,     0,     0,    89,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,    81,
      82,    83,    84,     0,    85,    86,    96,    97,    98,    99,
     100,   101,   102,     0,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,    82,    83,    84,     0,    85,    86,
       0,     0,     0,     0,     0,    87,    53,   234,     0,     0,
       0,    89,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    81,    82,    83,    84,     0,    85,    86,    96,
      97,    98,    99,   100,   101,   102,     0,   103,   104,   105,
     106,   107,   108,   109,   110,    89,     0,     0,   149,     0,
      90,    91,    92,    93,    94,    95,   148,    82,    83,    84,
       0,    85,    86,    96,    97,    98,    99,     0,    87,    53,
     300,     0,     0,     0,    89,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    81,    82,    83,    84,     0,
      85,    86,    96,    97,    98,    99,   100,   101,   102,     0,
     103,   104,   105,   106,   107,   108,   109,   110,    89,   274,
       0,     0,     0,    90,    91,    92,    93,    94,    95,     0,
       0,     0,     0,     0,     0,     0,    96,    97,    98,    99,
       0,    87,    53,     0,     0,     0,     0,    89,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,   148,    82,
      83,    84,     0,    85,    86,    96,    97,    98,    99,   100,
     101,   102,     0,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     2,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,   148,    82,    83,    84,     0,    85,    86,
      89,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,   148,    82,    83,    84,     0,    85,    86,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,   335,     0,     0,     0,    89,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    95,   148,    82,    83,    84,
       0,    85,    86,    96,    97,    98,    99,     0,     0,   158,
       0,     0,     0,     0,    89,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,   148,    82,    83,    84,     0,
      85,    86,    96,    97,    98,    99,     0,     0,     0,     0,
       0,     0,   190,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,   148,
      82,    83,    84,     0,    85,    86,    96,    97,    98,    99,
       0,    87,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,   148,    82,
      83,    84,     0,    85,    86,    96,    97,    98,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,     0,     0,   304,     0,    90,    91,    92,    93,
      94,    95,   148,    82,    83,    84,     0,    85,    86,    96,
      97,    98,    99,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,   333,     0,    90,    91,    92,    93,    94,
      95,   148,    82,    83,    84,     0,    85,    86,    96,    97,
      98,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,   341,     0,     0,     0,    90,
      91,    92,    93,    94,    95,   148,    82,    83,    84,     0,
      85,    86,    96,    97,    98,    99,     0,     0,     0,     0,
       0,     0,     0,   172,     0,     0,     0,     0,    90,    91,
      92,    93,    94,    95,   148,    82,    83,    84,     0,    85,
      86,    96,    97,    98,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
      61,     0,     0,     1,     0,     0,    89,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,     0,     0,     0,
       0,     0,     0,     0,    96,    97,    98,    99,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     1,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     1,     0,     0,     0,     0,     0,     0,
     236,   301,   237,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   141,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,     0,     0,     0,     0,     0,     0,
       0,   142,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,   260,
     301,   237,     0,     0,     0,     0,     0,     0,     0,    23,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,     0,     0,   331,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       2,    53,     0,     0,     0,    72,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       2,     0,     0,   164,     0,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,   252,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,    53,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   309,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     2,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
       0,    59,    58,    23,    89,    34,    22,    59,     0,    25,
     186,   143,     3,    17,     3,    77,    76,     3,    72,   105,
      80,    42,    43,    43,     3,   110,    26,    27,   158,    89,
     239,    31,    84,    85,    86,    35,     3,     3,   114,    55,
      50,     3,   100,    35,    65,    52,   178,   133,   100,   100,
      47,    58,   261,    23,     3,    71,    53,    52,    58,    55,
      49,    56,   114,    79,    55,    57,    55,    53,    72,    55,
       3,    50,    49,    43,    65,    52,    65,    12,    13,    65,
      49,    51,    74,    52,    50,   171,    50,   172,    55,   174,
      57,    56,    51,    55,   270,   181,   154,   182,   183,   184,
     162,    54,   154,   154,   158,    75,    76,    77,   166,    52,
      80,   196,   172,    56,   166,   166,    75,    76,    77,    89,
       3,    80,    55,   143,    57,    49,    53,   143,    52,    55,
      89,    57,    65,    68,    69,   211,   212,   213,    52,    65,
     132,   195,    56,    49,   229,    53,    52,   233,    52,     7,
       8,     9,    56,    52,    55,   209,    57,    56,   178,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   231,   264,   237,
      52,    32,    55,   313,    56,   237,   237,   263,    55,    52,
      52,    55,   162,    56,    56,    49,    47,    55,   256,    57,
      49,    59,   172,   162,   256,   256,    57,    51,    52,    70,
     239,   263,    55,   172,    57,    60,   236,    65,    66,    67,
     236,    63,    64,    74,   218,   219,   220,   221,    55,    16,
      57,    10,    11,   319,   320,   321,   236,   322,   323,   255,
     260,    14,    15,   243,    51,    52,    51,    52,    52,    53,
     308,   307,    71,   214,   215,   341,   308,   308,    54,   313,
     260,   347,   216,   217,   350,   222,   223,    56,    52,   327,
     324,    53,    58,    56,    82,   327,    53,    49,     3,     3,
       3,    56,    56,     3,     4,     5,     6,    55,     8,     9,
      56,    58,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    56,    58,    80,    49,   224,   307,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    54,    49,
      50,    51,   225,   227,   226,    55,    71,   228,    75,   255,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      63,     8,     9,    73,    74,    75,    76,    77,    78,    79,
     172,    81,    82,    83,    84,    85,    86,    87,    88,   243,
     132,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   156,    49,    50,    51,    35,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,     3,
       4,     5,     6,    -1,     8,     9,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    -1,     8,     9,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    55,    -1,    -1,    58,    -1,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      -1,     8,     9,    73,    74,    75,    76,    -1,    49,    50,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    55,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      -1,    49,    50,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,     3,     4,
       5,     6,    -1,     8,     9,    73,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,    -1,     8,     9,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      -1,     8,     9,    73,    74,    75,    76,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,     3,
       4,     5,     6,    -1,     8,     9,    73,    74,    75,    76,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,     3,     4,
       5,     6,    -1,     8,     9,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    58,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    -1,     8,     9,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    58,    -1,    60,    61,    62,    63,    64,
      65,     3,     4,     5,     6,    -1,     8,     9,    73,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,     3,     4,     5,     6,    -1,     8,
       9,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,
       0,    -1,    -1,     3,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      28,    50,    -1,    -1,    -1,    54,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      28,    -1,    -1,    51,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    50,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    55,    65,   111,   112,   115,   116,   117,   118,
     124,   127,   128,   129,   130,   150,   151,   152,     3,    50,
     128,   127,   130,   131,    49,   113,   114,   128,   112,   112,
       3,    50,   112,    50,   111,   112,   143,   144,    55,    57,
     129,     0,   151,    50,     3,   125,   126,    56,   127,   130,
      49,    52,    54,   143,   144,    50,   116,   119,   120,   121,
     127,     3,     4,     5,     6,     8,     9,    49,    51,    55,
      60,    61,    62,    63,    64,    65,    73,    74,    75,    76,
      77,    78,    79,    81,    82,    83,    84,    85,    86,    87,
      88,    90,    91,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   109,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   128,   111,
     143,     3,    56,   112,   132,   133,   134,   135,     3,    58,
      93,   106,   110,   125,    54,    51,    52,   114,    50,   107,
     139,   143,   119,   121,    51,   120,    53,   122,   123,   128,
     121,    53,    55,    93,    55,    93,    93,   109,   121,   136,
     110,    53,    55,    55,    55,   141,    55,     3,    49,    49,
      49,   109,     7,     8,     9,    55,    57,    59,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    54,   108,
      95,    65,    66,    67,    63,    64,    10,    11,    12,    13,
      68,    69,    14,    15,    60,    70,    71,    16,    17,    72,
      49,    52,    51,   145,    51,   141,    55,    57,   128,   130,
     137,   138,    56,    52,    52,    56,    58,    51,   110,   126,
     139,   140,    51,   110,    49,    52,    53,   141,   136,    56,
      55,   130,   137,    56,    53,   141,   109,   109,   109,    82,
     146,    49,    49,     3,    56,    92,   107,   109,     3,   107,
      95,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      98,    99,    99,   100,   101,   102,   103,   104,   109,   107,
      51,    56,   132,   137,    58,   110,   138,    55,    57,    48,
     134,     3,    51,    52,   123,   110,    56,    95,   141,    56,
      56,    56,    55,   146,    52,    56,    58,    53,    56,    56,
      58,    56,   132,    58,   110,    51,   139,   141,   141,   141,
     109,    56,   109,   107,   106,    56,    58,    80,    56,   141,
      56,   141,    49,   141
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    92,
      93,    93,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    96,    96,    96,    97,    97,
      97,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   109,   110,
     111,   111,   112,   112,   112,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   118,   118,   119,   119,   120,   121,   121,   121,
     121,   122,   122,   123,   123,   123,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   131,   131,
     132,   132,   133,   133,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   139,   140,   140,   141,   141,
     141,   141,   141,   141,   142,   142,   142,   143,   143,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   147,
     148,   148,   148,   148,   149,   149,   149,   149,   149,   150,
     150,   151,   151,   152,   152,   152,   152
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     3,     2,     2,     1,     3,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     1,     2,     3,     2,     1,     2,
       1,     1,     3,     1,     2,     3,     4,     5,     2,     1,
       3,     1,     3,     1,     1,     2,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     2,     2,     3,     1,     2,
       1,     3,     1,     3,     2,     2,     1,     1,     3,     1,
       2,     1,     1,     2,     3,     2,     3,     3,     4,     2,
       3,     3,     4,     1,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     4,     3,     2,     3,     3,
       4,     1,     2,     1,     2,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     3,     2,     2,     2,     3,     1,
       2,     1,     1,     4,     3,     3,     2
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
  case 6: /* primary_expression: INVALID_ID  */
#line 108 "src/mylang.y"
                    { 
        yyerror("Invalid identifier used in expression"); 
        (yyval.nice) = "error";
    }
#line 1708 "src/y.tab.c"
    break;

  case 7: /* primary_expression: INVALID_CHAR  */
#line 112 "src/mylang.y"
                    { 
        yyerror("Invalid character in expression"); 
        (yyval.nice) = "error";
    }
#line 1717 "src/y.tab.c"
    break;

  case 8: /* primary_expression: INVALID_OCT  */
#line 116 "src/mylang.y"
                    { 
        yyerror("Invalid octal constant in expression"); 
        (yyval.nice) = "error";
    }
#line 1726 "src/y.tab.c"
    break;

  case 9: /* primary_expression: UNTERM_STRING  */
#line 120 "src/mylang.y"
                    { 
        yyerror("Unterminated string literal"); 
        (yyval.nice) = "error";
    }
#line 1735 "src/y.tab.c"
    break;

  case 26: /* unary_operator: AMPERSAND  */
#line 155 "src/mylang.y"
                        { (yyval.nice) = "&"; }
#line 1741 "src/y.tab.c"
    break;

  case 27: /* unary_operator: ASTERISK  */
#line 156 "src/mylang.y"
                        { (yyval.nice) = "*"; }
#line 1747 "src/y.tab.c"
    break;

  case 28: /* unary_operator: PLUS  */
#line 157 "src/mylang.y"
                        { (yyval.nice) = "+"; }
#line 1753 "src/y.tab.c"
    break;

  case 29: /* unary_operator: MINUS  */
#line 158 "src/mylang.y"
                        { (yyval.nice) = "-"; }
#line 1759 "src/y.tab.c"
    break;

  case 30: /* unary_operator: TILDE  */
#line 159 "src/mylang.y"
                        { (yyval.nice) = "~"; }
#line 1765 "src/y.tab.c"
    break;

  case 31: /* unary_operator: EXCLAMATION  */
#line 160 "src/mylang.y"
                        { (yyval.nice) = "!"; }
#line 1771 "src/y.tab.c"
    break;

  case 80: /* declaration: declaration_specifiers SEMICOLON  */
#line 269 "src/mylang.y"
                                           {
		  insertSymbol((yyvsp[-1].nice), "variable", currentType);
	  }
#line 1779 "src/y.tab.c"
    break;

  case 81: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 272 "src/mylang.y"
                                                                {
		  /* Use the variable name from init_declarator */
		  insertSymbol((yyvsp[-1].nice), "variable", currentType);
	  }
#line 1788 "src/y.tab.c"
    break;

  case 97: /* type_specifier: VOID  */
#line 308 "src/mylang.y"
                   { (yyval.nice) = strdup("VOID"); currentType = (yyval.nice); }
#line 1794 "src/y.tab.c"
    break;

  case 98: /* type_specifier: CHAR  */
#line 309 "src/mylang.y"
                   { (yyval.nice) = strdup("CHAR"); currentType = (yyval.nice); }
#line 1800 "src/y.tab.c"
    break;

  case 99: /* type_specifier: SHORT  */
#line 310 "src/mylang.y"
                   { (yyval.nice) = strdup("SHORT"); currentType = (yyval.nice); }
#line 1806 "src/y.tab.c"
    break;

  case 100: /* type_specifier: INT  */
#line 311 "src/mylang.y"
                   { (yyval.nice) = strdup("INT"); currentType = (yyval.nice); }
#line 1812 "src/y.tab.c"
    break;

  case 101: /* type_specifier: LONG  */
#line 312 "src/mylang.y"
                   { (yyval.nice) = strdup("LONG"); currentType = (yyval.nice); }
#line 1818 "src/y.tab.c"
    break;

  case 102: /* type_specifier: FLOAT  */
#line 313 "src/mylang.y"
                   { (yyval.nice) = strdup("FLOAT"); currentType = (yyval.nice); }
#line 1824 "src/y.tab.c"
    break;

  case 103: /* type_specifier: DOUBLE  */
#line 314 "src/mylang.y"
                   { (yyval.nice) = strdup("DOUBLE"); currentType = (yyval.nice); }
#line 1830 "src/y.tab.c"
    break;

  case 104: /* type_specifier: SIGNED  */
#line 315 "src/mylang.y"
                   { (yyval.nice) = strdup("SIGNED"); currentType = (yyval.nice); }
#line 1836 "src/y.tab.c"
    break;

  case 105: /* type_specifier: UNSIGNED  */
#line 316 "src/mylang.y"
                   { (yyval.nice) = strdup("UNSIGNED"); currentType = (yyval.nice); }
#line 1842 "src/y.tab.c"
    break;

  case 106: /* type_specifier: struct_or_union_specifier  */
#line 317 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 1848 "src/y.tab.c"
    break;

  case 107: /* type_specifier: enum_specifier  */
#line 318 "src/mylang.y"
                         { (yyval.nice) = (yyvsp[0].nice); }
#line 1854 "src/y.tab.c"
    break;

  case 108: /* type_specifier: TYPE_NAME  */
#line 319 "src/mylang.y"
                    { (yyval.nice) = strdup("TYPE_NAME"); currentType = (yyval.nice); }
#line 1860 "src/y.tab.c"
    break;

  case 133: /* type_qualifier: CONST  */
#line 380 "src/mylang.y"
                   { (yyval.nice) = strdup("CONST"); }
#line 1866 "src/y.tab.c"
    break;

  case 134: /* type_qualifier: VOLATILE  */
#line 381 "src/mylang.y"
                   { (yyval.nice) = strdup("VOLATILE"); }
#line 1872 "src/y.tab.c"
    break;

  case 135: /* declarator: pointer direct_declarator  */
#line 386 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 1878 "src/y.tab.c"
    break;

  case 136: /* declarator: direct_declarator  */
#line 387 "src/mylang.y"
                            { (yyval.nice) = (yyvsp[0].nice); }
#line 1884 "src/y.tab.c"
    break;

  case 137: /* direct_declarator: IDENTIFIER  */
#line 391 "src/mylang.y"
                     { (yyval.nice) = (yyvsp[0].nice); }
#line 1890 "src/y.tab.c"
    break;

  case 138: /* direct_declarator: LEFT_PAREN declarator RIGHT_PAREN  */
#line 392 "src/mylang.y"
                                            { (yyval.nice) = (yyvsp[-1].nice); }
#line 1896 "src/y.tab.c"
    break;

  case 139: /* direct_declarator: direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET  */
#line 393 "src/mylang.y"
                                                                           { (yyval.nice) = (yyvsp[-3].nice); }
#line 1902 "src/y.tab.c"
    break;

  case 140: /* direct_declarator: direct_declarator LEFT_BRACKET RIGHT_BRACKET  */
#line 394 "src/mylang.y"
                                                       { (yyval.nice) = (yyvsp[-2].nice); }
#line 1908 "src/y.tab.c"
    break;

  case 141: /* direct_declarator: direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN  */
#line 395 "src/mylang.y"
                                                                       { (yyval.nice) = (yyvsp[-3].nice); }
#line 1914 "src/y.tab.c"
    break;

  case 142: /* direct_declarator: direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN  */
#line 396 "src/mylang.y"
                                                                   { (yyval.nice) = (yyvsp[-3].nice); }
#line 1920 "src/y.tab.c"
    break;

  case 143: /* direct_declarator: direct_declarator LEFT_PAREN RIGHT_PAREN  */
#line 397 "src/mylang.y"
                                                   { (yyval.nice) = (yyvsp[-2].nice); }
#line 1926 "src/y.tab.c"
    break;

  case 144: /* pointer: ASTERISK  */
#line 401 "src/mylang.y"
                   { (yyval.nice) = NULL; }
#line 1932 "src/y.tab.c"
    break;

  case 145: /* pointer: ASTERISK type_qualifier_list  */
#line 402 "src/mylang.y"
                                       { (yyval.nice) = NULL; }
#line 1938 "src/y.tab.c"
    break;

  case 146: /* pointer: ASTERISK pointer  */
#line 403 "src/mylang.y"
                           { (yyval.nice) = NULL; }
#line 1944 "src/y.tab.c"
    break;

  case 147: /* pointer: ASTERISK type_qualifier_list pointer  */
#line 404 "src/mylang.y"
                                               { (yyval.nice) = NULL; }
#line 1950 "src/y.tab.c"
    break;

  case 213: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 541 "src/mylang.y"
                                                                                {
		  insertSymbol((yyvsp[-2].nice), "function", (yyvsp[-3].nice)); /* Insert function with its return type */
	  }
#line 1958 "src/y.tab.c"
    break;

  case 214: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 544 "src/mylang.y"
                                                               {
		  insertSymbol((yyvsp[-1].nice), "function", (yyvsp[-2].nice));
	  }
#line 1966 "src/y.tab.c"
    break;

  case 215: /* function_definition: declarator declaration_list compound_statement  */
#line 547 "src/mylang.y"
                                                         {
		  insertSymbol((yyvsp[-2].nice), "function", "auto"); /* Default to auto when return type isn't specified */
	  }
#line 1974 "src/y.tab.c"
    break;

  case 216: /* function_definition: declarator compound_statement  */
#line 550 "src/mylang.y"
                                        {
		  insertSymbol((yyvsp[-1].nice), "function", "auto");
	  }
#line 1982 "src/y.tab.c"
    break;


#line 1986 "src/y.tab.c"

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

#line 555 "src/mylang.y"


void yyerror(const char *s) {
    fprintf(stderr, "\033[1;31mSyntax Error\033[0m at line %d: %s\n", yylineno, s);
    grammarErrorCount++;
}
