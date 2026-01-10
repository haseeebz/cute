#include "../codegen/units.hpp"
#include "../node/node.hpp"
#include "transpiler.hpp"
#include "fstream"
#include "format"
#include <vector>


Codegen::RootUnit* CtTranspiler::handleRoot(CtNode::RootProgram *node)
{
	return this->handleSource(node->src);
}

Codegen::RootUnit* CtTranspiler::handleSource(CtNode::Source *node)
{
	std::vector<Codegen::Unit*> units;

	units.push_back(new Codegen::DirectiveUnit("include", "<stdio.h>"));

	for (auto func: node->functions)
	{
		units.push_back(this->handleFunction(func.second));
	}

	return new Codegen::RootUnit(std::move(units));
}

Codegen::FuncDefUnit* CtTranspiler::handleFunction(CtNode::Function *node)
{
	std::vector<Codegen::DeclUnit*> decl_units;

	for (auto decl: node->parameters)
	{
		decl_units.push_back(this->handleDeclaration(decl));
	}

	return new Codegen::FuncDefUnit(
		new Codegen::FuncDeclUnit(
			"void",
			node->name,
			decl_units
		),
		this->handleStmtBlock(node->block)
	);
}


Codegen::BlockUnit* CtTranspiler::handleStmtBlock(CtNode::StmtBlock *node)
{
	std::vector<Codegen::Unit*> units;

	for (auto stmt: node->stmts)
	{
		std::cout << (int)stmt->nt << std::endl;
		units.push_back(this->walk(stmt));
	}

	return new Codegen::BlockUnit(units);
}


Codegen::DeclUnit* CtTranspiler::handleDeclaration(CtNode::Declaration *node)
{
	if (node->val)
	{
		return new Codegen::DeclUnit(
			"int",
			node->name,
			static_cast<Codegen::ExprUnit*>(this->walk(node->val))
		);
	}
	else
	{
		return new Codegen::DeclUnit(
			"int",
			node->name
		);
	}
}

Codegen::IfUnit* CtTranspiler::handleIf(CtNode::If *node){ return nullptr;};
Codegen::WhileUnit* CtTranspiler::handleLoop(CtNode::Loop *node){return nullptr;};
Codegen::WhileUnit* CtTranspiler::handleWhile(CtNode::While *node){return nullptr;};
Codegen::ForUnit* CtTranspiler::handleFor(CtNode::For *node){return nullptr;};

Codegen::CallUnit* CtTranspiler::handleOut(CtNode::Out *node)
{
	return new Codegen::CallUnit(
		"printf",
		{
			new Codegen::LiteralUnit("\"%d\\n\""),
			static_cast<Codegen::ExprUnit*>(this->walk(node->expr))
		}
	);
}

Codegen::LiteralUnit* CtTranspiler::handleInt(CtNode::Int *node)
{
	return new Codegen::LiteralUnit(node->raw);
}

Codegen::LiteralUnit* CtTranspiler::handleFloat(CtNode::Float *node)
{
	return new Codegen::LiteralUnit(node->raw);
}

Codegen::LiteralUnit* CtTranspiler::handleBool(CtNode::Bool *node)
{
	return new Codegen::LiteralUnit(node->val ? "true" : "false");
}



static inline const char* to_c_op(CtLang::BinaryOpType op) {
    switch(op) {
        case CtLang::BinaryOpType::Add:           return "+";
        case CtLang::BinaryOpType::Sub:           return "-";
        case CtLang::BinaryOpType::Mul:           return "*";
        case CtLang::BinaryOpType::Div:           return "/";
        case CtLang::BinaryOpType::Mod:           return "%";

        case CtLang::BinaryOpType::Equal:         return "==";
        case CtLang::BinaryOpType::NotEqual:      return "!=";
        case CtLang::BinaryOpType::Lesser:        return "<";
        case CtLang::BinaryOpType::LesserEqual:   return "<=";
        case CtLang::BinaryOpType::Greater:       return ">";
        case CtLang::BinaryOpType::GreaterEqual:  return ">=";

        case CtLang::BinaryOpType::BitShiftLeft:  return "<<";
        case CtLang::BinaryOpType::BitShiftRight: return ">>";
        case CtLang::BinaryOpType::BitAnd:        return "&";
        case CtLang::BinaryOpType::BitOr:         return "|";
        case CtLang::BinaryOpType::BitXor:        return "^";

        case CtLang::BinaryOpType::LogicAnd:      return "&&";
        case CtLang::BinaryOpType::LogicOr:       return "||";

        default:                      return "<unknown>";
    }
}

Codegen::BinaryOpUnit* CtTranspiler::handleBinaryOp(CtNode::BinaryOp *node)
{
	return new Codegen::BinaryOpUnit(
		to_c_op(node->op),
		static_cast<Codegen::ExprUnit*>(this->walk(node->left)),
		static_cast<Codegen::ExprUnit*>(this->walk(node->right))
	);
}

Codegen::IdentifierUnit* CtTranspiler::handleIdentifier(CtNode::Identifier *node)
{
	return new Codegen::IdentifierUnit(node->val);
}

Codegen::CallUnit* CtTranspiler::handleFunctionCall(CtNode::FunctionCall *node) {return nullptr;}

Codegen::AssignUnit* CtTranspiler::handleAssignment(CtNode::Assignment *node)
{
	return new Codegen::AssignUnit(
		static_cast<Codegen::ExprUnit*>(this->walk(node->name)),
		static_cast<Codegen::ExprUnit*>(this->walk(node->value))
	);
}

Codegen::Unit* CtTranspiler::handleTypeCast(CtNode::TypeCast *node){return nullptr;}



void CtTranspiler::transpile(CtNode::RootProgram* root, std::string outfile)
{
	Codegen::Unit* root_unit = this->CtTranspiler::handleRoot(root);
	Codegen::Accumulator acc;

	std::ofstream stream("build.c");
	stream << acc.accumulate(root_unit);
	stream.close();

	std::string str = std::format("gcc build.c -o {}", outfile);
	std::system(str.data());
}
