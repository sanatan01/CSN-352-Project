#include <expression.h>
#include <symtab.h>
#include <cassert>
#include <types.h>

int line_num=0,column=0;

void error_msg(std::string msg, int line_num=0, int column=0)
{
    std::cerr << "Error: " << msg << " at line " << line_num << ", column " << column << std::endl;
}

void warning_msg(std::string msg, int line_num=0, int column=0)
{
    std::cerr << "Warning: " << msg << " at line " << line_num << ", column " << column << std::endl;
}


bool isInt(ConstantType op){
    return (op.type>-1 && op.type<10);
}

bool isFloat(ConstantType op){
    return (op.type>=10 && op.type<13);
}

void castTypes(ConstantType &op1, ConstantType &op2){
    if (op1.type != op2.type){
        if(op1.type == VOID_T || op2.type == VOID_T || op1.type == ERROR_T || op2.type == ERROR_T){
            error_msg("Invalid types for operation", line_num, column);
            op1.type = ERROR_T;
            op2.type = ERROR_T;
            return;
        }
        if(op1.type == BOOL_T){
            op1.type = op2.type;
            return;
        }
        if(op2.type == BOOL_T){
            op2.type = op1.type;
            return;
        }
        // Cast to the larger type based on enum order
        // The enum is in sorted order of size, so higher enum value = larger type
        if (op1.type > op2.type) {
            // op1 is larger, cast op2 to op1's type
            op2.type = op1.type;
        } else {
            // op2 is larger, cast op1 to op2's type
            op1.type = op2.type;
        }
    }
}
void make_signed(ConstantType &op)
{

    if(op.type%2==0 && op.type<10 && op.type>-1){
        op.type++;
    }
}

void make_unsigned(ConstantType &op)
{
    if(op.type%2 && op.type<10 && op.type>-1){
        op.type--;
    }
}
bool isUnsigned(ConstantType op)
{
    if (op.type%2 == 0 && op.type<10 && op.type>-1)
    {
        return true;
    }
    if(op.type>=10 && op.type<14){
        return true;
    }
    return false;
}
bool isInvalid(std::initializer_list<ConstantType> ops)
{
    bool result = false;
    for (ConstantType op : ops)
    {
        result = result || (op.type == ERROR_T);
    }
    return result;
}

PrimaryExpression::PrimaryExpression() : Expression(ConstantType(ERROR_T), 0) {}

// TODO: Implement this
Expression *create_primary_expression(ExpressionType *typ)
{
    PrimaryExpression *pe = new PrimaryExpression();
    pe->type = *typ;
    return pe;
}

ArgumentExprList::ArgumentExprList() : Expression() {}

// TODO: Implement this
ArgumentExprList *create_argument_expr_assignement(Expression *ase)
{
    ArgumentExprList *ae_list = new ArgumentExprList();
    ae_list->args.push_back(ase);
    // ArgumentExprList does not have any type as it is a composite entity
    // ae_list->name = "arguments";
    // ae_list->add_children({ase});
    return ae_list;
}

ArgumentExprList *create_argument_expr_list(ArgumentExprList *ae_list, Expression *ase)
{
    ae_list->args.push_back(ase);
    // ArgumentExprList does not have any type as it is a composite entity
    // ae_list->name = "arguments";
    // ae_list->add_children({ase});
    return ae_list;
}

// utils
Expression *multiplicative_expression(OpExpression *oe)
{

    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) || op1Type.type == VOID_T || op2Type.type == VOID_T )
    {
        error_msg("Invalid types for multiplication" + oe->op, line_num, column);
        oe->type = ConstantType(ERROR_T);
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
            
            oe->type = op1Type.type > op2Type.type ? op1Type : op2Type;
            if(isUnsigned(op1Type) || isUnsigned(op2Type)){
                make_unsigned(oe->type);
            }
            // add 3AC code
    }
    else if (oe->op == "%")
    {
        if (!isInt(op1Type) || !isInt(op2Type))
        {
            error_msg("Invalid types for modulo" + oe->op, line_num, column);
            oe->type = ConstantType(ERROR_T);
            return oe;
        }
        oe->type = op1Type;
        make_unsigned(oe->type);
        // make it unsigned

        // add 3AC code
    }
    else
    {
        assert(0);
    }

    // oe->name = "multiplicative_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    return oe;
}

// utils
Expression *additive_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        error_msg("Invalid types for addition/subtraction " + oe->op, line_num, column);
        oe->type = ConstantType(ERROR_T);
        return oe;
    }

    if (isInt(op1Type) && isInt(op2Type))
    {

        oe->type = op1Type.type>op2Type.type ? op1Type : op2Type;
        make_unsigned(oe->type);
        // 3AC code would be added here
    }
    else if (isFloat(op1Type) && isFloat(op2Type))
    {
        oe->type = op1Type.type>op2Type.type ? op1Type : op2Type;
        // 3AC code would be added here
    }
    else if ((isFloat(op1Type) && isInt(op2Type)) || (isInt(op1Type) && isFloat(op2Type)))
    {
        oe->op += "f";
        oe->type = op1Type.type>op2Type.type ? op1Type : op2Type;
        // 3AC code would be added here
    }
    else if (op1Type.ptr_level > 0 && isInt(op2Type))
    { 
        //TODO
        oe->type = op1Type;
        
        // 3AC code for pointer + int would be added here
    }
    else if (op2Type.ptr_level > 0 && isInt(op1Type))
    {
        //TODO
        oe->type = op2Type;
        // 3AC code for int + pointer would be added here
    }

    // oe->name = "additive_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    return oe;
}

// utils
Expression *relational_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for relational operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<" || oe->op == ">" || oe->op == "<=" || oe->op == ">=")
    {
        // Check if both operands are numeric
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->type = ConstantType(BOOL_T);

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
        std::cerr << "Incorrect relation expression. Something went wrong\n";
    }

    // oe->name = "relational_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *shift_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for shift operation " + oe->op, line_num, column);
        return oe;
    }

    if (oe->op == "<<" || oe->op == ">>")
    {

            oe->type = op1Type;

            // If first operand is unsigned, mark operation as unsigned
            if (isUnsigned(op1Type))
            {
                oe->op += "u";
            }
    }
    else
    {
        // This should not happen
        std::cerr << "Incorrect shift expression. Something went wrong\n";
    }

    // oe->name = "shift_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *equality_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        error_msg("Invalid types for equality operation " + oe->op, line_num, column);
        oe->type = ConstantType(ERROR_T);
        return oe;
    }

    if (oe->op == "==" || oe->op == "!=")
    {
        // Handle pointer comparisons
        if (op1Type.ptr_level > 0 && op2Type.ptr_level > 0)
        {
            oe->type = ConstantType(BOOL_T);
        }
        // if ptr_level==0 : TODO
        else if (op1Type.ptr_level == 0 && op2Type.ptr_level == 0)
        {

            oe->type = ConstantType(BOOL_T);

            // Add warning for signed/unsigned mismatch
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);
            if (op1Unsigned != op2Unsigned)
            {
                warning_msg("Comparison " + oe->op + " between signed and unsigned values", line_num, column);
            }
        }
    }
    else
    {
        std::cerr << "Incorrect equality expression. Something went wrong\n";
    }

    // oe->name = "equality_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *and_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for bitwise AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&")
    {
        // Determine the result type (using the "wider" of the two types)
        oe->type = op1Type.type > op2Type.type ? op1Type : op2Type;

        // Handle unsigned/signed issues
        bool op1Unsigned = isUnsigned(op1Type);
        bool op2Unsigned = isUnsigned(op2Type);

        if (!(op1Unsigned && op2Unsigned))
        {
            // upgrade unsigned to signed for safety
            make_signed(oe->type);
        }

        // 3AC code would be added here
        
    }
    else
    {
        std::cerr << "Incorrect and_expression. Something went wrong\n";
    }

    // oe->name = "and_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *xor_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        error_msg("Invalid types for exclusive OR operation", line_num, column);
        oe->type = ConstantType(ERROR_T);
        return oe;
    }

    if (oe->op == "^")
    {
        // Determine the result type (ideally the wider of the two types) :TODO
        oe->type = op1Type.type > op2Type.type ? op1Type : op2Type;

        // Handle unsigned/signed issues
        bool op1Unsigned = isUnsigned(op1Type);
        bool op2Unsigned = isUnsigned(op2Type);

        if (!(op1Unsigned && op2Unsigned))
        {
            make_signed(oe->type);
        }
    }
    else
    {
        std::cerr << "Incorrect exclusive or expression. Something went wrong\n";
    }

    // oe->name = "exclusive_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *or_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for bitwise OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "|")
    {
        // Determine the result type (would ideally use the wider of the two types) :TODO
        oe->type = op1Type.type > op2Type.type ? op1Type : op2Type;

        // Handle unsigned/signed issues
        bool op1Unsigned = isUnsigned(op1Type);
        bool op2Unsigned = isUnsigned(op2Type);

        if (!(op1Unsigned && op2Unsigned))
        {
            make_signed(oe->type);
        }
    }
    else
    {
        std::cerr << "Incorrect inclusive or expression. Something went wrong\n";
    }

    // oe->name = "inclusive_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    return oe;
}

// utils
Expression *logical_and_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for logical AND operation", line_num, column);
        return oe;
    }

    if (oe->op == "&&")
    {
        // Result type is boolean
        oe->type = ConstantType(BOOL_T);
    }
    else
    {
        std::cerr << "Incorrect logical and expression. Something went wrong\n";
    }

    // oe->name = "logical_and_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    // append(oe->truelist, oe->op2.truelist);
    // append(oe->falselist, oe->op1.falselist);
    // append(oe->falselist, oe->op2.falselist);

    return oe;
}

// utils
Expression *logical_or_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    if (isInvalid({op1Type, op2Type})  )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for logical OR operation", line_num, column);
        return oe;
    }

    if (oe->op == "||")
    {
        // Result type is boolean
        oe->type = ConstantType(BOOL_T);
    }
    else
    {
        std::cerr << "Incorrect logical or expression. Something went wrong\n";
    }

    // oe->name = "logical_or_expression";
    // Node *n_op = create_non_terminal(oe->op.c_str(), {});
    // oe->add_children({&oe->op1, n_op, &oe->op2});
    // 3AC code would be added here
    // append(oe->truelist, oe->op1.truelist);
    // append(oe->truelist, oe->op2.truelist);
    // append(oe->falselist, oe->op2.falselist);

    return oe;
}

// utils
Expression *conditional_expression(OpExpression *oe)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    ConstantType op3Type = oe->op3.type;

    if (isInvalid({op1Type, op2Type, op3Type}))
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for conditional expression", line_num, column);
        return oe;
    }

    // check: TODO
    // Check if condition is an integer
    // if (type_specifiers[INT_T].isEqual(*op1Type.standard_type))
    if (op1Type.type == INT_T)
    {
        // Check if true and false expressions have compatible types
        if (true){
            error_msg("Invalid types for conditional expression", line_num, column);
            oe->type = ConstantType(ERROR_T);
            return oe;
        }
        else if (op2Type.type == op3Type.type && op2Type.ptr_level>0)
        {
            // check: TODO
            // Both expressions are pointers of the same type
            oe->type = op2Type;
            oe->type.ptr_level = op2Type.ptr_level;
        }
        else
        {
            // Determine the result type (wider of the two types): TODO
            oe->type = op2Type.type > op3Type.type ? op2Type : op3Type;

            // Handle unsigned/signed issues
            bool op2Unsigned = isUnsigned(op2Type);
            bool op3Unsigned = isUnsigned(op3Type);

            if (!(op2Unsigned && op3Unsigned))
            {
                // As safety, we upgrade unsigned to signed
                make_signed(oe->type);
            }
        }

    }

    // oe->name = "conditional_expression";
    // oe->add_children({&oe->op1, &oe->op2, &oe->op3});

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
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;

    if (isInvalid({op1Type, op2Type}))
    {
        error_msg("Invalid types for toplevel expression", line_num, column);
        oe->type = ConstantType(ERROR_T);
        return oe;
    }

    //////need TO DO LATER///////////

    // oe->name = "toplevel_expression";
    // oe->add_children({&oe->op1, &oe->op2});
    return oe;
}

Expression *create_assignment_expression(OpExpression *oe, Node *n_op)
{
    ConstantType op1Type = oe->op1.type;
    ConstantType op2Type = oe->op2.type;
    // Terminal *op = (Terminal *)n_op;
    // TODO:
    // oe->op = op->name;

    if (isInvalid({op1Type, op2Type}) )
    {
        oe->type = ConstantType(ERROR_T);
        error_msg("Invalid types for assignment expression", line_num, column);
        return oe;
    }

    // check if op1 is a contant expression then it cannot be assigned to anything
    if (op1Type.type == CONSTANT)
    {
        oe->type = ConstantType(ERROR_T);
        return oe;
    }

    if (oe->op == "=")
    {
        // Simple assignment
        if (isInt(op1Type) && isInt(op2Type))
        {
            // Integer or float assignment
            if (op1Type.type != op2Type.type)
            {
                warning_msg("Assignment between different types:"+ typeName(op1Type.type) + "and" + typeName(op2Type.type), line_num, column);
            }
            oe->type = op1Type;
        }
        else if (op1Type.ptr_level > 0 && op2Type.ptr_level > 0)
        {
            // Pointer assignment
            //  TODO: how to do level check
            if (op2Type.type == VOID_T && (op1Type.type != op2Type.type || op1Type.ptr_level != op2Type.ptr_level))
            {
                warning_msg("Assignment between different pointer types", line_num, column);
            }
            oe->type = op1Type;
        }
        // 3AC code would be added here
    }
    else if (oe->op == "+=" || oe->op == "-=")
    {
        // Addition/subtraction assignment
        if ((op1Type.type == INT_T || op1Type.type == FLOAT_T) &&
             (op2Type.type == INT_T || op2Type.type == FLOAT_T))
        {
            if (op1Type.type != op2Type.type)
            {
                warning_msg("Assignment between different types",line_num, column);
            }
            oe->type = op1Type;
        }
        else if (op1Type.ptr_level > 0 && op2Type.type == INT_T)
        {
            // Pointer arithmetic assignment
            oe->type = op1Type;
        }
    }
    else if (oe->op == "*=" || oe->op == "/=" || oe->op == "%=")
    {
        // Multiplicative assignment
        if (oe->op == "%=" && !isInt(op1Type) && !isInt(op2Type))
        {
            error_msg("Modulo operation requires integer operands", line_num, column);
            oe->type = ERROR_T;
            return oe;
        }
        else if (isInt(op1Type) && isInt(op2Type))
        {
            if (op1Type.type != op2Type.type)
            {
                warning_msg("Assignment between different types:"+ typeName(op1Type.type) + "and" + typeName(op2Type.type), line_num, column);
            }
            oe->type = op1Type;
        }
        else
        {
            error_msg("Invalid operands for " + oe->op, line_num, column);
            oe->type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "<<=" || oe->op == ">>=")
    {
        // Bitshift assignment
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->type = op1Type;
        }
        else
        {
            error_msg("Shift operations require integer operands", line_num, column);
            oe->type = ERROR_T;
            return oe;
        }
    }
    else if (oe->op == "&=" || oe->op == "|=" || oe->op == "^=")
    {
        // Bitwise operations assignment
        if (isInt(op1Type) && isInt(op2Type))
        {
            oe->type = op1Type;

            // Handle unsigned/signed issues
            bool op1Unsigned = isUnsigned(op1Type);
            bool op2Unsigned = isUnsigned(op2Type);

            if (!(op1Unsigned && op2Unsigned))
            {
                // As safety, we upgrade unsigned to signed
                make_signed(oe->type);
            }
        }
        else
        {
            error_msg("Bitwise operations require integer operands", line_num, column);
            oe->type = ERROR_T;
            return oe;
        }
        // 3AC code would be added here
    }
    else
    {
        std::cerr << "Incorrect assignment expression. Something went wrong\n";
    }

//     oe->name = "assignment_expression";
//     oe->add_children({&oe->op1, &oe->op2});
    return oe;
}

// Expression *create_unary_expression(Terminal * op, Expression *ue)
// {
//    UnaryExpression *U = new UnaryExpression();
//     U->op1 = ue;
//     U->op = op->name;
//     GlobalType ueT = ue->type;
//     if ( ueT.getType() == "InvalidType" ) {
//         U->type.invalid_type = &INVALID_TYPE;
//         return U;
//     }
//     std::string u_op = op->name;
//     U->name = u_op;

//     if ( u_op == "++" || u_op == "--" ) {
//         // check if constant
//         // if ( ueT.is_const == true ) {
//         //     error_msg( "Invalid operand " + u_op + " with constant type",
//         //                op->line_num, op->column );
//         //     U->type.invalid_type = &INVALID_TYPE;
//         //     return U;
//         // }
// 		u_op = u_op.substr( 0, 1 );
// 		if ( ue->type.getType() == "Pointer" ) {
// 			U->type = ue->type;
// 		} else if ( type_specifiers[INT_T].isEqual(*ue->type.standard_type) ) {
// 			U->type = ue->type;
// 		} else if ( type_specifiers[FLOAT_T].isEqual(*ue->type.standard_type) ) {
//             U->type = ue->type;
// 		} else {
// 			// Incorrect type throw error
// 			error_msg( "Invalid operand " + u_op + "with type " +
// 						   ue->type.getType(),
// 					   op->line_num, op->column );
// 			U->type.invalid_type = &INVALID_TYPE;
// 			return U;
// 		}
//     } else if ( u_op == "sizeof" ) {
//         U->name = "sizeof";
//         U->type.standard_type = &type_specifiers[INT_T];
//         // TODO: make it const
//         // U->type.is_const = true;
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
//     GlobalType ceT = ce->type;

//     if ( ceT.getType() == "InvalidType" ) {
//         U->type.invalid_type = &INVALID_TYPE;
//         return U;
//     }

//     if ( u_op == "&" ) {
//         if ( ceT.getType() == "FunctionType" ) {
//             error_msg( "lvalue required as unary & operand", n_op->line_num,
//                        n_op->column );
//             U->type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->type = ce->type;
//         U->type.pointer_type->ptr_level++;
//     } else if ( u_op == "*" ) {
//         if ( ceT.getType() == "ArrayType" ) {
//             // Error because of dereference of non-pointer type
//             error_msg( "Cannot dereference type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->type = ce->type;
// 		U->type.pointer_type->ptr_level--;

//     } else if ( u_op == "-" || u_op == "+" ) {
//         if (type_specifiers[INT_T].isEqual(*ceT.standard_type) || type_specifiers[FLOAT_T].isEqual(*ceT.standard_type)) {
//             // Throw Error
//             error_msg( "Invalid operand " + u_op + " on type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		U->type = ce->type;
// 		U->type.make_signed();

//     } else if ( u_op == "!" ) {
//         if ( !type_specifiers[INT_T].isEqual(*ceT.standard_type) ) {
//             // Throw Error
//             error_msg( "Invalid operand " + u_op + " on type " + ceT.getType(),
//                        n_op->line_num, n_op->column );
//             U->type.invalid_type = &INVALID_TYPE;
//             return U;
//         }
//         U->type.standard_type = &type_specifiers[U_CHAR_T];
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
//     U->type.standard_type = &type_specifiers[INT_T];

//     return U;
// }

// Expression *create_cast_expression_typename(TypeName *tn, Expression *ce)
// {
//     CastExpression *P = new CastExpression();
//     P->op1 = ce;
//     GlobalType ceT = ce->type;
//     GlobalType tnT = tn->type;
//     if ( ceT.getType() == "InvalidType" || tnT.getType() == "InvalidType" ) {
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     }
//     if ( (type_specifiers[INT_T].isEqual(*ceT.standard_type) || type_specifiers[FLOAT_T].isEqual(*ceT.standard_type)) && (type_specifiers[INT_T].isEqual(*tnT.standard_type) || type_specifiers[FLOAT_T].isEqual(*tnT.standard_type)) ) {
//         P->type = tn->type;
//     } else if ( ceT.pointer_type->ptr_level > 0 && tnT.pointer_type->ptr_level > 0 ) {
//         P->type = tn->type;
//     } else {
//         error_msg( "Undefined casting operation of " + ceT.getType() +
//                        " into " + tnT.getType(),
//                    line_num );
//         P->type.invalid_type = &INVALID_TYPE;
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

//     if ( pe->type.getType() == "InvalidType" || exp->type.getType() == "InvalidType" ) {
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     if ( !type_specifiers[INT_T].isEqual(*exp->type.standard_type) ) {
//         // Error
//         error_msg( "Array index must be of type integer", line_num );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

// 	if ( pe->type.getType() == "ArrayType" ) {
// 		P->type = pe->type;
// 		P->type.array_type->dim--;
// 		P->type.array_type->dims.erase( P->type.array_type->dims.begin() );
// 		// P->type.is_const = false; //TODO: make it non-constant
// 	} else if ( pe->type.getType() == "PointerType" ) {
// 		P->type = pe->type;
// 		P->type.pointer_type->ptr_level--;
// 		// P->type.is_const = false; //TODO: make it non-constant
//         // TODO: What type to update to?
// 		// if ( P->type.pointer_type->ptr_level == 0 ) {
// 			// P->type.pointer_type->is_pointer = false;
// 		// }
// 	} else {
// 		error_msg( "Subscripted value is neither array nor pointer",
// 				   line_num );
// 		P->type.invalid_type = &INVALID_TYPE;
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
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.getType() != "FunctionType" ) {
//         // Error
//         error_msg( "Called object '" + fi->value + "' is not a function",
//                    fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.function_type->num_args != 0 ) {
//         // Error
//         error_msg( "Too few arguments to function '" + fi->value + "'",
//                    fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     P->name = "FUNCTION CALL";
//     P->add_children({fi});
//     P->line_num = fi->line_num;
//     P->column = fi->column;

//     P->type = ste->type;
//     P->type.function_type->is_defined = false;
//     P->type.function_type->num_args = 0;
//     P->type.function_type->args.clear();

//     return P;
// }

// Expression *create_postfix_expr_fun( Identifier *fi, ArgumentExprList *ae )
// {
//    PostfixExpression *P = new PostfixExpression();

//     SymTabEntry *ste = global_symbol_table.get_symbol_from_table( fi->value );
//     if ( ste == nullptr ) {
//         // Error
//         error_msg( "Undeclared symbol " + fi->value, fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.getType() != "FunctionType" ) {
//         // Error
//         error_msg( "Called object '" + fi->value + "' is not a function",
//                    fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.function_type->num_args > ae->args.size() ) {
//         // Error
//         error_msg( "Too few arguments to function '" + fi->value +
//                        "'. Expected " + std::to_string( ste->type.function_type->num_args ) +
//                        ", got " + std::to_string( ae->args.size() ),
//                    fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.function_type->num_args < ae->args.size() ) {
//         // Error
//         error_msg( "Too many arguments to function '" + fi->value +
//                        "'. Expected " + std::to_string( ste->type.function_type->num_args ) +
//                        ", got " + std::to_string( ae->args.size() ),
//                    fi->line_num, fi->column );
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     } else if ( ste->type.function_type->num_args == ae->args.size() ) {
//         int i = 0;
//         for (auto itr: ste->type.function_type->args) {
//             if ( itr.second.getType() == "InvalidType" ) {
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             if ( !( itr.second.isEqual(ae->args[i]->type) ) ) {
//                 error_msg( "Type mismatch at argument " + std::to_string( i ) +
//                                " of function '" + fi->value + "'. Expected " +
//                                itr.second.getType() + ", got " +
//                                ae->args[i]->type.getType(),
//                            fi->line_num, fi->column );
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             i++;
//         }
//     }

//     P->name = "FUNCTION CALL";
//     P->add_children({fi, ae});
//     P->line_num = fi->line_num;
//     P->column = fi->column;
//     P->type = ste->type;
//     P->type.function_type->is_defined = false;
//     P->type.function_type->num_args = 0;
//     P->type.function_type->args.clear();

//     return P;
// }

// Expression *create_postfix_expr_struct( std::string access_op, Expression *pe, Identifier *id){
//     PostfixExpression *P = new PostfixExpression();

//     if ( pe->type.getType() == "InvalidType" ) {
//         P->type.invalid_type = &INVALID_TYPE;
//         return P;
//     }

//     GlobalType peT = pe->type;
//     if ( access_op == "." ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->type.pointer_type->ptr_level == 0 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " +
//                                pe->type.getType(),
//                            id->line_num, id->column );
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             // whether i exists in Struct
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType == nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             } else {
//                 P->type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand . with type " + pe->type.getType(), id->line_num,
//                        id->column );
//             P->type.invalid_type = &INVALID_TYPE;
//             return P;
//         }
//     } else if ( access_op == "->" ) {
//         if ( ( peT.getType() == "Struct" || peT.getType() == "Union" ) && pe->type.pointer_type->ptr_level == 1 ) {
//             if ( peT.struct_type == nullptr ) {
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             }
//             // whether i exists in Struct*
//             GlobalType iType = *peT.union_type->definition->get_member( id );
//             if ( iType==nullptr ) {
//                 // Error
//                 error_msg( id->value + " is not a member of " + peT.getType(),
//                            id->line_num, id->column );
//                 P->type.invalid_type = &INVALID_TYPE;
//                 return P;
//             } else {
//                 P->type = iType;
//             }
//         } else {
//             error_msg( "Invalid operand -> with type " + pe->type.getType(),
//                        id->line_num, id->column );
//             P->type.invalid_type = &INVALID_TYPE;
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

//     if ( pe->type.getType() == "InvalidType" ) {
//         P->type.invalid_type = &INVALID_TYPE;
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
// 	if ( pe->type.is_const == true ) {
// 		error_msg( "Invalid operand " + op->name + " with constant type",
// 				   op->line_num, op->column );
// 		P->type.invalid_type = &INVALID_TYPE;
// 		return P;
// 	}

// 	if ( pe->type.pointer_type->ptr_level > 0 ) {
// 		P->type = pe->type;
// 		GlobalType t = pe->type;
// 		t.pointer_type->ptr_level--;
// 	} else if ( type_specifiers[INT_T].isEqual(*pe->type.standard_type) ) {
// 		P->type = pe->type;
// 	} else if ( type_specifiers[FLOAT_T].isEqual(*pe->type.standard_type) ) {
// 		P->type = pe->type;
// 	} else {
// 		// Error postfix operator
// 		error_msg( "Invalid operand " + op->name + " with type " +
// 					   pe->type.getType(),
// 				   op->line_num, op->column );
// 		P->type.invalid_type = &INVALID_TYPE;
// 		return P;
// 	}

//     P->add_children({pe});
//     return P;
// }

// // Unary Expression
// Expression *create_unary_expression( Terminal *op, Expression *ue ) {
//     UnaryExpression *U = new UnaryExpression();
//     U->op1 = ue;
//     U->op = op->name;
//     GlobalType ueT = ue->type;
//     if ( ueT.getType() == "InvalidType" ) {
//         U->type.invalid_type = &INVALID_TYPE;
//         return U;
//     }
//     std::string u_op = op->name;
//     U->name = u_op;
//     Address *inc_value = nullptr;

//     if ( u_op == "++" || u_op == "--" ) {
//         if ( ueT.is_const == true ) {
//             error_msg( "Invalid operand " + u_op + " with constant type",
//                        op->line_num, op->column );
//             U->type.invalid_type = &INVALID_TYPE;
//             return U;
//         }

// 		u_op = u_op.substr( 0, 1 );
// 		if ( ue->type.getType() == "PointerType" ) {
// 			U->type = ue->type;
// 			GlobalType t = ue->type;
// 			t.pointer_type->ptr_level--;
// 		} else if ( ue->type.getType() == "StandardType" ) {
// 			U->type = ue->type;
// 		} else if ( ue->type.getType() == "FloatType" ) {
// 			U->type = ue->type;
// 		} else {
// 			// Incorrect type throw error
// 			error_msg( "Invalid operand " + u_op + " with type " +
// 						   ue->type.getType(),
// 					   op->line_num, op->column );
// 			U->type.invalid_type = &INVALID_TYPE;
// 			return U;
// 		}
//     } else if ( u_op == "sizeof" ) {
//         U->name = "sizeof";
//         U->type.standard_type = &type_specifiers[PrimitiveTypes::INT_T];
//         U->type.pointer_type->ptr_level = 0;
//         // U->type.is_const = true;
//     } else {
//         // Raise Error
//         std::cerr << "Error parsing Unary Expression.\n";
//         std::cerr << "ERROR at line " << line_num << "\n";
//         exit( 0 );
//     }
//     U->add_children({ue});
//     return U;
// }

Expression *create_expression(ExpressionOpType op_type, std::string op,VectorExpression* ve)
{
    OpExpression *oe = new OpExpression();
    oe->op_type = op_type;
    oe->op = op;
    switch (op_type)
    {
    case MULTIPLICATIVE:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return multiplicative_expression(oe);
    case ADDITIVE:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return additive_expression(oe);
    case RELATIONAL:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return relational_expression(oe);
    case SHIFT:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return shift_expression(oe);
    case EQUALITY:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return equality_expression(oe);
    case AND:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return and_expression(oe);
    case XOR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return xor_expression(oe);
    case OR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return or_expression(oe);
    case LOGICAL_AND:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_and_expression(oe);
    case LOGICAL_OR:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        return logical_or_expression(oe);
    case CONDITIONAL:
        oe->op1 = ve->operands[0];
        oe->op2 = ve->operands[1];
        oe->op3 = ve->operands[2];
        return conditional_expression(oe);
    case CONSTANT:
        oe->op1 = ve->operands[0];
        return constant_expression(oe);
    case TOPLEVEL:
        oe->op1 = ve->operands[0];
        return toplevel_expression(oe);
    default:
        std::cerr << "Incorrect expression. Something went wrong\n";
        return nullptr;
    }
}