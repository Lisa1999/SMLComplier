#include "IntExprAST.h"

Value *IntExprAST::codegen() {
  return ConstantInt::get(TheContext, APInt(32, _int));
}


IntExprAST::~IntExprAST() {}
