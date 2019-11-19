#pragma once
#include"DecAST.h"
#include"Dec1AST.h"

class Dec2AST:public Dec1AST{
public:
  DecAST *_dec;
  Dec1AST *_dec1;
  
  Dec2AST(DecAST *_dec, Dec1AST *_dec1) {
    this->_dec = _dec;
    this->_dec1 = _dec1;
  };
  Value *codegen();
  ~Dec2AST();
};
