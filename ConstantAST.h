#pragma once
#include"NumberAST.h"
#include"StringAST.h"
#include"CharAST.h"
#include"BoolValAST.h"

class ConstantAST : public ASTGen {
public:
  NumberAST *numberAST = nullptr;
  StringAST *stringAST = nullptr;
  CharAST *charAST = nullptr;
  BoolValAST *boolValAST = nullptr;

  ConstantAST(NumberAST *numberAST);
  ConstantAST(StringAST *stringAST);
  ConstantAST(CharAST *charAST);
  ConstantAST(BoolValAST *boolValAST);
  Value *codegen();
  virtual ~ConstantAST();
};
