#pragma once
#include"ASTGen.h"
enum boolValue {True, False};

class BoolValAST : public ASTGen {
public:
  boolValue _boolValue;
  BoolValAST(boolValue _boolValue);
  ~BoolValAST();
};
