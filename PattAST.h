#pragma once
#include"ASTGen.h"
class PattAST : public ASTGen{
public:
  //PattAST();
  Value *codegen();
  ~PattAST();
};
