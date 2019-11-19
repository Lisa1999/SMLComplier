#pragma once
#include "PattAST.h"

// pat ::= op id patt
class BinopIdPattAST : public PattAST {
  char _op;
  string _idName;
  PattAST *_patt;

public:
  BinopIdPattAST(char _op, string &_idName, PattAST *_patt) {
    this->_op = _op;
    this->_idName = _idName;
    this->_patt = _patt;
  };
  Value *codegen();
  ~BinopIdPattAST();
};
