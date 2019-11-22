#pragma once
#include"ASTGen.h"
//#include"GeneralFile.h"

class ExprAST : public ASTGen {
public:
  Value *codegen();

  ~ExprAST();
};
