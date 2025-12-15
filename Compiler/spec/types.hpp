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
		uint size;

		TypeInfo(): kind(TypeKind::Void) {};
		TypeInfo(std::string id, TypeKind kind, uint size): kind(kind), id(id), size(size) {};
	};


	inline std::map<std::string, TypeInfo> primitiveTypeMap =
	{
		{"i32" , TypeInfo("i32", TypeKind::Int32, 4)},
		{"i64",  TypeInfo("i64", TypeKind::Int64, 8)},
		{"f32",  TypeInfo("f32", TypeKind::Float32, 4)},
		{"f64",  TypeInfo("f64", TypeKind::Float64, 8)},

		{"bool", TypeInfo("bool", TypeKind::Int32, 4)},
	};	

}