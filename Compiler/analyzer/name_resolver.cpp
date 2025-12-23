#include <format>

#include "../node/node.hpp"

#include "../spec/scope.hpp"
#include "../spec/error.hpp"
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
		CtError::raise(
			CtError::ErrorType::NameError, 
			std::format("Variable already defined within scope: {}", node->name)
		);
	};

	this->current_scope->variables[node->name] = CtScope::Variable(CtScope::VarKind::Local, node->name, node->type_id);
}


void CtNameResolver::handleOut(CtNode::Out *node)
{
	this->walk(node->expr);
}


void CtNameResolver::handleLoop(CtNode::Loop *node)
{
	for (auto stmt: node->block)
	{
		this->walk(stmt);
	}
}


void CtNameResolver::handleIf(CtNode::If *node)
{
	this->walk(node->condition);
	for (auto stmt: node->block)
	{
		this->walk(stmt);
	}
}


void CtNameResolver::handleAssignment(CtNode::Assignment *node)
{
	if (!this->current_scope->variables.contains(node->name->val))
	{
		CtError::raise(
			CtError::ErrorType::NameError, 
			std::format("Undefined variable: {}", node->name->val)
		);
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

void CtNameResolver::handleBool(CtNode::Bool *node)
{

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
		CtError::raise(
			CtError::ErrorType::NameError, 
			std::format("Undefined variable: {}", node->val)
		);
	};
}

void CtNameResolver::handleFunctionCall(CtNode::FunctionCall *node)
{
	// nothing implemented
}


void CtNameResolver::handleTypeCast(CtNode::TypeCast *node)
{
	this->walk(node->expr);
}


CtNode::RootProgram* CtNameResolver::analyze(CtNode::RootProgram* root)
{
	this->root = root;
	this->current_scope = nullptr;
	this->walk(root);
	return root;
}

