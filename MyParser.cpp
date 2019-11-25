#include "MyParser.h"
#include<fstream>

//单词的vector
vector<WORD *> *tokensVec = nullptr;
//当前分析的单词
WORD *curToken = nullptr;
//单词的数量
int tokenCount = -1;
//指向当前分析的单词的序号
int curTokPoint = -1;
//获取下一个单词
WORD *getNextToken();

int blk = 0;
StmtAST *Root = nullptr;

WORD *getNextToken() {
  if (curTokPoint < tokenCount - 1) {
    curToken = (*tokensVec)[++curTokPoint];
    return curToken;
  } else
    return nullptr;
}

void MyParser::MainLoop(void) {
  while (curTokPoint < tokenCount - 1) {
    // curToken = (*tokensVec)[curTokPoint];
    curToken = getNextToken();
    switch (curToken->token) {
    case Semicolon:
      getNextToken();
      break;
    case Fun:
    case Local:
    case Val:
      ParseDeclaration();
      break;
    //case LPMul:
      ///skipComment();
      //break;
    default:
      ParseExpression();
      break;
    }
  }
}

void printAST(string content) {
  cout << content;
  /*ofstream out;
  if (out.bad()) {
    cout << "cannot write file" << std::endl;
  }
  out.open("parserResult.txt", ios::out | ios::app);

  out << content << "\n";

  out.close();*/
}

void blanks() {
  for (int i = 0; i < blk; i++)
    printAST("│ ");
  printAST("├ ");
}



//获取符号的优先级
static int GetTokPrecedence() {
  if (!(curToken->token == Plus || curToken->token == Minus ||
        curToken->token == Mul || curToken->token == Div ||
        curToken->token == DivInt || curToken->token == ModInt))
    return -1;
  int TokPrec = BinopPrecedence[curToken->token];
  if (TokPrec <= 0)
    return -1;
  return TokPrec;
}

MyParser::MyParser(const char *fileName) {
  //词法分析 获取源文件的tokens
  MyLexicalAnalysis *lex = nullptr;
  lex = new MyLexicalAnalysis(fileName);
  tokensVec = lex->getTokens();
  //得到单词的数量
  tokenCount = tokensVec->size();
  MainLoop();
}

MyParser::~MyParser() {}

//static void skipComment() {
//  while (curToken != nullptr) {
//    if (curToken->token == MulRP)
//      return;
//    curToken = getNextToken();
//  }
//  MyException(ParserEx, -1, "缺少*)");
//}

static PattAST *ParsePattern(void) {
  blk++;
  switch (curToken->token) {
  default:
    return 0;
  case LP: {
    getNextToken(); // eat '('
    std::vector<PattAST *> Pats;
    blanks();
    printAST("Tuple<Pattern>\n");
    if (curToken->token != RP) {
      while (1) {
        PattAST *Pat = ParsePattern();
        blk--;
        if (!Pat)
          return 0;
        Pats.push_back(Pat);
        if (curToken->token == RP)
          break;
        if (curToken->token != Comma) {
          MyException(ParserEx, curToken->row, "管道（Tuple）中缺少“,”");
          return nullptr;
        }
        // return ErrorP("Expected ',' in Tuple");
        getNextToken(); //
      }
    }
    getNextToken(); // eat ')'
    return new TuplePattAST(Pats);
  }
  case LS: {
    getNextToken(); // eat '['
    std::vector<PattAST *> Pats;
////#ifdef PRINT
    blanks();
    printAST("List<Pattern>\n");
////#endif // PRINT
    if (curToken->token != RS) {
      while (1) {
        PattAST *Pat = ParsePattern();
        blk--;
        if (!Pat)
          return 0;
        Pats.push_back(Pat);
        if (curToken->token == RS)
          break;
        if (curToken->token != Comma) {
          MyException(ParserEx, curToken->row, "list中缺少逗号");
          return nullptr;
        }
        getNextToken(); //
      }
    }
    getNextToken(); // eat ']'
    return new ListPattAST(Pats);
  }
  case DoubleColon: // the constructor only apply tok_merge(::)
  {
    getNextToken(); // eat '::'
    if (!(curToken->token == IdAlpha || curToken->token != IdSymbol)) {
      MyException(ParserEx, curToken->row, "缺少标识符");
      return nullptr;
    }
    string IdName = curToken->value;
    getNextToken(); // eat 'id'
//#ifdef PRINT
    blanks();
    printAST("Binop '::'<Pattern>\n");
    blanks();
    //printAST("Id:%s<Pattern>\n", IdName.c_str());
    printAST("Id:"+ IdName + "<Pattern>\n");
    //#endif // PRINT
    return new MergePattAST(DoubleColon, IdName);
  }
  case IdAlpha:
  case IdSymbol: {
    string IdName = curToken->value;
    getNextToken(); // eat 'id'
////#ifdef PRINT
    blanks();
    printAST("Id:" + IdName + "<Pattern>\n");
    //#endif // PRINT

    if (curToken->token == DoubleColon) {
//#ifdef PRINT
      blanks();
      printAST("Binop '::'<Pattern>\n");
//#endif                // PRINT
      getNextToken(); // eat '::'
      PattAST *RHS = ParsePattern();
      blk--;
      if (!RHS)
        return 0;
      return new IdConstructionPattAST(IdName, RHS);
    }

    if (curToken->token != As)
      return new IdPattAST(IdName);
    getNextToken(); // eat 'as'
    PattAST *Pat = ParsePattern();
    blk--;
    if (!Pat)
      return 0;
    return new IdAsPattAST(IdName, Pat);
  }
  }
}

static DecAST *ParseDeclaration(void) {
  blk++;
  switch (curToken->token) {
  default:
    return 0;
  case Fun: {
//#ifdef PRINT
    blanks();
    printAST("Keyword:fun<Declaration>\n");
//#endif              // PRINT
    getNextToken(); // eat 'fun'
//#ifdef PRINT
    blanks();
    printAST("Funbind<Declaration>\n");
//#endif // PRINT
    FunbindAST *Funbind = ParseFunbind();
    blk--;
    if (!Funbind)
      return 0;

//#ifdef PRINT
    blanks();
    printAST("Decl<Declaration>\n");
//#endif // PRINT
    Dec1AST *Decl = ParseDecl();
    blk--;
    if (!Decl)
      return 0;

    return new FunctionDeclAST(Funbind, Decl);
  }
  case Val: {
//#ifdef PRINT
    blanks();
    printAST("Keyword:val<Declaration>\n");
//#endif              // PRINT
    getNextToken(); // eat 'val'
//#ifdef PRINT
    blanks();
    printAST("Valbind<Declaration>\n");
//#endif // PRINT
    ValbindAST *Valbind = ParseValbind();
    blk--;
    if (!Valbind)
      return 0;

//#ifdef PRINT
    blanks();
    printAST("Decl<Declaration>\n");
//#endif // PRINT
    Dec1AST *Decl = ParseDecl();
    blk--;
    if (!Decl)
      return 0;

    return new ValueDeclAST(Valbind, Decl);
  }
  case Local: {
//#ifdef PRINT
    blanks();
    printAST("Keyword:local<Declaration>\n");
    blanks();
    printAST("Dec<Declaration>\n");
//#endif              // PRINT
    getNextToken(); // eat 'local'
    DecAST *Dec1 = ParseDeclaration();
    blk--;
    if (!Dec1)
      return 0;
    if (curToken->token != In) {
      MyException(ParserEx, curToken->row, "Local语句缺少in");
      return nullptr;
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:in<Declaration>\n");
    blanks();
    printAST("Dec<Declaration>\n");
//#endif              // PRINT
    getNextToken(); // eat 'in'
    DecAST *Dec2 = ParseDeclaration();
    blk--;
    if (!Dec2)
      return 0;
    if (curToken->token != End) {
      MyException(ParserEx, curToken->row, "Local语句缺少end");
      return nullptr;
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:end<Declaration>\n");
    blanks();
    printAST("Decl<Declaration>\n");
//#endif              // PRINT
    getNextToken(); // eat 'end'

    Dec1AST *Decl = ParseDecl();
    blk--;
    if (!Decl)
      return 0;

    return new LocalDecAST(Dec1, Dec2, Decl);
  }
  }
}

static FunbindAST *ParseFunbind(void) {
  blk++;
  std::vector<FunmatchAST *> Funmatchs;
//#ifdef PRINT
  blanks();
  printAST("Funmatch<Funbind>\n");
//#endif // PRINT
  FunmatchAST *Funmatch = ParseFunmatch();
  blk--;
  if (!Funmatch)
    return 0;
  Funmatchs.push_back(Funmatch);
  if (curToken->token == Or) {
    while (1) {
      getNextToken(); // eat '|'
      FunmatchAST *Funmatch = ParseFunmatch();
      blk--;
      if (!Funmatch)
        return 0;
      Funmatchs.push_back(Funmatch);
      if (curToken->token != Or)
        break;
    }
  }
  return new FunbindAST(Funmatchs);
}

// funmatch
// input must be 'id'
static FunmatchAST *ParseFunmatch(void) {
  blk++;
  std::string IdName = curToken->value;
  getNextToken(); // eat 'id'
//#ifdef PRINT
  blanks();
  //printAST("Id:%s<Funmatch>\n", IdName.c_str());
  printAST("Id:" + IdName + "<Funmatch>\n");
  //#endif // PRINT
  std::vector<PattAST *> Pats;
//#ifdef PRINT
  blanks();
  printAST("Pat<Funmatch>\n");
//#endif // PRINT
  if (curToken->token == Equal) {
    MyException(ParserEx, curToken->row, "参数list中缺少模式");
    return nullptr;
  }
  while (1) {
    PattAST *Pat = ParsePattern();
    blk--;
    if (!Pat)
      return 0;
    Pats.push_back(Pat);
    if (curToken->token == Equal)
      break;
  }
  getNextToken(); // eat
//#ifdef PRINT
  blanks();
  printAST("Exp<Funmatch>\n");
//#endif // PRINT
  ExprAST *Exp = ParseExpression();
  blk--;
  if (!Exp)
    return 0;
  return new FunmatchAST(IdName, Pats, Exp);
}

// valbind
static ValbindAST *ParseValbind(void) {
  blk++;
  switch (curToken->token) {
  default:
    break;
  case '(':
  case '[':
  case DoubleColon:
  case IdAlpha:
  case IdSymbol: {
//#ifdef PRINT
    blanks();
    printAST("Pat<Valbind>\n");
//#endif // PRINT
    PattAST *Pat = ParsePattern();
    blk--;
    if (!Pat)
      return 0;
    if (curToken->token != Equal) {
      MyException(ParserEx, curToken->row, "缺少 = ");
      return nullptr;
    }
    // return ErrorV("Expected '=' in Valbind");
    getNextToken(); // eat '='
//#ifdef PRINT
    blanks();
    printAST("Exp<Valbind>\n");
//#endif // PRINT
    ExprAST *Exp = ParseExpression();
    blk--;
    if (!Exp)
      return 0;
    return new ValbindAST(Pat, Exp);
  }
  }
}

// exp
static ExprAST *ParseExpression(void) {
  blk++;
  switch (curToken->token) {
  default:
    return 0;
  case Let: {
//#ifdef PRINT
    blanks();
    printAST("Keyword:let<Let-In>\n");
    blanks();
    printAST("Dec<Let-In>\n");
//#endif              // PRINT
    getNextToken(); // eat 'let'
    DecAST *Decl = ParseDeclaration();
    blk--;
    if (!Decl)
      return 0;
    if (curToken->token != In) {
      MyException(ParserEx, curToken->row, "缺少 in");
      return nullptr;
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:in<Let-In>\n");
    blanks();
    printAST("Exp<Let-In>\n");
//#endif              // PRINT
    getNextToken(); // eat 'in'
    std::vector<ExprAST *> Exps;

    if (curToken->token != End) {
      while (1) {
        ExprAST *Exp = ParseExpression();
        blk--;
        if (!Exp)
          return 0;
        Exps.push_back(Exp);
        if (curToken->token == End)
          break;
        if (curToken->token != ';') {
          MyException(ParserEx, curToken->row, "let in end 语句缺少 end");
          return nullptr;
        }
        getNextToken();
      }
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:end<Let-In>\n");
    blanks();
    printAST("Expr<Let-In>\n");
//#endif              // PRINT
    getNextToken(); // eat 'end'
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new LetExprAST(Decl, Exps, Expr);
  }
  case If: {
//#ifdef PRINT
    blanks();
    printAST("Id:if<Keyword>\n");
    blanks();
    printAST("Exp<If-Else>\n");
//#endif              // PRINT
    getNextToken(); // eat 'if'
    ExprAST *Exp1 = ParseExpression();
    blk--;
    if (!Exp1)
      return 0;
    if (curToken->token != Then) {
      MyException(ParserEx, curToken->row, "if else 语句缺少 then");
      return nullptr;
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:then<If-Else>\n");
    blanks();
    printAST("Exp<If-Else>\n");
//#endif              // PRINT
    getNextToken(); // eat 'then'
    ExprAST *Exp2 = ParseExpression();
    blk--;
    if (!Exp2)
      return 0;

    if (curToken->token != Else) {
      MyException(ParserEx, curToken->row, "if else 语句缺少 else");
      return nullptr;
    }
//#ifdef PRINT
    blanks();
    printAST("Keyword:else<If-Else>\n");
    blanks();
    printAST("Exp<If-Else>\n");
//#endif              // PRINT
    getNextToken(); // eat 'else'
    ExprAST *Exp3 = ParseExpression();
    blk--;
    if (!Exp3)
      return 0;
//#ifdef PRINT
    blanks();
    printAST("Expr<If-Else>\n");
//#endif // PRINT
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new IfExprAST(Exp1, Exp2, Exp3, Expr);
  }
  case '(': {
    getNextToken(); // eat '('
    std::vector<ExprAST *> Exps;
//#ifdef PRINT
    blanks();
    printAST("Tuple<Expression>\n");
//#endif // PRINT
    if (curToken->token != ')') {
      while (1) {
        ExprAST *Exp = ParseExpression();
        blk--;
        if (!Exp)
          return 0;
        Exps.push_back(Exp);
        if (curToken->token == ')')
          break;
        if (curToken->token != ',') {
          MyException(ParserEx, curToken->row, "tuple 语句缺少 , ");
          return nullptr;
        }
        getNextToken(); //
      }
    }
//#ifdef PRINT
    blanks();
    printAST("Expr<Expression>\n");
//#endif              // PRINT
    getNextToken(); // eat ')'
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new SequenceExprAST(Exps, Expr);
  }
  case '[': {
    getNextToken(); // eat '['
    std::vector<ExprAST *> Exps;
//#ifdef PRINT
    blanks();
    printAST("List<Pattern>\n");
//#endif // PRINT
    if (curToken->token != ']') {
      while (1) {
        ExprAST *Exp = ParseExpression();
        blk--;
        if (!Exp)
          return 0;
        Exps.push_back(Exp);
        if (curToken->token == ']')
          break;
        if (curToken->token != ',') {
          MyException(ParserEx, curToken->row, "list 语句缺少 , ");
          return nullptr;
        }
        getNextToken(); //
      }
    }
//#ifdef PRINT
    blanks();
    printAST("Expr<Expression>\n");
//#endif              // PRINT
    getNextToken(); // eat ']'
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new ListExprAST(Exps, Expr);
  }
  case DoubleColon: {
    getNextToken(); // eat '::'
//#ifdef PRINT
    blanks();
    printAST("Binop '::'<Expression>\n");
//#endif // PRINT
    if (!(curToken->token == IdAlpha || curToken->token == IdSymbol)) {
      MyException(ParserEx, curToken->row, "list 语句缺少 , ");
      return nullptr;
    }
    /// return ErrorE("Expected RHS in Binop Expression");
    string IdName = curToken->value;
//#ifdef PRINT
    blanks();
    //printAST("Id:%s<Expression>\n", IdName.c_str());
    printAST("Id:" + IdName + "<Expression>\n");
    blanks();
    printAST("Expr<Expression>\n");
//#endif              // PRINT
    getNextToken(); // eat 'id'
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new BinopLongIdExprAST(DoubleColon, IdName, Expr);
  }
  case IdAlpha:
  case IdSymbol: // id or id pat (if the next token is '::')
  {
    std::string IdName = curToken->value;
//#ifdef PRINT
    blanks();
    printAST("Id:" + IdName + "<Expression>\n");
    blanks();
    printAST("Expr<Expression>\n");
//#endif              // PRINT
    getNextToken(); // eat 'id'
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr)
      return 0;
    return new IdExprAST(IdName, Expr);
  }
  }
}

// expr
static Expr1AST *ParseExpr(void) {
  blk++;
  switch (curToken->token) {
  default:
//#ifdef PRINT
    blanks();
    printAST("ε<Expression+>\n");
    break;
//#endif // PRINT
       // return 0;
  case Let:
  case If:
  case '(':
  case '[':
  case DoubleColon:
  case IdAlpha:
  case IdSymbol: {
//#ifdef PRINT
    blanks();
    printAST("Exp<Expression+>\n");
//#endif // PRINT
    ExprAST *Exp = ParseExpression();
    blk--;
    if (!Exp)
      return 0;
//#ifdef PRINT
    blanks();
    printAST("Expr<Expression+>\n");
//#endif // PRINT
    Expr1AST *Expr = ParseExpr();
    blk--;
    if (!Expr) {
      return 0;
    }
    return new ExprExpr1AST(Exp, Expr);
  }
  case Then:
  case Else:
  case End:
  case ')':
  case ']':
  case ',':
  case ';':
  case '|':
  case In:
  case '=': {
//#ifdef PRINT
    blanks();
    printAST("ε<Expression+>\n");
//#endif // PRINT
  }
  }
}

// decl
static Dec1AST *ParseDecl(void) {
  blk++;
  switch (curToken->token) {
  default:
//#ifdef PRINT
    blanks();
    printAST("ε<Declaration+>\n");
//#endif // PRINT
    break;
  case Fun:
  case Val:
  case Local: {
//#ifdef PRINT
    blanks();
    printAST("Dec<Declaration+>\n");
//#endif // PRINT
    DecAST *Dec = ParseDeclaration();
    blk--;
    if (!Dec) {
      return 0;
    }
//#ifdef PRINT
    blanks();
    printAST("Decl<Declaration+>\n");
//#endif // PRINT
    Dec1AST *Decl = ParseDecl();
    blk--;
    if (!Decl) {
      return 0;
    }

    return new Dec2AST(Dec, Decl);
  }
  case In:
  case End: {
    // case tok_eof:
//#ifdef PRINT
    blanks();
    printAST("ε<Declaration+>\n");
//#endif // PRINT
  }
  }
}

