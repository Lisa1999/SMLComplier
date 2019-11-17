#include "IntAST.h"

Value *IntAST::codegen()
{
  return ConstantInt::get(TheContext, APInt(32, _int));
}


IntAST::~IntAST() {}
