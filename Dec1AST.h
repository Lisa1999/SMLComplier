#pragma once
#include"ASTGen.h"

class Dec1AST : public ASTGen{
public:
  //Dec1AST();
  
	Value *codegen();
	~Dec1AST();
};
