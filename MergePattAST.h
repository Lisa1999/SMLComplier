#pragma once
#include"PattAST.h"


class MergePattAST : public PattAST {
  char _op;
  string _idName;

public:
  MergePattAST(char _op, std::string _idName) {
    this->_op = _op;
    this->_idName = _idName;
  };
  Value *codegen();
  ~MergePattAST();
};
