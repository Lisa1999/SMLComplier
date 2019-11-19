#pragma once
#include"DecAST.h"
#include"Dec1AST.h"

// dec ::= local dec in dec end
class LocalDecAST {
  DecAST *_local;
  DecAST *_in;
  Dec1AST *_dec1;

public:
  LocalDecAST(DecAST *_local, DecAST *_in, Dec1AST *_dec1) {
    this->_local = _local;
    this->_in = _in;
    this->_dec1 = _dec1;
  };
  Value *codegen();
  ~LocalDecAST();
};
