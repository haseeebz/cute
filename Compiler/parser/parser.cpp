#include "node.hpp"
#include "parser.hpp"

#include "../tokenizer/token.hpp"
#include <iostream>
#include <string>
#include <vector>


std::map<BinaryOpType, int> BinaryPrecedence = 
{
	{binaryADD, 1},
	{binarySUB, 2},
	{binaryMUL, 3},
	{binaryDIV, 4}
};


Node* Parser::parse(std::vector<Token> tokens)
{
	this->tokens = tokens;
	root = parseExpr(0);
	root->print(0);
	return root;
};


Node* Parser::parseExpr(int previous_precedence)
{
	Node* lhs;
	Node* rhs;

	Token tok;

	if (currTok >= tokens.size()) {return new Node();}

	tok = tokens[currTok++];

	if (tok.type == TokenType::tokenInt)
	{
		lhs = new Node(std::stoi(tok.str));
	}

	while (currTok < tokens.size())
	{
		tok = tokens[currTok++];

		if (tok.type == TokenType::tokenSymbol)
		{
			BinaryOpType op = getBinaryOp(tok.str);
			int precedence = BinaryPrecedence[op];

			if (precedence > previous_precedence)
			{
				rhs = parseExpr(precedence);
				lhs = new Node(op, lhs, rhs);
				currTok--;
			}
			else 
			{
				break;
			}
		} 
	}

	return lhs;
}


BinaryOpType Parser::getBinaryOp(std::string sym)
{
	switch (sym[0]) 
	{
		case '+': return BinaryOpType::binaryADD;
		case '-': return BinaryOpType::binarySUB;
		case '*': return BinaryOpType::binaryMUL;
		case '/': return BinaryOpType::binaryDIV;
	}
}