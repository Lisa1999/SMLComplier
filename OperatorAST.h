#pragma once
#include"ASTGen.h"
enum Operator : public ASTGen {
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

class OperatorAST {
public:
  Operator op;

  OperatorAST(Operator op);
  ~OperatorAST();
};
