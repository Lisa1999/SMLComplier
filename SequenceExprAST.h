#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

// exp ::= ( exp ) expr ---------- skip the AST class

// exp ::= ( exp , exp , ... , exp ) expr

class SequenceExprAST : public ExprAST {
  vector<ExprAST *> _exprVec;
  Expr1AST *_expr1;

public:
  SequenceExprAST(vector<ExprAST *> _exprVec, Expr1AST *_expr1) {
    this->_exprVec = _exprVec;
    this->_expr1 = _expr1;
  };
  Value *codegen();
  ~SequenceExprAST();
};
