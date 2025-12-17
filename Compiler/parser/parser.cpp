#include "../node/node.hpp"

#include "../tokenizer/token.hpp"
#include "../spec/lang.hpp"
#include <exception>
#include <iostream>

#include "parser.hpp"



void CtParser::startParsingFile()
{
	auto *func = this->parseFunction();
	source->functions[func->name] = func;
}


CtNode::Function* CtParser::parseFunction()
{
	auto* func = new CtNode::Function();
	func->name = "main";

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

	if (this->tokens->expectType(CtTokenType::EndOfFile, nullptr)) {return nullptr;}

	if (this->tokens->expectType(CtTokenType::Keyword, &token))
	{
		switch (token.val.keyword)
		{
			case CtLang::KeyWord::Let: stmt = this->parseDeclaration(); break;
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
		dec->name = str;
	}

	this->tokens->expectSymbol(CtLang::Symbol::Colon);

	if (this->tokens->getWord(&str))
	{
		dec->type = str;
	}

	this->tokens->expectType(CtTokenType::EndOfLine, nullptr);
	return dec;
};




CtNode::Expression* CtParser::parseExpression(uint prev_precedence)
{
	CtToken tok;

	CtNode::Expression *lhs;

	std::string str;
	CtLang::Symbol sym;

	if (this->tokens->getInt(&str))
	{
		lhs = new CtNode::Int(str);
	}
	else if (this->tokens->getFloat(&str))
	{
		lhs = new CtNode::Float(str);
	}
	else if (this->tokens->getWord(&str))
	{
		lhs = new CtNode::Identifier(str);
	}
	else if (this->tokens->expectSymbol(CtLang::Symbol::LeftParan))
	{
		lhs = this->parseExpression(0);
	}
	else if (this->tokens->expectSymbol(CtLang::Symbol::LeftBraces))
	{
		this->tokens->getWord(&str);
		this->tokens->expectSymbol(CtLang::Symbol::RightBraces);
		auto cast = new CtNode::TypeCast();
		cast->to_type = str;
		cast->expr = this->parseExpression(CtLang::binaryOpMap.size());
		// What this will do is grab the next literal.

		lhs = cast;
	}
	else 
	{
		tok = this->tokens->peek();
		std::cout << "Invalid Token Sequence! Token Type: " << int(tok.type) << "\n";
		throw std::exception();
		std::exit(1);
	}

	
	while (true)
	{
		
		CtLang::Symbol sym;

		if (this->tokens->expectType(CtTokenType::EndOfLine, nullptr))
		{
			return lhs;
		}

		if (this->tokens->expectType(CtTokenType::EndOfFile, nullptr))
		{
			return nullptr;
		}

		if (this->tokens->getSymbol(&sym))
		{
			if (sym == CtLang::Symbol::RightParan)
			{
				return lhs;
			}

			if (sym == CtLang::Symbol::Equal)
			{
				auto* assign = new CtNode::Assignment();
				assign->name = static_cast<CtNode::Identifier*>(lhs); //assuming this is right for now
				assign->value = this->parseExpression();
				return assign;
			}

			auto *binary = new CtNode::BinaryOp();

			uint prec = CtLang::binaryOpMap.at(sym);

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
	std::cout << this->tokens->toString() << std::endl;
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

