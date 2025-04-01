#include <string>
#include <map>
#include <assert.h>
#include <types.h>

class GlobalType* combine_types(class GlobalType* type1, class GlobalType* type2){
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
        {FLOAT_T, new StandardType("float", sizeof(float))},
        {DOUBLE_T, new StandardType("double", sizeof(double))},
        {LONG_DOUBLE_T, new StandardType("long double", sizeof(long double))},
        {VOID_T, new StandardType("void", 0)},
        {ERROR_T, new StandardType("error", 0)}
    };

    return type_specifiers;
}

Identifier::Identifier(std::string name, unsigned int _line_num, unsigned int _column) : type(new GlobalType()) {
    this->name = name;
}

Identifier::Identifier(class GlobalType* type) :
    type(type) {
    this->name = "";
}

std::unordered_map<PrimitiveTypes, StandardType*> type_specifiers = createStandardTypes();

StandardType::StandardType(): name(""), size(0), specifiers(new Specifiers()){}

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

FunctionType::FunctionType(class GlobalType* return_type, class VectorIdentifiers *args): return_type(return_type), args(*(args)) {
}

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

// Struct

Struct::Struct(std::string name) : StandardType("struct", 0), struct_name(name), members(VectorStructElement()) {}

Struct::Struct(std::string name, VectorStructElement *members1) : StandardType("struct", 0), struct_name(name), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        this->size += member.size;
    }
}

Struct::Struct(VectorStructElement *members1) : StandardType("struct", 0), struct_name("Default"), members(*(members1)) {
    this->size = 0;
    for (auto& member : members1->elements) {
        this->size += member.size;
    }
}

StructElement::StructElement(Identifier* id, size_t size) : id(id), size(size) {}

VectorStructElement::VectorStructElement() : elements(std::vector<StructElement>()) {}

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

InvalidType::InvalidType(int _line_num, int _column, std::string _err_message): line_num(_line_num), column(_column), err_message(_err_message) {}

// GlobalType
class GlobalType* create_primitive_type(PrimitiveTypes type, Specifiers* specifiers) {
    class GlobalType* typ = new GlobalType();
    typ->type_tag = STANDARD_TYPE;
    typ->standard_type = type_specifiers[type];
    if (specifiers != nullptr) {
        typ->standard_type->specifiers = specifiers;
    }
    return typ;
}

class GlobalType* create_function_type(class GlobalType* return_type, class VectorIdentifiers* args, Specifiers* specifiers) {
    class GlobalType *type = new GlobalType();
    type->type_tag = FUNCTION_TYPE;
    type->function_type = new FunctionType(return_type, args);
    if (specifiers != nullptr) {
        type->function_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_struct_type(Struct* _struct, Specifiers* specifiers) {
    class GlobalType *type = new GlobalType();
    type->type_tag = STRUCT_TYPE;
    type->struct_type = _struct;
    if (specifiers != nullptr) {
        type->struct_type->specifiers = specifiers;
    }
    return type;
}

class GlobalType* create_pointer_type(class GlobalType* return_type, int ptr_level, Specifiers* specifiers) {
    class GlobalType *type = new GlobalType();
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

    return right;
}

void sample_function(class GlobalType* left, class GlobalType* right) {
    
}

Specifiers* combine_specs(Specifiers* spec1, Specifiers* spec2) {
	Specifiers* combined = new Specifiers();
	combined->is_typedef = spec1->is_typedef || spec2->is_typedef;
	combined->is_extern = spec1->is_extern || spec2->is_extern;
	combined->is_static = spec1->is_static || spec2->is_static;
	combined->is_auto = spec1->is_auto || spec2->is_auto;
	combined->is_register = spec1->is_register || spec2->is_register;
	combined->is_const = spec1->is_const || spec2->is_const;
	combined->is_volatile = spec1->is_volatile || spec2->is_volatile;
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