#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

// exp ::= [ exp , exp , ... , exp ] expr

class ListExprAST : public ExprAST{
public:
  vector<ExprAST *> _exprVec;
  Expr1AST *_expr1;

  ListExprAST(vector<ExprAST *> _exprVec, Expr1AST *_expr1) {
    this->_exprVec = _exprVec;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~ListExprAST();
};
