#include <map>
#include <string>




#pragma once 


namespace CtSyntax
{

	// Keywords


	enum class KeyWord
	{
		// declaration
		Let,

		// control flow
		If,
		Else,
		While,
		For,
		Loop,
		Break,
		Continue,

		// Complex
		FunctionDef
	};


	inline std::map<std::string, KeyWord> keywordMap =
	{
		{"let",      KeyWord::Let},

		{"if",       KeyWord::If},
		{"else",     KeyWord::Else},
		{"while",    KeyWord::While},
		{"for",      KeyWord::For},
		{"loop",     KeyWord::Loop},
		{"break",    KeyWord::Break},
		{"continue", KeyWord::Continue},

		{"func",     KeyWord::FunctionDef},
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

		Greater,
		GreaterEqual,
		DoubleGreater,

		Lesser,
		LesserEqual,
		DoubleLesser,

		Hashtag,
		Exclamation,
		Colon,
		Dot,

		SingleQuote,
		DoubleQuote,
	};


	inline std::map<std::string, Symbol> symbolMap =
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

		{ ">",  Symbol::Greater },
		{ ">=", Symbol::GreaterEqual },
		{ ">>", Symbol::DoubleGreater },

		{ "<",  Symbol::Lesser },
		{ "<=", Symbol::LesserEqual },
		{ "<<", Symbol::DoubleLesser },

		{ "#",  Symbol::Hashtag },
		{ "!",  Symbol::Exclamation },
		{ ":",  Symbol::Colon },
		{ ".",  Symbol::Dot },

		{ "'",  Symbol::SingleQuote },
		{ "\"", Symbol::DoubleQuote }
	};

 

	inline std::map<Symbol, uint> binaryOpMap =
	{
		{Symbol::Plus,  	 1},
		{Symbol::Minus, 	 1},
		{Symbol::Star,  	 2},
		{Symbol::Slash,      2},
		{Symbol::Percentage, 2}
	};

}