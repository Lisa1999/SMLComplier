#pragma once
#include"ASTGen.h"
enum OPERATOR {
  Plus,   // +
  Minus,  // -
  Mul,    // *
  Div,    // /
  DivInt, // div
  ModInt, // mod
  // Colon,		// :
  Less,   // <
  Equal,  // =
  More,   // >
  // DoubleEq,	// ==
  MoreEq, // >=
  LessEq, // <=
  NotEq   // <>
};

class OperatorAST : public ASTGen {
public:
  OPERATOR op;

  OperatorAST(OPERATOR op);
  ~OperatorAST();
};
