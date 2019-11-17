#include "RealAST.h"

Value *RealAST::codegen() 
{
  return ConstantFP::get(TheContext, APFloat(_real));
}



RealAST::~RealAST() {}
