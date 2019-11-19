#pragma once
#include "Patt1AST.h"
#include "PattAST.h"
class IdPattPatt1AST : public PattAST {
  string _idName;
  PattAST *_patt;
  Patt1AST *patt1;

public:
  IdPattPatt1AST(string &_idName, PattAST *_patt, Patt1AST *_patt1) {
    this->_idName = _idName;
    this->_patt = _patt;
    this->patt1 = _patt1;
  };
  Value *codegen();
  ~IdPattPatt1AST();
};
