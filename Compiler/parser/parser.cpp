#include "../node/node.hpp"

#include "../tokenizer/token.hpp"
#include "../spec/spec.hpp"
#include <exception>
#include <iostream>

#include "parser.hpp"



void CtParser::startParsingFile()
{
	auto *func = this->parseFunction();
	source->functions[func->name->val] = func;
}


CtNode::Function* CtParser::parseFunction()
{
	auto* func = new CtNode::Function();
	func->name = new CtNode::Identifier("main");

	while (this->tokens->peek().type != CtTokenType::EndOfFile)
	{
		CtNode::Statement* stmt = this->parseStatement();
		if (stmt == nullptr) {break;}
		func->statements.push_back(stmt);
	}

	return func;
}


CtNode::Statement* CtParser::parseStatement()
{
	CtNode::Statement* stmt = nullptr;

	CtToken token;

	while (this->tokens->expectType(CtTokenType::EndOfLine, nullptr)) {continue;};

	if (this->tokens->expectType(CtTokenType::Keyword, &token))
	{
		switch (token.val.keyword)
		{
			case CtSpec::KeyWord::Let: stmt = this->parseDeclaration(); break;
			default: std::cout << "Unimplemented keyword!\n";
		}

		return stmt;
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

	this->tokens->expectSymbol(CtSpec::Symbol::Colon);

	if (this->tokens->getWord(&str))
	{
		dec->type = new CtNode::Identifier(str);
	}

	this->tokens->expectType(CtTokenType::EndOfLine, nullptr);
	return dec;
};




CtNode::Expression* CtParser::parseExpression(uint prev_precedence)
{
	CtToken tok;

	CtNode::Expression *lhs;

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
		std::cout << "Invalid Token Sequence! Token Type: " << int(tok.type) <<  ":" << int(tok.val.sym) << "\n";
		throw std::exception();
		std::exit(1);
	}

	
	while (true)
	{
		
		CtSpec::Symbol sym;

		if (this->tokens->expectType(CtTokenType::EndOfLine, NULL))
		{
			return lhs;
		}

		if (this->tokens->getSymbol(&sym))
		{
			if (sym == CtSpec::Symbol::Equal)
			{
				auto* assign = new CtNode::Assignment();
				assign->name = static_cast<CtNode::Identifier*>(lhs); //assuming this is right for now
				assign->value = this->parseExpression();
				return assign;
			}

			auto *binary = new CtNode::BinaryOp();

			uint prec = CtSpec::binaryOpMap.at(sym);

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


CtNode::Source* CtParser::parseFile(std::string filepath)
{
	auto tokens = tokenizer.tokenize(filepath);
	this->tokens = &tokens;
	this->source = new CtNode::Source();
	this->startParsingFile();
	return this->source;
}


CtNode::RootProgram* CtParser::parse(std::string filepath)
{
	auto* root = new CtNode::RootProgram();
	root->src = this->parseFile(filepath);

	return root;
}

