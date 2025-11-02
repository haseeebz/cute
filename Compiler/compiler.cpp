#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "parser/node.hpp"

#include <string>


void CuteCompiler::compile(std::string filepath)
{
	tokenizer.tokenize(filepath);
	tokenizer.printTokens();

	Node* root = parser.parse(tokenizer.getTokens());

	writer.setOutFile("code.bin");
	writer.write(root);

	delete root;
}