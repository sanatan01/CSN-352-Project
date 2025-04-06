#include <expression.h>
#include <cassert>
#include <initializer_list>
#include <tac.h>

int line_num = 0, column = 0;

void error_msg(std::string msg, int line_num, int column)
{
    std::cerr << "[  ERROR  ] " << msg << " at line " << line_num << ", column " << column << std::endl;
}

void warning_msg(std::string msg, int line_num, int column)
{
    std::cerr << "[ WARNING ] " << msg << " at line " << line_num << ", column " << column << std::endl;
}

void debug_msg(std::string msg, int line_num, int column)
{
#ifdef _DEBUG_MODE
    if (line_num == 0 && column == 0)
    {
        std::cerr << "[  DEBUG  ] " << msg << std::endl;
    }
    else
    {
        std::cerr << "[  DEBUG  ] " << msg << " at line " << line_num << ", column " << column << std::endl;
    }
#endif
}

Expression::Expression(PrimitiveTypes type, int num_operands) : prim_type(static_cast<int>(type)), num_operands(num_operands), is_assignable(true), exp_type(create_primitive_type(type)) {};
Expression::Expression() : prim_type(static_cast<int>(ERROR_T)), num_operands(0), is_assignable(true), exp_type(create_invalid_type("Invalid expression", line_num, column)) {};

Expression::Expression(class GlobalType *type) : prim_type(static_cast<int>(ERROR_T)), num_operands(0), exp_type(type)
{
    if (type == nullptr)
    {
        error_msg("Invalid expression", line_num, column);
        exp_type = create_invalid_type("Invalid expression", line_num, column);
        return;
    }

    if (type->type_tag == STANDARD_TYPE)
    {
        prim_type = type_map[type->standard_type->name];
    }
};

bool isInt(PrimitiveTypes op)
{
    return ((op > -1 && op < 10) || op == 14);
}

bool isFloat(PrimitiveTypes op)
{
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
    {"bool", BOOL_T}};

PrimitiveTypes getPrimitiveType(std::string type)
{
    auto it = type_map.find(type);
    if (it != type_map.end())
    {
        return it->second;
    }
    return ERROR_T;
}

PrimitiveTypes deduceType(const std::string &input)
{
    // Check if the string contains a decimal point or exponent,
    // indicating a floating point literal.

    PrimitiveTypes ret_type = ERROR_T;

    if (input.find('.') != std::string::npos || input.find('e') != std::string::npos || input.find('E') != std::string::npos)
    {
        try
        {
            long double val = std::stold(input);
            // First try float; if the converted value is nearly identical, we choose float.
            float f = static_cast<float>(val);
            if (std::abs(static_cast<long double>(f) - val) < 1e-6L)
            {
                ret_type = FLOAT_T;
            }
            else
            {
                // Next try double.
                double d = static_cast<double>(val);
                if (std::abs(static_cast<long double>(d) - val) < 1e-12L)
                {
                    ret_type = DOUBLE_T;
                }
                else
                {
                    // Otherwise, use long double.
                    ret_type = LONG_DOUBLE_T;
                }
            }
        }
        catch (...)
        {
            ;
        }
    }
    else
    {
        // Determine the base and convert the literal accordingly.
        long long val = 0;
        try
        {
            if (input.size() > 2 && input[0] == '0' &&
                (input[1] == 'x' || input[1] == 'X'))
            {
                // Hexadecimal literal
                val = std::stoll(input, nullptr, 16);
            }
            else if (input[0] == '0' && input.size() > 1)
            {
                // Octal literal
                val = std::stoll(input, nullptr, 8);
            }
            else
            {
                // Decimal literal
                val = std::stoll(input, nullptr, 10);
            }

            if (val >= std::numeric_limits<int>::min() &&
                val <= std::numeric_limits<int>::max())
                ret_type = INT_T;
            else if (val >= std::numeric_limits<long>::min() &&
                     val <= std::numeric_limits<long>::max())
                ret_type = LONG_T;
            else
                ret_type = LLONG_T;
        }
        catch (...)
        {
            ret_type = ERROR_T;
        }
    }

    debug_msg("Deduced type: " + typeName(ret_type));
    return ret_type;
}

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

void make_signed(PrimitiveTypes &op)
{

    if (op % 2 == 0 && op < 10 && op > -1)
    {
        op = static_cast<PrimitiveTypes>(static_cast<int>(op) + 1);
    }
}

void make_unsigned(PrimitiveTypes &op)
{

    if (op % 2 && op < 10 && op > -1)
    {
        op = static_cast<PrimitiveTypes>(static_cast<int>(op) - 1);
    }
}

bool isUnsigned(PrimitiveTypes op)
{
    if (op % 2 == 0 && op < 10 && op > -1)
    {
        return true;
    }

    if (op >= 10 && op < 14)
    {
        return true;
    }

    return false;
}

bool isInvalid(std::initializer_list<PrimitiveTypes> ops)
{
    bool result = false;
    for (PrimitiveTypes op : ops)
    {
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

// ArgumentExprList::ArgumentExprList(): Expression() {}

// // TODO: Implement this
// ArgumentExprList* create_argument_expr_assignement(Expression* ase) {
//     ArgumentExprList* ae_list = new ArgumentExprList();
//     ae_list->args.push_back(ase);
//     // ArgumentExprList does not have any type as it is a composite entity
//     // ae_list->name = "arguments";
//     // ae_list->add_children({ase});
//     return ae_list;
// }

// ArgumentExprList* create_argument_expr_list(ArgumentExprList* ae_list, Expression* ase) {
//     ae_list->args.push_back(ase);
//     // ArgumentExprList does not have any type as it is a composite entity
//     // ae_list->name = "arguments";
//     // ae_list->add_children({ase});
//     return ae_list;
// }

Expression *multiplicative_expression(OpExpression *oe)
{

    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (oe->op2.exp_type->type_tag == STANDARD_TYPE && oe->op1.exp_type->type_tag == STANDARD_TYPE && isInvalid({op1Type, op2Type}) || op1Type == VOID_T || op2Type == VOID_T)
    {
        error_msg("Invalid types for multiplication" + oe->op, line_num, column);
        oe->prim_type = ERROR_T;
        return oe;
    }

    if (oe->op == "*" || oe->op == "/")
    {
        bool op1Unsigned = isUnsigned(op1Type);
        bool op2Unsigned = isUnsigned(op2Type);

        if (!op1Unsigned && !op2Unsigned)
        {
            // Both are signed
            ;
        }
        else if (op1Unsigned && op2Unsigned)
        {
            // Both are unsigned integers
            oe->op += "u";
        }
        else if (!op1Unsigned && op2Unsigned)
        {
            // make op1 unsigned
            oe->op += "u";
        }
        else if (op1Unsigned && !op2Unsigned)
        {
            // make op2 unsigned
            oe->op += "u";
        }

        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        if (isUnsigned(op1Type) || isUnsigned(op2Type))
        {
            PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
            make_unsigned(tmp);
            oe->prim_type = tmp;
        }

        oe->name = TAC::get_temp();
        TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    }
    else if (oe->op == "%")
    {

        if (!isInt(op1Type) || !isInt(op2Type))
        {
            error_msg("Invalid types for modulo" + oe->op, line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        oe->prim_type = op1Type;
        PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
        make_unsigned(tmp);
        oe->prim_type = tmp;

        oe->name = TAC::get_temp();
        TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    }
    else
    {
        // Code should not reach here
        assert(0);
    }

    return oe;
}

Expression *additive_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if ((op1Type == ERROR_T && op2Type != ERROR_T) || (op2Type == ERROR_T && op1Type != ERROR_T))
    {
        error_msg("Invalid types for addition/subtraction " + oe->op, line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (isInt(op1Type) && isInt(op2Type))
    {

        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
        PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
        make_signed(tmp);
        oe->prim_type = tmp;
    }
    else if (isFloat(op1Type) && isFloat(op2Type))
    {
        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
    }
    else if ((isFloat(op1Type) && isInt(op2Type)) || (isInt(op1Type) && isFloat(op2Type)))
    {
        oe->op += "f";
        oe->prim_type = op1Type > op2Type ? op1Type : op2Type;
    }
    else if (oe->op1.exp_type->type_tag == POINTER_TYPE && isInt(op2Type))
    {
        // TODO
        oe->prim_type = ERROR_T;
        oe->exp_type = oe->op1.exp_type;
    }
    else if (oe->op2.exp_type->type_tag == POINTER_TYPE && isInt(op1Type))
    {
        // TODO
        oe->prim_type = ERROR_T;
        oe->exp_type = oe->op2.exp_type;
    }
    else
    {
        error_msg("Invalid types for addition/subtraction " + oe->op, line_num, column);
        oe->prim_type = ERROR_T;
        return oe;
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

Expression *relational_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for relational operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<" || oe->op == ">" || oe->op == "<=" || oe->op == ">=")
    {
        // Check if both operands are numeric
        if (op1Type != VOID_T && op2Type != VOID_T && op1Type != ERROR_T && op2Type != ERROR_T)
        {
            oe->prim_type = PrimitiveTypes(BOOL_T);

            // Add warning for signed/unsigned mismatch
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);
            if (op1Unsigned != op2Unsigned)
            {
                warning_msg("Comparison " + oe->op + " between signed and unsigned values", line_num, column);
            }

            // 3AC code would be added here
        }
    }
    else
    {
        error_msg("Incorrect relation expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *shift_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for shift operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<<" || oe->op == ">>")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->prim_type = op1Type;

            // If first operand is unsigned, mark operation as unsigned
            if (isUnsigned(op1Type))
            {
                oe->op += "u";
            }
        }
        else
        {
            error_msg("Invalid types for shift operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        // This should not happen
        error_msg("Incorrect shift expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *equality_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({op1Type, op2Type}))
    {
        error_msg("Invalid types for equality operation " + oe->op, line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (oe->op == "==" || oe->op == "!=")
    {
        // Handle pointer comparisons
        if (oe->op1.exp_type->type_tag == POINTER_TYPE && oe->op2.exp_type->type_tag == POINTER_TYPE)
        {
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else if ((oe->op1.exp_type->type_tag == STANDARD_TYPE && oe->op2.exp_type->type_tag == STANDARD_TYPE) && (isInt(op1Type) || isFloat(op1Type)) && (isInt(op2Type) || isFloat(op2Type)))
        {

            oe->prim_type = PrimitiveTypes(BOOL_T);

            // Add warning for signed/unsigned mismatch
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);
            if (op1Unsigned != op2Unsigned)
            {
                warning_msg("Comparison " + oe->op + " between signed and unsigned values", line_num, column);
            }
        }
        else
        {
            error_msg("Invalid types for equality operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect equality expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *and_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for bitwise AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned))
            {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else
        {
            error_msg("Invalid types for bitwise AND operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect and_expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *xor_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (isInvalid({op1Type, op2Type}))
    {
        error_msg("Invalid types for exclusive OR operation", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    if (oe->op == "^")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned))
            {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else
        {
            error_msg("Invalid types for bitwise XOR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect exclusive or expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *or_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for bitwise OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "|")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Determine the result type (using the "wider" of the two types)
            oe->prim_type = op1Type > op2Type ? op1Type : op2Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned))
            {
                // upgrade unsigned to signed for safety
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            // 3AC code would be added here
        }
        else
        {
            error_msg("Invalid types for bitwise OR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect inclusive or expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *logical_and_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for logical AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&&")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Result type is boolean
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else
        {
            error_msg("Invalid types for logical AND operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect logical AND expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);
    return oe;
}

// utils
Expression *logical_or_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for logical OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "||")
    {
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Result type is boolean
            oe->prim_type = PrimitiveTypes(BOOL_T);
        }
        else
        {
            error_msg("Invalid types for logical OR operation " + oe->op, line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Incorrect logical OR expression. Something went wrong");
    }

    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name, oe->op1.name, oe->op, oe->op2.name);

    return oe;
}

bool isCompatiblePrim(PrimitiveTypes p1, PrimitiveTypes p2)
{
    debug_msg("Comparing " + typeName(p1) + " and " + typeName(p2));
    if (p1 == ERROR_T || p2 == ERROR_T)
    {
        return false;
    }
    if ((isInt(p1) || isFloat(p1)) && (isInt(p2) || isFloat(p2)))
    {
        return true;
    }
    return p1 == p2;
}

bool isCompatible(GlobalType *op1, GlobalType *op2)
{
    if (op1->type_tag == STANDARD_TYPE && op2->type_tag == STANDARD_TYPE)
    {
        return isCompatiblePrim(type_map[op1->standard_type->name], type_map[op2->standard_type->name]);
    }
    else if (op1->type_tag != op2->type_tag)
    {
        return false;
    }
    else
    {
        if (op1->type_tag == FUNCTION_TYPE)
        {
            return isCompatible(op1->function_type->return_type, op2->function_type->return_type);
        }
        else if (op1->type_tag == POINTER_TYPE)
        {
            if (op1->pointer_type->ptr_level != op2->pointer_type->ptr_level)
            {
                return false;
            }
            return isCompatible(op1->pointer_type->return_type, op2->pointer_type->return_type);
        }
        else if (op1->type_tag == ARRAY_TYPE)
        {
            if (op1->array_type->dims != op2->array_type->dims)
            {
                return false;
            }
            return isCompatible(op1->array_type->return_type, op2->array_type->return_type);
        }
        else if (op1->type_tag == ENUM_TYPE)
        {
            return true;
        }
        else if (op1->type_tag == STRUCT_TYPE)
        {
            return op1->struct_type->struct_name == op2->struct_type->struct_name;
        }
        else if (op1->type_tag == UNION_TYPE)
        {
            return op1->union_type->union_name == op2->union_type->union_name;
        }
        else if (op1->type_tag == INVALID_TYPE)
        {
            return true;
        }
    }
    return false;
}

// utils
Expression *conditional_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    PrimitiveTypes op3Type = PrimitiveTypes(oe->op3.prim_type);

    if (isInvalid({op1Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for conditional expression", line_num, column);
        return oe;
    }
    if ((op2Type == ERROR_T && op3Type != ERROR_T) || (op3Type == ERROR_T && op2Type != ERROR_T))
    {
        error_msg("Invalid types for conditional expression", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    // check: TODO
    // Check if condition is an integer
    // if (type_specifiers[INT_T].isEqual(*op1Type.standard_type))
    if (isInt(op1Type))
    {
        // Check if true and false expressions have compatible types
        if (op2Type == ERROR_T && op3Type == ERROR_T && !isCompatible(oe->op2.exp_type, oe->op3.exp_type))
        {
            error_msg("Types mismatch for conditional expression", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
        else if (op2Type == ERROR_T && op3Type == ERROR_T && isCompatible(oe->op2.exp_type, oe->op3.exp_type))
        {
            oe->prim_type = PrimitiveTypes(ERROR_T);
            oe->exp_type = oe->op1.exp_type;
        }
        else if ((isInt(op2Type) || isFloat(op2Type)) && (isInt(op3Type) || isFloat(op3Type)))
        {
            oe->prim_type = op2Type > op3Type ? op2Type : op3Type;
            if (!(isUnsigned(op2Type) && isUnsigned(op3Type)))
            {
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }
        }
        else if (op2Type == op3Type)
        {
            oe->prim_type = op1Type;
        }
        else
        {
            error_msg("Types mismatch for conditional expression", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Comparison expression is not an int", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }

    // oe->name = "conditional_expression";
    // oe->add_children({&PrimitiveTypes(oe->op1.prim_type), &PrimitiveTypes(oe->op2.prim_type), &oe->op3});

    TAC::add_label(TRUE_C);
    TAC::add_label(FALSE_C);
    std::string true_label = TAC::get_label(TRUE_C);
    std::string false_label = TAC::get_label(FALSE_C);
    TAC::print_tac("if " + oe->op1.name + " == 0 goto " + false_label);
    oe->name = TAC::get_temp();
    TAC::print_tac(oe->name + " = " + oe->op2.name);
    TAC::print_tac("goto " + true_label);
    TAC::remove_false_label();
    TAC::print_tac(oe->name + " = " + oe->op3.name);
    TAC::remove_true_label();

    return oe;
}

// utils : TODO
Expression *constant_expression(OpExpression *oe)
{
    return oe;
}

// utils
Expression *toplevel_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);

    if (isInvalid({op1Type, op2Type}))
    {
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
Expression *assignment_expression(OpExpression *oe)
{
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if (oe->op1.is_assignable == false)
    {
        error_msg("Invalid assignment expression : Lvalue not present", line_num, column);
        oe->prim_type = PrimitiveTypes(ERROR_T);
        return oe;
    }
    // Terminal *op = (Terminal *)n_op;
    // TODO:
    // oe->op = op->name;

    if (oe->op2.exp_type->type_tag == STANDARD_TYPE && oe->op1.exp_type->type_tag == STANDARD_TYPE && isInvalid({op1Type, op2Type}))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for assignment expression", line_num, column);
        return oe;
    }

    // check if op1 is a contant expression then it cannot be assigned to anything
    // if (op1Type == PrimitiveTypes(CONSTANT)) {
    //     oe->prim_type = PrimitiveTypes(ERROR_T);
    //     error_msg("Cannot assign to a constant", line_num, column);
    //     return oe;
    // }

    if (oe->op == "=")
    {
        // Simple assignment
        // additional checking needed for checking complex types;
        if ((isInt(op1Type) || isFloat(op1Type)) && (isInt(op2Type) || isFloat(op2Type)))
        {
            // Integer or float assignment
            if (op1Type != op2Type)
            {
                warning_msg("Assignment between different types:" + typeName(op1Type) + "and" + typeName(op2Type), line_num, column);
            }
            oe->prim_type = op1Type;
        }
        else if (oe->op1.exp_type->type_tag == POINTER_TYPE && oe->op2.exp_type->type_tag == POINTER_TYPE)
        {
            // Pointer assignment
            //  TODO: how to do level check
            PrimitiveTypes p1 = static_cast<PrimitiveTypes>(oe->op1.exp_type->pointer_type->return_type->type_tag);
            PrimitiveTypes p2 = static_cast<PrimitiveTypes>(oe->op2.exp_type->pointer_type->return_type->type_tag);
            int p1_ptr_level = oe->op1.exp_type->pointer_type->ptr_level;
            int p2_ptr_level = oe->op2.exp_type->pointer_type->ptr_level;
            if (p2 != VOID_T && (p1 != p2 || p1_ptr_level != p2_ptr_level))
            {
                warning_msg("Assignment between different pointer types", line_num, column);
            }
            oe->prim_type = p1;
        }
        else
        {
            error_msg("Invalid types for assignment expression" + typeName(oe->op1.exp_type->type_tag) + "" + typeName(oe->op2.exp_type->type_tag), line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }

        if (oe->op2.name[0] == '*')
        {
            std::string new_temp = TAC::get_temp();
            TAC::print_tac(new_temp + " = " + oe->op2.name);
            TAC::print_tac(oe->op1.name + " = " + new_temp);
        }
        else
        {
            TAC::print_tac(oe->op1.name + " = " + oe->op2.name);
        }
        oe->name = oe->op1.name;
    }
    else if (oe->op == "+=" || oe->op == "-=")
    {
        // Addition/subtraction assignment
        if ((isInt(op1Type) || isFloat(op1Type)) &&
            (isInt(op2Type) || isFloat(op2Type)))
        {
            if (op1Type != op2Type)
            {
                warning_msg("Assignment between different types", line_num, column);
            }
            oe->prim_type = op1Type;
        }
        else if (oe->op1.exp_type->type_tag == POINTER_TYPE && op2Type == INT_T)
        {
            // Pointer arithmetic assignment
            oe->prim_type = op1Type;
        }
        else
        {
            error_msg("Invalid types for addition/subtraction assignment", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
        std::string temp = TAC::get_temp();
        TAC::print_tac(temp, oe->op1.name, oe->op.substr(0, 1), oe->op2.name);
        // TAC::print_tac(oe->op1.name + " = " + temp);
        oe->name = oe->op1.name;
    }
    else if (oe->op == "*=" || oe->op == "/=" || oe->op == "%=")
    {
        // Multiplicative assignment
        if (oe->op == "%=" && !isInt(op1Type) && !isInt(op2Type))
        {
            error_msg("Modulo operation requires integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        else if (isInt(op1Type) && isInt(op2Type))
        {
            if (op1Type != op2Type)
            {
                warning_msg("Assignment between different types:" + typeName(op1Type) + "and" + typeName(op2Type), line_num, column);
            }
            oe->prim_type = op1Type;

            std::string temp = TAC::get_temp();
            TAC::print_tac(temp, oe->op1.name, oe->op.substr(0, 1), oe->op2.name);
            // TAC::print_tac(oe->op1.name + " = " + temp);
            oe->name = oe->op1.name;
        }
        else
        {
            error_msg("Invalid operands for " + oe->op, line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "<<=" || oe->op == ">>=")
    {
        // Bitshift assignment
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->prim_type = op1Type;

            std::string temp = TAC::get_temp();
            TAC::print_tac(temp, oe->op1.name, oe->op.substr(0, 2), oe->op2.name);
            // TAC::print_tac(oe->op1.name + " = " + temp);
            oe->name = oe->op1.name;
        }
        else
        {
            error_msg("Shift operations require integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "&=" || oe->op == "|=" || oe->op == "^=")
    {
        // Bitwise operations assignment
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->prim_type = op1Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned))
            {
                // As safety, we upgrade unsigned to signed
                PrimitiveTypes tmp = static_cast<PrimitiveTypes>(oe->prim_type);
                make_signed(tmp);
                oe->prim_type = tmp;
            }

            std::string temp = TAC::get_temp();
            TAC::print_tac(temp, oe->op1.name, oe->op.substr(0, 1), oe->op2.name);
            // TAC::print_tac(oe->op1.name + " = " + temp);
            oe->name = oe->op1.name;
        }
        else
        {
            error_msg("Bitwise operations require integer operands", line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }
        // 3AC code would be added here
    }
    else
    {
        error_msg("Incorrect assignment expression. Something went wrong");
    }

    //     oe->name = "assignment_expression";
    //     oe->add_children({&PrimitiveTypes(oe->op1.prim_type), &PrimitiveTypes(oe->op2.prim_type)});

    return oe;
}

// Expression *create_unary_expression(Terminal *op, TypeName *t_name )
// {
//     UnaryExpression *U = new UnaryExpression();
//     std::string u_op = op->name;
//     U->name = u_op;
//     U->add_children({op, t_name});
//     U->prim_type.standard_type = &type_specifiers[INT_T];

//     return U;
// }

Expression *create_cast_expression_typename(OpExpression *oe)
{
    // CastExpression *P = new CastExpression();
    // P->op1 = ce;
    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(oe->op2.prim_type);
    if ((isInvalid({op1Type}) && (!isInvalid({op2Type}))) || (isInvalid({op2Type}) && (!isInvalid({op1Type}))))
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for cast expression", line_num, column);
        return oe;
    }
    if (op1Type == ERROR_T && op2Type == ERROR_T && oe->op1.exp_type->type_tag == NONE)
    {
        oe->prim_type = PrimitiveTypes(ERROR_T);
        error_msg("Invalid types for cast expression", line_num, column);
        return oe;
    }
    if ((isInt(op1Type) || isFloat(op1Type)) && (isInt(op2Type) || isFloat(op2Type)))
    {
        oe->prim_type = oe->op1.prim_type;
    }
    else if (oe->op1.exp_type->type_tag == POINTER_TYPE && oe->op2.exp_type->type_tag == POINTER_TYPE)
    {
        if (isCompatible(oe->op1.exp_type, oe->op2.exp_type))
        {
            oe->prim_type = oe->op1.prim_type;
            oe->exp_type = oe->op1.exp_type;
        }
        else
        {
            error_msg("Invalid types for cast expression", line_num, column);
            oe->prim_type = PrimitiveTypes(ERROR_T);
            return oe;
        }
    }
    else
    {
        error_msg("Undefined casting operation" + line_num);
        oe->prim_type = ERROR_T;
        return oe;
    }
    // 3AC or AST
    // P->name = "cast_expression";
    // P->add_children({tn, ce});
    return oe;
}

Expression *create_postfix_expr_arr(Expression *pe, Expression *exp)
{
    Expression *P = new Expression();
    // if (pe ) {
    //     P->pe = dynamic_cast<PostfixExpression *>(pe);
    // } else {
    //     P->pe = nullptr;
    // }
    // P->exp = exp;
    // P->name = "ARRAY ACCESS";
    PrimitiveTypes op1Type = PrimitiveTypes(pe->prim_type);
    PrimitiveTypes op2Type = PrimitiveTypes(exp->prim_type);

    if (isInvalid({op2Type}))
    {
        P->prim_type = ERROR_T;
        error_msg("Invalid types for array access", line_num, column);
        return P;
    }
    if (!isInt(op2Type))
    {
        error_msg("Array index must be of type integer", line_num);
        P->prim_type = ERROR_T;
        return P;
    }

    if (pe->exp_type == nullptr)
    {
        error_msg("Array index must be of type integer", line_num);
        P->prim_type = ERROR_T;
        return P;
    }

    if (pe->exp_type->type_tag == ARRAY_TYPE)
    {

        P->prim_type = ERROR_T;
        P->exp_type = pe->exp_type;
        P->exp_type->array_type->dim--;
        P->exp_type->array_type->dims.erase(P->exp_type->array_type->dims.begin());

        if (P->exp_type->array_type->dim == 0)
        {
            P->exp_type = new GlobalType();
            P->exp_type->standard_type = pe->exp_type->array_type->return_type->standard_type;
            P->exp_type->type_tag = STANDARD_TYPE;
            P->prim_type = getPrimitiveType(pe->exp_type->array_type->return_type->standard_type->name);
        }
        // oe->prim_type.is_const = false; //TODO: make it non-constant
    }
    else if (pe->exp_type->type_tag == POINTER_TYPE)
    {
        P->exp_type = pe->exp_type;
        P->prim_type = ERROR_T;
        P->exp_type->pointer_type->ptr_level--;
        // P->prim_type.is_const = false; //TODO: make it non-constant
        // TODO: What type to update to?
        if (P->exp_type->pointer_type->ptr_level == 0)
        {
            P->exp_type = new GlobalType();
            P->exp_type->standard_type = pe->exp_type->pointer_type->return_type->standard_type;
            P->exp_type->type_tag = STANDARD_TYPE;
            P->prim_type = getPrimitiveType(pe->exp_type->pointer_type->return_type->standard_type->name);
        }
    }
    else
    {
        error_msg("Subscripted value is neither array nor pointer",
                  line_num);
        P->prim_type = ERROR_T;
        return P;
    }

    // oe->add_children({pe, exp});
    // oe->line_num = line_num;
    // oe->column = column;
    return P;
}

// // check its implementation
// Expression *create_postfix_expr_voidfun(Identifier *fi)
// {
//     PostfixExpression *P = new PostfixExpression();
//     // Lookup Function type from symbol table - should be void
//     SymTabEntry *ste = global_symbol_table.get_symbol_from_table( fi->name );
//     if ( ste == nullptr ) {
//         // Error
//         error_msg( "Undeclared symbol " + fi->name, fi->line_num, fi->column );
//         P->prim_type= ERROR_T;
//         return P;
//     } else if ( ste->exp_type->type_tag != "FunctionType" ) {
//         // Error
//         error_msg( "Called object '" + fi->name + "' is not a function",
//                    fi->line_num, fi->column );
//         P->prim_type= ERROR_T;
//         return P;
//     } else if ( ste->identifier.type->function_type->args.identifiers.size()  != 0 ) {
//         // Error
//         error_msg( "Too few arguments to function '" + fi->name + "'",
//                    fi->line_num, fi->column );
//         P->prim_type= ERROR_T;
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

Expression *create_postfix_expr_fun(Identifier *fi, VectorExpression *ae)
{
    Expression *P = new Expression();

    Symbol *ste = SymbolTable::get_symbol(fi->name);
    if (ste == nullptr)
    {
        // Error
        error_msg("Undeclared symbol:  " + fi->name);
        P->prim_type = ERROR_T;
        return P;
    }
    else if (ste->identifier.type->type_tag != FUNCTION_TYPE)
    {
        // Error
        error_msg("Called object '" + fi->name + "' is not a function");
        P->prim_type = ERROR_T;
        return P;
    }
    else if (ste->identifier.type->function_type->args.identifiers.size() > ae->operands.size())
    {
        // Error
        error_msg("Too few arguments to function '" + fi->name +
                  "'. Expected " + std::to_string(ste->identifier.type->function_type->args.identifiers.size()) +
                  ", got " + std::to_string(ae->operands.size()));
        P->prim_type = ERROR_T;
        return P;
    }
    else if (ste->identifier.type->function_type->args.identifiers.size() < ae->operands.size())
    {
        // Error
        error_msg("Too many arguments to function '" + fi->name +
                  "'. Expected " + std::to_string(ste->identifier.type->function_type->args.identifiers.size()) +
                  ", got " + std::to_string(ae->operands.size()));
        P->prim_type = ERROR_T;
        return P;
    }
    else if (ste->identifier.type->function_type->args.identifiers.size() == ae->operands.size())
    {
        int i = 0;
        for (auto &itr : ste->identifier.type->function_type->args.identifiers)
        {
            if (itr.type->type_tag == STANDARD_TYPE && ae->operands[i].prim_type != ERROR_T)
            {
                if (!isCompatiblePrim(getPrimitiveType(itr.type->standard_type->name), PrimitiveTypes(ae->operands[i].prim_type)))
                {
                    error_msg("Type mismatch at argument " + std::to_string(i) +
                                  " of function '" + fi->name + "'. Expected " +
                                  itr.type->getType() + ", got " +
                                  typeName(ae->operands[i].exp_type->type_tag),
                              line_num, column);
                    P->prim_type = ERROR_T;
                    return P;
                }
            }
            else if (ae->operands[i].exp_type == NULL)
            {
                error_msg("No argument type received from function call");
                P->prim_type = ERROR_T;
                return P;
            }
            else if (!(isCompatible(itr.type, ae->operands[i].exp_type)))
            {
                error_msg("Type mismatch at argument " + std::to_string(i) +
                              " of function '" + fi->name + "'. Expected " +
                              itr.type->getType() + ", got " +
                              typeName(ae->operands[i].exp_type->type_tag),
                          line_num, column);
                P->prim_type = ERROR_T;
                return P;
            }

            TAC::print_tac("param " + ae->operands[i].name);
            i++;
        }
    }

    std::string new_temp = TAC::get_temp();
    TAC::print_tac(new_temp + " = call " + fi->name + " , " + std::to_string(ste->identifier.type->function_type->args.identifiers.size()));
    P->exp_type = ste->identifier.type->function_type->return_type;
    if (P->exp_type->type_tag == STANDARD_TYPE)
    {
        P->prim_type = getPrimitiveType(P->exp_type->standard_type->name);
    }
    P->name = new_temp;

    return P;
}

// Expression *create_postfix_expr_struct( std::string access_op, Expression *pe, Identifier *id){
//     PostfixExpression *P = new PostfixExpression();

//     if ( pe->prim_type == ERROR_T ) {
//         P->prim_type= ERROR_T;
//         return P;
//     }

//     GlobalType peT = pe->prim_type;
//     if ( access_op == "." ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->prim_type.pointer_type->ptr_level == 0 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " +
//                                pe->exp_type->type_tag,
//                            id->line_num, id->column );
//                 P->prim_type= ERROR_T;
//                 return P;
//             }
//             // whether i exists in Struct
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType == nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type= ERROR_T;
//                 return P;
//             } else {
//                 P->prim_type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand . with type " + pe->exp_type->type_tag, id->line_num,
//                        id->column );
//             P->prim_type= ERROR_T;
//             return P;
//         }
//     } else if ( access_op == "->" ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->prim_type.pointer_type->ptr_level == 1 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type= ERROR_T;
//                 return P;
//             }
//             // whether i exists in Struct*
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType==nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->prim_type= ERROR_T;
//                 return P;
//             } else {
//                 P->prim_type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand -> with type " + pe->exp_type->type_tag,
//                        id->line_num, id->column );
//             P->prim_type= ERROR_T;
//             return P;
//         }
//     }

//     P->name = access_op;
//     P->add_children({pe, id});
//     return P;
// }

Expression *create_postfix_expr_ido(std::string op, Expression *pe)
{

    Expression *P = new Expression();

    if (pe->prim_type == ERROR_T)
    {
        P->prim_type = ERROR_T;
        if (pe->exp_type != NULL && pe->exp_type->type_tag == POINTER_TYPE)
        {
            if (pe->exp_type->getSpecifiers()->is_const == true)
            {
                error_msg("Invalid operand " + op + " with constant type",
                          line_num, column);
                return P;
            }
            P->exp_type = pe->exp_type;
        }
        else
        {
            error_msg("Invalid operand " + op + " with type " +
                          typeName(pe->exp_type->type_tag),
                      line_num, column);
        }
        return P;
    }

    // P->op = op;
    if (op == "++")
        P->name = "POST INCREMENT";
    else
        P->name = "POST DECREMENT";

    // std::string op_code = op.substr( 0, 1 );

    // Address *inc_value;
    if (op != "++" && op != "--")
    {
        error_msg("PANIC: Invalid operation " + std::string(op));
        return P;
    }

    if (isInt(PrimitiveTypes(pe->prim_type)) || isFloat(PrimitiveTypes(pe->prim_type)))
    {
        P->prim_type = PrimitiveTypes(pe->prim_type);
    }
    else
    {
        // Error postfix operator
        error_msg("Invalid operand " + op + " with type " +
                      typeName(pe->exp_type->type_tag),
                  line_num, column);
        P->prim_type = ERROR_T;
        return P;
    }

    // P->add_children({pe});
    return P;
}

// // Unary Expression
Expression *create_unary_expression(OpExpression *oe)
{

    PrimitiveTypes op1Type = PrimitiveTypes(oe->op1.prim_type);
    // 3AC
    std::string u_op = oe->op;

    if (u_op == "++" || u_op == "--")
    {

        oe->is_assignable = false;
        if ((op1Type == ERROR_T) && (oe->op1.exp_type->type_tag != NONE) && oe->op1.exp_type->getSpecifiers()->is_const == true)
        {
            error_msg("Invalid operand " + u_op + " with constant type",
                      line_num, column);
            // Assuming invalid_type handling remains unchanged
            oe->prim_type = ERROR_T;
            return oe;
        }
        else if (op1Type == ERROR_T && (oe->op1.exp_type->type_tag == NONE))
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = ERROR_T;
            return oe;
        }

        // u_op = u_op.substr( 0, 1 );
        if (op1Type == ERROR_T && oe->op1.exp_type->type_tag != NONE)
        {

            if (oe->op1.exp_type->type_tag == POINTER_TYPE)
            {
                oe->prim_type = oe->op1.prim_type;
                oe->exp_type = oe->op1.exp_type;
            }
            else if (oe->op1.exp_type->type_tag == STANDARD_TYPE)
            {
                oe->prim_type = oe->op1.prim_type;
            }
            else
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                return oe;
            }
        }
        else
        {

            if (isInt(op1Type))
            {

                // 3AC
            }
            else if (isFloat(op1Type))
            {
                // 3AC
            }
            else
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }

            oe->prim_type = oe->op1.prim_type;
        }

        std::string temp = TAC::get_temp();
        TAC::print_tac(temp, oe->op1.name, u_op.substr(0, 1), "1");
        // TAC::print_tac(oe->op1.name + " = " + temp);
        oe->name = oe->op1.name;
        return oe;
    }
    else if (u_op == "sizeof")
    {
        oe->is_assignable = false;
        oe->name = "sizeof";
        oe->prim_type = INT_T;

        if (oe->op1.prim_type == ERROR_T && (oe->op1.exp_type != NULL))
        {
            std::string new_temp;
            switch (oe->op1.exp_type->type_tag)
            {
            case STANDARD_TYPE:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = INT_T;
                return oe;
            }
            case ARRAY_TYPE:
            case POINTER_TYPE:
            {
                oe->prim_type = INT_T;
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = " + std::to_string(sizeof(int)));
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                break;
            }

            case FUNCTION_TYPE:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = INT_T;
                return oe;
            }

            case STRUCT_TYPE:
            {
                oe->prim_type = INT_T;
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = " + std::to_string(oe->op1.exp_type->struct_type->size));
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                break;
            }

            case UNION_TYPE:
            {
                oe->prim_type = INT_T;
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = " + std::to_string(oe->op1.exp_type->union_type->size));
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                break;
            }

            default:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = INT_T;
                return oe;
            }
            }
        }

        if (oe->op1.exp_type == NULL)
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = INT_T;
            return oe;
        }

        if (oe->op1.exp_type->type_tag == STANDARD_TYPE)
        {
            if (oe->op1.prim_type == ERROR_T)
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = INT_T;
                return oe;
            }
        }
    }
    else if (u_op == "&")
    {
        oe->is_assignable = false;
        if (oe->op1.prim_type == ERROR_T)
        {
            if (oe->op1.exp_type == NULL)
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }
            std::string new_temp;
            switch (oe->op1.exp_type->type_tag)
            {
            case FUNCTION_TYPE:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }
            case ARRAY_TYPE:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }
            case STRUCT_TYPE:
            {
                oe->prim_type = ERROR_T;
                oe->exp_type = create_pointer_type(oe->op1.exp_type);
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = addr " + oe->op1.name);
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                return oe;
            }
            case UNION_TYPE:
            {
                oe->prim_type = ERROR_T;
                oe->exp_type = create_pointer_type(oe->op1.exp_type);
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = addr " + oe->op1.name);
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                return oe;
            }
            case POINTER_TYPE:
            {
                oe->prim_type = ERROR_T;
                oe->exp_type->pointer_type->ptr_level++;
                new_temp = TAC::get_temp();
                TAC::print_tac(new_temp + " = addr " + oe->op1.name);
                // TAC::print_tac(oe->op1.name + " = " + new_temp);
                oe->name = new_temp;
                return oe;
            }
            default:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }
            }
        }
        else
        {
            std::string new_temp;
            oe->exp_type = create_pointer_type(oe->op1.exp_type);
            oe->prim_type = ERROR_T;
            new_temp = TAC::get_temp();
            TAC::print_tac(new_temp + " = addr " + oe->op1.name);
            // TAC::print_tac(oe->op1.name + " = " + new_temp);
            oe->name = new_temp;
            return oe;
        }
    }
    else if (u_op == "*")
    {
        oe->is_assignable = oe->op1.is_assignable;
        if (oe->op1.prim_type == ERROR_T)
        {
            if (oe->op1.exp_type == NULL)
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }

            switch (oe->op1.exp_type->type_tag)
            {
            case POINTER_TYPE:
            {
                oe->exp_type = create_pointer_type(oe->op1.exp_type->pointer_type->return_type,
                                                   oe->op1.exp_type->pointer_type->ptr_level);
                oe->prim_type = ERROR_T;
                oe->exp_type->pointer_type->ptr_level--;
                if (oe->exp_type->pointer_type->ptr_level == 0)
                {
                    oe->exp_type = new GlobalType();
                    oe->exp_type->standard_type = oe->op1.exp_type->pointer_type->return_type->standard_type;
                    oe->exp_type->type_tag = STANDARD_TYPE;
                    oe->prim_type = getPrimitiveType(oe->op1.exp_type->pointer_type->return_type->standard_type->name);
                }
                oe->name = u_op + oe->op1.name;
                return oe;
            }
            default:
            {
                error_msg("Invalid operand " + u_op + " with type " +
                              oe->op1.exp_type->getType(),
                          line_num, column);
                oe->prim_type = ERROR_T;
                return oe;
            }
            }
        }
        else
        {
            oe->prim_type = ERROR_T;
            oe->exp_type = new GlobalType();
            error_msg("Invalid operand " + u_op + " with type " +
                          typeName(oe->op1.prim_type),
                      line_num, column);
            return oe;
        }
    }
    else if (u_op == "-")
    {
        std::string new_temp;
        if (isInt(op1Type) || isFloat(op1Type))
        {
            // 3AC
            oe->prim_type = op1Type;
            PrimitiveTypes temp = PrimitiveTypes(oe->op1.prim_type);
            make_signed(temp);
            oe->prim_type = temp;

            new_temp = TAC::get_temp();
            TAC::print_tac(new_temp + " = addr " + oe->op1.name);
            // TAC::print_tac(oe->op1.name + " = " + new_temp);
            oe->name = new_temp;
            oe->is_assignable = false;
        }
        else
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = ERROR_T;
            oe->is_assignable = false;
            return oe;
        }
    }
    else if (u_op == "+")
    {
        std::string new_temp;
        if (isInt(op1Type) || isFloat(op1Type))
        {
            // 3AC
            oe->prim_type = op1Type;
            new_temp = TAC::get_temp();
            TAC::print_tac(new_temp + " = addr " + oe->op1.name);
            // TAC::print_tac(oe->op1.name + " = " + new_temp);
            oe->name = new_temp;
            oe->is_assignable = false;
        }
        else
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = ERROR_T;
            oe->is_assignable = false;
            return oe;
        }
    }
    else if (u_op == "!")
    {
        std::string new_temp;
        if (isInt(op1Type))
        {
            // 3AC
            oe->prim_type = BOOL_T;
            TAC::print_tac(new_temp + " = addr " + oe->op1.name);
            // TAC::print_tac(oe->op1.name + " = " + new_temp);
            oe->name = new_temp;
            oe->is_assignable = false;
        }
        else
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = ERROR_T;
            oe->is_assignable = false;
            return oe;
        }
    }
    else if (u_op == "~")
    {
        if (isInt(op1Type))
        {
            // 3AC

            oe->prim_type = op1Type;
            PrimitiveTypes temp = PrimitiveTypes(oe->op1.prim_type);
            make_signed(temp);
            oe->prim_type = temp;
            std::string new_temp = TAC::get_temp();
            TAC::print_tac(new_temp + " = addr " + oe->op1.name);
            // TAC::print_tac(oe->op1.name + " = " + new_temp);
            oe->name = new_temp;
            oe->is_assignable = false;
        }
        else
        {
            error_msg("Invalid operand " + u_op + " with type " +
                          oe->op1.exp_type->getType(),
                      line_num, column);
            oe->prim_type = ERROR_T;
            oe->is_assignable = false;
            return oe;
        }
    }
    else
    {
        oe->is_assignable = false;
        error_msg("Error parsing Unary Expression");
        error_msg("ERROR at line " + std::to_string(line_num));
    }
    return oe;
}

Expression *create_expression_simple(ExpressionType exp_type, std::string token)
{
    Expression *e = new Expression();

    switch (exp_type)
    {
    case IDENTIFIER_ET:
    {
        // Lookup the identifier in the symbol table
        Symbol *s = SymbolTable::get_symbol(token);
        if (s == NULL)
        {
            error_msg("Undeclared symbol " + token, line_num, column);
            e->prim_type = ERROR_T;
            return e;
        }

        // Set the type of the expression based on the symbol's type
        e->exp_type = s->identifier.type;

        if (e->exp_type->type_tag == STANDARD_TYPE)
        {
            e->prim_type = static_cast<PrimitiveTypes>(type_map[s->identifier.type->standard_type->name]);
        }

        e->name = token;
        return e;
        break;
    }
    case CONSTANT_ET:
    {
        PrimitiveTypes type = deduceType(token);
        if (type == ERROR_T)
        {
            error_msg("Invalid constant type for " + token, line_num, column);
            e->prim_type = ERROR_T;
            e->exp_type = create_primitive_type(ERROR_T);
            return e;
        }
        e->exp_type = create_primitive_type(type);
        e->prim_type = type;

        e->name = token;
        return e;
        break;
    }
    case EXPRESSION_ET:
    default:
    {
        error_msg("Incorrect expression. Something went wrong");
        e->name = "error";
        return e;
    };
    }
}

Expression *create_expression(ExpressionOpType op_type, std::string op, VectorExpression *ve)
{
    OpExpression *oe = new OpExpression();
    oe->op_type = op_type;
    oe->op = op;
    if (op_type != ASSIGNMENT || op_type != UNARY)
    {
        for (auto &expr : ve->operands)
        {
            if (expr.name[0] == '*')
            {
                std::string temp = TAC::get_temp();
                TAC::print_tac(temp + " = * " + expr.name.substr(1));
                expr.name = temp;
            }
        }
    }
    else
    {
        oe->is_assignable = false;
    }
    switch (op_type)
    {
    case MULTIPLICATIVE:
        debug_msg("Enum name: MULTIPLICATIVE");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return multiplicative_expression(oe); // Done Done
    case ADDITIVE:
        debug_msg("Enum name: ADDITIVE");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return additive_expression(oe); // Done Done
    case RELATIONAL:
        debug_msg("Enum name: RELATIONAL");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return relational_expression(oe); // Done Done
    case SHIFT:
        debug_msg("Enum name: SHIFT");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return shift_expression(oe); // Done Done
    case EQUALITY:
        debug_msg("Enum name: EQUALITY");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return equality_expression(oe); // Done Done
    case AND:
        debug_msg("Enum name: AND");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return and_expression(oe); // Done Done
    case XOR:
        debug_msg("Enum name: XOR");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return xor_expression(oe); // Done Done
    case OR:
        debug_msg("Enum name: OR");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return or_expression(oe); // Done Done
    case LOGICAL_AND:
        debug_msg("Enum name: LOGICAL_AND");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_and_expression(oe); // Done Done
    case LOGICAL_OR:
        debug_msg("Enum name: LOGICAL_OR");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_or_expression(oe); // Done Done
    case CONDITIONAL:
        debug_msg("Enum name: CONDITIONAL");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        oe->op3 = ve->operands[2];
        return conditional_expression(oe); // Basic done (Please check) (Please check)
    case CONSTANT:
        debug_msg("Enum name: CONSTANT");
        oe->op1 = ve->operands[0];
        return constant_expression(oe);
    case TOPLEVEL:
        debug_msg("Enum name: TOPLEVEL");
        oe->op1 = ve->operands[0];
        return toplevel_expression(oe);
    case ASSIGNMENT:
        debug_msg("Enum name: ASSIGNMENT");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return assignment_expression(oe);
    case UNARY:
        debug_msg("Enum name: UNARY");
        oe->op1 = ve->operands[0];
        return create_unary_expression(oe);
    case CAST_TYPE:
        debug_msg("Enum name: CAST_TYPE");
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return create_cast_expression_typename(oe);
    default:
        error_msg("Incorrect expression. Unknown enum type ");
        return nullptr;
    }
}

bool is_expr_signed(class Expression *expr)
{
    if (expr->prim_type == 5 || (expr->prim_type >= 0 && expr->prim_type < 4))
    {
        return true;
    }
    return false;
}

bool is_expr_unsigned(class Expression *expr)
{
    if (expr->prim_type == 0 || expr->prim_type == 2 || expr->prim_type == 4)
    {
        return true;
    }
    return false;
}