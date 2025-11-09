#include <map>
#include "node.hpp"

#include "../tokenizer/token.hpp"

#pragma once 

extern std::map<char, int> BinaryOpPrecedence;

class Parser
{
	TokenStream* currStream;
	
	ctNode* parseExpr(int previous_precedence);

	public:

	ctNode* parse(TokenStream* tokens);
};