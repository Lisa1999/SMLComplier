#pragma once
#include"ASTGen.h"

class Expr1AST : public ASTGen{
public:
  //ExpressionAST();
  Value *codegen();
  ~Expr1AST();
};
