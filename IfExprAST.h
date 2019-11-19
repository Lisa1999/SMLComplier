#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

// exp ::= if exp then exp else exp expr

class IfExprAST :public ExprAST{
  ExprAST *_condition;
  ExprAST *_then;
  ExprAST *_else;
  Expr1AST *_expr1;

public:
  IfExprAST(ExprAST *_condition, ExprAST *_then, ExprAST *_else,
            Expr1AST *_expr1) {
    this->_condition = _condition;
    this->_then = _then;
    this->_else = _else;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~IfExprAST();
};
