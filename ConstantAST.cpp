#include "ConstantAST.h"


ConstantAST::ConstantAST(NumberAST *numberAST) { this->numberAST = numberAST; }

ConstantAST::ConstantAST(StringAST *stringAST) { this->stringAST = stringAST; }

ConstantAST::ConstantAST(CharAST *charAST) { this->charAST = charAST; }

ConstantAST::ConstantAST(BoolValAST *boolValAST) {
  this->boolValAST = boolValAST;
}

Value *ConstantAST::codegen() {
  if (this->numberAST != nullptr)
    return numberAST->codegen();
  return nullptr;
}



ConstantAST::~ConstantAST() {
  if (this->numberAST != nullptr)
    delete this->numberAST;
  if (this->stringAST != nullptr)
    delete this->stringAST;
  if (this->charAST != nullptr)
    delete this->charAST;
  if (this->boolValAST != nullptr)
    delete this->boolValAST;
}
