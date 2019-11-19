#pragma once
#include"PattAST.h"
#include"Patt1AST.h"

// pat ::= con patt
class IntPattAST : public PattAST {
  int _intVal;
  Patt1AST *_patt1;

public:
  IntPattAST(int _intVal, Patt1AST *_patt1) {
    this->_intVal = _intVal;
    this->_patt1 = _patt1;
  };
  Value *codegen();
  ~IntPattAST();
};
