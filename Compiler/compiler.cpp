#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "parser/node.hpp"

#include <iostream>
#include <string>

#include "internals.hpp"


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	tokenizer.tokenize(filepath);

	ctDebug("Tokenized Source:\n");
	ctDebug(tokenizer.toString());

	Node* root = parser.parse(tokenizer.getTokens());
	
	ctDebug("Parsed Code:\n")
	ctDebug(root->str());

	writer.setOutFile(outfile);
	writer.write(root);

	delete root;
}