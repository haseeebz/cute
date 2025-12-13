#include "CuteCompiler.hpp"

#include <iostream>
#include <string>

#include "node/node.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto tokens = this->tokenizer.tokenize(filepath);
	
	std::cout << tokens.toString() << "\n";

	auto* root = this->parser.parse(outfile);
	
	CtNodePrinter printer;

	printer.walk(root);

	this->emitter.emit(root, outfile);

	delete root;
}


