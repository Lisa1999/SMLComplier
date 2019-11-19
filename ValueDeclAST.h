#pragma once
#include"DecAST.h"
#include"Dec1AST.h"
#include"ValbindAST.h"

// dec ::= val (var)(') valbind ---delete
// dec ::= val valbind
class ValueDeclAST : public DecAST {
  ValbindAST *_valbind;
  Dec1AST *_dec1;

public:
  ValueDeclAST(ValbindAST *_valbind, Dec1AST *_dec1) {
    this->_valbind = _valbind;
    this->_dec1 = _dec1;
  };
  Value *codegen();
  ~ValueDeclAST();
};
