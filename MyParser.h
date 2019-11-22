#pragma once
#include "MyLexicalAnalysis.h"
#include"MyException.h"
#include"ASTAll.h"


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
//�������ȼ�
extern map<int, int> BinopPrecedence;


static ExprAST *ParseExpression(void);
static Expr1AST *ParseExpr(void);
static PattAST *ParsePattern(void);
static DecAST *ParseDeclaration(void);
static Dec1AST *ParseDecl(void);
static ValbindAST *ParseValbind(void);
static FunmatchAST *ParseFunmatch(void);
static FunbindAST *ParseFunbind(void);
static void skipComment(void);

class MyParser {
public:
  void MainLoop(void);
  void blanks();
	
	MyParser(const char *fileName);
	~MyParser();
};
