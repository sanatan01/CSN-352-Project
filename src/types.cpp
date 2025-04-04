#include <string>
#include <map>
#include <assert.h>
#include <types.h>

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
        {ERROR_T, new StandardType("error", 0)}
    };

    return type_specifiers;
}


std::string typeName(int type) {
    switch (type) {
    case U_CHAR_T:
        return "unsigned char";
    case CHAR_T:
        return "char";
    case U_SHORT_T:
        return "unsigned short";
    case SHORT_T:
        return "short";
    case U_INT_T:
        return "unsigned int";
    case INT_T:
        return "int";
    case U_LONG_T:
        return "unsigned long";
    case LONG_T:
        return "long";
    case LLONG_T:
        return "long long";
    case U_LLONG_T:
        return "unsigned long long";
    case FLOAT_T:
        return "float";
    case DOUBLE_T:
        return "double";
    case LONG_DOUBLE_T:
        return "long double";
    case VOID_T:
        return "void";
    case BOOL_T:
        return "bool";
    default:
        return "unknown";
    }
}

// -------------------------- Standard Methods ----------------------------

Specifiers::Specifiers(): is_typedef(false), is_extern(false), is_static(false), is_register(false), is_const(false), is_volatile(false) {}

bool combine_flag(bool a, bool b, std::string err) {
    if (a && b)
        std::cerr << err << std::endl;
    return a || b;
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

    combined->is_typedef = combine_flag(spec1->is_typedef, spec2->is_typedef, "Error: 'typedef' keyword is used more than once.");
    combined->is_extern = combine_flag(spec1->is_extern, spec2->is_extern, "Error: 'extern' keyword is used more than once.");
    combined->is_static = combine_flag(spec1->is_static, spec2->is_static, "Error: 'static' keyword is used more than once.");
    combined->is_register = combine_flag(spec1->is_register, spec2->is_register, "Error: 'register' keyword is used more than once.");
    combined->is_const = combine_flag(spec1->is_const, spec2->is_const, "Error: 'const' keyword is used more than once.");
    combined->is_volatile = combine_flag(spec1->is_volatile, spec2->is_volatile, "Error: 'volatile' keyword is used more than once.");
    return combined;
}

Identifier::Identifier(std::string name, unsigned int _line_num, unsigned int _column): type(new GlobalType()) { this->name = name; }

Identifier::Identifier(class GlobalType* type): type(type) { this->name = ""; }

std::unordered_map<PrimitiveTypes, StandardType*> type_specifiers = createStandardTypes();

StandardType::StandardType(): name(""), size(0), specifiers(new Specifiers()) {}

StandardType::StandardType(std::string name, size_t size): name(name), size(size) {}

bool StandardType::isEqual(const StandardType& obj) const { return name == obj.name && size == obj.size; }

std::string StandardType::getSpecifierName() const {
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
    if (specifiers->is_register) {
        st += "register ";
    }
    return st + name;
}

// ---------------------------- Struct Class Methods ---------------------

StructElement::StructElement(Identifier* id, size_t size): id(id), size(size) {}
StructElement::StructElement(size_t size) : id(new Identifier(new GlobalType())), size(size) {}

VectorStructElement::VectorStructElement(): elements(std::vector<StructElement>()) {}

void VectorStructElement::add_element(StructElement* element) {
    this->elements.push_back(*element);
}

void VectorStructElement::add_elements(VectorStructElement* other) {
    for (auto& element : other->elements) {
        this->elements.push_back(element);
    }
}

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

// --------------------------- Union Class Methods ---------------------------

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

// --------------------------- Array Class Methods ---------------------------

ArrayType::ArrayType(unsigned int dim, class GlobalType* type, std::vector<unsigned int> dims, std::string name): dim(dim), return_type(type), dims(dims) {
    this->name = name;
    int cnt = 1;
    for (auto& d : dims) {
        cnt *= d;
    }
    this->size = cnt * type->getSize();
}

ArrayType::ArrayType(): dim(0), return_type(nullptr), dims(std::vector<unsigned int>()) {};

// -------------------------- Function Class Methods --------------------------

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

FunctionType::FunctionType(class GlobalType* return_type, class VectorIdentifiers* args): return_type(return_type), args(*(args)) {}

size_t FunctionType::get_num_args() const {
    return args.identifiers.size();
}

// -------------------------- Pointer Class Methods --------------------------

PointerType::PointerType() {
    this->ptr_level = 1;
}

PointerType::PointerType(class GlobalType* return_type) {
    this->ptr_level = 1;
    this->return_type = return_type;
}

// -------------------------------- Enum Class Methods --------------------------

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

EnumType::EnumType(std::string name, VectorEnumElement* enum_values): StandardType("enum", sizeof(int)), enum_name(name), enum_values(*(enum_values)) {}

EnumType::EnumType(VectorEnumElement* enum_values): StandardType("enum", sizeof(int)), enum_name("Default"), enum_values(*(enum_values)) {}

EnumType::EnumType(std::string name): StandardType("enum", sizeof(int)), enum_name(name), enum_values(VectorEnumElement()) {}

// -------------------------- InvalidType Class Methods -------------------------

InvalidType::InvalidType(std::string _err_message, int _line_num, int _column): line_num(_line_num), column(_column), err_message(_err_message) {}

// -------------------------- GlobalType Class Methods -------------------------

GlobalType::GlobalType(): standard_type(nullptr), struct_type(nullptr), union_type(nullptr), array_type(nullptr), function_type(nullptr), pointer_type(nullptr), enum_type(nullptr), invalid_type(nullptr), type_tag(NONE) {};

GlobalType::~GlobalType() {
    if (standard_type != nullptr)
        delete standard_type;
    if (struct_type != nullptr)
        delete struct_type;
    if (union_type != nullptr)
        delete union_type;
    if (array_type != nullptr)
        delete array_type;
    if (function_type != nullptr)
        delete function_type;
    if (pointer_type != nullptr)
        delete pointer_type;
    if (enum_type != nullptr)
        delete enum_type;
    if (invalid_type != nullptr)
        delete invalid_type;
}

std::string GlobalType::getType() const {
    switch (type_tag) {
    case STANDARD_TYPE:
    {
        return "1 " + standard_type->getSpecifierName();
    }
    case STRUCT_TYPE:
        return struct_type->getSpecifierName();
    case UNION_TYPE:
        return union_type->getSpecifierName();
    case ARRAY_TYPE:
    {
        std::string st = "";

        for(auto i: array_type->dims) {
            st += "[" + ((i == 0) ? " " : std::to_string(i)) + "]";
        }

        return "Array: " + array_type->getSpecifierName() + array_type->return_type->getType() + st;
    }
    case FUNCTION_TYPE:
    {
        return "Function: " + function_type->getSpecifierName() + function_type->return_type->getType();
    }
    case POINTER_TYPE:
    {

        std::string st = "";
        for (int i = 0; i < pointer_type->ptr_level; i++) {
            st += "*";
        }
        return "2 " + st + pointer_type->getSpecifierName() + pointer_type->return_type->getType();
    }
    case ENUM_TYPE:
        return enum_type->getSpecifierName();
    case INVALID_TYPE:
        return "InvalidType";
    default:
        return "None";
    }
}

size_t GlobalType::getSize() const {
    switch (type_tag) {
    case STANDARD_TYPE:
        return standard_type ? standard_type->size : 0;
    case STRUCT_TYPE:
        return struct_type ? struct_type->size : 0;
    case UNION_TYPE:
        return union_type ? union_type->size : 0;
    case ARRAY_TYPE:
        return array_type ? array_type->size : 0;
    case FUNCTION_TYPE:
        return function_type ? function_type->size : 0;
    case POINTER_TYPE:
        return pointer_type ? pointer_type->size : 0;
    case ENUM_TYPE:
        return enum_type ? enum_type->size : 0;
    default:
        return 0;
    }
}

bool GlobalType::isEqual(const class GlobalType& obj) const {
    if (type_tag != obj.type_tag)
        return false;
    switch (type_tag) {
    case STANDARD_TYPE:
        return standard_type && obj.standard_type && *standard_type == *obj.standard_type;
    case STRUCT_TYPE:
        return struct_type && obj.struct_type && *struct_type == *obj.struct_type;
    case UNION_TYPE:
        return union_type && obj.union_type && *union_type == *obj.union_type;
    case ARRAY_TYPE:
        return array_type && obj.array_type && *array_type == *obj.array_type;
    case FUNCTION_TYPE:
        return function_type && obj.function_type && *function_type == *obj.function_type;
    case POINTER_TYPE:
        return pointer_type && obj.pointer_type && *pointer_type == *obj.pointer_type;
    case ENUM_TYPE:
        return enum_type && obj.enum_type && *enum_type == *obj.enum_type;
    default:
        return false;
    }
}

Specifiers* GlobalType::getSpecifiers() const {
    switch (type_tag) {
    case STANDARD_TYPE:
        return standard_type ? standard_type->specifiers : nullptr;
    case STRUCT_TYPE:
        return struct_type ? struct_type->specifiers : nullptr;
    case UNION_TYPE:
        return union_type ? union_type->specifiers : nullptr;
    case ARRAY_TYPE:
        return array_type ? array_type->specifiers : nullptr;
    case FUNCTION_TYPE:
        return function_type ? function_type->specifiers : nullptr;
    case POINTER_TYPE:
        return pointer_type ? pointer_type->specifiers : nullptr;
    case ENUM_TYPE:
        return enum_type ? enum_type->specifiers : nullptr;
    default:
        return nullptr;
    }
}

void GlobalType::setSpecifiers(Specifiers* specifiers) {
    switch (type_tag) {
    case STANDARD_TYPE:
    {
        if (specifiers->is_register) {
            std::cerr << "Error: Pointer cannot be defined with register keywords" << std::endl;
        }
        standard_type->specifiers = specifiers;
        break;
    }
    case STRUCT_TYPE:
    {
        if (specifiers->is_register) {
            std::cerr << "Error: Struct cannot be defined with register keywords" << std::endl;
        }
        struct_type->specifiers = specifiers;
        break;
    }
    case UNION_TYPE:
    {
        if (specifiers->is_extern || specifiers->is_static || specifiers->is_register) {
            std::cerr << "Error: Union cannot be defined with extern, static, volatile keywords" << std::endl;
        }
        union_type->specifiers = specifiers;
        break;
    }
    case ARRAY_TYPE:
    {
        if (specifiers->is_register) {
            std::cerr << "Error: Pointer cannot be defined with register keywords" << std::endl;
        }
        array_type->specifiers = specifiers;
        break;
    }
    case FUNCTION_TYPE:
    {
        if (specifiers->is_typedef || specifiers->is_register || specifiers->is_volatile) {
            std::cerr << "Error: Function cannot be defined with typedef, register, volatile keywords" << std::endl;
        }
        function_type->specifiers = specifiers;
        break;
    }
    case POINTER_TYPE:
    {
        if (specifiers->is_register) {
            std::cerr << "Error: Pointer cannot be defined with register, keywords" << std::endl;
        }
        pointer_type->specifiers = specifiers;
        break;
    }
    case ENUM_TYPE:
    {
        if (specifiers->is_const || specifiers->is_volatile || specifiers->is_extern || specifiers->is_static || specifiers->is_register) {
            std::cerr << "Error: Enum cannot be defined with const, volatile, extern, static, register keywords" << std::endl;
        }
        enum_type->specifiers = specifiers;
        break;
    }
    default:
        break;
    }
}

// -------------------------- GlobalType Functions -------------------------

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
    if (args == nullptr){
        args = new VectorIdentifiers();
    }
    type->function_type = new FunctionType(return_type, args);
    if (specifiers != nullptr) {
        type->function_type->specifiers = specifiers;
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

class GlobalType *create_array_type(class GlobalType* return_type) {
    class GlobalType* array = new GlobalType();
    array->array_type = new ArrayType();
    array->type_tag = ARRAY_TYPE;
    array->array_type->return_type = return_type;
    return array;
}

class GlobalType* create_default_array_type() {
    class GlobalType* array = new GlobalType();
    array->array_type = new ArrayType();
    array->type_tag = ARRAY_TYPE;
    array->array_type->return_type = new GlobalType();
    array->array_type->dims.push_back(0);

    return array;
}

class GlobalType* add_dimension_array(class GlobalType* array_type, int dimension) {
    if (array_type->type_tag != ARRAY_TYPE) {
        std::cerr << "Add dimension called to invalid type\n";
        return nullptr;
    }

    array_type->array_type->dim++;
    array_type->array_type->dims.push_back(dimension);

    return array_type;
}

class GlobalType* create_invalid_type(std::string err_message, int line_num, int column) {
    class GlobalType* type = new GlobalType();
    type->type_tag = INVALID_TYPE;
    type->invalid_type = new InvalidType(err_message, line_num, column);
    std::cerr << err_message << std::endl;
    return type;
}

unsigned int convert_to_unsigned(std::string input) {
    // Ensure the input is not empty and contains only digits
    if (input.empty() || input.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Error: Invalid input, not a valid unsigned integer (" << input << ")" << std::endl;
        return 0;
    }

    // Convert to unsigned integer
    size_t pos;
    unsigned long val = std::stoul(input, &pos, 10);

    // Ensure full conversion and range check
    if (pos != input.size() || val > std::numeric_limits<unsigned int>::max()) {
        std::cerr << "Error: Number out of range (" << input << ")" << std::endl;
        return 0;
    }

    return static_cast<unsigned int>(val);
}

int convert_to_signed(std::string input) {
    // Ensure the input is not empty and contains only digits or a leading '-'
    if (input.empty() || 
        (input[0] != '-' && input.find_first_not_of("0123456789") != std::string::npos) || 
        (input[0] == '-' && (input.size() == 1 || input.find_first_not_of("0123456789", 1) != std::string::npos))) {
        std::cerr << "Error: Invalid input, not a valid signed integer (" << input << ")" << std::endl;
        return 0;
    }

    // Convert to signed integer
    size_t pos;
    long val = std::stol(input, &pos, 10);

    // Ensure full conversion and range check
    if (pos != input.size() || val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max()) {
        std::cerr << "Error: Number out of range (" << input << ")" << std::endl;
        return 0;
    }

    return static_cast<int>(val);
}

class GlobalType* combine_global_type(class GlobalType* left, class GlobalType* right) {
    // IMPORTANT NOTE:
    // This function assumes that right always is either array type, function type or pointer type and has a none return type
    switch (right->type_tag) {
    case NONE:
    {
        return left;
    }
    case FUNCTION_TYPE:
    {
        right->function_type->return_type = (left->type_tag == NONE) ? new GlobalType() : left;
        break;
    }
    case ARRAY_TYPE:
    {
        right->array_type->return_type = (left->type_tag == NONE) ? new GlobalType() : left;
        break;
    }
    case POINTER_TYPE:
    {
        right->pointer_type->return_type = (left->type_tag == NONE) ? new GlobalType() : left;
        break;
    }
    default:
    {
        std::cerr << "Cannot combine these two types\n";
        break;
    }
    }

    return right;
}