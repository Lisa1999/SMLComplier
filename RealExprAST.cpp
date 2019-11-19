#include "RealExprAST.h"

Value *RealExprAST::codegen() {
  return ConstantFP::get(TheContext, APFloat(_real));
}



RealExprAST::~RealExprAST() {}
