#pragma once
#include"DecAST.h"
#include"ExprAST.h"
#include"Expr1AST.h"

// exp ::= let dec then exp ; exp ; ... ; exp end expr

class LetExprAST :public ExprAST{
	DecAST *_let;
    vector<ExprAST *> _exprVec;
	Expr1AST *_expr1;

public:
    LetExprAST(DecAST *_let, vector<ExprAST *> _exprVec, Expr1AST *_expr1) {
		this->_let = _let;
        this->_exprVec = _exprVec;
        this->_expr1 = _expr1;
    };
    Value *codegen();
  ~LetExprAST();
};
