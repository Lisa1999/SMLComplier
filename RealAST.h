#pragma once
#include"ASTGen.h"
class RealAST : public ASTGen {
public:
	double _real;

	RealAST(double _real) { this->_real = _real; };

	Value *codegen();
	~RealAST();
};
