#include "CuteByte.h"
#include "CuteToken.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#pragma once

namespace AsmConstructs
{
	struct Function
	{
		uint32_t func_id;
		uint16_t args_count;
		uint16_t locals_size;
		std::vector<std::string> instrs;
		std::map<uint32_t, uint32_t> stations;
	};

	using FunctionMap = std::map<uint32_t, Function>;
	using ConstMap = std::map<uint32_t, ctProgramConst>; 
	using InstrVec = std::vector<ctInstrSize>;
	
	using InstrMapping = std::map<std::string, ctInstr>;
}



class CuteAssembler
{

	std::string srcfile;
	std::string outfile;
	
	Tokenizer tokenizer;
	TokenStream tokStream;

	AsmConstructs::FunctionMap funcMap;
	AsmConstructs::ConstMap    constMap;
	AsmConstructs::InstrVec    instrVec;

	void parse();
	
	void parseFunction();
	void parseConstant();


	void writeByte();

	AsmConstructs::InstrMapping getInstrMap();

	public:

	void throwError(std::string msg);
	void assemble(std::string filepath, std::string outfile);
};