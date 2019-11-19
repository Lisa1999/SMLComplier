#pragma once
#include"PattAST.h"
#include"Patt1AST.h"

class CharPattAST : public PattAST {
  char _charVal;
  Patt1AST *_patt1;

public:
  CharPattAST(const char _charVal, Patt1AST *_patt1) {
    this->_charVal = _charVal;
    this->_patt1 = _patt1;
  };
  Value *codegen();
  ~CharPattAST();
};
