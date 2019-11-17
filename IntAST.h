#pragma once
#include"ASTGen.h"
class IntAST : public ASTGen {
public:
  int _int;

  IntAST(int _int) 
  { this->_int = _int; 
  };

  Value* codegen();
  virtual ~IntAST();
};
