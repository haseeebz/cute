#include "../spec/lang.hpp"

#include "../spec/node.hpp"

#include "../tokenizer/token.hpp"
#include "../spec/error.hpp"

#include "parser.hpp"
#include "format"




void CtParser::startParsingFile()
{
	auto *func = this->parseFunction();
	source->functions[func->name] = func;
}


CtNode::Function* CtParser::parseFunction()
{
	auto* func = new CtNode::Function();
	func->name = "main";

	func->block = this->parseBlock();

	return func;
}


CtNode::StmtBlock* CtParser::parseBlock()
{
	auto* block = new CtNode::StmtBlock();

	while (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;};

	this->tokens->expectSymbolSpecific(CtLang::Symbol::LeftBracket);

	while (true)
	{
		while (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;};

		if (this->tokens->getSymbolSpecific(CtLang::Symbol::RightBracket)) {break;}

		CtNode::Statement* stmt = this->parseStatement();
		if (stmt == nullptr) {break;}
		block->stmts.push_back(stmt);
	}

	return block;
}


CtNode::Statement* CtParser::parseStatement()
{
	CtNode::Statement* stmt = nullptr;
	CtToken token;

	while (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;};

	if (this->tokens->getType(CtTokenType::EndOfFile, nullptr)) {return nullptr;}

	if (this->tokens->getType(CtTokenType::Keyword, &token))
	{
		switch (token.val.keyword)
		{
			case CtLang::KeyWord::Let:     stmt = this->parseDeclaration(); break;
			case CtLang::KeyWord::Out:     stmt = new CtNode::Out(this->parseExpression(0)); break;
			case CtLang::KeyWord::Loop:    stmt = this->parseLoop(); break;
			case CtLang::KeyWord::While:   stmt = this->parseWhile(); break;
			case CtLang::KeyWord::For:     stmt = this->parseFor(); break;
			case CtLang::KeyWord::If:      stmt = this->parseIf(); break;
			case CtLang::KeyWord::Escape:  stmt = this->parseEscape(); break;
			default: this->tokens->raiseError(
				&token, 
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

	this->tokens->expectWord(&str);
	dec->name = str;

	this->tokens->expectSymbolSpecific(CtLang::Symbol::Colon);

	this->tokens->expectWord(&str);
	dec->type_id = str;

	if (this->tokens->getSymbolSpecific(CtLang::Symbol::Equal))
	{
		dec->val = this->parseExpression(0);
	}

	this->tokens->expectType(CtTokenType::EndOfLine, nullptr);

	return dec;
};



CtNode::Loop* CtParser::parseLoop()
{
	auto loop = new CtNode::Loop();

	while (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;};

	loop->block = this->parseBlock();

	return loop;
}


CtNode::While* CtParser::parseWhile()
{
	auto* loop = new CtNode::While();

	this->tokens->expectSymbolSpecific(CtLang::Symbol::LeftParan);

	loop->condition = this->parseExpression(0);

	this->tokens->getSymbolSpecific(CtLang::Symbol::RightParan); // Expression parser will catch that right paran. Fix needed here.

	loop->block = this->parseBlock();

	return loop;
}


CtNode::For* CtParser::parseFor()
{
	auto* loop = new CtNode::For();

	this->tokens->expectSymbolSpecific(CtLang::Symbol::LeftParan);

	loop->init = this->parseStatement();
	loop->condition = this->parseExpression();
	this->tokens->expectType(CtTokenType::EndOfLine, nullptr); // duct tape
	loop->step = this->parseExpression();
	this->tokens->expectSymbolSpecific(CtLang::Symbol::RightParan);

	this->tokens->getSymbolSpecific(CtLang::Symbol::RightParan); 

	loop->block = this->parseBlock();

	return loop;
}


CtNode::If* CtParser::parseIf()
{
	auto if_node = new CtNode::If();

	this->tokens->expectSymbolSpecific(CtLang::Symbol::LeftParan);

	if_node->condition = this->parseExpression(0);

	this->tokens->getSymbolSpecific(CtLang::Symbol::RightParan); // Expression parser will catch that right paran. Fix needed here.

	if_node->then_block = this->parseBlock();

	while (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;};

	if (this->tokens->getKeywordSpecific(CtLang::KeyWord::Else))
	{
		if (this->tokens->getKeywordSpecific(CtLang::KeyWord::If))
		{
			if_node->else_stmt = this->parseIf();
		}
		else  
		{
			if_node->else_stmt = this->parseBlock();
		}
	}

	return if_node;
}


CtNode::Escape* CtParser::parseEscape()
{
	auto* escape_node = new CtNode::Escape();

	uint depth = 0;

	this->tokens->expectSymbolSpecific(CtLang::Symbol::LeftBracket);
	depth++;

	while (true)
	{
		if (this->tokens->getSymbolSpecific(CtLang::Symbol::LeftBracket))
		{
			depth++;
			escape_node->code.append("[");
			continue;
		}
		else if (this->tokens->getSymbolSpecific(CtLang::Symbol::RightBracket))
		{
			depth--;
			if (depth == 0) {break;}
			escape_node->code.append("]");
			continue;
		}

		if (this->tokens->getType(CtTokenType::EndOfLine, nullptr)) {continue;}

		CtToken token = this->tokens->next();
		escape_node->code.append(" ");
		escape_node->code.append(this->tokens->viewToken(&token));
		
	};

	return escape_node;
}


CtNode::Expression* CtParser::parseExpression(uint prev_precedence, uint depth)
{
	CtNode::Expression *lhs;

	CtToken tok;
	std::string str;

	if (this->tokens->getTypes({CtTokenType::Int, CtTokenType::Float, CtTokenType::Word}, &tok))
	{
		lhs = this->getLeafExpression(tok);
	}

	else if (this->tokens->getKeywordSpecific(CtLang::KeyWord::True))
	{
		lhs = new CtNode::Bool(true);
	}

	else if (this->tokens->getKeywordSpecific(CtLang::KeyWord::False))
	{
		lhs = new CtNode::Bool(false);
	}

	else if (this->tokens->getType(CtTokenType::Symbol, &tok))
	{

		if (tok.val.sym == CtLang::Symbol::LeftParan)
		{
			lhs = this->parseExpression(0, depth + 1);
		}
		else if (tok.val.sym == CtLang::Symbol::Minus)
		{
			lhs = this->parseExpression(CtLang::binaryOpPrecedence.size());
			lhs = new CtNode::BinaryOp(CtLang::BinaryOpType::Sub, new CtNode::Int("0"), lhs); // works, meh
		}
		else if (tok.val.sym == CtLang::Symbol::LeftBraces)
		{
			this->tokens->expectWord(&str);
			this->tokens->expectSymbolSpecific(CtLang::Symbol::RightBraces);
			auto cast = new CtNode::TypeCast();
			cast->to_type = str;
			cast->expr = this->parseExpression(CtLang::binaryOpPrecedence.size()); // grabs the next literal
			lhs = cast;
		}
		else
		{
			this->tokens->backtrack();
			goto error;
		}
		
	}

	else 
	{
		error:
		tok = this->tokens->peek();
		this->tokens->raiseError(
			&tok,
			std::format("Invalid syntax. Did not expect '{}'", this->tokens->viewToken(&tok))
		);		
	}

	

	while (true)
	{
		CtLang::Symbol sym;

		if (this->tokens->getTypes({CtTokenType::EndOfLine, CtTokenType::EndOfFile}, nullptr))
		{
			if (depth != 0)
			{
				this->tokens->backtrack();
				auto tok = this->tokens->next();
				this->tokens->raiseError(
					&tok,
					std::format("Unclosed expression.", this->tokens->viewToken(&tok))
				);	
			}
			this->tokens->backtrack(); // so EOL propagates
			return lhs;
		}

		if (this->tokens->getKeywordSpecific(CtLang::KeyWord::And))
		{
			sym = CtLang::Symbol::DoubleAnd;
		}
		else if (this->tokens->getKeywordSpecific(CtLang::KeyWord::Or))
		{
			sym = CtLang::Symbol::DoubleBar;
		}
		else  
		{
			this->tokens->expectSymbol(&sym);
		}
		
		if (sym == CtLang::Symbol::RightParan)
		{
			if (depth == 0) {this->tokens->backtrack();}
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

		binary->op = CtLang::symToBinaryOp.at(sym);
		uint prec = CtLang::binaryOpPrecedence.at(binary->op);

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
	
	return lhs;
}


CtNode::Expression* CtParser::getLeafExpression(CtToken& token)
{
	CtNode::Expression* leaf = nullptr;

	if (token.type == CtTokenType::Int)
	{
		leaf = new CtNode::Int(this->tokens->viewToken(&token));
	}
	else if (token.type == CtTokenType::Float)
	{
		leaf = new CtNode::Float(this->tokens->viewToken(&token));
	}
	else if (token.type == CtTokenType::Word)
	{
		leaf = new CtNode::Identifier(this->tokens->viewToken(&token));
	}
	else 
	{
		CtError::raise(
			CtError::ErrorType::CompilerError,
			std::format("A leaf node can only be of type: Int, Float or Word. Got: {}", (int) token.type)
		);
	}

	return leaf;
};


CtNode::Source* CtParser::parseFile(std::string filepath)
{
	auto tokens = tokenizer.tokenize(filepath);
	this->tokens = &tokens;
	std::cout << tokens.toString() << std::endl;
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

