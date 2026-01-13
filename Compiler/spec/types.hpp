#include <map>
#include <string>
#include <vector>

#pragma once

namespace CtTypes
{
	struct Info;
	struct ContainerInfo;
	struct FunctionInfo;

	enum class Kind {Container, Function};

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
		std::map<std::string, Overloads> constructors;
		FunctionInfo* destructor;

		ContainerInfo() {kind = Kind::Container;};
	};


	struct FunctionInfo : Info
	{
		ContainerInfo* return_type;
		std::vector<ContainerInfo*> parameters;

		FunctionInfo() {kind = Kind::Function;};
	};

}