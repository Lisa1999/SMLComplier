#pragma once
#include "ExprAST.h"
#include"Expr1AST.h"

class WordExprAST : public ExprAST {
public:
  int _word;
  Expr1AST *_expr1;
  WordExprAST(int _word, Expr1AST *_expr1) {
    this->_word = _word;
    this->_expr1 = _expr1;
  };

  Value *codegen();
  
  ~WordExprAST();
};
