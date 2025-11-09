#include "CuteCompiler.hpp"
#include "parser/node.hpp"

#include <string>

#include "internals.hpp"
#include "tokenizer/token.hpp"


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	TokenStream stream = tokenizer.tokenize(filepath);

	ctDebug("Tokenized Source:\n");
	ctDebug(stream.toString());

	
	ctNode* root = parser.parse(&stream);
	
	ctDebug("Parsed Code:\n")
	PrintVisitor printer;
	root->accept(&printer);

	//ctDebug(root->str());

	/*
	writer.setOutFile(outfile);
	writer.write(root);

	delete root;*/
}