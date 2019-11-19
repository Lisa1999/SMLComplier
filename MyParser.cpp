#include "MyParser.h"


//���ʵ�vector
vector<WORD *> *tokensVec = nullptr;
//��ǰ�����ĵ���
WORD *curToken = nullptr;
//���ʵ�����
int tokenCount = -1;
//ָ��ǰ�����ĵ��ʵ����
int curTokPoint = -1;
//��ȡ��һ������
WORD *getNextToken();

WORD *getNextToken()
{
  if (curTokPoint < tokenCount - 1)
    return (*tokensVec)[++curTokPoint];
  else
    return nullptr;
}

MyParser::MyParser(const char *fileName)
{
  //�ʷ����� ��ȡԴ�ļ���tokens
  MyLexicalAnalysis *lex = nullptr;
  lex = new MyLexicalAnalysis(fileName);
  tokensVec = lex->getTokens();
  //�õ����ʵ�����
  tokenCount = tokensVec->size();


	for (curTokPoint = 0; curTokPoint < tokenCount - 1; curTokPoint++)
	{
		//curToken = (*tokensVec)[curTokPoint];
          curToken = getNextToken();
		switch (curToken->token) {
		case Val:

		  break;
		default:
		  break;
		}
	}

}

MyParser::~MyParser() {}
