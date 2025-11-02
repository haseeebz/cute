#include <vector>
#include "node.hpp"

#include "../tokenizer/token.hpp"


#pragma once 

class Parser
{
	Node root;
	
	Node* parseExpr();

	public:

	Node* parse(std::vector<Token> tokens);
};