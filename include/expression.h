#pragma once

#include <ast.h>
#include <deque>
#include <map>
#include <string>
#include <symtab.h>
#include <types.h>
#include <unordered_map>
// #include <3ac.h>

// --------------------------------------------------------------------------------------------

// class PrimitiveTypes{
// public:
//   int type;
//   int ptr_level;
//   std::string value;

//   PrimitiveTypes(int type, int ptr_level=0) {
//     this->type = type;
//     this->ptr_level = ptr_level;
//   }
// };

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
  EXPRESSION_ET
};

extern std::unordered_map<std::string, PrimitiveTypes> type_map;

class Expression {
public:
  int num_operands;
  bool is_assignable;
  class GlobalType* exp_type;
  int prim_type;

  std::string name;
  // Address* res;
  // std::vector<GoTo*> truelist;
  // std::vector<GoTo*> falselist;

  Expression(PrimitiveTypes type, int num_operands);
  Expression();
  Expression(class GlobalType* type);
  void printExpression();
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


Expression* create_primary_expression(int typ, std::string name);


// // --------------------------------------------------------------------------------------------
// class ArgumentExprList: public Expression {
// public:
//   std::vector <Expression* > args;
//   ArgumentExprList() ;
// };

// // Grammar warppers for ArguementExpressionList
// ArgumentExprList* create_argument_expr_assignement(Expression* ase);
// ArgumentExprList* create_argument_expr_list(ArgumentExprList* ae_list, Expression* ase);

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

// // --------------------------------------------------------------------------------------------
// class Constant {
// public:
//   PrimitiveTypes constant_type;

//   Constant(std::string name, std::string value, int type, unsigned int line_num=0, unsigned int column=0):
//     constant_type(PrimitiveTypes(type)) {}

//   int getConstantType() {
//     return constant_type.type;
//   }
//   void negate();

// };

//Constant* create_constant(const char* name, const char* value, unsigned int line_num, unsigned int column);

Expression *create_assignment_expression(OpExpression *oe, Node *n_op);