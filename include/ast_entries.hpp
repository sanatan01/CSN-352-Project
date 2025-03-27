#pragma once

#include <deque>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include <types.hpp>
#include <symtab.hpp>
#include <ast.hpp>

typedef int TYPE_QUALIFIER;

// Creates a node in the AST called "IDENTIFIER" followed by name
class Identifier : public Terminal {
  public:
    Identifier( const char *name, unsigned int _line_num = 0, unsigned int _column = 0);
};

class TypeQualifierList : public NonTerminal {
  public:
    std::vector<TYPE_QUALIFIER> type_qualifier_list;

    TypeQualifierList();

    void append_to_list( TYPE_QUALIFIER type );

    ~TypeQualifierList();
};

TypeQualifierList *create_type_qualifier_list( TYPE_QUALIFIER type );
TypeQualifierList *add_to_type_qualifier_list( TypeQualifierList *tql, TYPE_QUALIFIER type );
void is_Valid( TypeQualifierList *ts );
class Pointer : public NonTerminal {
  public:
    TypeQualifierList *type_qualifier_list;
    Pointer *pointer;

    Pointer();
    Pointer( TypeQualifierList *type_qualifier_list, Pointer *pointer );
};

Pointer *create_pointer();
Pointer *create_pointer( TypeQualifierList *type_list, Pointer *pointer );

class DirectDeclarator;

class Declarator : public NonTerminal {
  public:
    Identifier *id;
    Pointer *pointer;
    DirectDeclarator *direct_declarator;
    Expression *init_expr;
    Terminal *eq;
    int get_pointer_level();
    Declarator();
    Declarator( Pointer *p, DirectDeclarator *dd );
    //	void dotify();
};

Declarator *add_initializer_to_declarator( Declarator *declarator, Terminal *eq, Expression *init_expr );
Declarator *create_declarator( Pointer *pointer, DirectDeclarator *direct_declarator );

typedef enum direct_declartor_enum {
    STANDARD,
    DECLARATOR,
    ARRAY,
    FUNCTION,
    NUM_DIRECT_DECLARATORS

} DIRECT_DECLARATOR_TYPE;

class DirectDeclarator : public NonTerminal {

  public:
    DIRECT_DECLARATOR_TYPE type;

    Identifier *id;
    std::vector<unsigned int> array_dims;
    ParameterTypeList *params;
    DirectDeclarator();
};

DirectDeclarator *create_dir_declarator_id( DIRECT_DECLARATOR_TYPE type, Identifier *id );
DirectDeclarator *create_dir_declarator_dec( DIRECT_DECLARATOR_TYPE type, Declarator *declarator );
DirectDeclarator *append_dir_declarator_arr( DIRECT_DECLARATOR_TYPE type, DirectDeclarator *direct_declarator, Constant *const_expr );
DirectDeclarator *append_dir_declarator_fun( DIRECT_DECLARATOR_TYPE type, DirectDeclarator *direct_declarator, ParameterTypeList *params );

class DeclaratorList : public NonTerminal {
  public:
    std::vector<Declarator *> declarator_list;
    DeclaratorList();
};

DeclaratorList *create_init_declarator_list( Declarator *init_declarator );
DeclaratorList *add_to_init_declarator_list( DeclaratorList *init_declarator_list, Declarator *init_declarator );

typedef int STORAGE_CLASS;
class TypeSpecifier;
int get_index (GlobalType t );

class DeclarationSpecifiers : public NonTerminal {
  public:
    std::vector<STORAGE_CLASS> storage_class;
    std::vector<TypeSpecifier *> type_specifier;
    std::vector<TYPE_QUALIFIER> type_qualifier;
    bool is_const;
    GlobalType *type;

    void create_type(); // Type Checking

    DeclarationSpecifiers();
};

DeclarationSpecifiers *new_storage_class( STORAGE_CLASS sc );
DeclarationSpecifiers *new_type_specifier( TypeSpecifier *ts );
DeclarationSpecifiers *new_type_qualifier( TYPE_QUALIFIER tq );

DeclarationSpecifiers *add_storage_class( DeclarationSpecifiers *ds, STORAGE_CLASS sc );
DeclarationSpecifiers *add_type_specifier( DeclarationSpecifiers *ds, TypeSpecifier *ts );
DeclarationSpecifiers *add_type_qualifier( DeclarationSpecifiers *ds, TYPE_QUALIFIER tq );

class Declaration : public NonTerminal {
  public:
    DeclarationSpecifiers *declaration_specifiers;
    DeclaratorList *init_declarator_list;
    int type;
    Declaration( DeclarationSpecifiers *declaration_specifiers_, DeclaratorList *init_declarator_list_ );
    void add_to_symbol_table( LocalSymbolTable &sym_tab );
    void add_to_symbol_table( GlobalSymbolTable &sym_tab );
    void dotify();
};

Declaration *new_declaration( DeclarationSpecifiers *declaraion_specifiers, DeclaratorList *init_declarator_list );

class DeclarationList : public NonTerminal {
  public:
    std::vector<Declaration *> declarations;
    DeclarationList();

    void create_symbol_table_level();
};

DeclarationList *create_declaration_list( Declaration *declaraiton );
DeclarationList *add_to_declaration_list( DeclarationList *declaraiton_list, Declaration *Declaration );

class FunctionDefinition : public NonTerminal {
  public:
    DeclarationSpecifiers *declaration_specifiers;
    Declarator *declarator;
    Node *compound_statement;
    int error;

    FunctionDefinition( DeclarationSpecifiers *declaration_specifiers_, Declarator *declarator_, Node *compound_statement_ );
};

FunctionDefinition *create_function_defintion( DeclarationSpecifiers *declaration_specifiers, Declarator *declarator, Node *compound_statement );
FunctionDefinition *add_stmt_to_function_definition( FunctionDefinition *fd, Node *compound_stmt );

int isValid(); // Type Checking         ;

class AbstractDeclarator;

typedef enum {
    ABSTRACT,
    SQUARE,
    ROUND
    // TODO: Fill this

} DIRECT_ABSTRACT_DECLARATOR_TYPE;

class DirectAbstractDeclarator : public NonTerminal {
  public:
    //    DIRECT_ABSTRACT_DECLARATOR_TYPE type;
    //    AbstractDeclarator *abstract_declarator;
    std::vector<unsigned int> array_dims;
    //    DirectAbstractDeclarator *direct_abstract_declarator;
    //    ParameterTypeList *parameter_type_list;
    DirectAbstractDeclarator();
};

DirectAbstractDeclarator *create_direct_abstract_declarator( Constant *_const );
DirectAbstractDeclarator *
append_direct_abstract_declarator( DirectAbstractDeclarator *dabs, Constant *_const );

class AbstractDeclarator : public NonTerminal {
  public:
    Pointer *pointer;
    DirectAbstractDeclarator *direct_abstract_declarator;
    AbstractDeclarator( Pointer *ptr, DirectAbstractDeclarator *dabs );
    int get_pointer_level();
};

AbstractDeclarator *
create_abstract_declarator( Pointer *pointer, DirectAbstractDeclarator *dabs );

class SpecifierQualifierList;

class TypeName : public NonTerminal {
  public:
    SpecifierQualifierList *sq_list;
    AbstractDeclarator *abstract_declarator;
    GlobalType type;
    TypeName();
};

TypeName *create_type_name( SpecifierQualifierList *, AbstractDeclarator * );

class ParameterDeclaration : public NonTerminal {
  public:
    DeclarationSpecifiers *declaration_specifiers;
    Declarator *declarator;
    AbstractDeclarator *abstract_declarator;
    GlobalType type;
    ParameterDeclaration();
    void create_type();
};

ParameterDeclaration *create_parameter_declaration( DeclarationSpecifiers *ds, Declarator *d, AbstractDeclarator *ad );

class ParameterTypeList : public NonTerminal {
  public:
    std::vector<ParameterDeclaration *> param_list;
    bool has_ellipsis;
    ParameterTypeList();
};

ParameterTypeList *add_to_parameter_list( ParameterTypeList *ptl = nullptr, ParameterDeclaration *pd );
ParameterTypeList *add_ellipsis_to_list( ParameterTypeList *ptl );

class SpecifierQualifierList : public NonTerminal {
  public:
    std::vector<TypeSpecifier *> type_specifiers;
    std::vector<TYPE_QUALIFIER> type_qualifiers;

    bool is_const;
    GlobalType *type;

    void create_type(); // Type Checking

    SpecifierQualifierList();
};

SpecifierQualifierList *create_type_specifier_sq( TypeSpecifier *type_specifier );
SpecifierQualifierList *create_type_qualifier_sq( TYPE_QUALIFIER type_qualifier );
SpecifierQualifierList *add_type_specifier_sq( SpecifierQualifierList *sq_list, TypeSpecifier *type_specifier );
SpecifierQualifierList *add_type_qualifier_sq( SpecifierQualifierList *sq_list, TYPE_QUALIFIER type_qualifier );

class UnionDeclaration : public NonTerminal {
  public:
    SpecifierQualifierList *sq_list;
    DeclaratorList *declarator_list;

    UnionDeclaration( SpecifierQualifierList *sq_list_, DeclaratorList *declarator_list_ );
    void add_to_union_definition( UnionDefinition * );
};

UnionDeclaration *create_union_declaration( SpecifierQualifierList *sq_list, DeclaratorList *union_declarator_list );

class UnionDeclarationList : public NonTerminal {
  public:
    std::vector<UnionDeclaration *> union_declaration_list;
    UnionDeclarationList();
};

UnionDeclarationList *add_to_union_declaration_list( UnionDeclarationList *union_declaration_list = nullptr, UnionDeclaration *union_declaration );
int verify_union_declarator( UnionDeclarationList *un );

// -------------------------------------STRUCT----------------------------------------

class StructDeclaration : public NonTerminal {
  public:
    SpecifierQualifierList *sq_list;
    DeclaratorList *declarator_list;

    StructDeclaration( SpecifierQualifierList *sq_list_, DeclaratorList *declarator_list_ );
    void add_to_struct_definition( StructDefinition * );
};

StructDeclaration *create_struct_declaration( SpecifierQualifierList *sq_list, DeclaratorList *struct_declarator_list );

class StructDeclarationList : public NonTerminal {
  public:
    std::vector<StructDeclaration *> struct_declaration_list;
    StructDeclarationList();
};

StructDeclarationList * add_to_struct_declaration_list( StructDeclarationList *struct_declaration_list = nullptr, StructDeclaration *struct_declaration );
int verify_struct_declarator( StructDeclarationList *st );

// -------------------------------------ENUM----------------------------------------

class Enumerator : public NonTerminal {
  public:
    Identifier *id;
    Node *init_expr;
    Enumerator( Identifier *id_, Node *init_expr );
};

Enumerator *create_enumerator( Identifier *id, Node *const_expr );

class EnumeratorList : public NonTerminal {
  public:
    std::vector<Enumerator *> enumerator_list;
    EnumeratorList();
};

EnumeratorList *add_to_enumerator_list( EnumeratorList *enumerator_list = nullptr, Enumerator *enumerator );

typedef int TYPE_SPECIFIER;

class TypeSpecifier : public Terminal {
  public:
    TYPE_SPECIFIER type;
    Identifier *id;
    StructDeclarationList *struct_declaration_list;
    EnumeratorList *enumerator_list;
    GlobalType *type;

    TypeSpecifier( TYPE_SPECIFIER typ, unsigned int line_num, unsigned int column );
    TypeSpecifier( TYPE_SPECIFIER type, Identifier *Id, StructDeclarationList *struct_declaration_list );
    TypeSpecifier( TYPE_SPECIFIER type, Identifier *Id, EnumeratorList *enumerator_list );
};

TypeSpecifier *create_type_specifier( TYPE_SPECIFIER type, unsigned int line_num, unsigned int column );
TypeSpecifier * create_struct_type( TYPE_SPECIFIER type, Identifier *id );                      
TypeSpecifier * add_struct_declaration( TypeSpecifier * ts, StructDeclarationList *struct_declaration_list );
TypeSpecifier *create_type_specifier( TYPE_SPECIFIER type, Identifier *id, EnumeratorList *enumerator_list );

Node *add_to_global_symbol_table( Declaration *declaration );

void error_msg( std::string str, unsigned int line_num, unsigned int column = 0);
void warning_msg( std::string str, unsigned int line_num, unsigned int column = 0);