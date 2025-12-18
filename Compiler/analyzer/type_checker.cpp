#include "../node/node.hpp"
#include "../spec/scope.hpp"
#include "../spec/types.hpp"
#include "../spec/error.hpp"

#include <format>

#include "iostream"

#include "type_checker.hpp"


void CtTypeChecker::handleRoot(CtNode::RootProgram *node)
{
	this->walk(node->src);
}


void CtTypeChecker::handleSource(CtNode::Source *node)
{
	for (auto func: node->functions)
	{
		this->walk(func.second);
	}
}


void CtTypeChecker::handleFunction(CtNode::Function *node)
{
	this->current_scope = node->scope;

	for (auto stmt: node->statements)
	{
		this->walk(stmt);
	}
}


void CtTypeChecker::handleDeclaration(CtNode::Declaration *node)
{	
	// assuming the name resolver did its job
	auto var = this->current_scope->variables.at(node->name);
	
	if (!CtTypes::primitiveTypeMap.contains(var.type))
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Unknown type: {}", var.type)
		);
	}
}


void CtTypeChecker::handleOut(CtNode::Out *node)
{
	this->walk(node->expr);
}


void CtTypeChecker::handleAssignment(CtNode::Assignment *node)
{
	auto var = this->current_scope->variables[node->name->val];
	this->walk(node->value);

	if (var.type != node->value->result_type)
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Expression of type {} can not be assigned to variable of type {}", node->value->result_type, var.type)
		);
	}

	node->result_type = node->value->result_type;
}


void CtTypeChecker::handleInt(CtNode::Int *node)
{
	node->result_type = "i32";
}


void CtTypeChecker::handleFloat(CtNode::Float *node)
{
	node->result_type = "f32";
}


void CtTypeChecker::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	if (node->left->result_type != node->right->result_type)
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format(
				"Binary operation '{}' not supported for types {} and {}.", 
				int(node->op), node->left->result_type, node->right->result_type
			)
		);
	}

	node->result_type = node->left->result_type;
}


void CtTypeChecker::handleIdentifier(CtNode::Identifier *node)
{
	auto var = this->current_scope->variables[node->val];
	node->result_type = var.type;
}


void CtTypeChecker::handleFunctionCall(CtNode::FunctionCall *node)
{
	// Not Implemented
}


void CtTypeChecker::handleTypeCast(CtNode::TypeCast *node)
{
	if (!CtTypes::primitiveTypeMap.contains(node->to_type))
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Unknown type specified for type casting: {}", node->to_type)
		);
	}
	node->result_type = node->to_type;
	this->walk(node->expr);
}


CtNode::RootProgram* CtTypeChecker::analyze(CtNode::RootProgram* root)
{
	this->root = root;
	this->current_scope = nullptr;
	this->walk(root);
	return root;
}