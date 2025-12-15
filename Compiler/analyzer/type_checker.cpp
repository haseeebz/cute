#include "../node/node.hpp"
#include "../spec/scope.hpp"
#include "../spec/types.hpp"

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
	std::cout << "Type Checking Function: " << node->name << "\n";

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
		std::cout << "Unknown type: " << var.type << std::endl;
		exit(1);
	}
}


void CtTypeChecker::handleAssignment(CtNode::Assignment *node)
{
	auto var = this->current_scope->variables[node->name->val];
	this->walk(node->value);

	if (var.type != node->value->result_type)
	{
		std::cout << "Type Mismatch. "<<var.type<<"="<<node->value->result_type<< std::endl;
		exit(1);
	}

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
		std::cout << "Invalid Binary Operation. Type Mismatch." << std::endl;
		exit(1);
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


CtNode::RootProgram* CtTypeChecker::analyze(CtNode::RootProgram* root)
{
	this->root = root;
	this->current_scope = nullptr;
	this->walk(root);
	return root;
}