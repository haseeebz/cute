#include "CuteCompiler.hpp"

#include <string>

#include "node/node.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto* root = this->parser.parse(filepath);

	root = this->analyzer.analyze(root);
	
	this->emitter.emit(root, outfile);
	
	delete root;
}


