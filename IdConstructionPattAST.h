#pragma once
#include"PattAST.h"

// pat ::= id pat
class IdConstructionPattAST : public PattAST {
  string _idName;
  PattAST *_patt;

public:
  IdConstructionPattAST(string _idName, PattAST *_patt) {
    this->_idName = _idName;
    this->_patt = _patt;
  };
  Value *codegen();
  ~IdConstructionPattAST();
};
