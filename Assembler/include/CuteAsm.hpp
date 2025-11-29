#include "CuteByte.h"
#include "CuteToken.hpp"
#include <map>
#include <string>
#include <vector>

#pragma once


namespace AsmConstruct
{
	enum UnitType
	{
		Instr,
		Int32,
		Int64,
		Float32,
		Float64,
		StationId
	};

	struct Unit
	{
		UnitType type;
		std::string content;

		Unit(UnitType t, std::string s): type(t), content(s) {};
	};


	struct Program
	{
		std::vector<AsmConstruct::Unit> units;
		std::map<std::string, uint> stations;
	};


	struct InstrDetails
	{
		ctInstr code;
		uint op_count;
		uint op_size;
	};

};

class CuteAssembler
{
	Tokenizer tokenizer;
	TokenStream tokStream;


	std::map<std::string, AsmConstruct::InstrDetails>& instrMap();

	AsmConstruct::Program program;
	ctProgramImage img;

	public:

	AsmConstruct::Program* parse(std::string srcFile);
	ctProgramImage* emit(AsmConstruct::Program* program);
	void write(ctProgramImage* img, std::string outFile);

	void assemble(std::string srcFile, std::string outFile);
};