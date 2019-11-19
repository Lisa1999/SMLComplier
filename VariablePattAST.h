#pragma once
#include"PattAST.h"
#include"Patt1AST.h"

// pat ::= id patt
class VariablePattAST : public PattAST {
  string _idName;
  Patt1AST *_patt;

public:
  VariablePattAST(string &_idName, Patt1AST *_patt) {
    this->_idName = _idName;
    this->_patt = _patt;
  };
  Value *codegen();
  ~VariablePattAST();
};
