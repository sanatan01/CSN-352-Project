#pragma once

// #include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

//Todo: remove this later
#include <iostream>
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
};

// TODO: this is supposed to throw errors when same symbol is defined twice
Specifiers* combine_specs(Specifiers* spec1, Specifiers* spec2);


class Identifier {
public:
	class GlobalType* type;
	std::string name;
	Identifier(std::string name, unsigned int _line_num = 0, unsigned int _column = 0);
	Identifier(class GlobalType* type);
};

class StandardType {
public:
	std::string name;
	size_t size;
	Specifiers* specifiers;
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

	std::string getSpecifierName() const {
		std::string st = "";
		if (specifiers == nullptr) {
			return name;
		}
		if (specifiers->is_const) {
			st += "const ";
		}
		if (specifiers->is_volatile) {
			st += "volatile ";
		}
		if (specifiers->is_typedef) {
			st += "typedef ";
		}
		if (specifiers->is_extern) {
			st += "extern ";
		}
		if (specifiers->is_static) {
			st += "static ";
		}
		if (specifiers->is_auto) {
			st += "auto ";
		}
		if (specifiers->is_register) {
			st += "register ";
		}
		return st + name;
	}
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
	std::string struct_name;
	//TODO: remember to add the "struct" as the name of the standard type
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

class VectorIdentifiers {
public:
	std::vector<Identifier> identifiers;

	VectorIdentifiers();
	void add_identifier(Identifier* id);
	void add_identifiers(VectorIdentifiers* other);
};

// -------------------------------------FUNCTION----------------------------------------

class FunctionType: public StandardType {
public:
	class VectorIdentifiers args;
	bool is_defined;
	class GlobalType* return_type;

	FunctionType(class GlobalType* return_type, class VectorIdentifiers* args);
	size_t get_num_args() {
		return args.identifiers.size();
	}
};

// -------------------------------------POINTER----------------------------------------

class PointerType: public StandardType {
public:
	class GlobalType* return_type;
	int ptr_level;
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

	GlobalType():
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
		case STANDARD_TYPE: {
			return standard_type->getSpecifierName();
		}
		case STRUCT_TYPE: return struct_type->getSpecifierName();
		case UNION_TYPE: return struct_type->getSpecifierName();
		case ARRAY_TYPE: {
			std::string st = "";

			for (int i = 0;i < array_type->dim;i++) {
				st += "[]";
			}
			return array_type->getSpecifierName() + array_type->return_type->getType() + st;
		}
		case FUNCTION_TYPE: {
			return "Function: " + function_type->getSpecifierName() + function_type->return_type->getType();
		}
		case POINTER_TYPE: {

			std::string st = "";
			for (int i = 0;i < pointer_type->ptr_level;i++) {
				st += "*";
			}
			return st + pointer_type->getSpecifierName() + pointer_type->return_type->getType();
		}
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

	std::string getName() const {
		switch (type_tag) {
		case STANDARD_TYPE: return standard_type ? standard_type->name : "";
		case STRUCT_TYPE: return struct_type ? struct_type->name : "";
		case UNION_TYPE: return union_type ? union_type->name : "";
		case ARRAY_TYPE: return array_type ? array_type->return_type->getName() : "";
		case FUNCTION_TYPE: return function_type ? function_type->return_type->getName() : "";
		case POINTER_TYPE: return pointer_type ? pointer_type->return_type->getName() : "";
		case ENUM_TYPE: return enum_type ? enum_type->name : "";
		default: return "abc";
		}
	}

	Specifiers* getSpecifiers() const {
		switch (type_tag) {
		case STANDARD_TYPE: return standard_type ? standard_type->specifiers : nullptr;
		case STRUCT_TYPE: return struct_type ? struct_type->specifiers : nullptr;
		case UNION_TYPE: return union_type ? union_type->specifiers : nullptr;
		case ARRAY_TYPE: return array_type ? array_type->specifiers : nullptr;
		case FUNCTION_TYPE: return function_type ? function_type->specifiers : nullptr;
		case POINTER_TYPE: return pointer_type ? pointer_type->specifiers : nullptr;
		case ENUM_TYPE: return enum_type ? enum_type->specifiers : nullptr;
		default: return nullptr;
		}
	}
};


class GlobalType* create_primitive_type(PrimitiveTypes type, Specifiers* specifiers = nullptr);
class GlobalType* create_function_type(class GlobalType* return_type, class VectorIdentifiers* args, Specifiers* specifiers = nullptr);
class GlobalType* create_pointer_type(class GlobalType* return_type, int ptr_level = 1, Specifiers* specifiers = nullptr);
class GlobalType* create_default_pointer_type();

class GlobalType* combine_types(class GlobalType* type1, class GlobalType* type2);

extern InvalidType INVALID_TYPE;

// This stores all the defined types (that are not standard types)
extern std::vector<class GlobalType> defined_types;

int add_to_defined_types(class GlobalType* typ);