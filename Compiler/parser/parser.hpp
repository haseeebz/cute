#include "../node/node.hpp"

#include "../tokenizer/token.hpp"

#pragma once

class CtParser
{
	CtTokenStream *tokens;

	CtNode::Source *source;

	void start();

	CtNode::Function* parseFunction();

	CtNode::Statement* parseStatement();
	CtNode::Expression* parseExpression(uint prev_precedence = 0);

	public:

	CtNode::Source* parse(CtTokenStream *tokens);
};