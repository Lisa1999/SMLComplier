#pragma once
#include"StmtAST.h"
#include"DecAST.h"

class StmtDecAST : public StmtAST {
  DecAST *_dec;
  StmtAST *_stmt;

public:
  StmtDecAST(DecAST *_dec, StmtAST *_stmt) {
    this->_dec = _dec;
    this->_stmt = _stmt;
  };
  Value *codegen();
  ~StmtDecAST();
};
