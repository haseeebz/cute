#include "node.hpp"
#include "parser.hpp"

#include "../tokenizer/token.hpp"



std::map<char, int> BinaryOpPrecedence = 
{
	{'=', 1},
	{'+', 2},
	{'-', 2},
	{'*', 3},
	{'/', 3},
};


ctSourceNode* Parser::parse(TokenStream* tokens)
{
	this->currStream = tokens;
	ctSourceNode* node = this->parseSource();
	return node;
};


ctSourceNode* Parser::parseSource()
{
	ctSourceNode* src = new ctSourceNode();

	while (this->currStream->peek().type != TokenType::tokenEOF)
	{
		ctNode* node = this->parseStmt(0);
		ctStmtNode* stmt = new ctStmtNode(node);
		src->stmts.push_back(stmt);
	}

	return src;
}


ctNode* Parser::parseStmt(int previous_precedence)
{
	ctNode* lhs;
	ctNode* rhs;

	Token tok;

	tok = this->currStream->next();

	if (tok.type == TokenType::tokenInt)
	{
		lhs = new ctIntNode(this->currStream->viewToken(&tok));
	}
	else if (tok.type == TokenType::tokenSymbol)
	{
		if (this->currStream->viewSymToken(&tok) == '(')
		{
			lhs = (ctNode*) this->parseStmt(0);
		}

	}
	else if (tok.type == TokenType::tokenWord)
	{
		lhs = new ctIdentifierNode(this->currStream->viewToken(&tok));
	}

	while (tok.type != TokenType::tokenEOF)
	{
		tok = this->currStream->next();

		if (tok.type == TokenType::tokenSymbol)
		{
			if (this->currStream->viewSymToken(&tok) == ')')
			{
				break;	
			}
			else if (this->currStream->viewSymToken(&tok) == ';')
			{
				break;
			}

			char op = this->currStream->viewSymToken(&tok);
			int precedence = BinaryOpPrecedence[op];

			if (precedence > previous_precedence)
			{
				rhs = (ctNode*)  this->parseStmt(precedence);
				lhs = new ctBinaryOpNode(op, lhs, rhs);
				this->currStream->backtrack();
			}
			else 
			{
				break;
			}
		} 

	}

	return lhs;
}


