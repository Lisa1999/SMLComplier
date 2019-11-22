#pragma once
//#include"ASTGen.h"
#include"GeneralFile.h"

class StmtAST {
public:
  //StmtAST();
  Value *codegen();
  ~StmtAST();
};
