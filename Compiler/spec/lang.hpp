#include <map>
#include <string>

#pragma once 

namespace CtLang
{

	enum class KeyWord
	{
		Let,
		Out,

		If,
		Else,
		While,
		For,
		Loop,
		Break,
		Continue,

		Func,

		True,
		False,

		And,
		Or,
		Not
	};


	inline const std::map<std::string, KeyWord> keywordMap =
	{
		{"let",      KeyWord::Let},
		{"out",      KeyWord::Out},

		{"if",       KeyWord::If},
		{"else",     KeyWord::Else},
		{"while",    KeyWord::While},
		{"for",      KeyWord::For},
		{"loop",     KeyWord::Loop},
		{"break",    KeyWord::Break},
		{"continue", KeyWord::Continue},

		{"func",     KeyWord::Func},

		{"true",     KeyWord::True},
		{"false",    KeyWord::False},

		{"and",     KeyWord::And},
		{"or",      KeyWord::Or},
		{"not",     KeyWord::Not},
	};


	// symbols

	enum class Symbol
	{
		Plus,
		Minus,
		Star,
		Slash,
		Percentage,
		

		LeftParan,
		RightParan,
		LeftBracket,
		RightBracket,
		LeftBraces,
		RightBraces,

		Equal,
		DoubleEqual,
		NotEqual,

		Greater,
		GreaterEqual,
		DoubleGreater,

		Lesser,
		LesserEqual,
		DoubleLesser,

		SingleBar,
		DoubleBar,
		SingleAnd,
		DoubleAnd,

		Exponent,
		Tilde,
		Hashtag,
		Exclamation,
		Colon,
		Dot,

		SingleQuote,
		DoubleQuote,
	};


	inline const char EOL = ';';

	inline const std::map<std::string, Symbol> symbolMap =
	{
		{ "+",  Symbol::Plus },
		{ "-",  Symbol::Minus },
		{ "*",  Symbol::Star },
		{ "/",  Symbol::Slash },
		{ "%",  Symbol::Percentage },

		{ "(",  Symbol::LeftParan },
		{ ")",  Symbol::RightParan },
		{ "[",  Symbol::LeftBracket },
		{ "]",  Symbol::RightBracket },
		{ "{",  Symbol::LeftBraces },
		{ "}",  Symbol::RightBraces },

		{ "=",  Symbol::Equal },
		{ "==", Symbol::DoubleEqual },
		{ "!=", Symbol::NotEqual },

		{ ">",  Symbol::Greater },
		{ ">=", Symbol::GreaterEqual },
		{ ">>", Symbol::DoubleGreater },

		{ "<",  Symbol::Lesser },
		{ "<=", Symbol::LesserEqual },
		{ "<<", Symbol::DoubleLesser },

		{ "|",  Symbol::SingleBar },
		{ "&",  Symbol::SingleAnd },
		{ "||", Symbol::DoubleBar },
		{ "&&", Symbol::DoubleAnd },
		{ "^",  Symbol::Exponent },
		{ "~",  Symbol::Tilde },

		{ "#",  Symbol::Hashtag },
		{ "!",  Symbol::Exclamation },
		{ ":",  Symbol::Colon },
		{ ".",  Symbol::Dot },

		{ "'",  Symbol::SingleQuote },
		{ "\"", Symbol::DoubleQuote }
	};


	enum class BinaryOpType
	{
		Add,
		Sub,
		Mul,
		Div,
		Mod,

		Equal,
		NotEqual,
		Lesser,
		LesserEqual,
		Greater,
		GreaterEqual,

		BitShiftLeft,
		BitShiftRight,
		BitAnd,
		BitOr,
		BitXor,

		LogicAnd,
		LogicOr,

		MemberAccess,
		NamespaceAccesss
	};

	
	inline const std::map<BinaryOpType, uint> binaryOpPrecedence =
	{
		{BinaryOpType::LogicOr, 1},
		{BinaryOpType::LogicAnd,2},
		{BinaryOpType::BitOr, 3},
		{BinaryOpType::BitXor, 4},
		{BinaryOpType::BitAnd, 5},
		{BinaryOpType::Equal, 6},
		{BinaryOpType::NotEqual, 7},
		{BinaryOpType::Greater, 8},
		{BinaryOpType::GreaterEqual, 8},
		{BinaryOpType::Lesser, 8},
		{BinaryOpType::LesserEqual, 8},
		{BinaryOpType::BitShiftLeft, 9},
		{BinaryOpType::BitShiftRight, 9},

		{BinaryOpType::Add, 10},
		{BinaryOpType::Sub, 10},
		{BinaryOpType::Mul, 11},
		{BinaryOpType::Div, 11},
		{BinaryOpType::Mod, 11},

		{BinaryOpType::MemberAccess, 12},
		{BinaryOpType::NamespaceAccesss, 12},
	};


	enum class UnaryOpType
	{
		LogicNot,
		BitNot,
		Negation,
		Increment,
		Decrement
	};

	
	inline const std::map<Symbol, BinaryOpType> symToBinaryOp 
	{
		{ Symbol::Plus,          BinaryOpType::Add },
		{ Symbol::Minus,         BinaryOpType::Sub },
		{ Symbol::Star,          BinaryOpType::Mul },
		{ Symbol::Slash,         BinaryOpType::Div },
		{ Symbol::Percentage,    BinaryOpType::Mod },

		{ Symbol::DoubleEqual,   BinaryOpType::Equal },
		{ Symbol::NotEqual,      BinaryOpType::NotEqual },
		{ Symbol::Greater,       BinaryOpType::Greater },
		{ Symbol::GreaterEqual,  BinaryOpType::GreaterEqual },
		{ Symbol::Lesser,        BinaryOpType::Lesser },
		{ Symbol::LesserEqual,   BinaryOpType::LesserEqual },

		{ Symbol::DoubleGreater, BinaryOpType::BitShiftRight },
		{ Symbol::DoubleLesser,  BinaryOpType::BitShiftLeft },

		{ Symbol::SingleBar,     BinaryOpType::BitOr },
		{ Symbol::SingleAnd,     BinaryOpType::BitAnd },
		{ Symbol::Exponent,      BinaryOpType::BitXor },

		{ Symbol::DoubleBar,     BinaryOpType::LogicOr },
		{ Symbol::DoubleAnd,     BinaryOpType::LogicAnd },
	};


	inline const std::map<Symbol, UnaryOpType> symToUnaryOp 
	{
		{ Symbol::Exclamation, UnaryOpType::LogicNot },
		{ Symbol::Tilde,       UnaryOpType::BitNot },  
		{ Symbol::Minus,       UnaryOpType::Negation }
	};
		
}