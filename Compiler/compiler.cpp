#include "CuteCompiler.hpp"
#include "CuteByte.h"
//#include "parser/node.hpp"

#include <iostream>
#include <string>

#include "internals.hpp"
#include "tokenizer/token.hpp"


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	TokenStream stream = tokenizer.tokenize(filepath);

	ctDebug("Tokenized Source:\n");
	ctDebug(stream.toString());
	return;
	/*
	Node* root = parser.parse(tokenizer.t);
	
	ctDebug("Parsed Code:\n")
	ctDebug(root->str());

	writer.setOutFile(outfile);
	writer.write(root);

	delete root;*/
}