#pragma once
#include "Token.h"
#include<string>
#include <vector>
#include<iostream>
using namespace std;

struct WORD {
  int row = 1;
  TOKEN token;
  string value = "";
};

struct SourceCode {
  int length = 0;
  char *buffer = nullptr;
};

class MyLexicalAnalysis {
private:
  SourceCode *mySourceCode;
  vector<WORD *> *wordVecPointer = nullptr;
  static TOKEN tokens[];
  static string tokensStr[];
  static char idSymbols[];

  bool isBlank(char c);
  bool isAlpha(char c);
  bool isNumber(char c);
  bool isNoZeroNumber(char c);
  SourceCode *readFile(const char *fileName);
  void LexAnalysis();
  static TOKEN tokenOrID(string s);
  bool isIdSymbol(char c);

public:
  // MyLexicalAnalysis();
  MyLexicalAnalysis(const char *fileName);
  
  void print();
  vector<WORD *> *getTokens();
  virtual ~MyLexicalAnalysis();
};
