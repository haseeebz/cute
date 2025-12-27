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


void CuteCompiler::invokeComponent(std::string filepath, std::string comp)
{
	if (!std::filesystem::exists(filepath))
	{
		CtError::raise(
			CtError::ErrorType::CompilerError, 
			std::format("File does not exist: {}", filepath)
		);
	}

	CtNodePrinter printer;

	if (comp == "tokenize")
	{
		auto tokens = this->tokenizer.tokenize(filepath);
		std::cout << "Tokenized File : " << filepath << std::endl;
		std::cout << tokens.toString();
	}
	else if (comp == "parse")
	{
		auto* root = this->parser.parse(filepath);
		printer.print(root);
	}
	else if (comp == "analyze")
	{
		auto* root = this->parser.parse(filepath);
		this->analyzer.analyze(root);
		printer.print(root);
	}
	else if (comp == "emit")
	{
		std::cout << "Emit API not implemented\n";
		return;
		auto* root = this->parser.parse(filepath);
		printer.print(root);
	}
	else
	{
		CtError::raise(
			CtError::ErrorType::CompilerError, 
			std::format("Unknown compiler function: {}", comp)
		);
	}
}