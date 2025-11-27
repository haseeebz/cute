#include "CuteByte.h"
#include "CuteToken.hpp"
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CuteAsm.hpp"


void CuteAssembler::assemble(std::string filepath, std::string outfile)
{
	this->tokStream = this->tokenizer.tokenize(filepath);

	std::cout << this->tokStream.toString() << "\n";
}