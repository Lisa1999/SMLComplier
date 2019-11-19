#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

class StringExprAST : public ExprAST {
public:
  string _string;
  Expr1AST *_expr1;

  StringExprAST(string _string, Expr1AST *_expr1) {
    this->_string = _string;
    this->_expr1 = _expr1;
  };

  Value *codegen();
  ~StringExprAST();
};
