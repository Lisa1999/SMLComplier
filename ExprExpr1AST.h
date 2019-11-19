#pragma once
#include "Expr1AST.h"
#include "ExprAST.h"

// expr ::= exp expr
class ExprExpr1AST : public Expr1AST{
  ExprAST *_expr;
  Expr1AST *_expr1;

public:
  ExprExpr1AST(ExprAST *_expr, Expr1AST *_expr1) {
    this->_expr = _expr;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~ExprExpr1AST();
};
