#pragma once
#include"ExprAST.h"
#include"PattAST.h"


class ValbindAST: public ASTGen{
public:
  ExprAST *_expr;
  PattAST *_patt;

  ValbindAST(ExprAST *_expr, PattAST *_patt) {
    this->_expr = _expr;
    this->_patt = _patt;
  };

  Value *codegen();

  ~ValbindAST();
};
