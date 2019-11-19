#pragma once
#include"ASTGen.h"
class Patt1AST : public ASTGen {
public:
  //Patt1();

  Value *codegen();
  ~Patt1AST();
};
