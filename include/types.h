#pragma once

// #include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include<vector>

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

class Specifiers {
public:
  bool is_typedef;
  bool is_extern;
  bool is_static;
  bool is_auto;
  bool is_register;
  bool is_const;
  bool is_volatile;

  Specifiers():
    is_typedef(false),
    is_extern(false),
    is_static(false),
    is_auto(false),
    is_register(false),
    is_const(false),
    is_volatile(false) {};

  void combine(Specifiers* other) {
    this->is_typedef = this->is_typedef || other->is_typedef;
    this->is_extern = this->is_extern || other->is_extern;
    this->is_static = this->is_static || other->is_static;
    this->is_auto = this->is_auto || other->is_auto;
    this->is_register = this->is_register || other->is_register;
    this->is_const = this->is_const || other->is_const;
    this->is_volatile = this->is_volatile || other->is_volatile;
  }
};



class Identifier {
public:
  class GlobalType* type;
  std::string name;
  Identifier(std::string name, unsigned int _line_num = 0, unsigned int _column = 0);
};

class StandardType {
public:
  std::string name;
  size_t size;
  Specifiers specifiers;
  StandardType();
  StandardType(std::string name, size_t size);

  // Important: Always use references when creating the objects to prevent object slicing
  virtual bool isEqual(const StandardType& obj) const;

  bool operator==(const StandardType& obj) const {
    return isEqual(obj);
  };

  bool operator!=(const StandardType& obj) const {
    return !(*this == obj);
  };
};
extern std::unordered_map<PrimitiveTypes, StandardType*> type_specifiers;

// -------------------------------------STRUCT----------------------------------------

class StructElement {
public:
  Identifier* id;
  size_t size;
  StructElement(Identifier* id, size_t size); // Add implementation if the identifier pointer is NULL
};


class Struct: public StandardType {
public:

  std::vector<StructElement> members;
  std::string name;
  Struct(std::string name, std::vector<StructElement> members);
  Struct(std::string name);
  Struct(std::vector<StructElement> members);
};

// -------------------------------------UNION----------------------------------------

class Union: public StandardType {
public:
  std::vector<StructElement> members;
  std::string name;
  Union(std::string name, std::vector<StructElement> members);
  Union(std::string name);
  Union(std::vector<StructElement> members);
};

// -------------------------------------COMPLEX TYPES----------------------------------------

class ArrayType: public StandardType {
public:
  class GlobalType* return_type;
  unsigned int dim;
  std::vector<unsigned int> dims;
  ArrayType(unsigned int dim, class GlobalType* type, std::vector<unsigned int> dims, std::string name);
  ArrayType():
    dim(0),
    return_type(nullptr),
    dims(std::vector<unsigned int>()) {};
};

class VectorIdentifiers{
public:
  std::vector<Identifier> identifiers;

  VectorIdentifiers();
  void add_identifier(Identifier* id);
  void add_identifiers(VectorIdentifiers* other);
};

// -------------------------------------FUNCTION----------------------------------------

class FunctionType: public StandardType {
public:
  unsigned int num_args;
  class VectorIdentifiers args;
  bool is_defined;
  class GlobalType* return_type;

  FunctionType(class GlobalType* return_type, class VectorIdentifiers *args);
};

// -------------------------------------POINTER----------------------------------------

class PointerType: public StandardType {
public:
  class GlobalType* return_type;
  int ptr_level;\
    PointerType();
  PointerType(class GlobalType* return_type);
};

// -------------------------------------ENUM----------------------------------------
class EnumElement {
public:
  std::string name;
  int value;
  bool is_defined;
  EnumElement(std::string name, int value);
  EnumElement(std::string name);
};

class EnumType: public StandardType {
public:
  std::vector<EnumElement> enum_values;
  EnumType(std::string name, std::vector<EnumElement>* enum_values);
  EnumType(std::vector<EnumElement>* enum_values);
  EnumType(std::string name);

};


// -------------------------------------INVALID TYPE----------------------------------------

// Important : Not an extension of StandardType
class InvalidType {
public:
  std::string err_message;
  int line_num;
  int column;
  InvalidType(int _line_num, int _column, std::string _err_message);
  InvalidType();
};

// -------------------------------------GLOBAL TYPES----------------------------------------
enum GlobalTypeTag {
  STANDARD_TYPE,
  STRUCT_TYPE,
  UNION_TYPE,
  ARRAY_TYPE,
  FUNCTION_TYPE,
  POINTER_TYPE,
  ENUM_TYPE,
  INVALID,
  NONE,
};

class GlobalType {
  public: 
  StandardType* standard_type;
  Struct* struct_type;
  Union* union_type;
  ArrayType* array_type;
  FunctionType* function_type;
  PointerType* pointer_type;
  EnumType* enum_type;
  InvalidType* invalid_type;
  enum GlobalTypeTag type_tag;

  GlobalType() :
    standard_type(nullptr),
    struct_type(nullptr),
    union_type(nullptr),
    array_type(nullptr),
    function_type(nullptr),
    pointer_type(nullptr),
    enum_type(nullptr),
    invalid_type(nullptr),
    type_tag(NONE) {};

    // Method to find out which type is not null
    std::string getType() const {
      switch (type_tag) {
        case STANDARD_TYPE: return "StandardType";
        case STRUCT_TYPE: return "Struct";
        case UNION_TYPE: return "Union";
        case ARRAY_TYPE: return "ArrayType";
        case FUNCTION_TYPE: return "FunctionType";
        case POINTER_TYPE: return "PointerType";
        case ENUM_TYPE: return "EnumType";
        case INVALID: return "InvalidType";
        default: return "None";
      }
    }

    size_t getSize() const {
      switch (type_tag) {
        case STANDARD_TYPE: return standard_type ? standard_type->size : 0;
        case STRUCT_TYPE: return struct_type ? struct_type->size : 0;
        case UNION_TYPE: return union_type ? union_type->size : 0;
        case ARRAY_TYPE: return array_type ? array_type->size : 0;
        case FUNCTION_TYPE: return function_type ? function_type->size : 0;
        case POINTER_TYPE: return pointer_type ? pointer_type->size : 0;
        case ENUM_TYPE: return enum_type ? enum_type->size : 0;
        default: return 0;
      }
    }

    bool isEqual(const class GlobalType& obj) const {
      if (type_tag != obj.type_tag) return false;
      switch (type_tag) {
        case STANDARD_TYPE: return standard_type && obj.standard_type && *standard_type == *obj.standard_type;
        case STRUCT_TYPE: return struct_type && obj.struct_type && *struct_type == *obj.struct_type;
        case UNION_TYPE: return union_type && obj.union_type && *union_type == *obj.union_type;
        case ARRAY_TYPE: return array_type && obj.array_type && *array_type == *obj.array_type;
        case FUNCTION_TYPE: return function_type && obj.function_type && *function_type == *obj.function_type;
        case POINTER_TYPE: return pointer_type && obj.pointer_type && *pointer_type == *obj.pointer_type;
        case ENUM_TYPE: return enum_type && obj.enum_type && *enum_type == *obj.enum_type;
        default: return false;
      }
    }
};

class GlobalType* create_primitive_type(PrimitiveTypes type, Specifiers* specifiers = nullptr);
class GlobalType* create_function_type(class GlobalType* return_type, class VectorIdentifiers* args, Specifiers* specifiers = nullptr);

class GlobalType* combine_types(class GlobalType* type1, class GlobalType* type2);
class GlobalType* combine_specifiers(class GlobalType* type, Specifiers* spec);

extern InvalidType INVALID_TYPE;

// This stores all the defined types (that are not standard types)
extern std::vector<class GlobalType> defined_types;

int add_to_defined_types(class GlobalType* typ);