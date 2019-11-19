#include"MyLexicalAnalysis.h"
#include "MyException.h"
#include"Test.h"

void testLexerAnalysis() {
  MyLexicalAnalysis *lexer = nullptr;
  //try {
    lexer = new MyLexicalAnalysis("sourceCode1.txt");
    lexer->print();
  //} catch (MyException e) {
  //  e.print();
  //}
}
