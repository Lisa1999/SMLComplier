#pragma once
#include"PattAST.h"
#include"Patt1AST.h"

class StringPattAST : public PattAST {
  string _stringVal;
  Patt1AST *_patt1;

public:
  StringPattAST(const string &_stringVal, Patt1AST *_patt1) {
    this->_stringVal = _stringVal;
    this->_patt1 = _patt1;
  };
  Value *codegen();
  ~StringPattAST();
};
