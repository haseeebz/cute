#include "../node/node.hpp"
#include "../node/scope.hpp"
#include "../spec/spec.hpp"

#include "map"
#include <string>
#include <format>
#include <iostream>

#include "transpiler.hpp"

using CtSpec::BinaryOpType;

static const std::string binop_to_c(BinaryOpType op)
{
	switch (op)
	{
		case BinaryOpType::Add:            return "+";
		case BinaryOpType::Sub:            return "-";
		case BinaryOpType::Mul:            return "*";
		case BinaryOpType::Div:            return "/";
		case BinaryOpType::Mod:            return "%";

		case BinaryOpType::Equal:          return "==";
		case BinaryOpType::NotEqual:       return "!=";
		case BinaryOpType::Lesser:         return "<";
		case BinaryOpType::LesserEqual:    return "<=";
		case BinaryOpType::Greater:        return ">";
		case BinaryOpType::GreaterEqual:   return ">=";

		case BinaryOpType::BitShiftLeft:   return "<<";
		case BinaryOpType::BitShiftRight:  return ">>";
		case BinaryOpType::BitAnd:         return "&";
		case BinaryOpType::BitOr:          return "|";
		case BinaryOpType::BitXor:         return "^";

		case BinaryOpType::LogicAnd:       return "&&";
		case BinaryOpType::LogicOr:        return "||";
	}

	return "/* invalid */";
}


void CtTranspiler::handleRoot(CtNode::RootProgram *node)
{
	this->walk(node->src);
}

void CtTranspiler::handleSource(CtNode::Source *node)
{
	code.append("#include <stdio.h>\n");
	code.append(std::format("#include \"{}\"\n", "../Cute/include/CuteLib.hpp"));
	this->walk(node->functions["main"]);
}

void CtTranspiler::handleFunction(CtNode::Function *node)
{
	code.append("int main()");
	this->walk(node->block);
}

void CtTranspiler::handleStmtBlock(CtNode::StmtBlock *node)
{
	code.append("{");
	for (auto stmt: node->stmts)
	{
		this->walk(stmt);
		code.append(";");
	}
	code.append("}");
}

void CtTranspiler::handleDeclaration(CtNode::Declaration *node)
{
	std::map<CtSpec::PrimitiveT, std::string> type_map = 
	{
		{CtSpec::PrimitiveT::Int,   "I64"},
		{CtSpec::PrimitiveT::UInt,  "U64"},
		{CtSpec::PrimitiveT::Float, "F64"},
		{CtSpec::PrimitiveT::Bool,  "Bool"},
	};

	code.append(type_map[node->type->primitive]);
	code.append(" ");
	code.append(node->name);

	if (node->assignment)
	{
		code.append(" = ");
		this->walk(node->assignment->value);
	}
}

void CtTranspiler::handleOut(CtNode::Out *node)
{
	code.append("printf(\"%d\\n\", ");
	this->walk(node->expr);
	code.append(")");
}

void CtTranspiler::handleIf(CtNode::If *node)
{
	code.append("if (");
	this->walk(node->condition);
	code.append(") ");
	this->walk(node->then_block);

	if (node->else_stmt)
	{
		code.append(" else ");
		this->walk(node->else_stmt);
	}
}

void CtTranspiler::handleLoop(CtNode::Loop *node)
{
	code.append("while (1) ");
	this->walk(node->block);
}

void CtTranspiler::handleWhile(CtNode::While *node)
{
	code.append("while (");
	this->walk(node->condition);
	code.append(") ");
	this->walk(node->block);
}

void CtTranspiler::handleFor(CtNode::For *node)
{
	code.append("for (");
	this->walk(node->init);
	code.append("; ");
	this->walk(node->condition);
	code.append("; ");
	this->walk(node->step);
	code.append(") ");
	this->walk(node->block);
}

void CtTranspiler::handleInt(CtNode::Int *node)
{
	code.append(node->raw);
}

void CtTranspiler::handleFloat(CtNode::Float *node)
{
	code.append(node->raw);
}

void CtTranspiler::handleBool(CtNode::Bool *node)
{
	code.append(node->val ? "1" : "0");
}

void CtTranspiler::handleBinaryOp(CtNode::BinaryOp *node)
{
	code.append("(");
	this->walk(node->left);
	code.append(std::format(" {} ", binop_to_c(node->op)));
	this->walk(node->right);
	code.append(")");
}

void CtTranspiler::handleIdentifier(CtNode::Identifier *node)
{
	code.append(node->val);
}


void CtTranspiler::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->name);
	code.append(" = ");
	this->walk(node->value);
}

void CtTranspiler::handleTypeCast(CtNode::TypeCast *node)
{
	static std::map<CtSpec::PrimitiveT, std::string> type_map = 
	{
		{CtSpec::PrimitiveT::Int,   "I64"},
		{CtSpec::PrimitiveT::UInt,  "U64"},
		{CtSpec::PrimitiveT::Float, "F64"},
		{CtSpec::PrimitiveT::Bool,  "Bool"},
	};

	code.append("(");
	code.append(type_map[node->expr_type->primitive]);
	code.append(")");
	this->walk(node->expr);
}

std::string CtTranspiler::transpile(CtNode::RootProgram* root)
{
	this->walk(root);
	return code;
}
