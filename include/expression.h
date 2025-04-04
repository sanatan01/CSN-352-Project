#pragma once

#include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <symtab.h>
// #include <3ac.h>


// --------------------------------------------------------------------------------------------

class ConstantType{
public:
  int type;
  int ptr_level;
  std::string value;

  ConstantType(int type, int ptr_level=0) {
    this->type = type;
    this->ptr_level = ptr_level;
  }
};

class Expression {
public:
  ConstantType type;
  int num_operands;
  // Address* res;
  // std::vector<GoTo*> truelist;
  // std::vector<GoTo*> falselist;

  Expression(ConstantType type, int num_operands):
    type(type), num_operands(num_operands) {};
  Expression() : type(ConstantType(ERROR_T)), num_operands(0) {};
};

class VectorExpression: public Expression {
public:
  std::vector<Expression> operands;
  VectorExpression() {
    this->operands = std::vector<Expression>();
  };
  void add_element(Expression* e) {
    this->operands.push_back(*e);
  };
  void add_elements(std::vector<Expression> elements) {
    this->operands.insert(this->operands.end(), elements.begin(), elements.end());
  };
};
// --------------------------------------------------------------------------------------------
union ExpressionType {
  Identifier* id;
  ConstantType* constant;
  Expression* exp;
};

class PrimaryExpression: public Expression {
public:
  ExpressionType type;
  PrimaryExpression();
};

// Grammar warppers for PrimaryExpression
Expression* create_primary_expression(ExpressionType* typ);

// --------------------------------------------------------------------------------------------
class ArgumentExprList: public Expression {
public:
  std::vector <Expression* > args;
  ArgumentExprList() ;
};

// Grammar warppers for ArguementExpressionList
ArgumentExprList* create_argument_expr_assignement(Expression* ase);
ArgumentExprList* create_argument_expr_list(ArgumentExprList* ae_list, Expression* ase);

// --------------------------------------------------------------------------------------------
enum ExpressionOpType {
  MULTIPLICATIVE,
  ADDITIVE,
  SHIFT,
  RELATIONAL,
  EQUALITY,
  AND,
  XOR,
  OR,
  LOGICAL_AND,
  LOGICAL_OR,
  CONDITIONAL,
  CONSTANT,
  TOPLEVEL,
  ASSIGNMENT
};

class OpExpression: public Expression {
public:
  Expression op1;
  Expression op2;
  Expression op3;
  ExpressionOpType op_type;
  std::string op;

  OpExpression(): Expression(ConstantType(ERROR_T), 2) {
    op1 = Expression();
    op2 = Expression();
    op3 = Expression();
    op_type = TOPLEVEL;
    op = "";
  }
};

// Grammar wrapper for OpExpression
Expression* create_expression(ExpressionOpType op_type, std::string op, VectorExpression* ve);

//-------------------------------------------------
class UnaryExpression: public Expression {
public:
  Expression* op1;
  std::string op;

  UnaryExpression() : Expression(ConstantType(ERROR_T), 1) {
    op1 = nullptr;
    op = "";
  }
};

// Grammar warppers for UnaryExpression
Expression* create_unary_expression(Terminal* op, Expression* ue); // INC_OP, DEC_OP, SIZEOF
Expression* create_unary_expression_cast(Node* n_op, Expression* ce);
// Expression* create_unary_expression(Terminal* op, TypeName* t_name);

// --------------------------------------------------------------------------------------------

class CastExpression: public Expression {
public:
  Expression* op1;
  /**
    Index of Type casted to in GlobalTypes
    -1 if there is no casting
  */
  int typeCast;

  CastExpression() : Expression(ConstantType(ERROR_T), 1) {
    op1 = nullptr;
    typeCast = -1;
  };
};

// Grammar wrapper for CastExpression
// Expression* create_cast_expression_typename(TypeName* tn, Expression* ce); // type_name wala add krna hai// can change string to node* later for assignment operator

// --------------------------------------------------------------------------------------------
class PostfixExpression: public Expression {
public:
  PostfixExpression* pe;
  Expression* exp;
  Identifier* id;
  ArgumentExprList* ae_list;
  std::string op;

  PostfixExpression(): Expression(ConstantType(ERROR_T), 0) {
    pe = nullptr;
    exp = nullptr;
    id = nullptr;
    ae_list = nullptr;
    op = "";
  };
};

// Grammar for PostfixExpression
Expression* create_postfix_expr_arr(Expression* pe, Expression* exp);
Expression* create_postfix_expr_voidfun(Identifier* fi);
Expression* create_postfix_expr_fun(Identifier* fi, ArgumentExprList* ae);
Expression* create_postfix_expr_struct(std::string access_op, Expression* pe, Identifier* id);
Expression* create_postfix_expr_ido(Terminal* op, Expression* pe);

// // --------------------------------------------------------------------------------------------
// class Constant {
// public:
//   ConstantType constant_type;

//   Constant(std::string name, std::string value, int type, unsigned int line_num=0, unsigned int column=0):
//     constant_type(ConstantType(type)) {}

//   int getConstantType() {
//     return constant_type.type;
//   }
//   void negate();

// };

//Constant* create_constant(const char* name, const char* value, unsigned int line_num, unsigned int column);

Expression *create_assignment_expression(OpExpression *oe, Node *n_op);