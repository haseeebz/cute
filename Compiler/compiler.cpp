#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "parser/node.hpp"

#include <iostream>
#include <string>


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	tokenizer.tokenize(filepath);

	std::cout << "Tokenized Source:\n";
	tokenizer.printTokens();

	Node* root = parser.parse(tokenizer.getTokens());
	std::cout << "Parsed Code:\n";
	root->print();

	writer.setOutFile(outfile);
	writer.write(root);

	delete root;
}