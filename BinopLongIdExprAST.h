#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

// exp ::= op longid expr
class BinopLongIdExprAST : public ExprAST {
  char _op;
  string _longIdName;
  Expr1AST *_expr1;

public:
  BinopLongIdExprAST(char _op, string _longIdName, Expr1AST *_expr1) {
    this->_op = _op;
    this->_longIdName = _longIdName;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~BinopLongIdExprAST();
};
