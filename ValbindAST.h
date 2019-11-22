#pragma once
#include"ExprAST.h"
#include"PattAST.h"


class ValbindAST: public ASTGen{
public:
  ExprAST *_expr;
  PattAST *_patt;

  ValbindAST(PattAST *_patt, ExprAST *_expr) {
        this->_patt = _patt;
		this->_expr = _expr;

  };

  Value *codegen();

  ~ValbindAST();
};
