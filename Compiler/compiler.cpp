#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "parser/node.hpp"

#include <iostream>
#include <string>


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	tokenizer.tokenize(filepath);

	std::cout << "Tokenized Source : ";
	tokenizer.printTokens();

	Node* root = parser.parse(tokenizer.getTokens());
	std::cout << "Parsed Code: \n";
	root->print(0);

	writer.setOutFile(outfile);
	writer.write(root);

	delete root;
}