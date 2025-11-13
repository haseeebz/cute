#include "CuteByte.h"
#include "../tokenizer/tokenizer.hpp"
#include "../tokenizer/token.hpp"
#include <map>

#pragma once

class CuteAssembler
{
	TokenStream* tokStream;
	std::string outfile;

	std::vector<ctInstrSize> currInstrs;
	std::vector<Constant> currConstants;

	std::map<std::string, ctInstr> getInstrMap();

	public:

	void assemble(TokenStream* tokens, std::string outfile);

};