#pragma once
#include "MyLexicalAnalysis.h"
#include"MyException.h"

//�ʷ������õ��ĵ��ʵ�vector
extern vector<WORD *> *tokensVec;
//��ǰ�����ĵ���
extern WORD *curToken;
//�õ���һ������
extern WORD *getNextToken();
//���ʵ�����
extern int tokenCount;
//��ǰ�����ĵ��ʵ����
extern int curTokPoint;

class MyParser {
public:

	
	MyParser(const char *fileName);
	~MyParser();
};
