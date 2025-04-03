#include <string>
#include <map>
#include <assert.h>
#include <types.h>

class GlobalType* combine_types(class GlobalType* type1, class GlobalType* type2) {
    return type1;
}

// Creates unordered map of standard types that can be accessed in O(1) time
std::unordered_map<PrimitiveTypes, StandardType*> createStandardTypes() {
    std::unordered_map<PrimitiveTypes, StandardType*> type_specifiers = {
        {U_CHAR_T, new StandardType("unsigned char", sizeof(unsigned char))},
        {CHAR_T, new StandardType("char", sizeof(char))},
        {U_SHORT_T, new StandardType("unsigned short", sizeof(unsigned short))},
        {SHORT_T, new StandardType("short", sizeof(short))},
        {U_INT_T, new StandardType("unsigned int", sizeof(unsigned int))},
        {INT_T, new StandardType("int", sizeof(int))},
        {U_LONG_T, new StandardType("unsigned long", sizeof(unsigned long))},
        {LONG_T, new StandardType("long", sizeof(long))},
        {LLONG_T, new StandardType("long long", sizeof(long long))},
        {U_LLONG_T, new StandardType("unsigned long long", sizeof(unsigned long long))},
        {FLOAT_T, new StandardType("float", sizeof(float))},
        {DOUBLE_T, new StandardType("double", sizeof(double))},
        {LONG_DOUBLE_T, new StandardType("long double", sizeof(long double))},
        {VOID_T, new StandardType("void", 0)},
        {ERROR_T, new StandardType("error", 0)},
        {SIGNED_T, new StandardType("signed", 0)},
        {UNSIGNED_T, new StandardType("unsigned", 0)}
    };

    return type_specifiers;
}

Identifier::Identifier(std::string name, unsigned int _line_num, unsigned int _column): type(new GlobalType()) {
    this->name = name;
}

Identifier::Identifier(class GlobalType* type):
    type(type) {
    this->name = "";
}

std::unordered_map<PrimitiveTypes, StandardType*> type_specifiers = createStandardTypes();

StandardType::StandardType(): name(""), size(0), specifiers(new Specifiers()) {}

StandardType::StandardType(std::string name, size_t size): name(name), size(size) {}

bool StandardType::isEqual(const StandardType& obj) const {
    return name == obj.name && size == obj.size;
}

ArrayType::ArrayType(unsigned int dim, class GlobalType* type, std::vector<unsigned int> dims, std::string name): dim(dim), return_type(type), dims(dims) {
    this->name = name;
    int cnt = 1;
    for (auto& d : dims) {
        cnt *= d;
    }
    this->size = cnt * type->getSize();
}

FunctionType::FunctionType(class GlobalType* return_type, class VectorIdentifiers* args): return_type(return_type), args(*(args)) {}

//VectorIdentifier to handle vectors in c
VectorIdentifiers::VectorIdentifiers() {
    this->identifiers = std::vector<Identifier>();
}

void VectorIdentifiers::add_identifier(Identifier* id) {
    this->identifiers.push_back(*id);
}
void VectorIdentifiers::add_identifiers(VectorIdentifiers* other) {
    for (auto& id : other->identifiers) {
        this->identifiers.push_back(id);
    }
}

// Union

Union::Union(std::string name): StandardType("union", 0), union_name(name), members(VectorStructElement()) {}

Union::Union(VectorStructElement* members1): StandardType("union", 0), union_name("Default"), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        if (this->size < member.size) {
            this->size = member.size;
        };
    }
}

Union::Union(std::string name, VectorStructElement* members1): StandardType("union", 0), union_name(name), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        if (this->size < member.size) {
            this->size = member.size;
        };
    }
}

// Struct

Struct::Struct(std::string name): StandardType("struct", 0), struct_name(name), members(VectorStructElement()) {}

Struct::Struct(std::string name, VectorStructElement* members1): StandardType("struct", 0), struct_name(name), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        this->size += member.size;
    }
}

Struct::Struct(VectorStructElement* members1): StandardType("struct", 0), struct_name("Default"), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        this->size += member.size;
    }
}

StructElement::StructElement(Identifier* id, size_t size): id(id), size(size) {}

VectorStructElement::VectorStructElement(): elements(std::vector<StructElement>()) {}

void VectorStructElement::add_element(StructElement* element) {
    this->elements.push_back(*element);
}

void VectorStructElement::add_elements(VectorStructElement* other) {
    for (auto& element : other->elements) {
        this->elements.push_back(element);
    }
}

//Pointer

PointerType::PointerType() {
    this->ptr_level = 1;
}

PointerType::PointerType(class GlobalType* return_type) {
    this->ptr_level = 1;
    this->return_type = return_type;
}

EnumElement::EnumElement(std::string name, int value): name(name), value(value), is_defined(1) {}
EnumElement::EnumElement(std::string name): name(name), value(0), is_defined(0) {}

VectorEnumElement::VectorEnumElement(): elements(std::vector<EnumElement>()) {}
void VectorEnumElement::add_element(EnumElement* id) {
    this->elements.push_back(*id);
}
void VectorEnumElement::add_elements(VectorEnumElement* other) {
    for (auto& id : other->elements) {
        this->elements.push_back(id);
    }
}

EnumType::EnumType(std::string name, VectorEnumElement* enum_values): StandardType("enum", sizeof(int)), enum_name(name), enum_values(*(enum_values)) {

}
EnumType::EnumType(VectorEnumElement* enum_values): StandardType("enum", sizeof(int)), enum_name("Default"), enum_values(*(enum_values)) {

}
EnumType::EnumType(std::string name): StandardType("enum", sizeof(int)), enum_name(name), enum_values(VectorEnumElement()) {

}


InvalidType::InvalidType(std::string _err_message, int _line_num, int _column): line_num(_line_num), column(_column), err_message(_err_message) {}

// GlobalType
class GlobalType* create_primitive_type(PrimitiveTypes type, Specifiers* specifiers) {
    class GlobalType* typ = new GlobalType();
    typ->type_tag = STANDARD_TYPE;
    StandardType* orig = type_specifiers[type];
    typ->standard_type = new StandardType(orig->name, orig->size);
    if (specifiers != nullptr) {
        typ->standard_type->specifiers = specifiers;
    }
    return typ;
}

class GlobalType* create_function_type(class GlobalType* return_type, class VectorIdentifiers* args, Specifiers* specifiers) {
    class GlobalType* type = new GlobalType();
    type->type_tag = FUNCTION_TYPE;
    type->function_type = new FunctionType(return_type, args);
    if (specifiers != nullptr) {
        type->function_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_enum_type(EnumType* _enum, Specifiers* specifiers) {
    class GlobalType* type = new GlobalType();
    type->type_tag = ENUM_TYPE;
    type->enum_type = _enum;
    if (specifiers != nullptr) {
        type->enum_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_union_type(Union* _union, Specifiers* specifiers) {
    class GlobalType* type = new GlobalType();
    type->type_tag = UNION_TYPE;
    type->union_type = _union;
    if (specifiers != nullptr) {
        type->union_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_struct_type(Struct* _struct, Specifiers* specifiers) {
    class GlobalType* type = new GlobalType();
    type->type_tag = STRUCT_TYPE;
    type->struct_type = _struct;
    if (specifiers != nullptr) {
        type->struct_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_pointer_type(class GlobalType* return_type, int ptr_level, Specifiers* specifiers) {
    class GlobalType* type = new GlobalType();
    type->type_tag = POINTER_TYPE;
    type->pointer_type = new PointerType(return_type);
    type->pointer_type->ptr_level = ptr_level;
    if (specifiers != nullptr) {
        type->pointer_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_default_pointer_type() {
    return create_pointer_type(new GlobalType(), 1);
}

class GlobalType* combine_global_type(class GlobalType* left, class GlobalType* right) {

    // This function assumes that left was written before right

    // If either type is none, return the other type
    if (left->type_tag == NONE) {
        return right;
    }
    else if (right->type_tag == NONE) {
        return left;
    }

    // If either type is invalid, return the invalid type
    if (left->type_tag == INVALID) {
        return left;
    }
    else if (right->type_tag == INVALID) {
        return right;
    }

    // If the right type is complex type -> Function, Array, Pointer make the return type as first one.
    switch (right->type_tag) {
    case FUNCTION_TYPE: {
        if (right->function_type->return_type == NULL || right->function_type->return_type->type_tag == NONE) {
            return right->function_type->return_type = left;
        }
        else {
            return right->function_type->return_type = combine_global_type(left, right->function_type->return_type);
        }
    }
    case ARRAY_TYPE: {
        if (right->array_type->return_type == NULL || right->array_type->return_type->type_tag == NONE) {
            return right->array_type->return_type = left;
        }
        else {
            return right->array_type->return_type = combine_global_type(left, right->array_type->return_type);
        }
    }
    case POINTER_TYPE: {
        if (right->pointer_type->return_type == NULL || right->pointer_type->return_type->type_tag == NONE) {
            return right->pointer_type->return_type = left;
        }
        else {
            return right->pointer_type->return_type = combine_global_type(left, right->pointer_type->return_type);
        }
    }
    case UNION_TYPE:
    case STRUCT_TYPE: {
        // cannot combine struct types with other types unless left is none
        if (left->type_tag == NONE) {
            right->struct_type->specifiers = combine_specs(left->getSpecifiers(), right->struct_type->specifiers);
            return right;
        } else if (left->type_tag == ENUM_TYPE) {
            right->enum_type = left->enum_type;
            right->struct_type = nullptr;
            right->type_tag = ENUM_TYPE;
            return right;
        }
        else return create_invalid_type("Cannot combine struct type with other types");
    }
    case ENUM_TYPE: {
        // only enum struct can be combined
        // enum struct Color {RED, GREEN, BLUE}; is valid code

    }

    }
    return right;
}

Specifiers* combine_specs(Specifiers* spec1, Specifiers* spec2) {

    if (spec1 == nullptr && spec2 == nullptr) {
        return new Specifiers();
    }
    else if (spec1 == nullptr) {
        Specifiers* spec = new Specifiers();
        *spec = *spec2;
        return spec;
    }
    else if (spec2 == nullptr) {
        Specifiers* spec = new Specifiers();
        *spec = *spec1;
        return spec;
    }

    Specifiers* combined = new Specifiers();
    auto combine_flag = [](bool a, bool b, const char* msg) {
        if (a && b) throw std::runtime_error(msg);
        return a || b;
    };

    combined->is_typedef = combine_flag(spec1->is_typedef, spec2->is_typedef, "Error: 'typedef' keyword is used more than once.");
    combined->is_extern = combine_flag(spec1->is_extern, spec2->is_extern, "Error: 'extern' keyword is used more than once.");
    combined->is_static = combine_flag(spec1->is_static, spec2->is_static, "Error: 'static' keyword is used more than once.");
    combined->is_register = combine_flag(spec1->is_register, spec2->is_register, "Error: 'register' keyword is used more than once.");
    combined->is_const = combine_flag(spec1->is_const, spec2->is_const, "Error: 'const' keyword is used more than once.");
    combined->is_volatile = combine_flag(spec1->is_volatile, spec2->is_volatile, "Error: 'volatile' keyword is used more than once.");
    return combined;
}

std::vector<GlobalType> defined_types;

int add_to_defined_types(GlobalType* typ) {
    for (int i = 0; i < defined_types.size(); i++) {
        if (defined_types[i].isEqual(*typ)) {
            return i;
        }
    }
    defined_types.push_back(*typ);
    return defined_types.size() - 1;
}