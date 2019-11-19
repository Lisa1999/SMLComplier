#include "MyParser.h"


//单词的vector
vector<WORD *> *tokensVec = nullptr;
//当前分析的单词
WORD *curToken = nullptr;
//单词的数量
int tokenCount = -1;
//指向当前分析的单词的序号
int curTokPoint = -1;
//获取下一个单词
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
  //词法分析 获取源文件的tokens
  MyLexicalAnalysis *lex = nullptr;
  lex = new MyLexicalAnalysis(fileName);
  tokensVec = lex->getTokens();
  //得到单词的数量
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
