#include <expression.h>
#include <cassert>
#include <initializer_list>

int line_num = 0, column = 0;

void error_msg(std::string msg, int line_num = 0, int column = 0) {
    std::cerr << "Error: " << msg << " at line " << line_num << ", column " << column << std::endl;
}

void warning_msg(std::string msg, int line_num = 0, int column = 0) {
    std::cerr << "Warning: " << msg << " at line " << line_num << ", column " << column << std::endl;
}

Expression::Expression(PrimitiveTypes type, int num_operands): prim_type(static_cast<int>(type)), num_operands(num_operands), exp_type(create_primitive_type(type)) {};
Expression::Expression(): prim_type(static_cast<int>(ERROR_T)), num_operands(0), exp_type(create_invalid_type("Invalid expression", line_num, column)) {};

bool isInt(PrimitiveTypes op) {
    return (op > -1 && op < 10);
}

bool isFloat(PrimitiveTypes op) {
    return (op >= 10 && op < 13);
}

std::unordered_map<std::string, PrimitiveTypes> type_map = {
    {"unsigned char", U_CHAR_T},
    {"char", CHAR_T},
    {"unsigned short", U_SHORT_T},
    {"short", SHORT_T},
    {"unsigned int", U_INT_T},
    {"int", INT_T},
    {"unsigned long", U_LONG_T},
    {"long", LONG_T},
    {"long long", LLONG_T},
    {"unsigned long long", U_LLONG_T},
    {"float", FLOAT_T},
    {"double", DOUBLE_T},
    {"long double", LONG_DOUBLE_T},
    {"void", VOID_T},
    {"error", ERROR_T},
    {"bool", BOOL_T}
  };

// void castTypes(PrimitiveTypes& op1, PrimitiveTypes& op2) {
//     if (op1 != op2) {
//         if (op1 == VOID_T || op2 == VOID_T || op1 == ERROR_T || op2 == ERROR_T) {
//             error_msg("Invalid types for operation", line_num, column);
//             op1 = ERROR_T;
//             op2 = ERROR_T;
//             return;
//         }
//         if (op1 == BOOL_T) {
//             op1 = op2;
//             return;
//         }
//         if (op2 == BOOL_T) {
//             op2 = op1;
//             return;
//         }
//         // Cast to the larger type based on enum order
//         // The enum is in sorted order of size, so higher enum value = larger type
//         if (op1 > op2) {
//             // op1 is larger, cast op2 to op1's type
//             op2 = op1;
//         }
//         else {
//             // op2 is larger, cast op1 to op2's type
//             op1 = op2;
//         }
//     }
// }

void make_signed(PrimitiveTypes& op) {

    if (op % 2 == 0 && op < 10 && op > -1) {
        op = static_cast<PrimitiveTypes>(static_cast<int>(op) + 1);
    }
}

void make_unsigned(PrimitiveTypes& op) {

    if (op % 2 && op <10 && op >-1) {
        op = static_cast<PrimitiveTypes>(static_cast<int>(op) - 1);
    }
}

bool isUnsigned(PrimitiveTypes op) {
    if (op % 2 == 0 && op <10 && op > -1) {
        return true;
    }

    if (op >= 10 && op < 14) {
        return true;
    }

    return false;
}

bool isInvalid(std::initializer_list<PrimitiveTypes> ops) {
    bool result = false;
    for (PrimitiveTypes op : ops) {
        result = result || (op == ERROR_T);
    }
    return result;
}

// PrimaryExpression::PrimaryExpression(): Expression(PrimitiveTypes(ERROR_T), 0) {}


// Expression* create_primary_expression(ExpressionType* typ) {
//     PrimaryExpression* pe = new PrimaryExpression();
//     pe->prim_type = *typ;
//     return pe;
// }

ArgumentExprList::ArgumentExprList(): Expression() {}

// TODO: Implement this
ArgumentExprList* create_argument_expr_assignement(Expression* ase) {
    ArgumentExprList* ae_list = new ArgumentExprList();
    ae_list->args.push_back(ase);
    // ArgumentExprList does not have any type as it is a composite entity
    // ae_list->name = "arguments";
    // ae_list->add_children({ase});
    return ae_list;
}

ArgumentExprList* create_argument_expr_list(ArgumentExprList* ae_list, Expression* ase) {
    ae_list->args.push_back(ase);
    // ArgumentExprList does not have any type as it is a composite entity
    // ae_list->name = "arguments";
    // ae_list->add_children({ase});
    return ae_list;
}


Expression* multiplicative_expression(OpExpression* oe) {

    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);


    if (oe->op2.exp_type->type_tag == STANDARD_TYPE && oe->op1.exp_type->type_tag == STANDARD_TYPE && isInvalid({ op1Type, op2Type }) || op1Type == VOID_T || op2Type == VOID_T) {
        error_msg("Invalid types for multiplication" + oe->op, line_num, column);
        oe->prim_type = ERROR_T;
        return oe;
    }

    if (oe->op == "*" || oe->op == "/") {
        bool op1Unsigned = isUnsigned(op1Type);
        bool op2Unsigned = isUnsigned(op2Type);

        if (!op1Unsigned && !op2Unsigned) {
            // Both are signed
            ;
        }
        else if (op1Unsigned && op2Unsigned) {
            // Both are unsigned integers
            oe->op += "u";
        }
        else if (!op1Unsigned && op2Unsigned) {
            // make op1 unsigned
            oe->op += "u";
        }
        else if (op1Unsigned && !op2Unsigned) {
            // make op2 unsigned
            oe->op += "u";
        }

        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        if (isUnsigned(op1Type) || isUnsigned(op2Type)) {
            PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
            make_unsigned(tmp);
            oe->prim_type = tmp;
        }
        // add 3AC code
    }
    else if (oe->op == "%") {

        if (!isInt(op1Type) || !isInt(op2Type)) {
            error_msg("Invalid types for modulo" + oe->op, line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        oe->prim_type = op1Type;
        PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
        make_unsigned(tmp);
        oe->prim_type = tmp;
        // make it unsigned

        // add 3AC code
    }
    else {
        // Code should not reach here
        assert(0);
    }

    // oe->name = "multiplicative_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &PrimitiveTypes(oe->op2.prim_type)});
    return oe;
}

Expression* additive_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (oe->op2.exp_type->type_tag == STANDARD_TYPE && oe->op1.exp_type->type_tag == STANDARD_TYPE && isInvalid({ op1Type, op2Type })) {
        error_msg("Invalid types for addition/subtraction " + oe->op, line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (isInt(op1Type) && isInt(op2Type)) {

        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
        make_unsigned(tmp);
        oe->prim_type = tmp;
        // 3AC code would be added here
    }
    else if (isFloat(op1Type) && isFloat(op2Type)) {
        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        // 3AC code would be added here
    }
    else if ((isFloat(op1Type) && isInt(op2Type)) || (isInt(op1Type) && isFloat(op2Type))) {
        oe->op += "f";
        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        // 3AC code would be added here
    }
    else if (oe->op1.exp_type->type_tag == POINTER_TYPE && isInt(op2Type)) {
        //TODO
        oe->prim_type = ERROR_T;
        oe->exp_type = oe->op1.exp_type;

        // 3AC code for pointer + int would be added here
    }
    else if (oe->op2.exp_type->type_tag == POINTER_TYPE && isInt(op1Type)) {
        //TODO
        oe->prim_type = ERROR_T;
        oe->exp_type = oe->op2.exp_type;
        // 3AC code for int + pointer would be added here
    }
    else {
        error_msg("Invalid types for addition/subtraction " + oe->op, line_num, column);
        oe->prim_type = ERROR_T;
        return oe;
    }

    // oe->name = "additive_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    return oe;
}

Expression* relational_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for relational operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<" || oe->op == ">" || oe->op == "<=" || oe->op == ">=") {
        // Check if both operands are numeric
        if (op1Type != VOID_T && op2Type != VOID_T && op1Type != ERROR_T && op2Type != ERROR_T) {
            oe->prim_type = PrimitiveTypes(BOOL_T);

            // Add warning for signed/unsigned mismatch
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);
            if (op1Unsigned != op2Unsigned) {
                warning_msg("Comparison " + oe->op + " between signed and unsigned values", line_num, column);
            }

            // 3AC code would be added here
        }
    }
    else {
        std::cerr << "Incorrect relation expression. Something went wrong\n";
    }

    // oe->name = "relational_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* shift_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for shift operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<<" || oe->op == ">>") {
        if (isInt(op1Type) && isInt(op2Type)) {
            oe->prim_type = op1Type;

            // If first operand is unsigned, mark operation as unsigned
            if (isUnsigned(op1Type)) {
                oe->op += "u";
            }
        }
        else {
            error_msg("Invalid types for shift operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }

    }
    else {
        // This should not happen
        std::cerr << "Incorrect shift expression. Something went wrong\n";
    }

    // oe->name = "shift_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* equality_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({ op1Type, op2Type })) {
        error_msg("Invalid types for equality operation " + oe->op, line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (oe->op == "==" || oe->op == "!=") {
        // Handle pointer comparisons
        if (oe->op1.exp_type->type_tag == POINTER_TYPE && oe->op2.exp_type->type_tag == POINTER_TYPE) {
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else if ((oe->op1.exp_type->type_tag == STANDARD_TYPE && oe->op2.exp_type->type_tag == STANDARD_TYPE)
                 && (isInt(op1Type) || isFloat(op1Type))
                 && (isInt(op2Type) || isFloat(op2Type))) {

            oe->prim_type = PrimitiveTypes(BOOL_T);

            // Add warning for signed/unsigned mismatch
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);
            if (op1Unsigned != op2Unsigned) {
                warning_msg("Comparison " + oe->op + " between signed and unsigned values", line_num, column);
            }
        }
        else {
            error_msg("Invalid types for equality operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else {
        std::cerr << "Incorrect equality expression. Something went wrong\n";
    }

    // oe->name = "equality_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* and_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for bitwise AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&") {
        if (isInt(op1Type) && isInt(op2Type)) {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned)) {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else {
            error_msg("Invalid types for bitwise AND operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else {
        std::cerr << "Incorrect and_expression. Something went wrong\n";
    }

    // oe->name = "and_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* xor_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({ op1Type, op2Type })) {
        error_msg("Invalid types for exclusive OR operation", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (oe->op == "^") {
        if (isInt(op1Type) && isInt(op2Type)) {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned)) {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else {
            error_msg("Invalid types for bitwise XOR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else {
        std::cerr << "Incorrect exclusive or expression. Something went wrong\n";
    }

    // oe->name = "exclusive_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* or_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for bitwise OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "|") {
        if (isInt(op1Type) && isInt(op2Type)) {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned)) {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else {
            error_msg("Invalid types for bitwise OR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else {
        std::cerr << "Incorrect inclusive or expression. Something went wrong\n";
    }

    // oe->name = "inclusive_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    return oe;
}

// utils
Expression* logical_and_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for logical AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&&") {
        if (isInt(op1Type) && isInt(op2Type)) {
            // Result type is boolean
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else {
            error_msg("Invalid types for logical AND operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }

    }
    else {
        std::cerr << "Incorrect logical AND expression. Something went wrong\n";
    }

    // oe->name = "logical_and_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    // append(oe->truelist, PrimitiveTypes(oe->op2.prim_type).truelist);
    // append(oe->falselist, PrimitiveTypes(oe->op1.prim_type).falselist);
    // append(oe->falselist, PrimitiveTypes(oe->op2.prim_type).falselist);

    return oe;
}

// utils
Expression* logical_or_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for logical OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "||") {
        if (isInt(op1Type) && isInt(op2Type)) {
            // Result type is boolean
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else {
            error_msg("Invalid types for logical OR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else {
        std::cerr << "Incorrect logical OR expression. Something went wrong\n";
    }

    // oe->name = "logical_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), n_op, &PrimitiveTypes(oe->op2.prim_type)});
    // 3AC code would be added here
    // append(oe->truelist, PrimitiveTypes(oe->op1.prim_type).truelist);
    // append(oe->truelist, PrimitiveTypes(oe->op2.prim_type).truelist);
    // append(oe->falselist, PrimitiveTypes(oe->op2.prim_type).falselist);

    return oe;
}

bool isCompatiblePrim(PrimitiveTypes p1, PrimitiveTypes p2){
    if((isInt(p1)||isFloat(p1)) && (isInt(p2)||isFloat(p2))){
        return true;
    }
    if(p1==ERROR_T || p2==ERROR_T){
        return false;
    }
    return p1 == p2;
}



bool isCompatible(GlobalType* op1, GlobalType* op2){
    if(op1->type_tag == STANDARD_TYPE && op2->type_tag == STANDARD_TYPE){
        return isCompatiblePrim(type_map[op1->standard_type->name],type_map[op2->standard_type->name]);
    }
    else if(op1->type_tag != op2->type_tag){
        return false;
    }
    else{
        if(op1->type_tag== FUNCTION_TYPE){
            return isCompatible(op1->function_type->return_type,op2->function_type->return_type);
        }
        else if(op1->type_tag== POINTER_TYPE){
            if(op1->pointer_type->ptr_level != op2->pointer_type->ptr_level){
                return false;
            }
            return isCompatible(op1->pointer_type->return_type,op2->pointer_type->return_type);
        }
        else if(op1->type_tag== ARRAY_TYPE){
            return false;
        }
        else if(op1->type_tag== ENUM_TYPE){
            return true;
        }
        else if(op1->type_tag== STRUCT_TYPE){
            return op1->struct_type->struct_name == op2->struct_type->struct_name;
        }
        else if(op1->type_tag == UNION_TYPE){
            return op1->union_type->union_name == op2->union_type->union_name;
        }
        else if(op1->type_tag == INVALID_TYPE){
            return true;
        }
    }
    return false;
}

// utils
Expression* conditional_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    PrimitiveTypes op3Type = PrimitiveTypes(oe->op3.prim_type);

    if (isInvalid({ op1Type})) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for conditional expression", line_num, column);
        return oe;
    }
    if((op2Type== ERROR_T && op3Type!=ERROR_T) || (op3Type==ERROR_T && op2Type!=ERROR_T)) {
        error_msg("Invalid types for conditional expression", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;         
    }

    // check: TODO
    // Check if condition is an integer
    // if (type_specifiers[INT_T].isEqual(*op1Type.standard_type))
    if (isInt(op1Type)) {
        // Check if true and false expressions have compatible types
        if (op2Type==ERROR_T && op3Type==ERROR_T && !isCompatible(oe->op2.exp_type,oe->op3.exp_type)) {
            error_msg("Types mismatch for conditional expression", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
        else if(op2Type==ERROR_T && op3Type==ERROR_T && isCompatible(oe->op2.exp_type,oe->op3.exp_type)){
            oe->prim_type=PrimitiveTypes(ERROR_T);
            oe->exp_type= oe->op1.exp_type;
        }
        else if((isInt(op2Type)||isFloat(op2Type))&&(isInt(op3Type)||isFloat(op3Type))){
            oe->prim_type = op2Type > op3Type ? op2Type : op3Type;
            if(!(isUnsigned(op2Type)&& isUnsigned(op3Type))){
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }
        }
        else if(op2Type == op3Type){
            oe->prim_type= op1Type;
        }
        else{
            error_msg("Types mismatch for conditional expression", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    } else {
        error_msg("Comparison expression is not an int", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    // oe->name = "conditional_expression";
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), &PrimitiveTypes(oe->op2.prim_type), &oe->op3});

    return oe;
}

// utils : TODO
Expression* constant_expression(OpExpression* oe) {
    return oe;
}

// utils
Expression* toplevel_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({ op1Type, op2Type })) {
        error_msg("Invalid types for toplevel expression", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    //////need TO DO LATER///////////

    // oe->name = "toplevel_expression";
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), &PrimitiveTypes(oe->op2.prim_type)});
    return oe;
}

// was using Node *n_op, not known why?
Expression* assignment_expression(OpExpression* oe) {
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    // Terminal *op = (Terminal *)n_op;
    // TODO:
    // oe->op = op->name;

    if (isInvalid({ op1Type, op2Type })) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for assignment expression", line_num, column);
        return oe;
    }

    // check if op1 is a contant expression then it cannot be assigned to anything
    if (op1Type == PrimitiveTypes(CONSTANT)) {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Cannot assign to a constant", line_num, column);
        return oe;
    }

    if (oe->op == "=") {
        // Simple assignment
        // additional checking needed for checking complex types;
        if (isInt(op1Type) && isInt(op2Type)) {
            // Integer or float assignment
            if (op1Type != op2Type) {
                warning_msg("Assignment between different types:" + typeName(op1Type) + "and" + typeName(op2Type), line_num, column);
            }
            oe->prim_type = op1Type;
        }
        else if (oe->op1.exp_type->type_tag == POINTER_TYPE && oe->op2.exp_type->type_tag == POINTER_TYPE) {
            // Pointer assignment
            //  TODO: how to do level check
            PrimitiveTypes p1 = static_cast<PrimitiveTypes>(oe->op1.exp_type->pointer_type->return_type->type_tag);
            PrimitiveTypes p2 = static_cast<PrimitiveTypes>(oe->op2.exp_type->pointer_type->return_type->type_tag);
            int p1_ptr_level = oe->op1.exp_type->pointer_type->ptr_level;
            int p2_ptr_level = oe->op2.exp_type->pointer_type->ptr_level;
            if (p2 != VOID_T && (p1 != p2 || p1_ptr_level != p2_ptr_level)) {
                warning_msg("Assignment between different pointer types", line_num, column);
            }
            oe->prim_type = p1;
        }
        // 3AC code would be added here
    }
    else if (oe->op == "+=" || oe->op == "-=") {
        // Addition/subtraction assignment
        if ((isInt(op1Type) || isFloat(op1Type)) &&
            (isInt(op2Type) || isFloat(op2Type))) {
            if (op1Type != op2Type) {
                warning_msg("Assignment between different types", line_num, column);
            }
            oe->prim_type = op1Type;
        }
        else if (oe->op1.exp_type->type_tag == POINTER_TYPE && op2Type == INT_T) {
            // Pointer arithmetic assignment
            oe->prim_type = op1Type;
        }
    }
    else if (oe->op == "*=" || oe->op == "/=" || oe->op == "%=") {
        // Multiplicative assignment
        if (oe->op == "%=" && !isInt(op1Type) && !isInt(op2Type)) {
            error_msg("Modulo operation requires integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        else if (isInt(op1Type) && isInt(op2Type)) {
            if (op1Type != op2Type) {
                warning_msg("Assignment between different types:" + typeName(op1Type) + "and" + typeName(op2Type), line_num, column);
            }
            oe->prim_type = op1Type;
        }
        else {
            error_msg("Invalid operands for " + oe->op, line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "<<=" || oe->op == ">>=") {
        // Bitshift assignment
        if (isInt(op1Type) && isInt(op2Type)) {
            oe->prim_type = op1Type;
        }
        else {
            error_msg("Shift operations require integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "&=" || oe->op == "|=" || oe->op == "^=") {
        // Bitwise operations assignment
        if (isInt(op1Type) && isInt(op2Type)) {
            oe->prim_type = op1Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned)) {
                // As safety, we upgrade unsigned to signed
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }
        }
        else {
            error_msg("Bitwise operations require integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        // 3AC code would be added here
    }
    else {
        std::cerr << "Incorrect assignment expression. Something went wrong\n";
    }

    //     oe->name = "assignment_expression";
    //     oe->add_children({&PrimitiveTypes(oe->op1.prim_type), &PrimitiveTypes(oe->op2.prim_type)});
    return oe;
}

// Expression *create_unary_expression(Terminal * op, Expression *ue)
// {
//    UnaryExpression *U = new UnaryExpression();
//     U->op1 = ue;
//     U->op = op->name;
//     GlobalType ueT = ue->prim_type;
//     if ( ueT.getType() == "InvalidType" ) {
//         U->prim_type.invalid_type = &INVALID_TYPE;
//         return U;
//     }
//     std::string u_op = op->name;
//     U->name = u_op;

//     if ( u_op == "++" || u_op == "--" ) {
//         // check if constant
//         // if ( ueT.is_const == true ) {
//         //     error_msg( "Invalid operand " + u_op + " with constant type",
//         //                op->line_num, op->column );
//         //     U->prim_type.invalid_type = &INVALID_TYPE;
//         //     return U;
//         // }
// 		u_op = u_op.substr( 0, 1 );
// 		if ( ue->prim_type.getType() == "Pointer" ) {
// 			U->prim_type = ue->prim_type;
// 		} else if ( type_specifiers[INT_T].isEqual(*ue->prim_type.standard_type) ) {
// 			U->prim_type = ue->prim_type;
// 		} else if ( type_specifiers[FLOAT_T].isEqual(*ue->prim_type.standard_type) ) {
//             U->prim_type = ue->prim_type;
// 		} else {
// 			// Incorrect type throw error
// 			error_msg( "Invalid operand " + u_op + "with type " +
// 						   ue->prim_type.getType(),
// 					   op->line_num, op->column );
// 			U->prim_type.invalid_type = &INVALID_TYPE;
// 			return U;
// 		}
//     } else if ( u_op == "sizeof" ) {
//         U->name = "sizeof";
//         U->prim_type.standard_type = &type_specifiers[INT_T];
//         // TODO: make it const
//         // U->prim_type.is_const = true;
//     } else {
//         // Raise Error
//         std::cerr << "Error parsing Unary Expression.\n";
//         std::cerr << "ERROR at line " << line_num << "\n";
//         exit( 0 );
//     }
//     U->add_children({ue});
//     return U;
// }

// // & (int) (x)
// // &(x) -> pointer value of x
// Expression *create_unary_expression_cast(Node *n_op, Expression *ce)
// {
//     UnaryExpression *U = new UnaryExpression();
//     Terminal *t_op = dynamic_cast<Terminal *>( n_op );
//     std::string u_op = t_op->name;
//     U->op = u_op;
//     U->op1 = ce;
//     GlobalType ceT = ce->prim_type;

//     if ( ceT.getType() == "InvalidType" ) {
//         U->prim_type.invalid_type = &INVALID_TYPE;
//         return U;
//     }

//     if ( u_op == "&" ) {
//         if ( ceT.getType() == "FunctionType" ) {
//             error_msg( "lvalue required as unary & operand", n_op->line_num,
//                        n_op->column );
//             U->prim_type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->prim_type = ce->prim_type;
//         U->prim_type.pointer_type->ptr_level++;
//     } else if ( u_op == "*" ) {
//         if ( ceT.getType() == "ArrayType" ) {
//             // Error because of dereference of non-pointer type
//             error_msg( "Cannot dereference type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->prim_type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->prim_type = ce->prim_type;
// 		U->prim_type.pointer_type->ptr_level--;

//     } else if ( u_op == "-" || u_op == "+" ) {
//         if (type_specifiers[INT_T].isEqual(*ceT.standard_type) || type_specifiers[FLOAT_T].isEqual(*ceT.standard_type)) {
//             // Throw Error
//             error_msg( "Invalid operand " + u_op + " on type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->prim_type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->prim_type = ce->prim_type;
// 		U->prim_type.make_signed();

//     } else if ( u_op == "!" ) {
//         if ( !type_specifiers[INT_T].isEqual(*ceT.standard_type) ) {
//             // Throw Error
//             error_msg( "Invalid operand " + u_op + " on type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->prim_type.invalid_type = &INVALID_TYPE;
//             return U;
//         }
//         U->prim_type.standard_type = &type_specifiers[U_CHAR_T];
// 		U->truelist = ce->falselist;
// 		U->falselist = ce->truelist;
//     } else {
//         // Throw Error
//         std::cerr << "Parse error, invalid unary operator\n";
//         std::cerr << "ERROR at line " << line_num << "\n";
//         exit( 0 );
//     }

//     U->name = "unary_expression";
//     U->add_children({n_op, ce});
//     return U;
// }

// Expression *create_unary_expression(Terminal *op, TypeName *t_name )
// {
//     UnaryExpression *U = new UnaryExpression();
//     std::string u_op = op->name;
//     U->name = u_op;
//     U->add_children({op, t_name});
//     U->prim_type.standard_type = &type_specifiers[INT_T];

//     return U;
// }

// Expression *create_cast_expression_typename(TypeName *tn, Expression *ce)
// {
//     CastExpression *P = new CastExpression();
//     P->op1 = ce;
//     GlobalType ceT = ce->prim_type;
//     GlobalType tnT = tn->prim_type;
//     if ( ceT.getType() == "InvalidType" || tnT.getType() == "InvalidType" ) {
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }
//     if ( (type_specifiers[INT_T].isEqual(*ceT.standard_type) || type_specifiers[FLOAT_T].isEqual(*ceT.standard_type)) && (type_specifiers[INT_T].isEqual(*tnT.standard_type) || type_specifiers[FLOAT_T].isEqual(*tnT.standard_type)) ) {
//         P->prim_type = tn->prim_type;
//     } else if ( ceT.pointer_type->ptr_level > 0 && tnT.pointer_type->ptr_level > 0 ) {
//         P->prim_type = tn->prim_type;
//     } else {
//         error_msg( "Undefined casting operation of " + ceT.getType() +
//                        " into " + tnT.getType(),
//                    line_num );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }
//     P->name = "cast_expression";
//     P->add_children({tn, ce});

//     return P;
// }

// Expression *create_postfix_expr_arr(Expression *pe, Expression *exp)
// {
//  PostfixExpression *P = new PostfixExpression();
//     if ( dynamic_cast<PostfixExpression *>( pe ) ) {
//         P->pe = dynamic_cast<PostfixExpression *>( pe );
//     } else {
//         P->pe = nullptr;
//     }
//     P->exp = exp;
//     P->name = "ARRAY ACCESS";

//     if ( pe->prim_type.getType() == "InvalidType" || exp->prim_type.getType() == "InvalidType" ) {
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     if ( !type_specifiers[INT_T].isEqual(*exp->prim_type.standard_type) ) {
//         // Error
//         error_msg( "Array index must be of type integer", line_num );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

// 	if ( pe->prim_type.getType() == "ArrayType" ) {
// 		P->prim_type = pe->prim_type;
// 		P->prim_type.array_type->dim--;
// 		P->prim_type.array_type->dims.erase( P->prim_type.array_type->dims.begin() );
// 		// P->prim_type.is_const = false; //TODO: make it non-constant
// 	} else if ( pe->prim_type.getType() == "PointerType" ) {
// 		P->prim_type = pe->prim_type;
// 		P->prim_type.pointer_type->ptr_level--;
// 		// P->prim_type.is_const = false; //TODO: make it non-constant
//         // TODO: What type to update to?
// 		// if ( P->prim_type.pointer_type->ptr_level == 0 ) {
// 			// P->prim_type.pointer_type->is_pointer = false;
// 		// }
// 	} else {
// 		error_msg( "Subscripted value is neither array nor pointer",
// 				   line_num );
// 		P->prim_type.invalid_type = &INVALID_TYPE;
// 	}

//     P->add_children({pe, exp});
//     P->line_num = pe->line_num;
//     P->column = pe->column;
//     return P;
// }

// // check its implementation
// Expression *create_postfix_expr_voidfun(Identifier *fi)
// {
//     PostfixExpression *P = new PostfixExpression();
//     // Lookup Function type from symbol table - should be void
//     SymTabEntry *ste = global_symbol_table.get_symbol_from_table( fi->value );
//     if ( ste == nullptr ) {
//         // Error
//         error_msg( "Undeclared symbol " + fi->value, fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.getType() != "FunctionType" ) {
//         // Error
//         error_msg( "Called object '" + fi->value + "' is not a function",
//                    fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.function_type->num_args != 0 ) {
//         // Error
//         error_msg( "Too few arguments to function '" + fi->value + "'",
//                    fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     P->name = "FUNCTION CALL";
//     P->add_children({fi});
//     P->line_num = fi->line_num;
//     P->column = fi->column;

//     P->prim_type = ste->prim_type;
//     P->prim_type.function_type->is_defined = false;
//     P->prim_type.function_type->num_args = 0;
//     P->prim_type.function_type->args.clear();

//     return P;
// }

// Expression *create_postfix_expr_fun( Identifier *fi, ArgumentExprList *ae )
// {
//    PostfixExpression *P = new PostfixExpression();

//     SymTabEntry *ste = global_symbol_table.get_symbol_from_table( fi->value );
//     if ( ste == nullptr ) {
//         // Error
//         error_msg( "Undeclared symbol " + fi->value, fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.getType() != "FunctionType" ) {
//         // Error
//         error_msg( "Called object '" + fi->value + "' is not a function",
//                    fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.function_type->num_args > ae->args.size() ) {
//         // Error
//         error_msg( "Too few arguments to function '" + fi->value +
//                        "'. Expected " + std::to_string( ste->prim_type.function_type->num_args ) +
//                        ", got " + std::to_string( ae->args.size() ),
//                    fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.function_type->num_args < ae->args.size() ) {
//         // Error
//         error_msg( "Too many arguments to function '" + fi->value +
//                        "'. Expected " + std::to_string( ste->prim_type.function_type->num_args ) +
//                        ", got " + std::to_string( ae->args.size() ),
//                    fi->line_num, fi->column );
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->prim_type.function_type->num_args == ae->args.size() ) {
//         int i = 0;
//         for (auto itr: ste->prim_type.function_type->args) {
//             if ( itr.second.getType() == "InvalidType" ) {
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             if ( !( itr.second.isEqual(ae->args[i]->prim_type) ) ) {
//                 error_msg( "Type mismatch at argument " + std::to_string( i ) +
//                                " of function '" + fi->value + "'. Expected " +
//                                itr.second.getType() + ", got " +
//                                ae->args[i]->prim_type.getType(),
//                            fi->line_num, fi->column );
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             i++;
//         }
//     }

//     P->name = "FUNCTION CALL";
//     P->add_children({fi, ae});
//     P->line_num = fi->line_num;
//     P->column = fi->column;
//     P->prim_type = ste->prim_type;
//     P->prim_type.function_type->is_defined = false;
//     P->prim_type.function_type->num_args = 0;
//     P->prim_type.function_type->args.clear();

//     return P;
// }

// Expression *create_postfix_expr_struct( std::string access_op, Expression *pe, Identifier *id){
//     PostfixExpression *P = new PostfixExpression();

//     if ( pe->prim_type.getType() == "InvalidType" ) {
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     GlobalType peT = pe->prim_type;
//     if ( access_op == "." ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->prim_type.pointer_type->ptr_level == 0 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " +
//                                pe->prim_type.getType(),
//                            id->line_num, id->column );
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             // whether i exists in Struct
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType == nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             } else {
//                 P->prim_type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand . with type " + pe->prim_type.getType(), id->line_num,
//                        id->column );
//             P->prim_type.invalid_type = &INVALID_TYPE;
//             return P;
//         }
//     } else if ( access_op == "->" ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->prim_type.pointer_type->ptr_level == 1 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             // whether i exists in Struct*
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType==nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type.invalid_type = &INVALID_TYPE;
//                 return P;
//             } else {
//                 P->prim_type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand -> with type " + pe->prim_type.getType(),
//                        id->line_num, id->column );
//             P->prim_type.invalid_type = &INVALID_TYPE;
//             return P;
//         }
//     }

//     P->name = access_op;
//     P->add_children({pe, id});
//     return P;
// }

// Expression *create_postfix_expr_ido(Terminal *op, Expression *pe){

//     PostfixExpression *P = new PostfixExpression();
//     if ( dynamic_cast<PostfixExpression *>( pe ) ) {
//         P->pe = dynamic_cast<PostfixExpression *>( pe );
//     } else {
//         P->pe = nullptr;
//     }

//     if ( pe->prim_type.getType() == "InvalidType" ) {
//         P->prim_type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     P->op = op->name;

//     if ( op->name == "++" )
//         P->name = "POST INCREMENT";
//     else
//         P->name = "POST DECREMENT";

//     std::string op_code = op->name.substr( 0, 1 );

//     Address *inc_value;
//         if (  op->name != "++" && op->name != "--" ) {
// 		std::cerr << "PANIC: Invalid operation " << op->name <<"\n";
// 		assert(0);
// 		return P;
//     }
// 	if ( pe->prim_type.is_const == true ) {
// 		error_msg( "Invalid operand " + op->name + " with constant type",
// 				   op->line_num, op->column );
// 		P->prim_type.invalid_type = &INVALID_TYPE;
// 		return P;
// 	}

// 	if ( pe->prim_type.pointer_type->ptr_level > 0 ) {
// 		P->prim_type = pe->prim_type;
// 		GlobalType t = pe->prim_type;
// 		t.pointer_type->ptr_level--;
// 	} else if ( type_specifiers[INT_T].isEqual(*pe->prim_type.standard_type) ) {
// 		P->prim_type = pe->prim_type;
// 	} else if ( type_specifiers[FLOAT_T].isEqual(*pe->prim_type.standard_type) ) {
// 		P->prim_type = pe->prim_type;
// 	} else {
// 		// Error postfix operator
// 		error_msg( "Invalid operand " + op->name + " with type " +
// 					   pe->prim_type.getType(),
// 				   op->line_num, op->column );
// 		P->prim_type.invalid_type = &INVALID_TYPE;
// 		return P;
// 	}

//     P->add_children({pe});
//     return P;
// }

// // Unary Expression
Expression *create_unary_expression( OpExpression *oe ) {
    
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    if ( op1Type == ERROR_T)
        oe->prim_type = ERROR_T;
        return oe;
    }
    //3AC
    std::string u_op = oe->op;
    // oe->name = u_op;
    // Address *inc_value = nullptr;

    if ( u_op == "++" || u_op == "--" ) {
        if ( oe->exp_type->getSpecifiers()->is_const == true ) {
            error_msg( "Invalid operand " + u_op + " with constant type",
                       op->line_num, op->column );
            oe->prim_type.invalid_type = &INVALID_TYPE;
            return oe;
        
		u_op = u_op.substr( 0, 1 );
		if ( ue->prim_type.getType() == "PointerType" ) {
			oe->prim_type = ue->prim_type;
			GlobalType t = ue->prim_type;
			t.pointer_type->ptr_level--;
		} else if ( ue->prim_type.getType() == "StandardType" ) {
			oe->prim_type = ue->prim_type;
		} else if ( ue->prim_type.getType() == "FloatType" ) {
			oe->prim_type = ue->prim_type;
		} else {
			// Incorrect type throw error
			error_msg( "Invalid operand " + u_op + " with type " +
						   ue->prim_type.getType(),
					   op->line_num, op->column );
			oe->prim_type.invalid_type = &INVALID_TYPE;
			return oe;
		}
    } else if ( u_op == "sizeof" ) {
        oe->name = "sizeof";
        oe->prim_type.standard_type = &type_specifiers[PrimitiveTypes::INT_T];
        oe->prim_type.pointer_type->ptr_level = 0;
        // oe->prim_type.is_const = true;
    } else {
        // Raise Error
        std::cerr << "Error parsing Unary Expression.\n";
        std::cerr << "ERROR at line " << line_num << "\n";
        exit( 0 );
    }
    oe->add_children({ue});
    return oe;
}

PrimitiveTypes deduceType(const std::string& input) {
    // Check if the string contains a decimal point or exponent,
    // indicating a floating point literal.
    if (input.find('.') != std::string::npos || input.find('e') != std::string::npos || input.find('E') != std::string::npos) {
        try {
            long double val = std::stold(input);
            // First try float; if the converted value is nearly identical, we choose float.
            float f = static_cast<float>(val);
            if (std::abs(static_cast<long double>(f) - val) < 1e-6L)
                return FLOAT_T;
            // Next try double.
            double d = static_cast<double>(val);
            if (std::abs(static_cast<long double>(d) - val) < 1e-12L)
                return DOUBLE_T;
            // Otherwise, use long double.
            return LONG_DOUBLE_T;
        } catch (...) {
            return ERROR_T;
        }
    }

    else {
        // Determine the base and convert the literal accordingly.
        long long val = 0;
        try {
            if (input.size() > 2 && input[0] == '0' &&
                (input[1] == 'x' || input[1] == 'X')) {
                // Hexadecimal literal
                val = std::stoll(input, nullptr, 16);
            }
            else if (input[0] == '0' && input.size() > 1) {
                // Octal literal
                val = std::stoll(input, nullptr, 8);
            }
            else {
                // Decimal literal
                val = std::stoll(input, nullptr, 10);
            }

            if (val >= std::numeric_limits<int>::min() &&
                val <= std::numeric_limits<int>::max())
                return INT_T;
            else if (val >= std::numeric_limits<long>::min() &&
                     val <= std::numeric_limits<long>::max())
                return LONG_T;
            else
                return LLONG_T;
        } catch (...) {
            return ERROR_T;
        }
    }
}

Expression* create_expression_simple(ExpressionType exp_type, std::string token) {
    Expression* e = new Expression();


    switch (exp_type) {
    case IDENTIFIER_ET: {
        // Lookup the identifier in the symbol table
        Symbol* s = SymbolTable::get_symbol(token);
        if (s == NULL) {
            error_msg("Undeclared symbol " + token, line_num, column);
            e->prim_type = ERROR_T;
            return e;
        }

        // Set the type of the expression based on the symbol's type
        e->exp_type = s->identifier.type;

        if (e->exp_type->type_tag == STANDARD_TYPE) {
            e->prim_type = static_cast<PrimitiveTypes>(s->identifier.type->type_tag);
        }
        return e;
        break;
    }
    case CONSTANT_ET:
    {
        PrimitiveTypes type = deduceType(token);
        if (type == ERROR_T) {
            error_msg("Invalid constant type for " + token, line_num, column);
            e->prim_type = ERROR_T;
            e->exp_type = create_primitive_type(ERROR_T);
            return e;
        }
        e->exp_type = create_primitive_type(type);
        e->prim_type = type;
        return e;
        break;

    }
    case EXPRESSION_ET:
    default: {
        std::cerr << "Incorrect expression. Something went wrong\n";
        return e;
        };
    }
}

Expression* create_expression(ExpressionOpType op_type, std::string op, VectorExpression* ve) {
    OpExpression* oe = new OpExpression();
    oe->op_type = op_type;
    oe->op = op;
    switch (op_type) {
    case MULTIPLICATIVE:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return multiplicative_expression(oe); // Done
    case ADDITIVE:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return additive_expression(oe); // Done
    case RELATIONAL:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return relational_expression(oe); // Done
    case SHIFT:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return shift_expression(oe); // Done
    case EQUALITY:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return equality_expression(oe); // Done
    case AND:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return and_expression(oe); // Done
    case XOR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return xor_expression(oe); // Done
    case OR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return or_expression(oe); // Done
    case LOGICAL_AND:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_and_expression(oe); // Done
    case LOGICAL_OR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_or_expression(oe); // Done
    case CONDITIONAL:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        oe->op3 = ve->operands[2];
        return conditional_expression(oe); // Basic done (Please check)
    case CONSTANT:
        oe->op1 = ve->operands[0];
        return constant_expression(oe);
    case TOPLEVEL:
        oe->op1 = ve->operands[0];
        return toplevel_expression(oe);
    case ASSIGNMENT:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        //Node* n_op?
        return assignment_expression(oe);
    case UNARY:
        oe->op1 = ve->operands[0];
        return create_unary_expression(oe);
    default:
        std::cerr << "Incorrect expression. Something went wrong\n";
        return nullptr;
    }
}

