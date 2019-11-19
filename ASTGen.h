#pragma once
#include"GeneralFile.h"
#include"MyParser.h"

class ASTGen {
public:

};

/// ExprAST - Base class for all expression nodes.
//class ExprAST {
//public:
//  virtual ~ExprAST() {}
//  virtual Value *codegen() = 0;
//};
//static ExprAST *ParseExpression();

//class ExpressionAST {
//public:
//  virtual ~ExpressionAST() {}
//  virtual Value *codegen() = 0;
//};
//static ExpressionAST *ParseExpr();

/// exp ::= con expr	
/// int
//class IntExprAST : public ExprAST {
//  int intVal;
//  ExpressionAST *expr;
//
//public:
//  IntExprAST(int _intVal, ExpressionAST *_expr)
//      : intVal(_intVal), expr(_expr) {}
//  virtual Value *codegen();
//};

/// char
//class CharExprAST : public ExprAST {
//  char charVal;
//  ExpressionAST *expr;
//
// public:
//  CharExprAST(char _charVal, ExpressionAST *_expr)
//      : charVal(_charVal), expr(_expr) {}
//   virtual Value *codegen();
//};

/// string
//class StringExprAST : public ExprAST {
//  string stringVal;
//  ExpressionAST *expr;
//
//  public:
//  StringExprAST(string _stringVal, ExpressionAST *_expr)
//        : stringVal(_stringVal), expr(_expr) {}
//    virtual Value *codegen();
//};

/// real
//class RealExprAST : public ExprAST {
//  double realVal;
//  ExpressionAST *expr;
//
//public:
//  RealExprAST(double _realVal, ExpressionAST *_expr)
//      : realVal(_realVal), expr(_expr) {}
//  virtual Value *codegen();
//};


// exp ::= id expr
//class IdExprAST : public ExprAST {
//  string IdName;
//  ExpressionAST *Expr;
//
//public:
//  IdExprAST(string IdName, ExpressionAST *Expr)
//      : IdName(IdName), Expr(Expr) {}
//  virtual Value *codegen();
//};

// Pattern : pat
//class PattAST {
//public:
//  virtual ~PattAST() {}
//  virtual Value *codegen() = 0;
//};
//static PattAST *ParsePattern(void);