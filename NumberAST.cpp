#include "NumberAST.h"

NumberAST::NumberAST(IntAST *_int) {
  this->_int = _int;
  this->type = 0;
}

NumberAST::NumberAST(RealAST *_real) {
  this->_real = _real;
  this->type = 1;
}

Value *NumberAST::codegen() {
  if (_int != nullptr)
    return _int->codegen();
  if (_real != nullptr)
    return _real->codegen();
  return nullptr;
}


NumberAST::~NumberAST() {
  if (this->_int != nullptr)
    delete this->_int;
  if (this->_real != nullptr)
    delete this->_real;
}
