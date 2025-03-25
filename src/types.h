#pragma once

#include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include "ast_entries.h"

// --------------------------------------PRIMITVE TYPES----------------------------------------
enum PrimitiveTypes {
    ERROR_T = -1,
    U_CHAR_T,
    CHAR_T,
    U_SHORT_T,
    SHORT_T,
    U_INT_T,
    INT_T,
    U_LONG_T,
    LONG_T,
    FLOAT_T,
    DOUBLE_T,
    LONG_DOUBLE_T,
    VOID_T,
  };
  
  class StandardType {
    public:
      std::string name;
      size_t size;
      StandardType(std::string name, size_t size);
  
    // Important: Always use references when creating the objects to prevent object slicing
    virtual bool isEqual(const StandardType &obj) const;
  
    bool operator==( const StandardType& obj ) const {
      return isEqual(obj);
    };
  
    bool operator!=( const StandardType &obj ) const {
      return !(*this == obj);
    };
  };
  
  // Creates unordered map of standard types that can be accessed in O(1) time
  // TODO: move this to symtab.cpp
  std::unordered_map<PrimitiveTypes, StandardType> createStandardTypes() {
    std::unordered_map<PrimitiveTypes, StandardType> type_specifiers = {
        {U_CHAR_T, StandardType("unsigned char", sizeof(unsigned char))},
        {CHAR_T, StandardType("char", sizeof(char))},
        {U_SHORT_T, StandardType("unsigned short", sizeof(unsigned short))},
        {SHORT_T, StandardType("short", sizeof(short))},
        {U_INT_T, StandardType("unsigned int", sizeof(unsigned int))},
        {INT_T, StandardType("int", sizeof(int))},
        {U_LONG_T, StandardType("unsigned long", sizeof(unsigned long))},
        {LONG_T, StandardType("long", sizeof(long))},
        {FLOAT_T, StandardType("float", sizeof(float))},
        {DOUBLE_T, StandardType("double", sizeof(double))},
        {LONG_DOUBLE_T, StandardType("long double", sizeof(long double))},
        {VOID_T, StandardType("void", 0)},
        {ERROR_T, StandardType("error", 0)}
    };
    return type_specifiers;
  }
  
  // -------------------------------------STRUCT----------------------------------------
  
  class StructDeclarationList;
  
  class StructDefinition {
    public:
      std::unordered_map<std::string, GlobalType> members;
  
      StructDefinition();
      size_t get_offset( Identifier *id );
      GlobalType *get_member( Identifier *id );
  
      private:
          int recursive;
  };
  
  class Struct : public StandardType {
    public:
      StructDefinition *definition;
      Struct();
  };
  
  StructDefinition *create_struct_definition( StructDeclarationList *sdl );
  
  // -------------------------------------UNION----------------------------------------
  class UnionDeclarationList;
  
  class UnionDefinition {
    public:
      std::unordered_map<std::string, GlobalType> members;
  
      UnionDefinition();
      GlobalType *get_member( Identifier *id );
  };
  
  class Union : public StandardType {
    public:
      UnionDefinition *definition;
      Union();
  };
  
  UnionDefinition *create_union_definition( UnionDeclarationList *udl );
  
  // -------------------------------------COMPLEX TYPES----------------------------------------
  
  class ArrayType : StandardType {
    public:
      unsigned int dim;
      std::vector<unsigned int> dims;
      ArrayType( unsigned int dim, GlobalType *type );
  };
  
  class FunctionType : StandardType {
    public:
      unsigned int num_args;
      std::unordered_map<std::string, GlobalType> args;
      bool is_defined;
  
      FunctionType( unsigned int num_args, std::unordered_map<std::string, GlobalType> args );
  };
  
  class PointerType : StandardType {
    public:
      GlobalType *type;
      int ptr_level;
      PointerType( GlobalType *type );
  };
  
  // -------------------------------------INVALID TYPE----------------------------------------
  
  // Important : Not an extension of StandardType
  class InvalidType {
    public:
      std::string err_message;
      int line_num;
      int column;
      InvalidType(int _line_num, int _column, std::string _err_message);
  };
  
  // -------------------------------------GLOBAL TYPES----------------------------------------
  
  union GlobalType {
    StandardType *standard_type;
    Struct *struct_type;
    Union *union_type;
    ArrayType *array_type;
    FunctionType *function_type;
    PointerType *pointer_type;
    InvalidType *invalid_type;
  };
  
  extern InvalidType INVALID_TYPE;
  
  // This stores all the defined types (that are not standard types)
  extern std::vector<GlobalType> defined_types;
  
  int add_to_defined_types( GlobalType *typ );