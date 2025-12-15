#include <iostream>

#include "../node/node.hpp"

#include "../spec/scope.hpp"
#include "name_resolver.hpp"



void CtNameResolver::handleRoot(CtNode::RootProgram *node)
{
	this->walk(node->src);
}


void CtNameResolver::handleSource(CtNode::Source *node)
{
	for (auto func: node->functions)
	{
		this->walk(func.second);
	}
}

void CtNameResolver::handleFunction(CtNode::Function *node)
{
	std::cout << "Resolving Function: " << node->name << "\n";

	node->scope = new CtScope::Scope(this->current_scope);
	this->current_scope = node->scope;

	for (auto stmt: node->statements)
	{
		this->walk(stmt);
	}
}


void CtNameResolver::handleDeclaration(CtNode::Declaration *node)
{	
	if (this->current_scope->variables.contains(node->name))
	{
		std::cout << "Variable '" << node->name << "' already declared within scope!\n";
		exit(1);
	};

	this->current_scope->variables[node->name] = CtScope::Variable(CtScope::VarKind::Local, node->name, node->type);
}


void CtNameResolver::handleAssignment(CtNode::Assignment *node)
{
	if (!this->current_scope->variables.contains(node->name->val))
	{
		std::cout << "Variable '" << node->name->val << "' undefined!\n";
		exit(1);
	};
	this->walk(node->value);
}


void CtNameResolver::handleInt(CtNode::Int *node)
{
	// does not need to do anything
};

void CtNameResolver::handleFloat(CtNode::Float *node)
{
	// does not need to do anythings
};

void CtNameResolver::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);
};

void CtNameResolver::handleIdentifier(CtNode::Identifier *node)
{
	if (!this->current_scope->variables.contains(node->val))
	{
		std::cout << "Variable '" << node->val << "' undefined!\n";
		exit(1);
	};
}

void CtNameResolver::handleFunctionCall(CtNode::FunctionCall *node)
{
	// nothing implemented
}


CtNode::RootProgram* CtNameResolver::analyze(CtNode::RootProgram* root)
{
	std::cout << "Resolving Root..\n";
	this->root = root;
	this->current_scope = nullptr;
	this->walk(root);
	return root;
}
