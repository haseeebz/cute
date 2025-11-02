#include <map>
#include <vector>
#include "node.hpp"

#include "../tokenizer/token.hpp"

#pragma once 

extern std::map<BinaryOpType, int> BinaryPrecedence;

class Parser
{
	Node* root;
	std::vector<Token> tokens;
	uint currTok = 0;
	
	Node* parseExpr(int previous_precedence);
	BinaryOpType getBinaryOp(std::string sym);

	public:

	Node* parse(std::vector<Token> tokens);
};