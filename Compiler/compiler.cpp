#include "CuteCompiler.hpp"

#include <iostream>
#include <string>

#include "node/node.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto tokens = this->tokenizer.tokenize(filepath);
	std::cout << tokens.toString() << "\n";
	auto *source = this->parser.parse(&tokens);
	
	auto root = new CtNode::RootProgram();
	root->src = source;

	CtNodePrinter printer;

	printer.walk(root);

	this->emitter.emit(root, outfile);

	delete root;
}


