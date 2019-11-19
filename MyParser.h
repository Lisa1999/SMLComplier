#pragma once
#include "MyLexicalAnalysis.h"
#include"MyException.h"

//词法分析得到的单词的vector
extern vector<WORD *> *tokensVec;
//当前分析的单词
extern WORD *curToken;
//得到下一个单词
extern WORD *getNextToken();
//单词的总数
extern int tokenCount;
//当前分析的单词的序号
extern int curTokPoint;

class MyParser {
public:

	
	MyParser(const char *fileName);
	~MyParser();
};
