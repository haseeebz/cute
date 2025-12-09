#include "../node/node.hpp"

#include "../tokenizer/token.hpp"
#include <iostream>

#include "parser.hpp"





void CtParser::start()
{
	auto *func = new CtNode::Function();
	func->name = new CtNode::Identifier("main");


	while (true)
	{
		auto *stmt = this->parseStatement();
		if (!stmt) {break;}
		func->statements.push_back(stmt);
	}

	source->functions[func->name->val] = func;
}

//CtNode::Function* CtParser::parseFunction();

CtNode::Statement* CtParser::parseStatement()
{
	auto *expr = this->parseExpression();
	if (!expr) {return nullptr;}
	auto *stmt = new CtNode::ExprStatment(expr);
	return stmt;
}

CtNode::Expression* CtParser::parseExpression(uint prev_precedence)
{
	static std::map<char, uint> ops_prec = {
		{'+', 1},
		{'-', 1},
		{'*', 2},
		{'/', 2}
	};

	static std::map<char, CtNode::BinaryOp::Type> ops_node = {
		{'+', CtNode::BinaryOp::Type::Add},
		{'-', CtNode::BinaryOp::Type::Sub},
		{'*', CtNode::BinaryOp::Type::Mul},
		{'/', CtNode::BinaryOp::Type::Div}
	};


	CtToken tok;

	CtNode::Expression *lhs;
	CtNode::Expression *rhs;

	tok = this->tokens->next();

	if (tok.type == CtTokenType::Int)
	{
		lhs = new CtNode::Int(this->tokens->viewToken(&tok));
	}
	else if (tok.type == CtTokenType::Float)
	{
		lhs = new CtNode::Float(this->tokens->viewToken(&tok));
	}
	else if (tok.type == CtTokenType::EndOfFile)
	{
		return nullptr;
	}
	else 
	{
		std::cout << "Invalid Token : " << this->tokens->viewToken(&tok) << "\n";
		return nullptr;
	}

	
	while (true)
	{
		tok = this->tokens->next();

		if (tok.type == CtTokenType::Symbol)
		{
			char sym = this->tokens->viewSymToken(&tok);

			if (sym == ';')
			{
				break;
			}

			auto *binary = new CtNode::BinaryOp();

			uint prec = ops_prec[sym];

			if (prec < prev_precedence)
			{
				this->tokens->backtrack();
				break;
			}

			binary->op = ops_node[sym];
			binary->left = lhs;
			binary->right = this->parseExpression(prec);

			lhs = binary;
			
			continue;
		}

		this->tokens->backtrack();
		break;
	}
	
	return lhs;
}



CtNode::Source* CtParser::parse(CtTokenStream *tokens)
{
	this->tokens = tokens;
	this->source = new CtNode::Source();

	this->start();
	
	return this->source;
}