#include "../node/node.hpp"
#include "../spec/scope.hpp"
#include "../spec/error.hpp"

#include <format>


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
	this->walk(node->block);
}


void CtTypeChecker::handleStmtBlock(CtNode::StmtBlock *node)
{
	for (auto stmt: node->stmts)
	{
		this->walk(stmt);
	}
}


void CtTypeChecker::handleDeclaration(CtNode::Declaration *node)
{	
	// assuming the name resolver did its job
	auto& var = this->current_scope->variables.at(node->name);
	
	if (!primitiveTypes.contains(var.type_id))
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Unknown type: {}", var.type_id)
		);
	}

	var.type = primitiveTypes[var.type_id];

	if (node->assignment) {this->walk(node->assignment);}
}


void CtTypeChecker::handleOut(CtNode::Out *node)
{
	this->walk(node->expr);
}


void CtTypeChecker::handleLoop(CtNode::Loop *node)
{
	this->walk(node->block);
}


void CtTypeChecker::handleWhile(CtNode::While *node)
{
	this->walk(node->condition);
	if (*node->condition->expr_type != *primitiveTypes["bool"])
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("While loop condition must evaluate to type 'bool', not {}.", node->condition->expr_type->name)
		);
	}

	this->walk(node->block);
}


void CtTypeChecker::handleFor(CtNode::For *node)
{
	this->walk(node->init);

	this->walk(node->condition);
	if (*node->condition->expr_type != *primitiveTypes["bool"])
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("For loop condition must evaluate to type 'bool', not {}.", node->condition->expr_type->name)
		);
	}

	this->walk(node->step);
	this->walk(node->block);
}


void CtTypeChecker::handleIf(CtNode::If *node)
{
	this->walk(node->condition);
	if (*node->condition->expr_type != *primitiveTypes["bool"])
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("If condition must evaluate to type 'bool', not {}.", node->condition->expr_type->name)
		);
	}

	this->walk(node->then_block);
	if (node->else_stmt) {this->walk(node->else_stmt);}
}


void CtTypeChecker::handleAssignment(CtNode::Assignment *node)
{
	auto var = this->current_scope->variables[node->name->val];
	this->walk(node->value);

	if (*var.type != *node->value->expr_type)
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Expression of type {} can not be assigned to variable of type {}", node->value->expr_type->name, var.type->name)
		);
	}

	node->expr_type = node->value->expr_type;
}


void CtTypeChecker::handleInt(CtNode::Int *node)
{
	if (CtSpec::strToInt(node->raw, node->val.i64))
	{
		node->expr_type = primitiveTypes["int"];
	}
	else if (CtSpec::strToUInt(node->raw, node->val.u64))
	{
		node->expr_type = primitiveTypes["uint"];
	}
	else 
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Invalid integar : {}", node->raw)
		);
	}
}


void CtTypeChecker::handleFloat(CtNode::Float *node)
{
	if (CtSpec::strToFloat(node->raw, node->val.f64))
	{
		node->expr_type = primitiveTypes["float"];
	}
	else 
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Invalid floating number : {}", node->raw)
		);
	}
}


void CtTypeChecker::handleBool(CtNode::Bool *node)
{
	node->expr_type = primitiveTypes["bool"];
};


void CtTypeChecker::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	if (node->left->expr_type == primitiveTypes["bool"])
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format(
				"Binary operation '{}' not supported for bool types. {} & {}", 
				int(node->op), node->left->expr_type->name, node->right->expr_type->name
			)
		);
	}

	if (node->left->expr_type != node->right->expr_type)
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format(
				"Binary operation '{}' not supported for types {} and {}.", 
				int(node->op), node->left->expr_type->name, node->right->expr_type->name
			)
		);
	}

	node->expr_type = node->left->expr_type;
}


void CtTypeChecker::handleIdentifier(CtNode::Identifier *node)
{
	auto var = this->current_scope->variables[node->val];
	node->expr_type = var.type;
}


void CtTypeChecker::handleFunctionCall(CtNode::FunctionCall *node)
{
	// Not Implemented
}


void CtTypeChecker::handleTypeCast(CtNode::TypeCast *node)
{
	if (!primitiveTypes.contains(node->to_type))
	{
		CtError::raise(
			CtError::ErrorType::TypeError, 
			std::format("Unknown type specified for type casting: {}", node->to_type)
		);
	}
	node->expr_type = primitiveTypes[node->to_type];
	this->walk(node->expr);
}


CtNode::RootProgram* CtTypeChecker::analyze(CtNode::RootProgram* root)
{
	this->root = root;
	this->current_scope = nullptr;
	this->walk(root);
	return root;
}