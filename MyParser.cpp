#include "MyParser.h"

MyParser::MyParser(const char *fileName)
{
	//�ʷ����� ��ȡԴ�ļ���tokens
  MyLexicalAnalysis* lex = nullptr;
  lex = new MyLexicalAnalysis(fileName);
  tokensVec = lex->getTokens();
  WORD *word = nullptr;

  int tokenCount = tokensVec->size;

  for (int i = 0; i< tokenCount ;i++)
  {
    word = (*tokensVec)[i];
    switch (word->token) {
    case :
      break;
    default:
      break;
    }
  }

}

MyParser::~MyParser() {}
