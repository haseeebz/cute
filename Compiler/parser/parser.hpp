#include "../node/node.hpp"

#include "../tokenizer/token.hpp"


#pragma once


static inline std::map<CtLang::Symbol, CtSpec::BinaryOpType> symToBinaryOp =
{
	{CtLang::Symbol::Plus,  CtSpec::BinaryOpType::Add},
	{CtLang::Symbol::Minus, CtSpec::BinaryOpType::Sub},
	{CtLang::Symbol::Star,  CtSpec::BinaryOpType::Mul},
	{CtLang::Symbol::Slash, CtSpec::BinaryOpType::Div},
};


class CtParser
{
	std::string filepath;
	CtNode::Source *source;

	CtTokenizer tokenizer;
	CtTokenStream *tokens;

	void startParsingFile();

	CtNode::Function* parseFunction();

	CtNode::StmtBlock* parseBlock();

	CtNode::Statement* parseStatement();

	CtNode::Declaration* parseDeclaration();
	CtNode::Loop* parseLoop();
	CtNode::While* parseWhile();
	CtNode::For* parseFor();
	CtNode::If* parseIf();

	CtNode::Expression* parseExpression(uint prev_precedence = 0);
	CtNode::Expression* getLeafExpression(CtToken& token);


	public:

	CtNode::Source* parseFile(std::string filepath);

	CtNode::RootProgram* parse(std::string filepath);
};


