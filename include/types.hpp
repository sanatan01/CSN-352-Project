#pragma once

#include <ast.hpp>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <ast_entries.hpp>
#include <unordered_map>

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
    StandardType();
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
  
// -------------------------------------STRUCT----------------------------------------
class StructDeclarationList;

class StructDefinition {
  public:
    std::unordered_map<std::string, GlobalType> members;

    StructDefinition();
    size_t get_offset( Identifier *id );
    GlobalType *get_member( Identifier *id );

  private:
    bool recursive;
};

class Struct : public StandardType {
  public:
    StructDefinition *definition;
    Struct(std::string name);
    Struct(StructDefinition *definition) : definition(definition) {}
};

Struct *create_struct( StructDeclarationList *sdl );

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
    Union(std::string name);
    Union(UnionDefinition *definition) : definition(definition) {}
};

Union *create_union( UnionDeclarationList *udl );
  
// -------------------------------------COMPLEX TYPES----------------------------------------

class ArrayType : public StandardType {
  public:
    GlobalType *return_type;
    unsigned int dim;
    std::vector<unsigned int> dims;
    ArrayType( unsigned int dim, GlobalType *type, std::vector<unsigned int> dims , std::string name);
};

class FunctionType : public StandardType {
  public:
    unsigned int num_args;
    std::unordered_map<std::string, GlobalType> args;
    bool is_defined;

    FunctionType( unsigned int num_args, std::unordered_map<std::string, GlobalType> args, std::string name );
};

class PointerType : public StandardType {
  public:
    GlobalType *type;
    int ptr_level;
    PointerType( GlobalType *type, std::string name);
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

    // Method to find out which type is not null
    std::string getType() const {
        if (standard_type) return "StandardType";
        if (struct_type) return "Struct";
        if (union_type) return "Union";
        if (array_type) return "ArrayType";
        if (function_type) return "FunctionType";
        if (pointer_type) return "PointerType";
        if (invalid_type) return "InvalidType";
        return "None";
    }

    size_t getSize() const {
        if (standard_type) return standard_type->size;
        if (struct_type) return struct_type->size;
        if (union_type) return union_type->size;
        if (array_type) return array_type->size;
        if (function_type) return function_type->size;
        if (pointer_type) return pointer_type->size;
        return 0;
    }

    bool isEqual(const GlobalType &obj) const {
        if (getType() != obj.getType()) return false;
        if (standard_type) return *standard_type == *obj.standard_type;
        if (struct_type) return *struct_type == *obj.struct_type;
        if (union_type) return *union_type == *obj.union_type;
        if (array_type) return *array_type == *obj.array_type;
        if (function_type) return *function_type == *obj.function_type;
        if (pointer_type) return *pointer_type == *obj.pointer_type;
        return false;
    }
    void make_unsigned() {
        if (standard_type) {
          if (standard_type->name == "char"){
            standard_type->name = "unsigned char";
            standard_type->size = sizeof(unsigned char);
          } 
          else if (standard_type->name == "short")
          {
            standard_type->name = "unsigned short";
            standard_type->size = sizeof(unsigned short);
          }
          else if (standard_type->name == "int")
          {
            standard_type->name = "unsigned int";
            standard_type->size = sizeof(unsigned int);
          }
          else if (standard_type->name == "long")
          {
            standard_type->name = "unsigned long";
            standard_type->size = sizeof(unsigned long);
          }
        }
    }

    void make_signed() {
        if (standard_type) {
            if (standard_type->name == "unsigned char"){
              standard_type->name = "char";
              standard_type->size = sizeof(char);
            }
            else if (standard_type->name == "unsigned short")
            {
              standard_type->name = "signed short";
              standard_type->size = sizeof(signed short);
            }
            else if (standard_type->name == "unsigned int")
            {
              standard_type->name = "int";
              standard_type->size = sizeof(int);
            }
            else if (standard_type->name == "unsigned long")
            {
              standard_type->name = "long";
              standard_type->size = sizeof(long);
            }
        }
    }
};
  
extern InvalidType INVALID_TYPE;

// This stores all the defined types (that are not standard types)
extern std::vector<GlobalType> defined_types;

int add_to_defined_types( GlobalType *typ );