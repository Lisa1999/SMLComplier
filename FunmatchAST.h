#pragma once
#include"PattAST.h"
#include"ExprAST.h"

// funmatch ::= id pat ... pat = exp(| funmatch) -- delete
// funmatch ::= id pat ... pat = exp

class FunmatchAST {
  string _strId;
  ExprAST *_expr;
  vector<PattAST *> _pattVec;


public:
  FunmatchAST(string _strId, vector<PattAST *> _pattVec, ExprAST *_expr) {
    this->_strId = _strId;
    this->_pattVec = _pattVec;
    this->_expr = _expr;
  };

  Value *codegen();

  ~FunmatchAST();
};
