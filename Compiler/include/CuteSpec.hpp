#include <map>
#include <string>


#pragma once

namespace CtSpec
{
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


	enum class BinaryOp
	{
		Add,
		Sub,
		Mul,
		Div
	};

	inline std::map<char, BinaryOp> binaryOpMap =
	{
		{'+', BinaryOp::Add},
		{'-', BinaryOp::Sub},
		{'*', BinaryOp::Mul},
		{'/', BinaryOp::Div},
	};	

	inline std::map<char, int> binaryPrecedenceMap =
	{
		{'+', 1},
		{'-', 1},
		{'*', 2},
		{'/', 2},
	};	

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