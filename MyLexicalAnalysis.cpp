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
    Hashtag,      // #				定义：#"a"	#" "	#"\n"
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
    Backslash,    // \			用法：\n	\t	\\	\"
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

    IdAlpha,     //字母名字
    IdSymbol,    //符号名字
    ConstInt,    //整数
    ConstString, //字符串
    ConstReal,   //实数
    ConstChar,   // char #"a"
    ConstWord    // word类型

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
  in.seekg(0, ios::end);   //移动到末尾
  sc->length = in.tellg(); //获得长度
  in.seekg(0, ios::beg);   //移动到开头
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
    MyException(LexerEx, -1, "没有内容");
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
=	" default		字母	数字

符号名字：由字符组成： ! % & # + - * / : < = > ? @ \ ~ ^ | `
    


    */
    switch (this->mySourceCode->buffer[i]) {
    case '_':
      MyException(LexerEx, row, "不能以下划线开头");
      i++;
      // :	符号名字
    case '!':
    case '%':
    case '&':
    // case '#':
    case '+':
    case '-': //含其他情况	-	->
    // case '*': //含其他情况	*	*)
    case '/':
    case ':':
    case '<': //含其他情况		<	<=	<>
    case '=': //含其他情况		=	==	=>
    case '>': //含其他情况		>	>=
    case '?':
    case '@':
    case '\\':
    // case '~': //含其他情况
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
    case '~': /// ~ 负数
      if (i + 1 < this->mySourceCode->length &&
          isNumber(this->mySourceCode->buffer[i + 1])) //负数
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
            MyException(LexerEx, row, "非法符号\"0\"");
            i++;
          } else // 小数
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
                MyException(LexerEx, row, "非法字符");
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
              MyException(LexerEx, row, "非法符号\"-0.\"");
              i++;
            }
          }
        } else // 不以0开头
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
          } else // char不是数字
          {
            if (this->mySourceCode->buffer[i + j] == '.') //浮点数
            {
              j++; // i+j 指向.后面的字符
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
                } else // 浮点数
                {
                  if (j == curJ) {
                    MyException(LexerEx, row, "非法字符");
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
            } else //整数
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
        MyException(LexerEx, row, "程序不完整");
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
    //常量  ConstInt ConstReal Identifier  Keyword
    default:
      if (isAlpha(
              this->mySourceCode->buffer
                  [i])) //标识符：以字母开头，后面是字母或数字或下划线或撇号（单引号）；或由符号组成。
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
      } else if (isNumber(this->mySourceCode->buffer[i])) //正数
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
                MyException(LexerEx, row, "非法字符");
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
              MyException(LexerEx, row, "非法符号\"0.\"");
              i++;
            }
          }
          else if (i + 1 < this->mySourceCode->length && this->mySourceCode->buffer[i + 1] != '.')	// 非小数
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
            MyException(LexerEx, row, "非法符号\"0\"");
            i++;
          }
		  else // 小数
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
                MyException(LexerEx, row, "非法字符");
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
              MyException(LexerEx, row, "非法符号\"0.\"");
              i++;
            }
          }
        } 
		else // 不以0开头
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
          } else // char不是数字
          {
            if (this->mySourceCode->buffer[i + j] == '.') //浮点数
            {
              j++; // i+j 指向.后面的字符
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
                } else // 浮点数
                {
                  if (j == curJ) {
                    MyException(LexerEx, row, "非法字符");
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
            } else //整数
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
        MyException(LexerEx, row, "非法字符");
        i++;
      }
    }
  }
}

bool MyLexicalAnalysis::isBlank(char c) //是否是空白
{
  return c == ' ' || c == '\t' || c == '\n';
}
bool MyLexicalAnalysis::isAlpha(char c) // 是否是字母
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool MyLexicalAnalysis::isNumber(char c) // 是否是数字
{
  return c >= '0' && c <= '9';
}
bool MyLexicalAnalysis::isNoZeroNumber(char c) // 是否是非零数字
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