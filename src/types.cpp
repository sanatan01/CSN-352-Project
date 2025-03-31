#include <string>
#include <map>
#include <assert.h>
#include <types.hpp>

extern std::unordered_map<PrimitiveTypes, StandardType> type_specifiers=createStandardTypes();
// Creates unordered map of standard types that can be accessed in O(1) time
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

StandardType::StandardType() : name(""), size(0) {}

StandardType::StandardType(std::string name, size_t size) : name(name), size(size) {}

bool StandardType::isEqual(const StandardType &obj) const {
    return name == obj.name && size == obj.size;
}

StructDefinition::StructDefinition() : recursive(false) {}

size_t StructDefinition::get_offset( Identifier *id ) {
    size_t offset = 0;
    for (auto &member : members) {
        if (member.first == id->name) {
            return offset;
        }
        offset += member.second.getSize();
    }
    return 0;
}

GlobalType *StructDefinition::get_member( Identifier *id ) {
    for (auto &member : members) {
        if (member.first == id->name) {
            return &member.second;
        }
    }
    return nullptr;
}

Struct::Struct(std::string name) : StandardType(name, 0), definition(nullptr) {}

Struct *create_struct( StructDeclarationList *sdl ) {

    StructDefinition *sd = new StructDefinition();
	size_t offset = 0;

    for ( auto it = sdl->struct_declaration_list.begin(); it != sdl->struct_declaration_list.end(); it++ ) {
        GlobalType* dec_type = ( *it )->sq_list->type;
        bool is_const = ( *it )->sq_list->is_const;

        std::vector<Declarator *> dl = ( *it )->declarator_list->declarator_list;

        for ( auto jt = dl.begin(); jt != dl.end(); jt++ ) {
            int pointer_level = ( *jt )->get_pointer_level();
            DirectDeclarator *dd = ( *jt )->direct_declarator;
            GlobalType type;

            if ( dd->type == STANDARD ) {
                type.standard_type = dec_type->standard_type;

            } else if ( dd->type == ARRAY ) {
                type.array_type = new ArrayType( dd->array_dims.size(), dec_type, dd->array_dims, dd->id->value );

            } else if ( dd->type == FUNCTION ) {
                error_msg("Function cannot be member of struct/union", ( *jt )->id->line_num, ( *jt )->id->column );
                continue;

            }
            sd->members.insert( {( *jt )->id->value, type} );
        }
    }
    
    return new Struct(sd);
}

UnionDefinition::UnionDefinition() {}

GlobalType *UnionDefinition::get_member( Identifier *id ) {
    for (auto &member : members) {
        if (member.first == id->name) {
            return &member.second;
        }
    }
    return nullptr;
}

Union::Union(std::string name) : StandardType(name, 0), definition(nullptr) {}

Union *create_union( UnionDeclarationList *udl ) {
    UnionDefinition *ud = new UnionDefinition();

    for ( auto it = udl->union_declaration_list.begin(); it != udl->union_declaration_list.end(); it++ ) {
        GlobalType* dec_type = ( *it )->sq_list->type;
        bool is_const = ( *it )->sq_list->is_const;

        std::vector<Declarator *> dl =
            ( *it )->declarator_list->declarator_list;

        for ( auto jt = dl.begin(); jt != dl.end(); jt++ ) {
            int pointer_level = ( *jt )->get_pointer_level();
            DirectDeclarator *dd = ( *jt )->direct_declarator;
            GlobalType type;

            if ( dd->type == STANDARD ) {
                type.standard_type = dec_type->standard_type;

            } else if ( dd->type == ARRAY ) {
                type.array_type = new ArrayType( dd->array_dims.size(), dec_type, dd->array_dims, dd->id->value );
        
            } else if ( dd->type == FUNCTION ) {
                error_msg( "Function cannot be member of struct/union", ( *jt )->id->line_num, ( *jt )->id->column );
                continue;
            }

            ud->members.insert( {( *jt )->id->value, type} );
        }
    }
    return new Union(ud);
}

ArrayType::ArrayType( unsigned int dim, GlobalType *type, std::vector<unsigned int> dims, std::string name) : dim(dim), return_type(type), dims(dims) {
    this->name = name;
    int cnt = 1;
    for (auto &d : dims) {
        cnt *= d;
    }
    this->size = cnt * type->getSize();
}

FunctionType::FunctionType( unsigned int num_args, std::unordered_map<std::string, GlobalType> args, std::string name ) : num_args(num_args), args(args), is_defined(false) {
    this->name = name;
}

PointerType::PointerType( GlobalType *type, std::string name) : type(type), ptr_level(1) {
    this->name = name;
}

InvalidType::InvalidType(int _line_num, int _column, std::string _err_message) : line_num(_line_num), column(_column), err_message(_err_message) {}

std::vector<GlobalType> defined_types;

int add_to_defined_types( GlobalType *typ ) {
    for ( int i = 0; i < defined_types.size(); i++ ) {
        if ( defined_types[i].isEqual( *typ ) ) {
            return i;
        }
    }
    defined_types.push_back( *typ );
    return defined_types.size() - 1;
}

