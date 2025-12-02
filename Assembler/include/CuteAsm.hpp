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

#define addMultipleInstrs(vector, instrs, count) \
for (uint i = 0; i < count; i++) \
{vector.push_back(instrs[i]);};


namespace AsmDef
{
	enum UnitType
	{
		Instr,
		Int,
		Float,
		Station
	};


	struct Unit
	{
		UnitType type;
		std::string content;

		Unit(UnitType t, std::string c): type(t), content(c) {};
		Unit() = default;
	};


	struct Function
	{
		uint id;
		uint args;
		uint locals;
		// parser level
		std::vector<Unit> units;
		std::map<uint, uint> stations;

		// emitter level
		std::map<uint, uint> patches;
		std::vector<ctInstrSize> instrs;

		void addUnit(Unit u) {units.push_back(u);}
		void addStation(uint id, uint pos) {stations[id] = pos;}
	};


	struct Program
	{
		std::map<uint, Function> functions;
		// writer level
		ctProgramImage img;
		std::vector<ctInstrSize> instrs;
		std::vector<ctFuncMetadata> func_table;
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

	std::map<std::string, AsmDef::InstrDetails>& instrMap();

	AsmDef::Program program;
	ctProgramImage img;

	void notify(std::string msg);
	void notifyDebug(std::string msg);
	void throwError(std::string name, std::string msg);

	void parse();

	void parseFunction();
	void parseInstrBlock(AsmDef::Function& func);

	void emit();

	void emitFunction(AsmDef::Function& func);
	void emitInstrBlock(AsmDef::Function& func);
	void patchJumps(AsmDef::Function& func);

	void write(std::string outFile);

	public:

	void assemble(std::string srcFile, std::string outFile);
};