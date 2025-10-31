#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "tokenizer/token.hpp"

#include <string>
#include <vector>


void CuteCompiler::compile(std::string filepath)
{
	tokenizer.tokenize(filepath);
	tokenizer.printTokens();
}