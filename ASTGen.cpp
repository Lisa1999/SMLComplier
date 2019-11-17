#include "ASTGen.h"

//ASTGen::ASTGen() {}

ASTGen::~ASTGen() {}

void ASTGen::setRow(int row) { this->row = row; }

Value *ASTGen::codegen() { return nullptr; }

ArrayRef<Value *> ASTGen::codegenArr() { return nullptr; }