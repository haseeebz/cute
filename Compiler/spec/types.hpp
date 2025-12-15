#include <map>
#include <string>


#pragma once

namespace CtTypes
{

	enum class TypeKind {Void, Int32, Int64, Float32, Float64};


	struct TypeInfo
	{
		TypeKind kind;
		std::string id;

		TypeInfo(): kind(TypeKind::Void) {};
		TypeInfo(std::string id, TypeKind kind): kind(kind), id(id) {};
	};


	inline std::map<std::string, TypeInfo> primitiveTypeMap =
	{
		{"i32" , TypeInfo("i32", TypeKind::Int32)},
		{"i64",  TypeInfo("i64", TypeKind::Int64)},
		{"f32",  TypeInfo("f32", TypeKind::Float32)},
		{"f64",  TypeInfo("f64", TypeKind::Float64)},

		{"bool", TypeInfo("bool", TypeKind::Int32)},
	};	
	
}

