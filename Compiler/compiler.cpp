#include "CuteCompiler.hpp"
#include <string>


void CuteCompiler::compile(std::string str)
{
	tokenizer.tokenize(str);
	tokenizer.printTokens();
}