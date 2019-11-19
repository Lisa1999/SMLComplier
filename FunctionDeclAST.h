#pragma once
#include"FunbindAST.h"
#include"DecAST.h"
#include"Dec1AST.h"

// dec ::= fun (var)(') funbind---delete
// dec ::= fun funbind
class FunctionDeclAST : public DecAST {
  FunbindAST *_funbind;
  Dec1AST *_decl;

public:
  FunctionDeclAST(FunbindAST *_funbind, Dec1AST *_decl) {
    this->_funbind = _funbind;
    this->_decl = _decl;
  };
  Value *codegen();
  ~FunctionDeclAST();
};
