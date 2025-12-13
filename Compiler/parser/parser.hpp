#include "../node/node.hpp"

#include "../tokenizer/token.hpp"

#pragma once

class CtParser
{
	std::string filepath;
	CtNode::Source *source;

	CtTokenizer tokenizer;
	CtTokenStream *tokens;

	void startParsingFile();

	CtNode::Function* parseFunction();

	CtNode::Statement* parseStatement();

	CtNode::Expression* parseExpression(uint prev_precedence = 0);

	CtNode::Declaration* parseDeclaration();
	CtNode::Assignment* parseAssignment();

	public:

	CtNode::Source* parseFile(std::string filepath);

	CtNode::RootProgram* parse(std::string filepath);
};


