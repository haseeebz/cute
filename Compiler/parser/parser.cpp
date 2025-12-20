#include "../tokenizer/lang.hpp"

#include "../node/node.hpp"

#include "../tokenizer/token.hpp"
#include "../spec/error.hpp"

#include "../spec/spec.hpp"

#include <iostream>

#include "parser.hpp"
#include "format"


static inline std::map<CtLang::Symbol, CtSpec::BinaryOpType> symToBinaryOp =
{
	{CtLang::Symbol::Plus,  CtSpec::BinaryOpType::Add},
	{CtLang::Symbol::Minus, CtSpec::BinaryOpType::Sub},
	{CtLang::Symbol::Star,  CtSpec::BinaryOpType::Mul},
	{CtLang::Symbol::Slash, CtSpec::BinaryOpType::Div},
};


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
			case CtLang::KeyWord::Let:  stmt = this->parseDeclaration(); break;
			case CtLang::KeyWord::Out:  stmt = new CtNode::Out(this->parseExpression(0)); break;
			case CtLang::KeyWord::Loop: stmt = this->parseLoop(); break;
			default: CtError::raise(
				CtError::ErrorType::SyntaxError, 
				std::format("Unimplemented Keyword: {}", this->tokens->viewToken(&token))
			);
		}

		return stmt;
	}

	auto *expr = this->parseExpression();
	if (!expr) {return nullptr;}

	stmt = new CtNode::ExprStatment(expr);
	this->tokens->expectType(CtTokenType::EndOfLine, nullptr);
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
		dec->type_id = str;
	}

	this->tokens->expectType(CtTokenType::EndOfLine, nullptr);
	return dec;
};



CtNode::Loop* CtParser::parseLoop()
{
	auto loop = new CtNode::Loop();

	while (this->tokens->expectType(CtTokenType::EndOfLine, nullptr)) {continue;};

	if (!this->tokens->expectSymbol(CtLang::Symbol::LeftBracket))
	{
		CtError::raise(
			CtError::ErrorType::SyntaxError, 
			"Expected '['"
		);
	}

	while (true)
	{
		if (this->tokens->expectSymbol(CtLang::Symbol::RightBracket)) {break;}

		CtNode::Statement* stmt = this->parseStatement();
		if (stmt == nullptr) {break;}
		loop->block.push_back(stmt);
	}

	return loop;
}



CtNode::Expression* CtParser::parseExpression(uint prev_precedence)
{
	CtNode::Expression *lhs;

	CtToken tok;
	std::string str;

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
	else if (this->tokens->expectSymbol(CtLang::Symbol::Minus))
	{
		lhs = this->parseExpression(CtSpec::binaryOpPrecedence.size());
		lhs = new CtNode::BinaryOp(CtSpec::BinaryOpType::Sub, new CtNode::Int("0"), lhs); // works, meh
	}
	else if (this->tokens->expectSymbol(CtLang::Symbol::LeftBraces))
	{
		this->tokens->getWord(&str);
		this->tokens->expectSymbol(CtLang::Symbol::RightBraces);
		auto cast = new CtNode::TypeCast();
		cast->to_type = str;
		cast->expr = this->parseExpression(CtSpec::binaryOpPrecedence.size());
		// What this will do is grab the next literal.

		lhs = cast;
	}
	else 
	{
		tok = this->tokens->peek();
		CtError::raise(
			CtError::ErrorType::SyntaxError,
			std::format("Invalid syntax. Did not expect '{}'", this->tokens->viewToken(&tok))
		);
	}

	
	while (true)
	{
		CtLang::Symbol sym;

		if (this->tokens->expectType(CtTokenType::EndOfLine, nullptr))
		{
			this->tokens->backtrack(); // so EOL propagates
			return lhs;
		}

		if (this->tokens->expectType(CtTokenType::EndOfFile, nullptr))
		{
			this->tokens->backtrack();
			return lhs;
		}

		if (this->tokens->expectSymbol(CtLang::Symbol::RightBracket))
		{
			this->tokens->backtrack();
			return lhs;
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

			auto* binary = new CtNode::BinaryOp();

			binary->op = symToBinaryOp.at(sym);
			uint prec = CtSpec::binaryOpPrecedence[binary->op];

			if (prec < prev_precedence)
			{
				this->tokens->backtrack();
				return lhs;
			}
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
	std::cout << this->tokens->toString() << "\n";
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

