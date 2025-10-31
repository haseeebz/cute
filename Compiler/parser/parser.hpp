#include <vector>
#include "node.hpp"

#include "../tokenizer/token.hpp"


#pragma once 

class Parser
{
	Node root;
	

	public:

	Node* parse(std::vector<Token> tokens);
};