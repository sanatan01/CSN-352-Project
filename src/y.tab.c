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
  YYSYMBOL_array_declaration = 113,        /* array_declaration  */
  YYSYMBOL_declaration_specifiers = 114,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 115,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 116,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 117,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 118,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 119, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 120,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 121,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 122,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 123, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 124,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 125,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 126,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 127,          /* enumerator_list  */
  YYSYMBOL_enumerator = 128,               /* enumerator  */
  YYSYMBOL_type_qualifier = 129,           /* type_qualifier  */
  YYSYMBOL_declarator = 130,               /* declarator  */
  YYSYMBOL_direct_declarator = 131,        /* direct_declarator  */
  YYSYMBOL_pointer = 132,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 133,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 134,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 135,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 136,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 137,          /* identifier_list  */
  YYSYMBOL_type_name = 138,                /* type_name  */
  YYSYMBOL_abstract_declarator = 139,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 140, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 141,              /* initializer  */
  YYSYMBOL_initializer_list = 142,         /* initializer_list  */
  YYSYMBOL_statement = 143,                /* statement  */
  YYSYMBOL_labeled_statement = 144,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 145,       /* compound_statement  */
  YYSYMBOL_declaration_list = 146,         /* declaration_list  */
  YYSYMBOL_statement_list = 147,           /* statement_list  */
  YYSYMBOL_expression_statement = 148,     /* expression_statement  */
  YYSYMBOL_selection_statement = 149,      /* selection_statement  */
  YYSYMBOL_declaration_statement = 150,    /* declaration_statement  */
  YYSYMBOL_iteration_statement = 151,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 152,           /* jump_statement  */
  YYSYMBOL_translation_unit = 153,         /* translation_unit  */
  YYSYMBOL_external_declaration = 154,     /* external_declaration  */
  YYSYMBOL_function_definition = 155       /* function_definition  */
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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  229
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  388

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
       0,   109,   109,   110,   111,   112,   113,   121,   122,   123,
     124,   125,   126,   127,   128,   133,   134,   139,   140,   141,
     142,   143,   144,   148,   149,   150,   151,   152,   153,   158,
     159,   164,   165,   166,   167,   171,   172,   173,   177,   178,
     179,   184,   185,   186,   187,   188,   192,   193,   194,   199,
     200,   204,   205,   209,   210,   215,   216,   220,   221,   226,
     227,   232,   233,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   252,   253,   254,   258,   265,   270,
     273,   278,   286,   290,   294,   301,   302,   307,   315,   316,
     323,   324,   325,   326,   330,   331,   335,   336,   337,   341,
     349,   350,   351,   352,   353,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   379,   380,
     381,   385,   386,   390,   391,   395,   399,   400,   401,   402,
     406,   407,   411,   412,   413,   418,   419,   420,   424,   425,
     429,   430,   435,   436,   441,   442,   446,   447,   448,   449,
     450,   451,   452,   456,   457,   458,   459,   463,   464,   469,
     470,   474,   475,   479,   480,   481,   485,   486,   490,   491,
     495,   496,   497,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   514,   515,   516,   520,   521,   526,   527,   528,
     529,   530,   531,   535,   536,   537,   541,   542,   543,   544,
     548,   549,   553,   554,   558,   559,   564,   565,   566,   570,
     571,   575,   576,   577,   578,   579,   583,   584,   585,   586,
     587,   592,   593,   597,   598,   602,   605,   608,   611,   614
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
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "ERROR", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration", "array_declaration",
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

#define YYPACT_NINF (-179)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     809,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,    40,     6,   -25,     8,  -179,    21,  1478,  1369,  -179,
      71,  -179,  1478,   747,   141,    11,   314,  -179,  -179,   -38,
      47,    24,  -179,  -179,   -25,  -179,   386,    35,    89,  -179,
      60,  -179,    48,  -179,    -2,   106,  1240,  -179,  -179,  -179,
      93,  1180,  -179,    64,  -179,    21,  -179,   747,  1302,   587,
     141,  -179,  -179,    47,    77,   194,  -179,  -179,  -179,  -179,
      73,  -179,  -179,  1076,  1091,  1091,  -179,  -179,   575,  -179,
    -179,  -179,  -179,  -179,  -179,  1124,    86,    91,   133,   177,
     746,   197,   254,   213,   251,   872,    10,  -179,   176,   636,
    1124,  -179,   114,   212,   269,   180,   274,   221,   239,   231,
     292,    20,  -179,   261,   159,  -179,  -179,  -179,   449,   620,
    -179,  -179,  -179,  -179,   891,  -179,    28,   954,  1124,    49,
    -179,  -179,  -179,   747,  1180,  1401,  1272,  -179,    69,  1180,
    -179,  -179,  -179,  -179,    46,   260,   266,  -179,    26,  -179,
    -179,  -179,  -179,  -179,   262,   232,  1124,  -179,    47,   746,
     575,  -179,  1139,  -179,  -179,   270,    76,    87,   265,   271,
     746,  1139,  1139,  1139,   241,   512,   276,  -179,  -179,  -179,
     185,  1124,   323,  -179,  -179,   965,  1139,   324,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  1124,
    -179,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,
    1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1139,
     240,  -179,  1124,  -179,   683,  -179,  -179,   891,  -179,  -179,
    -179,  -179,  -179,   273,  -179,   984,  -179,  1433,  -179,  -179,
    -179,  1124,   198,  -179,   275,  -179,  1202,   997,  -179,    39,
    -179,   196,  -179,  1457,   329,  -179,  -179,  -179,  -179,  -179,
    -179,   277,  -179,  1331,   203,  -179,  1124,   746,  -179,    98,
     134,   153,   279,  -179,  -179,   512,  1028,  -179,  -179,  -179,
    -179,  -179,   167,  -179,    -4,  -179,  -179,  -179,  -179,  -179,
     114,   114,   212,   212,   269,   269,   269,   269,   180,   180,
     274,   221,   239,   231,   292,   238,  -179,  -179,  -179,  -179,
     242,  -179,  -179,   280,  -179,  -179,  -179,    69,  1124,  -179,
     281,   283,  -179,   282,   196,   684,  1060,  -179,  -179,  -179,
    -179,  -179,  -179,   746,   746,   746,  1139,   285,  1139,  1139,
    1124,  -179,  -179,  1124,  -179,   854,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,   306,  -179,   305,   284,  -179,  -179,   168,
     746,   173,   188,  -179,  -179,  -179,  -179,  -179,  -179,   746,
     316,  -179,   746,   746,  -179,  -179,  -179,  -179
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   146,   116,   100,   101,   102,   103,   104,   106,   107,
     108,   109,   112,   113,   110,   111,   142,   143,   105,   121,
     122,     0,     0,   153,     0,   224,     0,    88,    90,   114,
       0,   115,    92,     0,   145,     0,     0,   221,   223,   137,
       0,     0,   157,   155,   154,    82,     0,     0,     0,    94,
      96,   229,   146,    79,     0,     0,    96,    89,    91,   117,
     120,     0,    93,     0,   200,     0,   228,     0,     0,     0,
     144,     1,   222,     0,   140,     0,   138,   147,   158,   156,
       2,     3,     4,     0,     0,     0,   204,   196,     0,    23,
      28,    27,    26,    25,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,    17,    29,
       0,    31,    35,    38,    41,    46,    49,    51,    53,    55,
      57,    59,    61,    74,     0,   202,   187,   188,     0,     0,
     189,   190,   191,   192,     0,    83,     0,     0,     0,     0,
      84,    80,   226,     0,     0,   127,     0,   123,     0,   129,
     201,   227,   166,   152,   165,     0,   159,   161,     0,     2,
     149,     6,    29,    78,     0,     0,     0,   135,     0,     0,
       0,    21,     0,    18,    19,     6,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,   218,   219,
       0,     0,     0,    13,    14,     0,     0,     0,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    63,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,   198,     0,   197,   203,     0,   182,    98,
      95,     6,    97,     0,    81,     0,   225,     0,   126,   119,
     124,     0,     0,   130,   132,   128,     0,     0,   163,   170,
     164,   171,   150,     0,     0,   151,   148,   136,   141,   139,
     193,     0,     5,     0,   170,   169,     0,     0,   195,     0,
       0,     0,     0,   204,   210,     0,     0,   216,   220,    76,
      12,     9,     0,    15,     0,    11,    62,    32,    33,    34,
      37,    36,    39,    40,    44,    45,    42,    43,    47,    48,
      50,    52,    54,    56,    58,     0,    77,    75,   199,   185,
       0,    85,    87,     0,   118,   133,   125,     0,     0,   178,
       0,     0,   174,     0,   172,     0,     0,   160,   162,   167,
      22,    30,   194,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     8,     0,   183,     0,    86,   131,   134,   179,
     173,   175,   180,     0,   176,     0,   206,   208,   211,     0,
       0,     0,     0,    16,    60,   184,   186,   181,   177,     0,
       0,   213,     0,     0,   207,   212,   215,   214
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,   -50,  -179,   -64,    81,    90,    51,
      75,   142,   143,   144,   140,   145,  -179,   -54,  -114,  -179,
      32,   -51,     2,  -179,     0,   -10,   235,  -179,    72,  -179,
    -179,   228,  -138,    94,  -179,    50,  -179,   301,   207,   166,
       3,   -29,   -18,  -179,   -67,  -179,   113,  -179,   214,   -98,
    -174,  -133,  -179,   -78,  -179,    -3,    79,   255,  -178,  -179,
      97,  -179,  -179,  -179,   349,  -179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   107,   108,   292,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   209,
     124,   164,    64,   139,    65,    48,    49,    27,    28,    29,
      30,   146,   147,   148,   252,   253,    31,    75,    76,    32,
      50,    34,    35,    44,   330,   156,   157,   158,   178,   331,
     261,   239,   320,   125,   126,   127,    67,   129,   130,   131,
     286,   132,   133,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   155,    25,    33,   242,    43,    70,   285,   250,     1,
      59,     1,    73,     1,     1,   163,    55,    16,    17,   162,
     238,    51,   184,   238,    52,    41,    79,    57,    58,    56,
      66,     1,    62,   171,   173,   174,    26,   228,    25,    33,
      23,   163,     1,    39,   179,   162,   210,   140,   232,     1,
      74,   236,   134,   142,   352,    55,   260,    45,    46,    45,
     162,    22,   191,    22,   151,    22,    22,     1,   154,   150,
      53,    23,     1,    23,    60,    23,    22,   289,   264,   275,
      77,   293,   265,    22,   163,   334,    23,   243,   162,   134,
      40,   270,   229,    23,   256,   296,   257,    47,   244,    47,
     334,   256,   278,   257,   319,   138,   245,   347,   349,   250,
      54,    23,   163,    45,   137,   268,   162,    47,   317,    22,
     176,    61,   251,   238,    22,   128,   169,    59,   232,    23,
     150,   166,   272,   145,    23,   143,   259,   190,   135,   180,
     246,   136,   273,   144,   257,   150,   181,   297,   298,   299,
     232,   254,    23,    47,   343,   141,   236,   258,   136,   274,
     145,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   211,
     212,   213,   177,   192,   193,   194,   232,   284,   182,    42,
     344,   163,   218,   219,   323,   162,    68,   163,    69,   342,
     325,   162,   176,   163,   176,   232,   333,   162,   231,   345,
      78,   232,   341,   279,   280,   281,   145,   145,   145,   350,
     232,   145,   376,   351,   380,   232,   162,   149,   294,   382,
      70,   195,   183,   196,   288,   197,   373,   232,   259,   248,
     232,   238,   145,   255,   383,   167,   168,   326,   220,   221,
     327,   335,   185,   336,   149,   274,   154,   186,   273,    41,
     257,   315,   187,   154,   177,   366,   367,   368,   363,   304,
     305,   306,   307,   154,   163,   214,   215,   358,   162,   216,
     217,   224,   163,   267,   168,   365,   162,   284,   222,   223,
     232,   353,   381,   354,   355,   300,   301,   308,   309,   374,
     188,   384,   226,   162,   386,   387,   302,   303,   227,   225,
     149,   149,   149,   230,    71,   149,   262,     1,   263,   145,
     266,   276,   191,   282,   277,   287,   290,   295,   328,   316,
     254,   321,   339,   340,   346,   154,   149,   359,   356,   360,
     361,   370,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   377,   378,   379,   385,   310,   313,   311,    22,
     312,   240,   247,   314,   165,   269,   338,   357,   369,    23,
     371,   372,   348,   234,   271,    72,     0,     0,     0,    80,
      81,    82,    83,     0,    84,    85,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,    86,    46,    87,     0,     0,
       0,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,    80,    81,    82,    83,     0,    84,    85,     0,
       0,     0,     0,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    86,    46,
     233,     0,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,   159,    81,    82,    83,     0,
      84,    85,     0,     0,     0,     0,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,   283,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,   159,    81,
      82,    83,     0,    84,    85,     0,     0,     0,     0,     0,
     159,    81,    82,    83,     0,    84,    85,     0,     0,     0,
       0,   106,     0,     2,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    80,    81,    82,    83,     0,    84,    85,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
      94,     0,    88,     0,     0,   160,     0,    89,    90,    91,
      92,    93,    94,     0,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   175,     0,     0,     0,     0,    86,
      46,   235,     0,     0,     0,    88,   161,     0,     0,     0,
      89,    90,    91,    92,    93,    94,    80,    81,    82,    83,
     208,    84,    85,     0,     0,     0,     0,    95,    96,    97,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   175,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    86,    46,   318,     0,     0,     0,    88,     0,
     362,     0,     0,    89,    90,    91,    92,    93,    94,    80,
      81,    82,    83,     0,    84,    85,     0,     0,     0,     0,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   175,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    86,    46,    46,     0,     0,
       0,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   175,    63,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   159,    81,    82,
      83,     0,    84,    85,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,   159,    81,    82,    83,     0,
      84,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,    81,    82,    83,    24,    84,
      85,     0,     0,     0,   237,   375,     0,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
       0,   189,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,     0,     0,
       0,   237,     0,   161,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,   159,    81,    82,
      83,   175,    84,    85,     0,     0,     0,     0,   159,    81,
      82,    83,     0,    84,    85,     0,     0,     0,     0,     0,
     161,     0,     0,     0,     0,     0,     0,   159,    81,    82,
      83,     0,    84,    85,     0,     0,     0,     0,     0,     0,
     159,    81,    82,    83,   237,    84,    85,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
      88,   291,     0,     0,     0,    89,    90,    91,    92,    93,
      94,   159,    81,    82,    83,     0,    84,    85,     0,    88,
       0,     0,   322,   241,    89,    90,    91,    92,    93,    94,
       0,     0,    88,     0,   161,   332,     0,    89,    90,    91,
      92,    93,    94,   159,    81,    82,    83,     0,    84,    85,
       0,     0,     0,   161,     0,     0,     0,    86,     0,   159,
      81,    82,    83,    88,    84,    85,   161,     0,    89,    90,
      91,    92,    93,    94,   159,    81,    82,    83,     0,    84,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,   175,   364,     0,
      89,    90,    91,    92,    93,    94,     0,   159,    81,    82,
      83,   170,    84,    85,     0,     0,    89,    90,    91,    92,
      93,    94,   159,    81,    82,    83,   172,    84,    85,   161,
       0,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,   161,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
     161,     0,     0,     0,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,     1,     0,     0,     2,     0,
       0,     0,     0,   161,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   175,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,     0,   256,   329,   257,
       0,     0,     0,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,     0,
      46,     0,     0,     0,   137,     0,     0,     0,     0,     0,
       2,     0,     0,     0,     0,   152,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,   249,     0,     0,     0,     0,     0,    63,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,   273,   329,   257,     0,
       0,     0,     0,     0,     0,     0,    23,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,     0,    23,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     0,    23,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,   324,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   337,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
       0,    68,     0,     0,   137,    23,    35,   185,   146,     3,
      28,     3,    50,     3,     3,    69,    26,    42,    43,    69,
     134,    24,   100,   137,     3,    22,    44,    27,    28,    26,
      33,     3,    32,    83,    84,    85,    36,    17,    36,    36,
      65,    95,     3,     3,    95,    95,   110,    49,    52,     3,
       3,   129,    54,    56,    58,    65,   154,    49,    50,    49,
     110,    55,    52,    55,    67,    55,    55,     3,    68,    67,
      49,    65,     3,    65,     3,    65,    55,   191,    52,   177,
      56,   195,    56,    55,   138,   259,    65,   138,   138,    54,
      50,   169,    72,    65,    55,   209,    57,    89,    49,    89,
     274,    55,   180,    57,   237,    57,    57,   285,   286,   247,
      89,    65,   166,    49,    54,   166,   166,    89,   232,    55,
      88,    50,    53,   237,    55,    46,    53,   145,    52,    65,
     128,    54,    56,    61,    65,    56,   154,   105,    49,    53,
     143,    52,    55,    50,    57,   143,    55,   211,   212,   213,
      52,   148,    65,    89,    56,    49,   234,   154,    52,   177,
      88,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,    65,
      66,    67,    88,     7,     8,     9,    52,   185,    55,    23,
      56,   245,    12,    13,   245,   245,    55,   251,    57,   277,
     251,   251,   170,   257,   172,    52,   257,   257,    49,    56,
      44,    52,   276,   181,   182,   183,   144,   145,   146,    52,
      52,   149,   355,    56,    56,    52,   276,    61,   196,    56,
     259,    55,    55,    57,    49,    59,   350,    52,   256,   145,
      52,   355,   170,   149,    56,    51,    52,    49,    68,    69,
      52,    55,    55,    57,    88,   273,   256,     3,    55,   256,
      57,   229,    49,   263,   170,   343,   344,   345,   335,   218,
     219,   220,   221,   273,   328,    63,    64,   328,   328,    10,
      11,    60,   336,    51,    52,   336,   336,   285,    14,    15,
      52,    53,   370,    51,    52,   214,   215,   222,   223,   353,
      49,   379,    71,   353,   382,   383,   216,   217,    16,    70,
     144,   145,   146,    52,     0,   149,    56,     3,    52,   247,
      58,    56,    52,    82,    53,    49,     3,     3,    53,    89,
     327,    58,     3,    56,    55,   335,   170,    56,    58,    56,
      58,    56,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    56,    58,    80,    49,   224,   227,   225,    55,
     226,   136,   144,   228,    73,   168,   263,   327,   346,    65,
     348,   349,   285,   128,   170,    36,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    89,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,    -1,     8,     9,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    -1,    55,    -1,    -1,    58,    -1,    60,    61,    62,
      63,    64,    65,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    89,    -1,    -1,    -1,    -1,    49,
      50,    51,    -1,    -1,    -1,    55,    89,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      54,     8,     9,    -1,    -1,    -1,    -1,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    49,    50,    51,    -1,    -1,    -1,    55,    -1,
      56,    -1,    -1,    60,    61,    62,    63,    64,    65,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    49,    50,    50,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    89,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     3,     4,     5,
       6,    -1,     8,     9,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    89,     8,
       9,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    50,    -1,    89,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,     3,     4,     5,
       6,    89,     8,     9,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    50,     8,     9,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,     3,     4,     5,     6,    -1,     8,     9,    -1,    55,
      -1,    -1,    58,    89,    60,    61,    62,    63,    64,    65,
      -1,    -1,    55,    -1,    89,    58,    -1,    60,    61,    62,
      63,    64,    65,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    49,    -1,     3,
       4,     5,     6,    55,     8,     9,    89,    -1,    60,    61,
      62,    63,    64,    65,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    89,    58,    -1,
      60,    61,    62,    63,    64,    65,    -1,     3,     4,     5,
       6,    55,     8,     9,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    55,     8,     9,    89,
      -1,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      89,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    89,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    89,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,     3,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    89,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    65,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    65,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    55,    65,    89,   112,   114,   117,   118,   119,
     120,   126,   129,   130,   131,   132,   153,   154,   155,     3,
      50,   130,   129,   132,   133,    49,    50,    89,   115,   116,
     130,   145,     3,    49,    89,   115,   130,   114,   114,   132,
       3,    50,   114,    89,   112,   114,   145,   146,    55,    57,
     131,     0,   154,    50,     3,   127,   128,    56,   129,   132,
       3,     4,     5,     6,     8,     9,    49,    51,    55,    60,
      61,    62,    63,    64,    65,    77,    78,    79,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    91,    92,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   110,   143,   144,   145,   146,   147,
     148,   149,   151,   152,    54,    49,    52,    54,    57,   113,
      49,    49,   145,   146,    50,   118,   121,   122,   123,   129,
     112,   145,     3,    56,   114,   134,   135,   136,   137,     3,
      58,    89,    94,   107,   111,   127,    54,    51,    52,    53,
      55,    94,    55,    94,    94,    89,   110,   123,   138,   111,
      53,    55,    55,    55,   143,    55,     3,    49,    49,    49,
     110,    52,     7,     8,     9,    55,    57,    59,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    54,   109,
      96,    65,    66,    67,    63,    64,    10,    11,    12,    13,
      68,    69,    14,    15,    60,    70,    71,    16,    17,    72,
      52,    49,    52,    51,   147,    51,   143,    50,   108,   141,
     116,    89,   141,   111,    49,    57,   145,   121,   123,    51,
     122,    53,   124,   125,   130,   123,    55,    57,   130,   132,
     139,   140,    56,    52,    52,    56,    58,    51,   111,   128,
     143,   138,    56,    55,   132,   139,    56,    53,   143,   110,
     110,   110,    82,    49,   112,   148,   150,    49,    49,   108,
       3,    56,    93,   108,   110,     3,   108,    96,    96,    96,
      97,    97,    98,    98,    99,    99,    99,    99,   100,   100,
     101,   102,   103,   104,   105,   110,    89,   108,    51,   141,
     142,    58,    58,   111,    51,   111,    49,    52,    53,    56,
     134,   139,    58,   111,   140,    55,    57,    48,   136,     3,
      56,    96,   143,    56,    56,    56,    55,   148,   150,   148,
      52,    56,    58,    53,    51,    52,    58,   125,   111,    56,
      56,    58,    56,   134,    58,   111,   143,   143,   143,   110,
      56,   110,   110,   108,   107,    51,   141,    56,    58,    80,
      56,   143,    56,    56,   143,    49,   143,   143
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
     112,   112,   112,   112,   112,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   120,   120,   121,   121,   122,   123,   123,   123,   123,
     124,   124,   125,   125,   125,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   132,   132,   132,   132,   133,   133,   134,
     134,   135,   135,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   141,   141,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   145,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   150,
     150,   151,   151,   151,   151,   151,   152,   152,   152,   152,
     152,   153,   153,   154,   154,   155,   155,   155,   155,   155
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
       3,     4,     2,     3,     3,     3,     4,     3,     1,     2,
       1,     2,     1,     2,     1,     3,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     5,     4,
       2,     1,     1,     1,     2,     3,     2,     1,     2,     1,
       1,     3,     1,     2,     3,     4,     5,     2,     1,     3,
       1,     3,     1,     1,     2,     1,     1,     3,     4,     3,
       4,     4,     3,     1,     2,     2,     3,     1,     2,     1,
       3,     1,     3,     2,     2,     1,     1,     3,     1,     2,
       1,     1,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     2,     3,     3,     4,
       1,     2,     1,     2,     1,     2,     5,     7,     5,     1,
       1,     5,     7,     6,     7,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     4,     3,     3,     2,     2
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
  case 6: /* primary_expression: ERROR  */
#line 113 "src/mylang.y"
                {
		yyerror((yyvsp[0].nice));
		yyerrok;
	}
#line 1753 "src/y.tab.c"
    break;

  case 23: /* unary_operator: AMPERSAND  */
#line 148 "src/mylang.y"
                        { (yyval.nice) = "&"; }
#line 1759 "src/y.tab.c"
    break;

  case 24: /* unary_operator: ASTERISK  */
#line 149 "src/mylang.y"
                        { (yyval.nice) = "*"; }
#line 1765 "src/y.tab.c"
    break;

  case 25: /* unary_operator: PLUS  */
#line 150 "src/mylang.y"
                        { (yyval.nice) = "+"; }
#line 1771 "src/y.tab.c"
    break;

  case 26: /* unary_operator: MINUS  */
#line 151 "src/mylang.y"
                        { (yyval.nice) = "-"; }
#line 1777 "src/y.tab.c"
    break;

  case 27: /* unary_operator: TILDE  */
#line 152 "src/mylang.y"
                        { (yyval.nice) = "~"; }
#line 1783 "src/y.tab.c"
    break;

  case 28: /* unary_operator: EXCLAMATION  */
#line 153 "src/mylang.y"
                        { (yyval.nice) = "!"; }
#line 1789 "src/y.tab.c"
    break;

  case 76: /* expression: ERROR COMMA assignment_expression  */
#line 254 "src/mylang.y"
                                            {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1798 "src/y.tab.c"
    break;

  case 77: /* expression: assignment_expression COMMA ERROR  */
#line 258 "src/mylang.y"
                                            {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1807 "src/y.tab.c"
    break;

  case 79: /* declaration: declaration_specifiers SEMICOLON  */
#line 270 "src/mylang.y"
                                           {
		  insertSymbol((yyvsp[-1].nice), "variable", (yyval.nice));
	  }
#line 1815 "src/y.tab.c"
    break;

  case 80: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 273 "src/mylang.y"
                                                                {
		  /* Use the variable name from init_declarator */
		  (yyval.nice) = (yyvsp[-2].nice);
		  insertSymbol((yyvsp[-1].nice), "variable", (yyval.nice));
	  }
#line 1825 "src/y.tab.c"
    break;

  case 81: /* declaration: declaration_specifiers IDENTIFIER array_declaration SEMICOLON  */
#line 278 "src/mylang.y"
                                                                        {
		char *temp = malloc(strlen((yyvsp[-3].nice)) + strlen((yyvsp[-1].nice)) + 3);
		strcpy(temp, (yyvsp[-3].nice));
		strcat(temp, strdup(" "));
		strcat(temp, (yyvsp[-1].nice));
		(yyval.nice) = temp;
		insertSymbol((yyvsp[-2].nice), "variable", (yyval.nice));
	}
#line 1838 "src/y.tab.c"
    break;

  case 82: /* declaration: ERROR SEMICOLON  */
#line 286 "src/mylang.y"
                          {
		yyerror((yyvsp[-1].nice));
		yyerrok;
	}
#line 1847 "src/y.tab.c"
    break;

  case 83: /* declaration: ERROR init_declarator_list SEMICOLON  */
#line 290 "src/mylang.y"
                                               {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1856 "src/y.tab.c"
    break;

  case 84: /* declaration: declaration_specifiers ERROR SEMICOLON  */
#line 294 "src/mylang.y"
                                                 {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1865 "src/y.tab.c"
    break;

  case 85: /* array_declaration: LEFT_BRACKET constant_expression RIGHT_BRACKET  */
#line 301 "src/mylang.y"
                                                         { (yyval.nice) = strdup("ARRAY");}
#line 1871 "src/y.tab.c"
    break;

  case 86: /* array_declaration: array_declaration LEFT_BRACKET constant_expression RIGHT_BRACKET  */
#line 302 "src/mylang.y"
                                                                           {
		char *temp = malloc(strlen("ARRAY") + strlen((yyvsp[-3].nice)) + 2);
		sprintf(temp, "ARRAY %s", (yyvsp[-3].nice));
		(yyval.nice) = temp;
	}
#line 1881 "src/y.tab.c"
    break;

  case 87: /* array_declaration: array_declaration LEFT_BRACKET RIGHT_BRACKET  */
#line 307 "src/mylang.y"
                                                       {
		char *temp = malloc(strlen("ARRAY") + strlen((yyvsp[-2].nice)) + 2);
		sprintf(temp, "ARRAY %s", (yyvsp[-2].nice));
		(yyval.nice) = temp;
	}
#line 1891 "src/y.tab.c"
    break;

  case 89: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 316 "src/mylang.y"
                                                         {
		char * temp = malloc(strlen((yyvsp[-1].nice)) + strlen((yyvsp[0].nice)) + 3);
		strcpy(temp, (yyvsp[-1].nice));
		strcat(temp, strdup(" "));
		strcat(temp, (yyvsp[0].nice));
		(yyval.nice) = temp;
	}
#line 1903 "src/y.tab.c"
    break;

  case 98: /* init_declarator: ERROR ASSIGN initializer  */
#line 337 "src/mylang.y"
                                   {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1912 "src/y.tab.c"
    break;

  case 99: /* init_declarator: declarator ASSIGN ERROR  */
#line 341 "src/mylang.y"
                                  {
		yyerror((yyvsp[-2].nice));
		yyerrok;
	}
#line 1921 "src/y.tab.c"
    break;

  case 105: /* type_specifier: VOID  */
#line 358 "src/mylang.y"
                   { (yyval.nice) = strdup("VOID"); }
#line 1927 "src/y.tab.c"
    break;

  case 106: /* type_specifier: CHAR  */
#line 359 "src/mylang.y"
                   { (yyval.nice) = strdup("CHAR");}
#line 1933 "src/y.tab.c"
    break;

  case 107: /* type_specifier: SHORT  */
#line 360 "src/mylang.y"
                   { (yyval.nice) = strdup("SHORT");}
#line 1939 "src/y.tab.c"
    break;

  case 108: /* type_specifier: INT  */
#line 361 "src/mylang.y"
                   { (yyval.nice) = strdup("INT");}
#line 1945 "src/y.tab.c"
    break;

  case 109: /* type_specifier: LONG  */
#line 362 "src/mylang.y"
                   { (yyval.nice) = strdup("LONG");}
#line 1951 "src/y.tab.c"
    break;

  case 110: /* type_specifier: FLOAT  */
#line 363 "src/mylang.y"
                   { (yyval.nice) = strdup("FLOAT");}
#line 1957 "src/y.tab.c"
    break;

  case 111: /* type_specifier: DOUBLE  */
#line 364 "src/mylang.y"
                   { (yyval.nice) = strdup("DOUBLE");}
#line 1963 "src/y.tab.c"
    break;

  case 112: /* type_specifier: SIGNED  */
#line 365 "src/mylang.y"
                   { (yyval.nice) = strdup("SIGNED");}
#line 1969 "src/y.tab.c"
    break;

  case 113: /* type_specifier: UNSIGNED  */
#line 366 "src/mylang.y"
                   { (yyval.nice) = strdup("UNSIGNED");}
#line 1975 "src/y.tab.c"
    break;

  case 114: /* type_specifier: struct_or_union_specifier  */
#line 367 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 1981 "src/y.tab.c"
    break;

  case 115: /* type_specifier: enum_specifier  */
#line 368 "src/mylang.y"
                         { (yyval.nice) = (yyvsp[0].nice); }
#line 1987 "src/y.tab.c"
    break;

  case 116: /* type_specifier: TYPE_NAME  */
#line 369 "src/mylang.y"
                    { (yyval.nice) = strdup("TYPE_NAME");}
#line 1993 "src/y.tab.c"
    break;

  case 117: /* type_specifier: type_specifier pointer  */
#line 370 "src/mylang.y"
                                 {
		char*temp = malloc(strlen((yyvsp[-1].nice)) + 2 );
		sprintf(temp, "%s*", (yyvsp[-1].nice));
		(yyval.nice) = temp;
	}
#line 2003 "src/y.tab.c"
    break;

  case 118: /* struct_or_union_specifier: struct_or_union IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE  */
#line 379 "src/mylang.y"
                                                                                    { (yyval.nice) = (yyvsp[-3].nice); }
#line 2009 "src/y.tab.c"
    break;

  case 120: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 381 "src/mylang.y"
                                     { (yyval.nice) = (yyvsp[0].nice); }
#line 2015 "src/y.tab.c"
    break;

  case 142: /* type_qualifier: CONST  */
#line 435 "src/mylang.y"
                   { (yyval.nice) = strdup("CONST"); }
#line 2021 "src/y.tab.c"
    break;

  case 143: /* type_qualifier: VOLATILE  */
#line 436 "src/mylang.y"
                   { (yyval.nice) = strdup("VOLATILE"); }
#line 2027 "src/y.tab.c"
    break;

  case 144: /* declarator: pointer direct_declarator  */
#line 441 "src/mylang.y"
                                    { (yyval.nice) = (yyvsp[0].nice); }
#line 2033 "src/y.tab.c"
    break;

  case 145: /* declarator: direct_declarator  */
#line 442 "src/mylang.y"
                            { (yyval.nice) = (yyvsp[0].nice); }
#line 2039 "src/y.tab.c"
    break;

  case 146: /* direct_declarator: IDENTIFIER  */
#line 446 "src/mylang.y"
                     { (yyval.nice) = (yyvsp[0].nice); }
#line 2045 "src/y.tab.c"
    break;

  case 147: /* direct_declarator: LEFT_PAREN declarator RIGHT_PAREN  */
#line 447 "src/mylang.y"
                                            { (yyval.nice) = (yyvsp[-1].nice); }
#line 2051 "src/y.tab.c"
    break;

  case 148: /* direct_declarator: direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET  */
#line 448 "src/mylang.y"
                                                                           { (yyval.nice) = (yyvsp[-3].nice); }
#line 2057 "src/y.tab.c"
    break;

  case 149: /* direct_declarator: direct_declarator LEFT_BRACKET RIGHT_BRACKET  */
#line 449 "src/mylang.y"
                                                       { (yyval.nice) = (yyvsp[-2].nice); }
#line 2063 "src/y.tab.c"
    break;

  case 150: /* direct_declarator: direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN  */
#line 450 "src/mylang.y"
                                                                       { (yyval.nice) = (yyvsp[-3].nice); }
#line 2069 "src/y.tab.c"
    break;

  case 151: /* direct_declarator: direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN  */
#line 451 "src/mylang.y"
                                                                   { (yyval.nice) = (yyvsp[-3].nice); }
#line 2075 "src/y.tab.c"
    break;

  case 152: /* direct_declarator: direct_declarator LEFT_PAREN RIGHT_PAREN  */
#line 452 "src/mylang.y"
                                                   { (yyval.nice) = (yyvsp[-2].nice); }
#line 2081 "src/y.tab.c"
    break;

  case 153: /* pointer: ASTERISK  */
#line 456 "src/mylang.y"
                   { (yyval.nice) = NULL; }
#line 2087 "src/y.tab.c"
    break;

  case 154: /* pointer: ASTERISK type_qualifier_list  */
#line 457 "src/mylang.y"
                                       { (yyval.nice) = NULL; }
#line 2093 "src/y.tab.c"
    break;

  case 155: /* pointer: ASTERISK pointer  */
#line 458 "src/mylang.y"
                           { (yyval.nice) = NULL; }
#line 2099 "src/y.tab.c"
    break;

  case 156: /* pointer: ASTERISK type_qualifier_list pointer  */
#line 459 "src/mylang.y"
                                               { (yyval.nice) = NULL; }
#line 2105 "src/y.tab.c"
    break;

  case 225: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 602 "src/mylang.y"
                                                                                {
		  insertSymbol((yyvsp[-2].nice), "function", (yyvsp[-3].nice)); /* Insert function with its return type */
	  }
#line 2113 "src/y.tab.c"
    break;

  case 226: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 605 "src/mylang.y"
                                                               {
		  insertSymbol((yyvsp[-1].nice), "function", (yyvsp[-2].nice));
	  }
#line 2121 "src/y.tab.c"
    break;

  case 227: /* function_definition: declarator declaration_list compound_statement  */
#line 608 "src/mylang.y"
                                                         {
		  insertSymbol((yyvsp[-2].nice), "function", "auto"); /* Default to auto when return type isn't specified */
	  }
#line 2129 "src/y.tab.c"
    break;

  case 228: /* function_definition: declarator compound_statement  */
#line 611 "src/mylang.y"
                                        {
		  insertSymbol((yyvsp[-1].nice), "function", "auto");
	  }
#line 2137 "src/y.tab.c"
    break;

  case 229: /* function_definition: ERROR compound_statement  */
#line 614 "src/mylang.y"
                                   {
		yyerror((yyvsp[-1].nice));
		yyerrok;
	}
#line 2146 "src/y.tab.c"
    break;


#line 2150 "src/y.tab.c"

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

#line 621 "src/mylang.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
    grammarErrorCount++;
}
