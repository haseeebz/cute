#include "node.hpp"
#include "parser.hpp"

#include "../tokenizer/token.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


std::map<BinaryOpType, int> BinaryPrecedence = 
{
	{binaryASSIGN, 1},
	{binaryADD, 2},
	{binarySUB, 2},
	{binaryMUL, 3},
	{binaryDIV, 3}
};


Node* Parser::parse(std::vector<Token> tokens)
{
	this->tokens = tokens;
	root = parseExpr(0);
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
	else if (tok.type == TokenType::tokenWord)
	{
		lhs = new Node(tok.str);
	}
	else if (tok.type == TokenType::tokenSymbol)
	{
		if (tok.str[0] == '(')
		{
			lhs = parseExpr(0);
		}

	}

	while (currTok < tokens.size())
	{
		tok = tokens[currTok++];

		if (tok.type == TokenType::tokenSymbol)
		{
			if (tok.str[0] == ')' or tok.str[0] == ';')
			{
				break;	
			}

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
		case '=': return BinaryOpType::binaryASSIGN;
		case '+': return BinaryOpType::binaryADD;
		case '-': return BinaryOpType::binarySUB;
		case '*': return BinaryOpType::binaryMUL;
		case '/': return BinaryOpType::binaryDIV;
	}

	printf("Invalid Symbol\n");
	exit(EXIT_FAILURE);
}