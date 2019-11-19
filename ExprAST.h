#pragma once
#include"ASTGen.h"
class ExprAST : public ASTGen{
public:
  Value *codegen();

  ~ExprAST();
};
