#include <map>
#include <string>


#pragma once

namespace CtSpec
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


	// types


	enum class TypeKind {Int32, Int64, Float32, Float64, Bool, Container};

	
	struct TypeInfo
	{
		TypeKind kind;

		std::string id;
		uint size;

		std::map<std::string, TypeInfo> fields;

		TypeInfo(TypeKind kind, uint size): kind(kind), size(size) {};
	};


	inline std::map<std::string, TypeInfo> primitiveTypeMap =
	{
		{"i32" , TypeInfo(TypeKind::Int32, 4)},
		{"i64",  TypeInfo(TypeKind::Int64, 8)},
		{"f32",  TypeInfo(TypeKind::Float32, 4)},
		{"f64",  TypeInfo(TypeKind::Float64, 8)},

		{"bool", TypeInfo(TypeKind::Bool, 4)},
	};	

}