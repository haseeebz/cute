#include "../node/node.hpp"

#include "../tokenizer/token.hpp"
#include "CuteSpec.hpp"
#include <exception>
#include <iostream>

#include "parser.hpp"





void CtParser::start()
{
	auto *func = new CtNode::Function();
	func->name = new CtNode::Identifier("main");

	while (this->tokens->peek().type != CtTokenType::EndOfFile)
	{
		CtNode::Statement* stmt = this->parseStatement();
		if (stmt == nullptr) {break;}
		func->statements.push_back(stmt);
	}

	source->functions[func->name->val] = func;
}

//CtNode::Function* CtParser::parseFunction();

CtNode::Statement* CtParser::parseStatement()
{
	CtNode::Statement* stmt;

	CtToken token;

	if (this->tokens->expectType(CtTokenType::Keyword, &token))
	{
		switch (token.val.keyword)
		{
			case CtSpec::KeyWord::Let: stmt = this->parseDeclaration(); break;
		}

		return stmt;
	}

	if (this->tokens->peek().type == CtTokenType::Word)
	{
		std::string id;
		this->tokens->getWord(&id);

		CtSpec::Symbol assign;

		if (this->tokens->getSymbol(&assign))
		{
			if (assign != CtSpec::Symbol::Equal)
			{
				this->tokens->backtrack();
			}

			auto* assignment = new CtNode::Assignment();
			assignment->name = new CtNode::Identifier(id);
			assignment->value = this->parseExpression();
			return assignment;
		}

		this->tokens->backtrack();
	}

	auto *expr = this->parseExpression();
	if (!expr) {return nullptr;}

	stmt = new CtNode::ExprStatment(expr);
	return stmt;
}


CtNode::Declaration* CtParser::parseDeclaration()
{
	CtNode::Declaration* dec = new CtNode::Declaration();

	std::string str;

	if (this->tokens->getWord(&str))
	{
		dec->name = new CtNode::Identifier(str);
	}

	this->tokens->obtainSymbol(CtSpec::Symbol::Colon);

	if (this->tokens->getWord(&str))
	{
		dec->type = new CtNode::Identifier(str);
	}

	CtToken token;

	this->tokens->expectType(CtTokenType::EndOfLine, &token);

	return dec;
};


CtNode::Expression* CtParser::parseExpression(uint prev_precedence)
{
	std::cout  << " Index: " << this->tokens->currentIndex() << "\n";

	CtToken tok;
	CtNodePrinter printer;

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
	else if (tok.type == CtTokenType::Word)
	{
		lhs = new CtNode::Identifier(this->tokens->viewToken(&tok));
	}
	else 
	{
		std::cout << "Invalid Token Sequence! Token Type:" << int(tok.type) << "\n";
		throw std::exception();
		std::exit(2);
	}

	
	while (true)
	{
		CtSpec::Symbol sym;

		if (this->tokens->expectType(CtTokenType::EndOfLine, &tok))
		{
			return lhs;
		}

		if (this->tokens->getSymbol(&sym))
		{
			if (sym == CtSpec::Symbol::Colon)
			{	
				return lhs;
			}

			auto *binary = new CtNode::BinaryOp();

			uint prec = CtSpec::binaryOpMap[sym];

			if (prec < prev_precedence)
			{
				this->tokens->backtrack();
				return lhs;
			}

			binary->op = sym;
			binary->left = lhs;
			binary->right = this->parseExpression(prec);

			lhs = binary;
			
			continue;
		}

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

