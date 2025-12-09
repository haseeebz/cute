#include "CuteCompiler.hpp"

#include <iostream>
#include <string>

#include "node/node.hpp"


using namespace CtNode;

void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto tokens = this->tokenizer.tokenize(filepath);
	std::cout << tokens.toString() << "\n";
	auto *source = this->parser.parse(&tokens);
	
	CtNodePrinter printer;

	printer.walk(source);
}


