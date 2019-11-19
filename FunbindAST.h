#pragma once
#include"FunmatchAST.h"

// funbind ::= funmatch(and funbind) --- delete
// funbind ::= funmatch(| funmatch)

class FunbindAST {
public:
  vector<FunmatchAST *> _funmatch;

  FunbindAST(vector<FunmatchAST *> _funmatch) { this->_funmatch = _funmatch; };
  Value *codegen();
  ~FunbindAST();
};
