#include "../spec/node.hpp"

#include "../tokenizer/token.hpp"


#pragma once

using Sym = CtLang::Symbol;
using Bin = CtLang::BinaryOpType;
using Un  = CtLang::UnaryOpType;


class CtParser
{
	std::string filepath;
	CtNode::Source *source;

	CtTokenizer tokenizer;
	CtTokenStream *tokens;

	void startParsingFile();

	CtNode::Container* 
	parseContainer();

	CtNode::Function* 
	parseFunction();

	CtNode::Declaration* 
	parseParameter();

	CtNode::StmtBlock* 
	parseBlock();

	CtNode::Statement* 
	parseStatement();

	CtNode::Declaration* 
	parseDeclaration();

	CtNode::Loop* 
	parseLoop();

	CtNode::While* 
	parseWhile();

	CtNode::For* 
	parseFor();

	CtNode::If* 
	parseIf();

	CtNode::Escape* 
	parseEscape();

	CtNode::Expression* 
	parseExpression(uint prev_precedence = 0, uint depth = 0, CtLang::Symbol delimiter = CtLang::Symbol::SemiColon);

	CtNode::Expression* 
	getLeafExpression(CtToken& token);


	public:

	CtNode::Source*
	parseFile(std::string filepath);

	CtNode::RootProgram* 
	parse(std::string filepath);
};


