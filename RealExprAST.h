#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

class RealExprAST : public ExprAST {
public:
  double _real;
  Expr1AST *_expr1;

  RealExprAST(double _real, Expr1AST *_expr1) {
    this->_real = _real;
    this->_expr1 = _expr1;
  };

  Value *codegen();
  ~RealExprAST();
};
