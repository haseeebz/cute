#include "CuteToken.hpp"
#include "CuteByte.h"
#include <map>

#pragma once

class CuteAssembler
{
	Tokenizer tokenizer;
	TokenStream tokStream;
	std::string outfile;

	std::vector<ctInstrSize> currInstrs;
	std::vector<ctProgramConstant> currConstants;

	std::map<std::string, ctInstr> getInstrMap();

	public:

	void assemble(std::string filepath, std::string outfile);
};