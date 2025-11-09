#include "node.hpp"
#include "parser.hpp"

#include "../tokenizer/token.hpp"



std::map<char, int> BinaryOpPrecedence = 
{
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
};


ctNode* Parser::parse(TokenStream* tokens)
{
	this->currStream = tokens;
	return parseExpr(0);
};


ctNode* Parser::parseExpr(int previous_precedence)
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
			lhs = parseExpr(0);
		}

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

			char op = this->currStream->viewSymToken(&tok);
			int precedence = BinaryOpPrecedence[op];

			if (precedence > previous_precedence)
			{
				rhs = parseExpr(precedence);
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


