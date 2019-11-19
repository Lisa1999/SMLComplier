#pragma once
#include "PattAST.h"
#include "Patt1AST.h"

class RealPattAST : public PattAST {
  double _realVal;
  Patt1AST *_patt1;

public:
  RealPattAST(double _realVal, Patt1AST *_patt1) {
    this->_realVal = _realVal;
    this->_patt1 = _patt1;
  };
  Value *codegen();
  ~RealPattAST();
};
