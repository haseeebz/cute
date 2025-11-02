#include "CuteCompiler.hpp"
#include "CuteByte.h"

#include <string>


void CuteCompiler::compile(std::string filepath)
{
	tokenizer.tokenize(filepath);
	tokenizer.printTokens();

	delete parser.parse(tokenizer.getTokens());
}