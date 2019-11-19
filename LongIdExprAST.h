#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

class LongIdExprAST : public ExprAST {
  string _longIdName;
  Expr1AST *_expr1;

public:
  LongIdExprAST(string _longIdName, Expr1AST *_expr1) {
    this->_longIdName = _longIdName;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~LongIdExprAST();
};
