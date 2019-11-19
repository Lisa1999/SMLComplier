#pragma once
#include"ASTGen.h"

class DecAST : public ASTGen{
public:
  //DecAST();

	Value *codegen();
  ~DecAST();


};
