#pragma once

#include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <symtab.h>
#include <3ac.h>


enum ConstantTypeEnum{
  INVALID=0,
  BOOL,
  CHAR,
  UNSIGNED_CHAR,
  SHORT,
  UNSIGNED_SHORT,
  INT,
  UNSIGNED_INT,
  LONG,
  UNSIGNED_LONG,
  LONG_LONG,
  UNSIGNED_LONG_LONG,
  FLOAT,
  UNSIGNED_FLOAT,
  DOUBLE,
  UNSIGNED_DOUBLE,
  LONG_DOUBLE,
  UNSIGNED_LONG_DOUBLE,
  STRING,
};

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
  Address* res;
  std::vector<GoTo*> truelist;
  std::vector<GoTo*> falselist;

  Expression(ConstantType type, int num_operands, Address* res, std::vector<GoTo*> truelist, std::vector<GoTo*> falselist):
    type(type), num_operands(num_operands), res(res), truelist(truelist), falselist(falselist) {};
};

// --------------------------------------------------------------------------------------------
union ExpressionType {
  Identifier* id;
  StringLiteral* str;
  Constant* con;
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
  ArgumentExprList() {};
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

  OpExpression();
};

// Grammar wrapper for OpExpression
Expression* create_expression(ExpressionOpType op_type, std::string op, std::initializer_list<Expression> operands);

//-------------------------------------------------
class UnaryExpression: public Expression {
public:
  Expression* op1;
  std::string op;

  UnaryExpression() {
    op1 = nullptr;
    op = "";
  }
};

// Grammar warppers for UnaryExpression
Expression* create_unary_expression(Terminal* op, Expression* ue); // INC_OP, DEC_OP, SIZEOF
Expression* create_unary_expression_cast(Node* n_op, Expression* ce);
Expression* create_unary_expression(Terminal*, TypeName* t_name);

// --------------------------------------------------------------------------------------------

class CastExpression: public Expression {
public:
  Expression* op1;
  /**
    Index of Type casted to in GlobalTypes
    -1 if there is no casting
  */
  int typeCast;

  CastExpression() {
    op1 = nullptr;
    typeCast = -1;
  };
};

// Grammar wrapper for CastExpression
Expression* create_cast_expression_typename(TypeName* tn, Expression* ce); // type_name wala add krna hai// can change string to node* later for assignment operator

// --------------------------------------------------------------------------------------------
class PostfixExpression: public Expression {
public:
  PostfixExpression* pe;
  Expression* exp;
  Identifier* id;
  ArgumentExprList* ae_list;
  std::string op;

  PostfixExpression() {
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

// --------------------------------------------------------------------------------------------
class Constant {
public:
  Constant(std::string name, std::string value, unsigned int line_num=0, unsigned int column=0):
    name(name), value(value), line_num(line_num), column(column) {
    constant_type.type = "constant";
  }
  ConstantType constant_type;

  int getConstantType() {
    return constant_type.type;
  }
  void negate();

};

Constant* create_constant(const char* name, const char* value, unsigned int line_num, unsigned int column);

// --------------------------------------------------------------------------------------------
class StringLiteral: public Constant {
public:
  StringLiteral(int name){
    constant_type.type = STRING;
    constant_type.value = name;
  }
};

Expression *create_assignment_expression(OpExpression *oe, Node *n_op);