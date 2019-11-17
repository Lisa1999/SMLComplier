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

  //符号名字：由字符组成： ! % & # + - * / : < = > ? @ \ ~ ^ | `
  Not,			// !
  AndSym,		// &
  Dollar,       // $
  Mode,         // % 
  Hashtag,      // #				定义：#"a"	#" "	#"\n"
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
  Backslash,	// \			用法：\n	\t	\\	\"
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


  IdAlpha,		//字母名字
  IdSymbol,		//符号名字
  ConstInt,		//整数
  ConstString,	//字符串
  ConstReal,	//实数
  ConstChar		//char #"a"
  
};

/*
  标识符
字母名字：由字母开始，后面可跟随任意数目的字母、数字、下划线（_）、撇号(单引号) ' 

*/

//标准库的名字为大写
enum STANLIB {
  Int,
  Math,
};

enum LIBFUN_INT { Min, Abs, Max, Sign };

enum LIBFUN_MATH { Sqrt, Sin, Cos, Atan, Exp, Ln };