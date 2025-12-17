#include "CuteCompiler.hpp"

#include <string>

#include "node/node.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto* root = this->parser.parse(filepath);
	CtNodePrinter p;
	p.print(root);

	root = this->analyzer.analyze(root);
	
	this->emitter.emit(root, outfile);

	delete root;
}


