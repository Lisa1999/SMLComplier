#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"
class CharExprAST : public ExprAST {
public:
  char _char;
  Expr1AST *_expr1;

  CharExprAST(char _char, Expr1AST *_expr1) {
    this->_char = _char;
    this->_expr1 = _expr1;
  };

  Value *codegen();
  ~CharExprAST();
};
