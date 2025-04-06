#pragma once

#include <deque>
#include <map>
#include <string>
#include <symtab.h>
#include <types.h>
#include <unordered_map>

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
  ASSIGNMENT,
  CAST_TYPE,
  UNARY
};

enum ExpressionType {
  IDENTIFIER_ET,
  CONSTANT_ET,
  EXPRESSION_ET,
  STRING_ET,
};

extern std::unordered_map<std::string, PrimitiveTypes> type_map;

class Expression {
public:
  int num_operands;
  bool is_assignable;
  class GlobalType* exp_type;
  int prim_type;

  std::string name;
  Expression(PrimitiveTypes type, int num_operands);
  Expression();
  Expression(class GlobalType* type);
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

Expression* create_expression_simple(ExpressionType exp_type, std::string token);
Expression* create_expression(ExpressionOpType op_type, std::string op, VectorExpression* ve);

// --------------------------------------------------------------------------------------------


class OpExpression: public Expression {
public:
  Expression op1;
  Expression op2;
  Expression op3;
  ExpressionOpType op_type;
  std::string op;

  OpExpression(): Expression(PrimitiveTypes(ERROR_T), 2) {
    op1 = Expression();
    op2 = Expression();
    op3 = Expression();
    op_type = TOPLEVEL;
    op = "";
  }
};

// Grammar wrapper for OpExpression

//-------------------------------------------------
class UnaryExpression: public Expression {
public:
  Expression* op1;
  std::string op;

  UnaryExpression() : Expression(PrimitiveTypes(ERROR_T), 1) {
    op1 = nullptr;
    op = "";
  }
};

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

  CastExpression() : Expression(PrimitiveTypes(ERROR_T), 1) {
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
  VectorExpression* ae_list;
  std::string op;

  PostfixExpression(): Expression(PrimitiveTypes(ERROR_T), 0) {
    pe = nullptr;
    exp = new Expression();
    id = nullptr;
    ae_list = nullptr;
    op = "";
  };
};

// Grammar for PostfixExpression
Expression* create_postfix_expr_arr(Expression* pe, Expression* exp);
Expression* create_postfix_expr_voidfun(Identifier* fi);
Expression* create_postfix_expr_fun(Identifier* fi, VectorExpression* ae);
Expression* create_postfix_expr_struct(std::string access_op, Expression* pe, Identifier* id);
Expression* create_postfix_expr_ido(std::string  op, Expression* pe);



bool isCompatible(class GlobalType *left, class GlobalType *right);
bool isCompatiblePrim(PrimitiveTypes p1, PrimitiveTypes p2);
PrimitiveTypes getPrimitiveType(std::string type);

bool is_expr_signed(class Expression* expr);
bool is_expr_unsigned(class Expression* expr);

void error_msg(std::string msg, int line_num = 0, int column = 0);
void warning_msg(std::string msg, int line_num = 0, int column = 0);
void debug_msg(std::string msg, int line_num = 0, int column = 0);

class Expression* prim_to_type(class Expression* expr);