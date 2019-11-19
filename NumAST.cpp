#include "NumAST.h"

NumAST::NumAST() {
  curToken = getNextToken();
  if (curToken->token != ConstInt && curToken->value[0] == '~')
    MyException(ParserEx, curToken->row, "numAST不正确，num应由纯数字组成");
  else
    this->_int = atoi(curToken->value.c_str());
}

//NumAST::NumAST(IntAST *_int) {
//  this->_int = _int;
//}

Value *NumAST::codegen() {
  //if (_int != NULL)
  //  return _int;
  //return NULL;
	return nullptr;
}


NumAST::~NumAST() {
}
