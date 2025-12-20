#include "CuteCompiler.hpp"

#include <iostream>
#include <string>

#include "node/node.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto* root = this->parser.parse(filepath);

	root = this->analyzer.analyze(root);
	
	auto* program = this->emitter.emit(root);

	this->writer.write(program, outfile);

	std::cout << "Program image written to: " << outfile << "\n";
	
	delete root;
	delete program;
}


