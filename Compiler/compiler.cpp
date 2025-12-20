#include "CuteCompiler.hpp"

#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "node/node.hpp"
#include "spec/error.hpp"



void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	if (!std::filesystem::exists(filepath))
	{
		CtError::raise(
			CtError::ErrorType::CompilerError, 
			std::format("File does not exist: {}", filepath)
		);
	}
	
	auto* root = this->parser.parse(filepath);

	root = this->analyzer.analyze(root);
	
	auto* program = this->emitter.emit(root);

	this->writer.write(program, outfile);

	std::cout << "Program image written to: " << outfile << "\n";

	delete root;
	delete program;
}


