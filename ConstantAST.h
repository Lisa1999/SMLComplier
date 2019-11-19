#pragma once
#include"StringExprAST.h"
#include"CharExprAST.h"
#include"IntExprAST.h"
#include"WordExprAST.h"
#include"RealExprAST.h"

class ConstantAST : public ASTGen {
public:
	
  StringExprAST *stringAST = nullptr;
  CharExprAST *charAST = nullptr;

  ConstantAST();
  Value *codegen();
  virtual ~ConstantAST();
};
