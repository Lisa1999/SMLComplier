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
    std::cout << "��" << this->row << "�г���";
    std::cout << '(';
    switch (this->type) {
    case LexerEx:
      std::cout << "�ʷ�����";
      break;
    case ParserEx:
      std::cout << "�﷨����";
      break;
    case StaticSemaEx:
      std::cout << "��̬�������";
      break;
    case DynamicSemaEx:
      std::cout << "��̬�������";
      break;
    case OtherEx:
      std::cout << "��������";
      break;
    }
    std::cout << ')';
    //std::cout << std::endl;
    std::cout << "    " << detail << std::endl;
    //exit(0);
  }
};