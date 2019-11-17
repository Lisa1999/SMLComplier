#pragma once

enum TOKEN {
  Abstype,
  And,
  Andalso,
  As,
  Case,
  Datatype,
  Do,
  End,
  Eqtype,
  Exception,
  Else,
  False,
  Fn,
  Fun,
  Functor,
  Handle,
  In,
  Include,
  If,
  Infix,
  Infixr,
  Let,
  Local,
  Nonfix,
  Of,
  Op,
  Open,
  Orelse,
  Raise,
  Rec,
  Sharing,
  Sig,
  Signature,
  Struct,
  Structure,
  Then,
  Type,
  Val,
  Where,
  While,
  With,
  Withtype,

  //�������֣����ַ���ɣ� ! % & # + - * / : < = > ? @ \ ~ ^ | `
  Not,			// !
  AndSym,		// &
  Dollar,       // $
  Mode,         // % 
  Hashtag,      // #				���壺#"a"	#" "	#"\n"
  Plus,			// +
  Minus,		// -
  Mul,		    // *
  Div,			// /
  DivInt,		// div
  ModInt,		// mod
  Colon,		// :
  Less,			// <
  Equal,		// =
  More,			// >	
  QueMark,		// ?
  At,			// @
  Backslash,	// \			�÷���\n	\t	\\	\"
  Negtive,      // ~
  BackQuote,	// `
  Non,			// ^
  Or,			// |

  DoubleColon,  //::  
  EqualMore,    // =>
  MinusMore,    // ->
  ColonMore,    // :>
  Dot,          // .
  LP,           // (
  RP,           // )
  LPMul,		// (*
  MulRP,		// *)
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
  Apostrophe,   //	'\


  IdAlpha,		//��ĸ����
  IdSymbol,		//��������
  ConstInt,		//����
  ConstString,	//�ַ���
  ConstReal,	//ʵ��
  ConstChar		//char #"a"
  
};

/*
  ��ʶ��
��ĸ���֣�����ĸ��ʼ������ɸ���������Ŀ����ĸ�����֡��»��ߣ�_����Ʋ��(������) ' 

*/

//��׼�������Ϊ��д
enum STANLIB {
  Int,
  Math,
};

enum LIBFUN_INT { Min, Abs, Max, Sign };

enum LIBFUN_MATH { Sqrt, Sin, Cos, Atan, Exp, Ln };