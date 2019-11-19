#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

class IdExprExpr1 : public Expr1AST{
  string _idName;
  ExprAST *_expr;
  Expr1AST *_expr1;

public:
  IdExprExpr1(string _idName, ExprAST *_expr, Expr1AST *_expr1) {
    this->_idName = _idName;
    this->_expr = _expr;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~IdExprExpr1();
};
