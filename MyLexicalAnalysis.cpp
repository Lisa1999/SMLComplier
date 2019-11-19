#include "MyLexicalAnalysis.h"
#include "MyException.h"
#include "Token.h"
#include <fstream>
#include <iomanip>

int tokensCount = 93;
TOKEN MyLexicalAnalysis::tokens[] = {
    Abstype,      And,    Andalso,   As,      Case,      Datatype, Do,
    End,          Eqtype, Exception, Else,    False,     Fn,       Fun,
    Functor,      Handle, In,        Include, If,        Infix,    Infixr,
    Let,          Local,  Nonfix,    Of,      Op,        Open,     Orelse,
    Raise,        Rec,    Sharing,   Sig,     Signature, Struct,   Structure,
    Then,         Type,   Val,       Where,   While,     With,     Withtype,

    Not,          // !
    AndSym,       // &
    Dollar,       // $
    Mode,         // %
    Hashtag,      // #				���壺#"a"	#" "	#"\n"
    Plus,         // +
    Minus,        // -
    Mul,          // *
    Div,          // /
    DivInt,       // div
    ModInt,       // mod
    Colon,        // :
    Less,         // <
    Equal,        // =
    More,         // >
    QueMark,      // ?
    At,           // @
    Backslash,    // \			�÷���\n	\t	\\	\"
    Negtive,      // ~
    BackQuote,    // `
    Non,          // ^
    Or,           // |
    DoubleColon,  //::
    EqualMore,    // =>
    MinusMore,    // ->
    ColonMore,    // :>
    Dot,          // .
    LP,           // (
    RP,           // )
    LPMul,        // (*
    MulRP,        // *)
    LS,           // [
    RS,           // ]
    LogE,         // E
    Semicolon,    // ;
    LB,           // {
    RB,           // }
    Comma,        // ,
    DoubleQuotes, // "
    DoubleEq,     // ==
    MoreEq,       // >=
    LessEq,       // <=
    NotEq,        // <>
    Underline,    // _
    Apostrophe,   //	'

    IdAlpha,     //��ĸ����
    IdSymbol,    //��������
    ConstInt,    //����
    ConstString, //�ַ���
    ConstReal,   //ʵ��
    ConstChar,   // char #"a"
    ConstWord    // word����

};

string MyLexicalAnalysis::tokensStr[] = {
    "abstype", "and",   "andalso",   "as",        "case",      "datatype",
    "do",      "end",   "eqtype",    "exception", "else",      "false",
    "fn",      "fun",   "functor",   "handle",    "in",        "include",
    "if",      "infix", "infixr",    "let",       "local",     "nonfix",
    "of",      "op",    "open",      "orelse",    "raise",     "rec",
    "sharing", "sig",   "signature", "struct",    "structure", "then",
    "type",    "val",   "where",     "while",     "with",      "withtype",

    "!",       "&",     "$",         "%",         "#",         "+",
    "-",       "*",     "/",         "mod",       "div",       ":",
    "<",       "=",     ">",         "?",         "@",         "\\",
    "~",       "`",     "^",         "|",         "::",        "=>",
    "->",      ":>",    "//",        "(",         ")",         "(*",
    "*)",      "[",     "]",         "E",         ";",         "{",
    "}",       ",",     "\"",        "==",        ">=",        "<=",
    "<>",      "_",     "'",
};

TOKEN MyLexicalAnalysis::tokenOrID(string s) {
  for (int i = 0; i < tokensCount; i++) {
    if (s == tokensStr[i]) {
      return tokens[i];
    }
  }
  return IdAlpha;
}

char MyLexicalAnalysis::idSymbols[] = {'!',  '&',  '$', '%', '#', '+', '-',
                                       '*"', '/',  ':', '<', '=', '>', '?',
                                       '@',  '\\', '~', '`', '^', '|'};
bool MyLexicalAnalysis::isIdSymbol(char c) {
  for (int i = 0; i < 20; i++) {
    if (c == idSymbols[i])
      return true;
  }
  return false;
}

MyLexicalAnalysis::MyLexicalAnalysis(const char *fileName) {
  this->mySourceCode = readFile(fileName);
  this->LexAnalysis();
}

MyLexicalAnalysis::~MyLexicalAnalysis() {
  delete mySourceCode;
  for (int i = 0; i < wordVecPointer->size(); i++) {
    delete wordVecPointer->at(i);
  }
  delete wordVecPointer;
}

SourceCode *MyLexicalAnalysis::readFile(const char *fileName) {
  fstream in;
  in.open(fileName, ios::in);
  SourceCode *sc = new SourceCode();
  in.seekg(0, ios::end);   //�ƶ���ĩβ
  sc->length = in.tellg(); //��ó���
  in.seekg(0, ios::beg);   //�ƶ�����ͷ
  sc->buffer = new char[sc->length];
  in.read(sc->buffer, sc->length);
  in.close();
  char *tCp = sc->buffer;
  if (sc->length > 0) {
    bool find = false;
    for (int i = 0; i < sc->length; i++) {
      if (tCp[i] == '\0' ||
          (tCp[i] == '$' && tCp[i + 1] == '$' && tCp[i + 2] == '$')) {
        find = true;
        sc->length = i;
        break;
      }
    }
  } else {
    MyException(LexerEx, -1, "û������");
    exit;
  }
  return sc;
}

void MyLexicalAnalysis::LexAnalysis() {
  this->wordVecPointer = new vector<WORD *>();
  int row = 1;
  WORD *word = nullptr;
  int j;
  string s = "";

  for (int i = 0; i < mySourceCode->length;) {
    while (isBlank(this->mySourceCode->buffer[i])) {

      if (this->mySourceCode->buffer[i] == '\n') {
        row++;
      }
      i++;
    }
    if (i >= mySourceCode->length)
      break;
    /*
    case:
_	:	!	$	;	{	}	[	]
(	)	.	,	+	-	*	/	% ~	> <
=	" default		��ĸ	����

�������֣����ַ���ɣ� ! % & # + - * / : < = > ? @ \ ~ ^ | `
    


    */
    switch (this->mySourceCode->buffer[i]) {
    case '_':
      MyException(LexerEx, row, "�������»��߿�ͷ");
      i++;
      // :	��������
    case '!':
    case '%':
    case '&':
    // case '#':
    case '+':
    case '-': //���������	-	->
    // case '*': //���������	*	*)
    case '/':
    case ':':
    case '<': //���������		<	<=	<>
    case '=': //���������		=	==	=>
    case '>': //���������		>	>=
    case '?':
    case '@':
    case '\\':
    // case '~': //���������
    case '^':
    case '|':
    case '`':
      j = 0;
      while (i + j < this->mySourceCode->length &&
             isIdSymbol(this->mySourceCode->buffer[i + j])) {
        s += this->mySourceCode->buffer[i + j];
        j++;
      }
      if (i + j == this->mySourceCode->length) {
        MyException(LexerEx, row, "Error");
        i++;
      } else {
        TOKEN tk = tokenOrID(s);
        word = new WORD();
        word->row = row;
        word->token = tk;
        word->value = s;
        s = "";
        i += j;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      }
      break;
    case ';': // ;
      word = new WORD();
      word->row = row;
      word->token = Semicolon;
      word->value = ";";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '{': // LB
      word = new WORD();
      word->row = row;
      word->token = LB;
      word->value = "{";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '}': // RB
      word = new WORD();
      word->row = row;
      word->token = RB;
      word->value = "}";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '[': // LS
      word = new WORD();
      word->row = row;
      word->token = RB;
      word->value = "[";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case ']': // RS
      word = new WORD();
      word->row = row;
      word->token = RB;
      word->value = "]";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '(': // LP LPMul
      if (i + 1 < mySourceCode->length &&
          this->mySourceCode->buffer[i + 1] == '*') {
        word = new WORD();
        word->row = row;
        word->token = LPMul;
        word->value = "(*";
        i += 2;
      } else {
        word = new WORD();
        word->row = row;
        word->token = LP;
        word->value = "(";
        i++;
      }
      this->wordVecPointer->push_back(word);
      word = nullptr;
      break;
    case ')': // RP
      word = new WORD();
      word->row = row;
      word->token = RP;
      word->value = ")";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '.': // Dot
      word = new WORD();
      word->row = row;
      word->token = Dot;
      word->value = ".";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case ',': // Comma
      word = new WORD();
      word->row = row;
      word->token = Comma;
      word->value = ",";
      this->wordVecPointer->push_back(word);
      i++;
      word = nullptr;
      break;
    case '#': // # #"char"
      if (i + 3 < mySourceCode->length &&
          this->mySourceCode->buffer[i + 1] == '"' &&
          isAlpha(this->mySourceCode->buffer[i + 2]) &&
          this->mySourceCode->buffer[i + 1] == '"') {
        word = new WORD();
        word->row = row;
        word->token = ConstChar;
        word->value = this->mySourceCode->buffer[i + 2];
        i += 4;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      } else if (i + 1 < this->mySourceCode->length &&
                 isIdSymbol(this->mySourceCode->buffer[i + j])) {
        j = 2;
        s = "*" + this->mySourceCode->buffer[i + 1];
        while (i + j < this->mySourceCode->length &&
               isIdSymbol(this->mySourceCode->buffer[i + j])) {
          s += this->mySourceCode->buffer[i + j];
          j++;
        }
        if (i + j == this->mySourceCode->length) {
          MyException(LexerEx, row, "Error");
          i++;
        } else {
          TOKEN tk = tokenOrID(s);
          word = new WORD();
          word->row = row;
          word->token = tk;
          word->value = s;
          s = "";
          i += j;
          this->wordVecPointer->push_back(word);
          word = nullptr;
          break;
        }
      } else {
        word = new WORD();
        word->row = row;
        word->token = Mul;
        word->value = "*";
        i++;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      }
    case '*': // * *)
      if (i + 1 < mySourceCode->length &&
          this->mySourceCode->buffer[i + 1] == ')') {
        word = new WORD();
        word->row = row;
        word->token = MulRP;
        word->value = "*)";
        i += 2;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      } else if (i + 1 < this->mySourceCode->length &&
                 isIdSymbol(this->mySourceCode->buffer[i + j])) {
        j = 2;
        s = "*" + this->mySourceCode->buffer[i + 1];
        while (i + j < this->mySourceCode->length &&
               isIdSymbol(this->mySourceCode->buffer[i + j])) {
          s += this->mySourceCode->buffer[i + j];
          j++;
        }
        if (i + j == this->mySourceCode->length) {
          MyException(LexerEx, row, "Error");
          i++;
        } else {
          TOKEN tk = tokenOrID(s);
          word = new WORD();
          word->row = row;
          word->token = tk;
          word->value = s;
          s = "";
          i += j;
          this->wordVecPointer->push_back(word);
          word = nullptr;
          break;
        }
      } else {
        word = new WORD();
        word->row = row;
        word->token = Mul;
        word->value = "*";
        i++;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      }
    case '~': /// ~ ����
      if (i + 1 < this->mySourceCode->length &&
          isNumber(this->mySourceCode->buffer[i + 1])) //����
      {
        i++;
        s += '~';
        if (this->mySourceCode->buffer[i] == '0') {
          if (i + 1 < this->mySourceCode->length &&
              this->mySourceCode->buffer[i + 1] != '.') {
            word = new WORD();
            word->row = row;
            word->token = ConstInt;
            word->value = "~0";
            i++;
            if (isAlpha(this->mySourceCode->buffer[i]) ||
                this->mySourceCode->buffer[i] == '_') {
              MyException(LexerEx, row,
                          "number can not be followed by letter or _");
              i++;
            }
            this->wordVecPointer->push_back(word);
            word = nullptr;
            break;
          } else if (i + 1 == this->mySourceCode->length) {
            MyException(LexerEx, row, "�Ƿ�����\"0\"");
            i++;
          } else // С��
          {
            j = 2;
            if (i + j < this->mySourceCode->length &&
                isNumber(this->mySourceCode->buffer[i + j])) {
              s += "0.";
              while (i + j < this->mySourceCode->length &&
                     isNumber(this->mySourceCode->buffer[i + j])) {
                s += this->mySourceCode->buffer[i + j];
                j++;
              }
              if (j == 2) {
                MyException(LexerEx, row, "�Ƿ��ַ�");
                i++;
              }
              word = new WORD();
              word->row = row;
              word->token = ConstReal;
              word->value = s;
              s = "";
              i += j;
              if (isAlpha(this->mySourceCode->buffer[i]) ||
                  this->mySourceCode->buffer[i] == '_') {
                MyException(LexerEx, row,
                            "number can not be followed by letter or _");
                i++;
              }
              j = 0;
              this->wordVecPointer->push_back(word);
              word = nullptr;
              break;
            } else {
              MyException(LexerEx, row, "�Ƿ�����\"-0.\"");
              i++;
            }
          }
        } else // ����0��ͷ
        {
          j = 0;
          while (i + j < this->mySourceCode->length &&
                 isNumber(this->mySourceCode->buffer[i + j])) {
            s += this->mySourceCode->buffer[i + j];
            j++;
          }
          if (i + j == this->mySourceCode->length) {
            MyException(LexerEx, row, "");
            i++;
          } else // char��������
          {
            if (this->mySourceCode->buffer[i + j] == '.') //������
            {
              j++; // i+j ָ��.������ַ�
              int curJ = j;
              s += '.';
              if (i + j == this->mySourceCode->length) {
                MyException(LexerEx, row, "");
                i++;
              } else {
                while (i + j < this->mySourceCode->length &&
                       isNumber(this->mySourceCode->buffer[i + j])) {
                  s += this->mySourceCode->buffer[i + j];
                  j++;
                }
                if (i + j == this->mySourceCode->length) {
                  MyException(LexerEx, row, "");
                  i++;
                } else // ������
                {
                  if (j == curJ) {
                    MyException(LexerEx, row, "�Ƿ��ַ�");
                    i++;
                  }
                  word = new WORD();
                  word->row = row;
                  word->token = ConstReal;
                  word->value = s;
                  s = "";
                  i += j;
                  if (isAlpha(this->mySourceCode->buffer[i]) ||
                      this->mySourceCode->buffer[i] == '_') {
                    MyException(LexerEx, row,
                                "number can not be followed by letter or _");
                    i++;
                  }
                  this->wordVecPointer->push_back(word);
                  word = nullptr;
                  break;
                }
              }
            } else //����
            {
              word = new WORD();
              word->row = row;
              word->token = ConstInt;
              word->value = s;
              s = "";
              i += j;
              if (isAlpha(this->mySourceCode->buffer[i]) ||
                  this->mySourceCode->buffer[i] == '_') {
                MyException(LexerEx, row,
                            "number can not be followed by letter or _");
                i++;
              }
              this->wordVecPointer->push_back(word);
              word = nullptr;
              break;
            }
          }
        }
      } else if (i + 1 < this->mySourceCode->length &&
                 isIdSymbol(this->mySourceCode->buffer[i + j])) {
        j = 2;
        s = "~" + this->mySourceCode->buffer[i + 1];
        while (i + j < this->mySourceCode->length &&
               isIdSymbol(this->mySourceCode->buffer[i + j])) {
          s += this->mySourceCode->buffer[i + j];
          j++;
        }
        if (i + j == this->mySourceCode->length) {
          MyException(LexerEx, row, "Error");
          i++;
        } else {
          TOKEN tk = tokenOrID(s);
          word = new WORD();
          word->row = row;
          word->token = tk;
          word->value = s;
          s = "";
          i += j;
          this->wordVecPointer->push_back(word);
          word = nullptr;
          break;
        }
      } else {
        word = new WORD();
        word->row = row;
        word->token = Negtive;
        word->value = "~";
        this->wordVecPointer->push_back(word);
        i++;
        word = nullptr;
        break;
      }
    case '\"': // ConstString
      j = 1;
      while (i + j < mySourceCode->length &&
             this->mySourceCode->buffer[i + j] != '\"') {
        s += this->mySourceCode->buffer[i + j];
        if (this->mySourceCode->buffer[i + j] == '\n') {
          row++;
        }
        j++;
      }
      if (i + j == mySourceCode->length) {
        MyException(LexerEx, row, "��������");
        i++;
      } else {
        word = new WORD();
        word->row = row;
        word->token = ConstString;
        word->value = s;
        s = "";
        i += j + 1;
        this->wordVecPointer->push_back(word);
        word = nullptr;
        break;
      }
    //����  ConstInt ConstReal Identifier  Keyword
    default:
      if (isAlpha(
              this->mySourceCode->buffer
                  [i])) //��ʶ��������ĸ��ͷ����������ĸ�����ֻ��»��߻�Ʋ�ţ������ţ������ɷ�����ɡ�
      {
        j = 0;
        while (i + j < this->mySourceCode->length &&
               (isAlpha(this->mySourceCode->buffer[i + j]) ||
                isNumber(this->mySourceCode->buffer[i + j]) ||
                this->mySourceCode->buffer[i + j] == '_' ||
                this->mySourceCode->buffer[i + j] == '\'')) {
          s += this->mySourceCode->buffer[i + j];
          j++;
        }
        if (i + j == this->mySourceCode->length) {
          MyException(LexerEx, row, "Error");
          i++;
        } else {
          TOKEN tk = tokenOrID(s);
          word = new WORD();
          word->row = row;
          word->token = tk;
          word->value = s;
          s = "";
          i += j;
          this->wordVecPointer->push_back(word);
          word = nullptr;
          break;
        }
      } else if (isNumber(this->mySourceCode->buffer[i])) //����
      {
        if (this->mySourceCode->buffer[i] == '0')
		{
          if (i + 1 < this->mySourceCode->length &&	this->mySourceCode->buffer[i + 1] == 'w')  		//0w  
		  {
            j = 2;
            if (i + j < this->mySourceCode->length && isNumber(this->mySourceCode->buffer[i + j]))
			{
              s = "";
              while (i + j < this->mySourceCode->length && isNumber(this->mySourceCode->buffer[i + j])) 
			  {
                s += this->mySourceCode->buffer[i + j];
                j++;
              }
              if (j == 2) {
                MyException(LexerEx, row, "�Ƿ��ַ�");
                i++;
              }
              word = new WORD();
              word->row = row;
              word->token = ConstWord;
              word->value = s;
              s = "";
              i += j;
              if (isAlpha(this->mySourceCode->buffer[i]) ||
                  this->mySourceCode->buffer[i] == '_') {
                MyException(LexerEx, row,
                            "number can not be followed by letter or _");
                i++;
              }
              this->wordVecPointer->push_back(word);
              word = nullptr;
              break;
            } else {
              MyException(LexerEx, row, "�Ƿ�����\"0.\"");
              i++;
            }
          }
          else if (i + 1 < this->mySourceCode->length && this->mySourceCode->buffer[i + 1] != '.')	// ��С��
		  {
            word = new WORD();
            word->row = row;
            word->token = ConstInt;
            word->value = "0";
            i++;
			if (isAlpha(this->mySourceCode->buffer[i]) ||
                       this->mySourceCode->buffer[i] == '_')
			{
              MyException(LexerEx, row,
                          "number can not be followed by letter or _");
              i++;
            }
            this->wordVecPointer->push_back(word);
            word = nullptr;
            break;
          } 
		  else if (i + 1 == this->mySourceCode->length)
		  {
            MyException(LexerEx, row, "�Ƿ�����\"0\"");
            i++;
          }
		  else // С��
          {
            j = 2;
            if (i + j < this->mySourceCode->length &&
                isNumber(this->mySourceCode->buffer[i + j])) {
              s = "0.";
              while (i + j < this->mySourceCode->length &&
                     isNumber(this->mySourceCode->buffer[i + j])) {
                s += this->mySourceCode->buffer[i + j];
                j++;
              }
              if (j == 2) {
                MyException(LexerEx, row, "�Ƿ��ַ�");
                i++;
              }
              word = new WORD();
              word->row = row;
              word->token = ConstReal;
              word->value = s;
              s = "";
              i += j;
              if (isAlpha(this->mySourceCode->buffer[i]) ||
                  this->mySourceCode->buffer[i] == '_') {
                MyException(LexerEx, row,
                            "number can not be followed by letter or _");
                i++;
              }
              this->wordVecPointer->push_back(word);
              word = nullptr;
              break;
            } else {
              MyException(LexerEx, row, "�Ƿ�����\"0.\"");
              i++;
            }
          }
        } 
		else // ����0��ͷ
        {
          j = 0;
          while (i + j < this->mySourceCode->length &&
                 isNumber(this->mySourceCode->buffer[i + j])) {
            s += this->mySourceCode->buffer[i + j];
            j++;
          }
          if (i + j == this->mySourceCode->length) {
            MyException(LexerEx, row, "");
            i++;
          } else // char��������
          {
            if (this->mySourceCode->buffer[i + j] == '.') //������
            {
              j++; // i+j ָ��.������ַ�
              int curJ = j;
              s += '.';
              if (i + j == this->mySourceCode->length) {
                MyException(LexerEx, row, "");
                i++;
              } else {
                while (i + j < this->mySourceCode->length &&
                       isNumber(this->mySourceCode->buffer[i + j])) {
                  s += this->mySourceCode->buffer[i + j];
                  j++;
                }
                if (i + j == this->mySourceCode->length) {
                  MyException(LexerEx, row, "");
                  i++;
                } else // ������
                {
                  if (j == curJ) {
                    MyException(LexerEx, row, "�Ƿ��ַ�");
                    i++;
                  }
                  word = new WORD();
                  word->row = row;
                  word->token = ConstReal;
                  word->value = s;
                  s = "";
                  i += j;
                  if (isAlpha(this->mySourceCode->buffer[i]) ||
                      this->mySourceCode->buffer[i] == '_') {
                    MyException(LexerEx, row,
                                "number can not be followed by letter or _");
                    i++;
                  }
                  this->wordVecPointer->push_back(word);
                  word = nullptr;
                  break;
                }
              }
            } else //����
            {
              word = new WORD();
              word->row = row;
              word->token = ConstInt;
              word->value = s;
              s = "";
              i += j;
              if (isAlpha(this->mySourceCode->buffer[i]) ||
                  this->mySourceCode->buffer[i] == '_') {
                MyException(LexerEx, row,
                            "number can not be followed by letter or _");
                i++;
              }
              this->wordVecPointer->push_back(word);
              word = nullptr;
              break;
            }
          }
        }
      } else {
        MyException(LexerEx, row, "�Ƿ��ַ�");
        i++;
      }
    }
  }
}

bool MyLexicalAnalysis::isBlank(char c) //�Ƿ��ǿհ�
{
  return c == ' ' || c == '\t' || c == '\n';
}
bool MyLexicalAnalysis::isAlpha(char c) // �Ƿ�����ĸ
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool MyLexicalAnalysis::isNumber(char c) // �Ƿ�������
{
  return c >= '0' && c <= '9';
}
bool MyLexicalAnalysis::isNoZeroNumber(char c) // �Ƿ��Ƿ�������
{
  return c >= '1' && c <= '9';
}

void MyLexicalAnalysis::print() {
  string tokens[] = {
      "Abstype",      "And",        "Andalso",   "As",       "Case",
      "Datatype",     "Do",         "End",       "Eqtype",   "Exception",
      "Else",         "False",      "Fn",        "Fun",      "Functor",
      "Handle",       "In",         "Include",   "If",       "Infix",
      "Infixr",       "Let",        "Local",     "Nonfix",   "Of",
      "Op",           "Open",       "Orelse",    "Raise",    "Rec",
      "Sharing",      "Sig",        "Signature", "Struct",   "Structure",
      "Then",         "Type",       "Val",       "Where",    "While",
      "With",         "Withtype",   "Not",       "AndSym",   "Dollar",
      "Mode",         "Hashtag",    "Plus",      "Minus",    "Mul",
      "Div",          "DivInt",     "ModInt",    "Colon",    "Less",
      "Equal",        "More",       "QueMark",   "At",       "Backslash",
      "Negtive",      "BackQuote",  "Non",       "Or",       "DoubleColon",
      "EqualMore",    "MinusMore",  "ColonMore", "Dot",      "LP",
      "RP",           "LPMul",      "MulRP",     "LS",       "RS",
      "LogE",         "Semicolon",  "LB",        "RB",       "Comma",
      "DoubleQuotes", "DoubleEq",   "MoreEq",    "LessEq",   "NotEq",
      "Underline",    "Apostrophe", "IdAlpha",   "IdSymbol", "ConstInt",
      "ConstString",  "ConstReal",  "ConstChar", "ConstWord"};

  ofstream out;
  if (out.bad()) {
    cout << "cannot write file" << std::endl;
  }
  out.open("test_1Result.txt", ios::out | ios::app);

  for (int i = 0; i < this->wordVecPointer->size(); i++) {
    WORD *word = this->wordVecPointer->at(i);
    out << "row: " << word->row << "\t\t\t"
        << "value: " << word->value << "\t\t\t"
        << "token: " << tokens[word->token] << "\n";
  }

  out.close();
}

vector<WORD *> *MyLexicalAnalysis::getTokens() { return this->wordVecPointer; }