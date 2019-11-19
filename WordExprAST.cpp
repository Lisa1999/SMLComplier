#include "WordExprAST.h"

Value *WordExprAST::codegen() {
  return ConstantInt::get(TheContext, APInt(32, _word));
}

WordExprAST::~WordExprAST() {}
