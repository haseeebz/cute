#include "spec.hpp"
#include <string>
#include <map>

#pragma once


namespace CtScope
{
	enum class VarKind {Local, Parameter, Global};

	struct Variable
	{
		VarKind kind;
		std::string id;
		std::string type_id;
		CtSpec::TypeInfo* type;

		Variable() = default;
		Variable(VarKind kind, std::string id, std::string type): kind(kind), id(id), type_id(type) {};
	};

	struct Scope
	{
		Scope* parent;
		std::map<std::string, Variable> variables;

		Scope(Scope* parent): parent(parent) {};
	};

};