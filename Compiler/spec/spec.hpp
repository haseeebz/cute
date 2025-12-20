#include <map>
#include <string>



#pragma once 


namespace CtSpec
{
	enum class BinaryOpType
	{
		Add,
		Sub,
		Mul,
		Div,
		Mod
	};

	inline std::map<BinaryOpType, uint> binaryOpPrecedence =
	{
		{BinaryOpType::Add, 1},
		{BinaryOpType::Sub, 1},
		{BinaryOpType::Mul, 2},
		{BinaryOpType::Div, 2},
		{BinaryOpType::Mod, 3},
	};


	struct TypeInfo;
	enum class TypeKind {Primitive, Container, Function};


	enum class PrimitiveT {I32, I64, F32, F64, Bool};


	struct ContainerT
	{
		std::string id;
		uint field_count;
		std::map<uint, TypeInfo*> field_types;

		ContainerT() = default;
		ContainerT(std::string id): id(id) {};
	};


	struct TypeInfo
	{
		TypeKind kind;

		union
		{
			PrimitiveT primitive;
			ContainerT container;
		};

		TypeInfo(PrimitiveT primitive): kind(TypeKind::Primitive), primitive(primitive) {};
		TypeInfo(ContainerT container): kind(TypeKind::Container), container(container) {};
	};

}