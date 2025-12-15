#include "../node/node.hpp"
#include <iostream>
#include "analyzer.hpp"
#include "../spec/types.hpp"



void CtAnalyzer::handleRoot(CtNode::RootProgram *node)
{
	CtNodePrinter printer;
	printer.print(node);
	this->walk(node->src);
}


void CtAnalyzer::handleSource(CtNode::Source *node)
{
	for (auto func: node->functions)
	{
		this->walk(func.second);
	}
}


void CtAnalyzer::handleFunction(CtNode::Function *node)
{
	std::cout << "Analyzing function: " << node->name->val << "\n";

	for (auto stmt: node->statements)
	{
		this->walk(stmt);
	}
}


void CtAnalyzer::handleDeclaration(CtNode::Declaration *node)
{
	if (CtTypes::primitiveTypeMap.contains(node->type->val))
	{
		auto type = CtTypes::primitiveTypeMap[node->type->val];
		this->typeMap[node->name->val] = type;
		std::cout << "Registered variable " << node->name->val << " with type " << type.id  << "\n";
		return;
	}
	
	std::cout << "Unknown primtive type: " << node->type->val << "\n";
	exit(1);
}

void CtAnalyzer::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->value);

	if (this->typeMap.contains(node->name->val))
	{
		if (node->value->result_type == this->typeMap[node->name->val].id)
		{
			return;
		}
		else 
		{
			std::cout << "Cannnot assign. Type mismatch." << this->typeMap[node->name->val].id<<"="<<node->value->result_type<<"\n";
			exit(1);
		}
	}
	else 
	{
		std::cout << "Unknown Identifier: " << node->name->val << "\n";
		exit(1);
	}
}

void CtAnalyzer::handleInt(CtNode::Int *node)
{
	node->val.i32 = std::stoi(node->raw);
	node->result_type = "i32";
}

void CtAnalyzer::handleFloat(CtNode::Float *node)
{
	node->val.f32 = std::stof(node->raw);
	node->result_type = "f32";
}

void CtAnalyzer::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	if (node->left->result_type != node->right->result_type)
	{
		std::cout << "Cannot carry binary operation. Type mismatch.\n" << std::endl;
		exit(1);
	}
	node->result_type = node->left->result_type;
}


void CtAnalyzer::handleIdentifier(CtNode::Identifier *node)
{
	if (this->typeMap.contains(node->val))
	{
		node->result_type = this->typeMap[node->val].id;
	}
	else 
	{
		std::cout << "Unknown Identifier: " << node->val << "\n";
		exit(1);
	}
}


void CtAnalyzer::handleFunctionCall(CtNode::FunctionCall *node){}

CtNode::RootProgram* CtAnalyzer::analyze(CtNode::RootProgram* root)
{
	this->walk(root);
	std::cout << "Root program successfully analyzed.\n";
	return root;
}
