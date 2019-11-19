#pragma once
#include"ExprAST.h"
#include"Expr1AST.h"

//enum Identifier {
//  IdAlpha,  //×ÖÄ¸Ãû×Ö
//  IdSymbol //·ûºÅÃû×Ö
//};

class IdExprAST : public ExprAST {
public:
  string _identifier;
  Expr1AST *_expr1;

  IdExprAST(string _identifier, Expr1AST *_expr1) {
    this->_identifier = _identifier;
    this->_expr1 = _expr1;
  };

  string codegenStr();

  ~IdExprAST();
};
