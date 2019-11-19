#pragma once
#include"StmtAST.h"
#include"Expr1AST.h"

// St ::= exp St
class Stmt1AST : public StmtAST {
  Expr1AST *_expr1;
  StmtAST *_stmt;

public:
  Stmt1AST(Expr1AST *_expr1, StmtAST *_stmt) {
    this->_expr1 = _expr1;
    this->_stmt = _stmt;
  };
  Value *codegen();
  ~Stmt1AST();
};
