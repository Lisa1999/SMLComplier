#pragma once
#include "MyLexicalAnalysis.h"
#include"MyException.h"
#include"ASTAll.h"


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
//符号优先级
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
