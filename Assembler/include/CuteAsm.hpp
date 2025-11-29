#include "CuteByte.h"
#include "CuteToken.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#pragma once

#ifndef ASM_DEBUG
#define ASM_DEBUG
#endif


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
		union
		{
			ctInstr instr;
			int32_t i32;
			int64_t i64;
			float f32;
			double f64;
			uint station;
		};

		Unit(ctInstr i)      : type(UnitType::Instr), instr(i) {}
		Unit(int32_t i)      : type(UnitType::Int32), i32(i) {}
		Unit(int64_t i)      : type(UnitType::Int64), i64(i) {}
		Unit(float f)        : type(UnitType::Float32), f32(f) {}
		Unit(double d)       : type(UnitType::Float64), f64(d) {}
		Unit(uint s)         : type(UnitType::StationId), station(s) {}

		Unit()               : type(UnitType::Instr), instr(ctInstr(0)) {}

	};


	struct Program
	{
		Unit lastUnit;
		std::vector<Unit> units;
		std::map<uint, uint> stations;
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
	TokenStream tokens;

	std::map<std::string, AsmConstruct::InstrDetails>& instrMap();

	AsmConstruct::Program program;
	ctProgramImage img;

	void notify(std::string msg);
	void notifyDebug(std::string msg);
	void throwError(std::string name, std::string msg);

	void parse();
	void emit();
	void write(std::string outFile);

	public:

	

	void assemble(std::string srcFile, std::string outFile);
};