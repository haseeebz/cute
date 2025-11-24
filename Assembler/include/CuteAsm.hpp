#include "CuteToken.hpp"
#include "CuteByte.h"
#include <cstdint>
#include <map>
#include <sys/types.h>

#pragma once


struct Function
{
	std::vector<ctInstrSize> currInstrs;
	uint arg_count;
	uint locals_size;
};


class CuteAssembler
{
	Tokenizer tokenizer;
	TokenStream tokStream;

	std::string outfile;

	std::vector<ctProgramConstant> defined_consts;

	std::map<uint32_t, Function> defined_funcs;
	Function main_func;

	std::vector<ctFuncMetadata> funcs;
	std::vector<ctInstrSize> instrs;
	std::map<std::string, ctInstr> getInstrMap();

	void startAssembling();

	void handleFunc();
	void handleConst();
	void handleInstr();

	ctProgramImage* makeProgramImage();

	void raiseError(std::string msg);

	public:

	void assemble(std::string filepath, std::string outfile);
};