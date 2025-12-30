#include "../node/node.hpp"

#pragma once

struct CtScope
{
	enum class DefKind {Variable, Function};

	struct Defintion
	{
		DefKind defkind;
		std::string id;
		std::string type_id;
		CtSpec::TypeInfo* type_info;

		union 
		{
			CtNode::Function* func;
		} node;

		Defintion() = default;
		Defintion(DefKind kind, std::string id, std::string type): defkind(kind), id(id), type_id(type) {};
	};


	CtScope* parent = nullptr;
	std::map<std::string, CtScope::Defintion> definitions;

	CtScope(CtScope* parent): parent(parent) {};

	bool has(std::string id, Defintion& def)
	{
		if (this->definitions.contains(id))
		{
			def = this->definitions[id];
			return true;
		}
		return false;
	}

	// recursively search upwards to look for the desired defintion
	bool search(std::string id, Defintion& def)
	{
		CtScope* scope = this;

		while (scope)
		{
			if (scope->definitions.contains(id))
			{
				def = scope->definitions[id];
				return true;
			}
			scope = scope->parent;
		}
		return false;
	}
};