#include <cstdint>
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


	enum class PrimitiveT {Int, UInt, Float, Bool};


	struct ContainerT
	{
		std::string id;
		uint field_count;
		std::map<uint, TypeInfo*> field_types;

		ContainerT() = default;
		ContainerT(std::string id): id(id) {};
		~ContainerT() = default;
	};


	struct TypeInfo
	{
		TypeKind kind;
		std::string name;
		union
		{
			PrimitiveT primitive;
			ContainerT container;
		};

		TypeInfo(std::string name, PrimitiveT primitive): kind(TypeKind::Primitive), name(name), primitive(primitive) {};
		TypeInfo(std::string name, ContainerT container): kind(TypeKind::Container), name(name), container(container) {};
		~TypeInfo();

		inline bool operator==(const TypeInfo& rhs) 
		{
			if (this->kind != rhs.kind)
			{
				return false;
			}

			if (this->kind == TypeKind::Primitive)
			{
				if (this->primitive == rhs.primitive) {return true;}
				return false;
			}

			return false;
		}

		inline bool operator!=(const TypeInfo& rhs) 
		{
			return !(*this == rhs);
		}
	};




	bool strToInt(std::string& str, int64_t& i);
	bool strToUInt(std::string& str, uint64_t& i);
	bool strToFloat(std::string& str, double& i);

}