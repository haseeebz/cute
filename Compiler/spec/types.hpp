#include <map>
#include <string>
#include <vector>

#pragma once

namespace CtTypes
{
	struct Info;
	struct ContainerInfo;
	struct FunctionInfo;
	struct VariableInfo;

	enum class Kind {Container, Function, Variable};

	struct Info
	{
		Kind kind;
	};

	// all data is a container in cute
	struct ContainerInfo : Info
	{
		std::map<std::string, ContainerInfo*> fields;

		using Overloads = std::vector<FunctionInfo*>;

		std::map<std::string, Overloads> methods;
		Overloads constructors;
		FunctionInfo* destructor;

		std::string repr;

		ContainerInfo() {kind = Kind::Container;};
	};


	struct FunctionInfo : Info
	{
		ContainerInfo* return_type;
		std::vector<ContainerInfo*> parameters;

		std::string repr;
		FunctionInfo() {kind = Kind::Function;};
	};

	struct VariableInfo : Info
	{
		ContainerInfo* type;

		std::string repr;
		VariableInfo() {kind = Kind::Variable;};
	};


	inline std::map<std::string ,ContainerInfo*> primitives;
	void initPrimitives();
}


struct CtScope 
{
	CtScope* parent = nullptr;
	std::map<std::string, CtTypes::Info*> symbols;

	CtScope() = default;
	CtScope(CtScope* parent): parent(parent) {}
	void addSymbol(std::string s, CtTypes::Info*);
	CtTypes::Info* getSymbol(std::string s);
};