#include <cstdint>
#include <map>
#include <string>



#pragma once 


namespace CtSpec
{

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


	inline std::map<BinaryOpType, uint> binaryOpPrecedence =
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

	bool strToInt(std::string& str, int64_t& i);
	bool strToUInt(std::string& str, uint64_t& i);
	bool strToFloat(std::string& str, double& i);

}