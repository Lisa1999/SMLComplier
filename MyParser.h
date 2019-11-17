#pragma once
#include"BoolValAST.h"


#include"MyLexicalAnalysis.h"


class MyParser {
public:
  vector<WORD *> *tokensVec;
  


  MyParser(const char *fileName);
  ~MyParser();
};
