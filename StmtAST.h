#pragma once
#include"ASTGen.h"

class StmtAST :public ASTGen{
public:
  //StmtAST();
  Value *codegen();
  ~StmtAST();
};
