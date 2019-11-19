#pragma once
#include"PattAST.h"

// pat ::= (pat , pat , ... , pat) patt -- delete
// pat ::= (pat , pat , ... , pat)
class TuplePattAST {
  vector<PattAST *> _pattVec;

public:
  TuplePattAST(vector<PattAST *> _pattVec) { this->_pattVec = _pattVec; }
  Value *codegen();
  ~TuplePattAST();
};
