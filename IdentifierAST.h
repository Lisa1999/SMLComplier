#pragma once
#include"ASTGen.h"

//enum Identifier {
//  IdAlpha,  //��ĸ����
//  IdSymbol //��������
//};

class IdentifierAST : public ASTGen {
public:
  string _identifier;

  IdentifierAST(string _identifier) { this->_identifier = _identifier; };
  string codegenStr();

  ~IdentifierAST();
};
