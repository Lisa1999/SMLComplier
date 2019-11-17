#pragma once
#include"IntAST.h"
#include"RealAST.h"

class NumberAST : public ASTGen {
public:
  int type; // 0 int    1 real
  IntAST *_int = nullptr;
  RealAST *_real = nullptr;

  NumberAST(IntAST *_int);         // type= 0
  NumberAST(RealAST *_real); // type =1
  Value *codegen();

  ~NumberAST();
};
