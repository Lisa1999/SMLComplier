#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

class IntExprAST : public ExprAST {
public:
  int _int;
  Expr1AST *_expr1;

  IntExprAST(int _int, Expr1AST *_expr1) { 
	  this->_int = _int; 
	  this->_expr1 = _expr1;
  };

  Value* codegen();
  virtual ~IntExprAST();
};
