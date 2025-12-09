#include "../node/node.hpp"

#include "../tokenizer/token.hpp"

#include "parser.hpp"




CtNode::Source *source;

void CtParser::start()
{
	CtToken tok;

	tok = tokens->next();

}
/*
CtNode::Function* CtParser::parseFunction();

CtNode::Statement* CtParser::parseStatement();
CtNode::Expression* CtParser::parseExpression();
*/


CtNode::Source* CtParser::parse(CtTokenStream *tokens)
{
	this->tokens = tokens;
	this->source = new CtNode::Source();

	this->start();
}