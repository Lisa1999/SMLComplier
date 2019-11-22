#pragma once
#include"PattAST.h"

// pat ::= id
class IdPattAST : public PattAST{
  string _idName;

public:
  IdPattAST(string _idName) { this->_idName = _idName; };
  Value *codegen();
  ~IdPattAST();
};
