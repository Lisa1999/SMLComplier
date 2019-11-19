#pragma once
#include"PattAST.h"

// pat ::= id as pat patt
class IdAsPattAST : public PattAST {
  string _idName;
  PattAST *_patt;

public:
  IdAsPattAST(string _idName, PattAST *_patt) {
    this->_idName = _idName;
    this->_patt = _patt;
  };
  Value *codegen();
  ~IdAsPattAST();
};
