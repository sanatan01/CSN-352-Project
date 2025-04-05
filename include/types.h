#pragma once

// #include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <string>
#include <iostream>
#include <cmath>

// --------------------------------------PRIMITVE TYPES----------------------------------------
enum PrimitiveTypes
{
	ERROR_T = -1,
	U_CHAR_T = 0,
	CHAR_T = 1,
	U_SHORT_T = 2,
	SHORT_T = 3,
	U_INT_T = 4,
	INT_T = 5,
	U_LONG_T = 6,
	LONG_T = 7,
	U_LLONG_T = 8,
	LLONG_T = 9,
	FLOAT_T = 10,
	DOUBLE_T = 11,
	LONG_DOUBLE_T = 12,
	VOID_T = 13,
	BOOL_T = 14,
};

std::string typeName(int type);

class Specifiers
{
public:
	bool is_typedef;
	bool is_extern;
	bool is_static;
	bool is_register;
	bool is_const;
	bool is_volatile;

	Specifiers();
};

Specifiers *combine_specs(Specifiers *spec1, Specifiers *spec2);

// -------------------------------------IDENTIFIER----------------------------------------

class Identifier
{
public:
	class GlobalType *type;
	std::string name;
	Identifier(std::string name, unsigned int _line_num = 0, unsigned int _column = 0);
	Identifier(class GlobalType *type);
};

// -------------------------------------STANDARD TYPE----------------------------------------

class StandardType
{
public:
	std::string name;
	size_t size;
	Specifiers *specifiers;
	StandardType();
	StandardType(std::string name, size_t size);

	// Important: Always use references when creating the objects to prevent object slicing
	virtual bool isEqual(const StandardType &obj) const;
	bool operator==(const StandardType &obj) const { return isEqual(obj); };
	bool operator!=(const StandardType &obj) const { return !(*this == obj); };

	std::string getSpecifierName() const;
};

extern std::unordered_map<PrimitiveTypes, StandardType *> type_specifiers;

// -------------------------------------STRUCT----------------------------------------

class StructElement
{
public:
	Identifier *id;
	size_t size;
	StructElement(Identifier *id, size_t size);
	StructElement(size_t size); // Add implementation if the identifier pointer is NULL
};

class VectorStructElement
{
public:
	std::vector<StructElement> elements;
	VectorStructElement();
	void add_element(StructElement *id);
	void add_elements(VectorStructElement *other);
};

class Struct : public StandardType
{
public:
	VectorStructElement members;
	std::string struct_name;
	Struct(std::string name, VectorStructElement *members);
	Struct(std::string name);
	Struct(VectorStructElement *members);
};

// -------------------------------------UNION----------------------------------------

class Union : public StandardType
{
public:
	VectorStructElement members;
	std::string union_name;
	Union(std::string name, VectorStructElement *members);
	Union(std::string name);
	Union(VectorStructElement *members);
};

// -------------------------------------COMPLEX TYPES----------------------------------------

class ArrayType : public StandardType
{
public:
	class GlobalType *return_type;
	unsigned int dim;
	std::vector<unsigned int> dims;
	ArrayType(unsigned int dim, class GlobalType *type, std::vector<unsigned int> dims, std::string name);
	ArrayType();
};

// -------------------------------------FUNCTION----------------------------------------

class VectorIdentifiers
{
public:
	std::vector<Identifier> identifiers;

	VectorIdentifiers();
	void add_identifier(Identifier *id);
	void add_identifiers(VectorIdentifiers *other);
};

class FunctionType : public StandardType
{
public:
	class VectorIdentifiers args;
	bool is_defined;
	class GlobalType *return_type;

	FunctionType(class GlobalType *return_type, class VectorIdentifiers *args);
	size_t get_num_args() const;
};

// -------------------------------------POINTER----------------------------------------

class PointerType : public StandardType
{
public:
	class GlobalType *return_type;
	int ptr_level;
	PointerType();
	PointerType(class GlobalType *return_type);
};

// -------------------------------------ENUM----------------------------------------
class EnumElement
{
public:
	std::string name;
	int value;
	bool is_defined;
	EnumElement(std::string name, int value);
	EnumElement(std::string name);
};

class VectorEnumElement
{
public:
	std::vector<EnumElement> elements;
	VectorEnumElement();
	void add_element(EnumElement *id);
	void add_elements(VectorEnumElement *other);
};

class EnumType : public StandardType
{
public:
	VectorEnumElement enum_values;
	std::string enum_name;
	EnumType(std::string name, VectorEnumElement *enum_values);
	EnumType(VectorEnumElement *enum_values);
	EnumType(std::string name);
};

// -------------------------------------INVALID TYPE----------------------------------------

// Important : Not an extension of StandardType
class InvalidType
{
public:
	std::string err_message;
	int line_num;
	int column;
	InvalidType(std::string _err_message, int _line_num = 0, int _column = 0);
	InvalidType();
};

// -------------------------------------GLOBAL TYPES----------------------------------------

enum GlobalTypeTag
{
	STANDARD_TYPE,
	STRUCT_TYPE,
	UNION_TYPE,
	ARRAY_TYPE,
	FUNCTION_TYPE,
	POINTER_TYPE,
	ENUM_TYPE,
	INVALID_TYPE,
	NONE,
};

class GlobalType
{
public:
	StandardType *standard_type;
	Struct *struct_type;
	Union *union_type;
	ArrayType *array_type;
	FunctionType *function_type;
	PointerType *pointer_type;
	EnumType *enum_type;
	InvalidType *invalid_type;
	enum GlobalTypeTag type_tag;

	GlobalType();
	~GlobalType();

	std::string getType() const;
	size_t getSize() const;
	bool isEqual(const class GlobalType &obj) const;
	Specifiers *getSpecifiers() const;
	void setSpecifiers(Specifiers *specifiers);
};

class GlobalType *create_enum_type(EnumType *_enum, Specifiers *specifiers = nullptr);

class GlobalType *create_union_type(Union *_union, Specifiers * = nullptr);

class GlobalType *create_struct_type(Struct *_struct, Specifiers *specifiers = nullptr);

class GlobalType *create_primitive_type(PrimitiveTypes type, Specifiers *specifiers = nullptr);

class GlobalType *create_function_type(class GlobalType *return_type, class VectorIdentifiers *args = nullptr, Specifiers *specifiers = nullptr);

class GlobalType *create_pointer_type(class GlobalType *return_type, int ptr_level = 1, Specifiers *specifiers = nullptr);

class GlobalType *create_default_pointer_type();

class GlobalType *create_array_type(class GlobalType *return_type);

class GlobalType *add_dimension_array(class GlobalType* array_type, int dimension = 0);

class GlobalType *create_invalid_type(std::string err_message, int line_num = 0, int column = 0);

class GlobalType *combine_global_type(class GlobalType *left, class GlobalType *right);

unsigned int convert_to_unsigned(std::string input);

int convert_to_signed(std::string input);