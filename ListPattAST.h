#pragma once
#include"PattAST.h"

// pat ::= [ pat , ... , pat ] patt
// pat ::= [ pat , ... , pat ]
class ListPattAST : public PattAST {
    vector<PattAST *> _patVec;

public:
	ListPattAST(vector<PattAST *> _patVec) { this->_patVec = _patVec; }
	Value *codegen();
	~ListPattAST();
};
