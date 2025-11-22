#include <map>
#include "node.hpp"

#include "CuteToken.hpp"

#pragma once 

extern std::map<char, int> BinaryOpPrecedence;

class Parser
{
	TokenStream* currStream;
	
	ctSourceNode* parseSource();

	ctNode* parseStmt(int previous_precedence);

	ctNode* parseIdentifier();

	public:

	ctSourceNode* parse(TokenStream* tokens);
};