#pragma once
#include"ASTGen.h"
class StringAST : public ASTGen {
public:
  string _string;

  StringAST(string _string) { this->_string = _string; };
  Value *codegen();
  ~StringAST();
};
