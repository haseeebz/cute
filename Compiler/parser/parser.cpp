#include "node.hpp"
#include "parser.hpp"

#include "CuteToken.hpp"
#include <iostream>
#include <vector>



std::map<char, int> BinaryOpPrecedence = 
{
	{'=', 1},
	{'+', 2},
	{'-', 2},
	{'*', 3},
	{'/', 3},
};


ctSourceNode *Parser::parse(TokenStream *tokens)
{
	this->currStream = tokens;
	ctSourceNode *node = this->parseSource();
	return node;
};


ctSourceNode *Parser::parseSource()
{
	ctSourceNode *src = new ctSourceNode();

	while (this->currStream->peek().type != TokenType::tokenEOF)
	{
		ctNode *node = this->parseStmt(0);
		ctStmtNode *stmt = new ctStmtNode(node);
		src->stmts.push_back(stmt);
	}

	return src;
}


ctNode *Parser::parseStmt(int previous_precedence)
{
	ctNode *lhs;
	ctNode *rhs;

	Token tok;
	char sym;



	tok = this->currStream->next();

	if (tok.type == TokenType::tokenInt)
	{
		lhs = new ctIntNode(this->currStream->viewToken(&tok));
	}
	else if (tok.type == TokenType::tokenSymbol)
	{
		sym = this->currStream->viewSymToken(&tok);

		if (sym == '(')
		{
			lhs = (ctNode*) this->parseStmt(0);
		}

	}
	else if (tok.type == TokenType::tokenWord)
	{
		this->currStream->backtrack();
		lhs = this->parseIdentifier();
	}



	while (tok.type != TokenType::tokenEOF)
	{
		tok = this->currStream->next();

		if (tok.type != TokenType::tokenSymbol)
		{
			std::cout << "Invalid Token\n";
			break;
		}
	
		sym = this->currStream->viewSymToken(&tok);

		if (this->currStream->viewSymToken(&tok) == ')')
		{
			break;	
		}
		else if (this->currStream->viewSymToken(&tok) == ';')
		{
			break;
		}

		int precedence = BinaryOpPrecedence[sym];

		if (precedence > previous_precedence)
		{
			rhs = (ctNode*) this->parseStmt(precedence);
			lhs = new ctBinaryOpNode(sym, lhs, rhs);
			this->currStream->backtrack();
		}
		else 
		{
			break;
		}

	}

	return lhs;
}



ctNode *Parser::parseIdentifier()
{
	Token tok = this->currStream->next();
	ctNode *node = new ctIdentifierNode(this->currStream->viewToken(&tok));
		
	tok = this->currStream->next();

	if (tok.type == TokenType::tokenWord)
	{
		ctNestedIdentifierNode *nested = new ctNestedIdentifierNode();
		nested->val = this->currStream->viewToken(&tok);
		nested->node = (ctIdentifierNode*) this->parseIdentifier();
		return nested;
	}
	else
	{
		this->currStream->backtrack();
		return node;
	}
}