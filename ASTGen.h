#pragma once
#include"GeneralFile.h"

class ASTGen {
public:
  int row = -1;
  std::string content = "";
  void setRow(int row);

  virtual ~ASTGen();
  virtual Value *codegen();
  virtual ArrayRef<Value *> codegenArr();
};
