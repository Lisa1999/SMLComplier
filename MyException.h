#pragma once

enum MyExType { LexerEx, ParserEx, StaticSemaEx, DynamicSemaEx, OtherEx };


struct MyException {
  int row;
  const char *detail;
  MyExType type;
  MyException(MyExType type, int row, const char *detail) {
    this->type = type;
    this->row = row;
    this->detail = detail;

	print();
  }
  void print() {
    std::cout << "µÚ" << this->row << "ÐÐ³ö´í£º";
    std::cout << '(';
    switch (this->type) {
    case LexerEx:
      std::cout << "´Ê·¨´íÎó";
      break;
    case ParserEx:
      std::cout << "Óï·¨´íÎó";
      break;
    case StaticSemaEx:
      std::cout << "¾²Ì¬ÓïÒå´íÎó";
      break;
    case DynamicSemaEx:
      std::cout << "¶¯Ì¬ÓïÒå´íÎó";
      break;
    case OtherEx:
      std::cout << "ÆäËû´íÎó";
      break;
    }
    std::cout << ')';
    //std::cout << std::endl;
    std::cout << "    " << detail << std::endl;
    //exit(0);
  }
};