#include"MyLexicalAnalysis.h"
#include "MyException.h"
#include"Test.h"
#include"MyParser.h"

void testLexerAnalysis() {
  MyLexicalAnalysis *lexer = nullptr;
  //try {
    lexer = new MyLexicalAnalysis("sourceCode1.txt");
    lexer->print();
  //} catch (MyException e) {
  //  e.print();
  //}
}


void testParser() {
  //∑˚∫≈”≈œ»º∂
  map<int, int> BinopPrecedence;

  BinopPrecedence[DoubleColon] = 5;
  BinopPrecedence[Less] = 10;
  BinopPrecedence[Plus] = 20;
  BinopPrecedence[Minus] = 20;
  BinopPrecedence[DivInt] = 30;
  BinopPrecedence[ModInt] = 30;
  BinopPrecedence[Div] = 40;
  BinopPrecedence[Mul] = 40;

  MyParser *parser = nullptr;
  parser = new MyParser("sourceCode1.txt");
}
