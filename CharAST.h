#pragma once
#include"ASTGen.h"
class CharAST : public ASTGen {
public:
  char _char;

  CharAST(char _char) { this->_char = _char; };
  //Value *codegen();
  ~CharAST();
};
