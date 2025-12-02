#include "CuteByte.h"
#include "CuteToken.hpp"
#include <cstdint>
#include <format>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CuteAsm.hpp"


std::map<std::string, AsmDef::InstrDetails>& CuteAssembler::instrMap()
{
	static std::map<std::string, AsmDef::InstrDetails> instrMap = 
	{
		
    {"Halt",            {instrHalt, 0, 0}},

    {"PopAtom",         {instrPopAtom, 0, 0}},
    {"DupAtom",         {instrDupAtom, 0, 0}},

    {"LoadCoI32",       {instrLoadCoI32, 1, 4}},
    {"LoadCoI64",       {instrLoadCoI64, 1, 8}},
    {"LoadCoF32",       {instrLoadCoF32, 1, 4}},
    {"LoadCoF64",       {instrLoadCoF64, 1, 8}},

    {"LoadI32",         {instrLoadI32, 1, 4}},
    {"LoadI64",         {instrLoadI64, 1, 4}},
    {"LoadF32",         {instrLoadF32, 1, 4}},
    {"LoadF64",         {instrLoadF64, 1, 4}},

    {"StoreI32",        {instrStoreI32, 1, 4}},
    {"StoreI64",        {instrStoreI64, 1, 4}},
    {"StoreF32",        {instrStoreF32, 1, 4}},
    {"StoreF64",        {instrStoreF64, 1, 4}},

    {"CopyI32",         {instrCopyI32, 2, 4}},
    {"CopyI64",         {instrCopyI64, 2, 4}},
    {"CopyF32",         {instrCopyF32, 2, 4}},
    {"CopyF64",         {instrCopyF64, 2, 4}},

    {"AddI32",          {instrAddI32, 0, 0}},
    {"AddI64",          {instrAddI64, 0, 0}},
    {"AddF32",          {instrAddF32, 0, 0}},
    {"AddF64",          {instrAddF64, 0, 0}},

    {"SubI32",          {instrSubI32, 0, 0}},
    {"SubI64",          {instrSubI64, 0, 0}},
    {"SubF32",          {instrSubF32, 0, 0}},
    {"SubF64",          {instrSubF64, 0, 0}},

    {"MulI32",          {instrMulI32, 0, 0}},
    {"MulI64",          {instrMulI64, 0, 0}},
    {"MulF32",          {instrMulF32, 0, 0}},
    {"MulF64",          {instrMulF64, 0, 0}},

    {"DivI32",          {instrDivI32, 0, 0}},
    {"DivI64",          {instrDivI64, 0, 0}},
    {"DivF32",          {instrDivF32, 0, 0}},
    {"DivF64",          {instrDivF64, 0, 0}},

    {"LogicAnd",        {instrLogicAnd, 0, 0}},
    {"LogicOr",         {instrLogicOr, 0, 0}},
    {"LogicNot",        {instrLogicNot, 0, 0}},

    {"CmpI32",          {instrCmpI32, 0, 0}},
    {"CmpI64",          {instrCmpI64, 0, 0}},
    {"CmpF32",          {instrCmpF32, 0, 0}},
    {"CmpF64",          {instrCmpF64, 0, 0}},

    {"Cmp2BoolEq",      {instrCmp2BoolEq, 0, 0}},
    {"Cmp2BoolNe",      {instrCmp2BoolNe, 0, 0}},
    {"Cmp2BoolLt",      {instrCmp2BoolLt, 0, 0}},
    {"Cmp2BoolLe",      {instrCmp2BoolLe, 0, 0}},
    {"Cmp2BoolGt",      {instrCmp2BoolGt, 0, 0}},
    {"Cmp2BoolGe",      {instrCmp2BoolGe, 0, 0}},

    {"JmpA",            {instrJmpA, 1, 4}},
    {"Jmp",             {instrJmp, 1, 4}},
    {"JmpTrue",         {instrJmpTrue, 1, 4}},
    {"JmpFalse",        {instrJmpFalse, 1, 4}},

    {"FuncCall",        {instrFuncCall, 1, 4}},
    {"Return",          {instrReturn, 0, 0}},
    {"ReturnValue",     {instrReturnValue, 0, 0}},

    {"OutI32",          {instrOutI32, 0, 0}},
    {"OutI64",          {instrOutI64, 0, 0}},
    {"OutF32",          {instrOutF32, 0, 0}},
    {"OutF64",          {instrOutF64, 0, 0}},

	};


	return instrMap;
}


void CuteAssembler::notify(std::string msg)
{
	std::cout << msg << std::endl;
}


void CuteAssembler::notifyDebug(std::string msg)
{
	#ifdef ASM_DEBUG
	std::cout << msg << std::endl;
	#endif
}


void CuteAssembler::throwError(std::string name, std::string msg)
{
	std::cout << name << " :: " << msg << std::endl;
	std::exit(0);
}


void CuteAssembler::parse()
{
	std::string word;

	while (true)
	{
		if (this->tokens.peek().type == TokenType::tokenEOF)
		{
			break;
		}

		if (this->tokens.getKeyword("Station"))
		{
			if (!this->tokens.getInt(&word))
			{
				this->throwError("Assembler Error", "Expected integar after station.");
			}
			uint i = std::stoi(word);
			this->program.addUnit(AsmDef::Unit(AsmDef::UnitType::Station, word));
			this->program.addStation(i, 0);
			continue;
		}

		if (this->tokens.getWord(&word))
		{	
			if (!this->instrMap().contains(word))
			{
				this->throwError("Assembler Error", "Unknown Instruction");
			}
			this->program.addUnit(AsmDef::Unit(AsmDef::UnitType::Instr, word));
			continue;
		}

		if (this->tokens.getInt(&word))
		{
			this->program.addUnit(AsmDef::Unit(AsmDef::UnitType::Int, word));
			continue;
		}
		
		if (this->tokens.getFloat(&word))
		{
			this->program.addUnit(AsmDef::Unit(AsmDef::UnitType::Float, word));
			continue;
		}

	}
}


void CuteAssembler::emit()
{
	for (uint i = 0; i < this->program.units.size(); i++)
	{
		AsmDef::Unit unit = this->program.units[i];

		if (unit.type == AsmDef::UnitType::Station)
		{
			uint id = std::stoi(unit.content);
			this->program.stations[id] = this->program.instrs.size();
			continue;
		}

		if (unit.type == AsmDef::UnitType::Instr)
		{
			this->emitInstr(i);
		}
	
	}

	this->patchJumps();
}


void CuteAssembler::emitInstr(uint& unitIndex)
{
	AsmDef::Unit unit = this->program.units[unitIndex];

	AsmDef::InstrDetails instr = this->instrMap()[unit.content];
	this->program.instrs.push_back(instr.code);

	int64_t i64 = 0;
	int32_t i32 = 0;
	float f32 = 0;
	double f64 = 0;

	if (instr.code == instrJmp | instr.code == instrJmpTrue | instr.code == instrJmpFalse)
	{
		ctInstrSize packed[4];
		uint station_id;

		unit = this->program.units[++unitIndex];

		if (unit.type != AsmDef::UnitType::Int)
		{
			this->throwError("Assembler Error", "Expected station id (int) after jump");
		}

		station_id = std::stoi(unit.content);

		this->program.patches[this->program.instrs.size()] = station_id;
		ctProgramImage_packInt32(&i32, packed); //placeholder
		addMultipleInstrs(this->program.instrs, packed, 4);
		return;
	}

	// below code writes the operands of instructions
	// operand size and count defined in the instrMap function

	uint temp = unitIndex + 1;
	unitIndex += instr.op_count;

	for (uint j = temp; j < temp + instr.op_count; j++)
	{
		unit = this->program.units[j];
		ctInstrSize packed4[4];
		ctInstrSize packed8[8];
		
		if (unit.type == AsmDef::UnitType::Int)
		{
			if (instr.op_size == 4)
			{
				i32 = std::stoi(unit.content);
				ctProgramImage_packInt32(&i32, packed4);
				addMultipleInstrs(this->program.instrs, packed4, 4);
			}
			else if (instr.op_size == 8)
			{
				i64 = std::stoll(unit.content);
				ctProgramImage_packInt64(&i64, packed8);
				addMultipleInstrs(this->program.instrs, packed8, 8);
			}
		}
		else if (unit.type == AsmDef::UnitType::Float)
		{
			if (instr.op_size == 4)
			{
				f32 = std::stof(unit.content);
				ctProgramImage_packFloat32(&f32, packed4);
				addMultipleInstrs(this->program.instrs, packed4, 4);
			}
			else if (instr.op_size == 8)
			{
				f64 = std::stod(unit.content);
				ctProgramImage_packFloat64(&f64, packed8);
				addMultipleInstrs(this->program.instrs, packed8, 8);
			}
		}
		else 
		{
			this->throwError("Assembler Error", "Expected int or float as instruction operands.");
		}

	}

}


void CuteAssembler::patchJumps()
{
	for (auto patch: this->program.patches)
	{
		if (!this->program.stations.contains(patch.second))
		{
			this->throwError("Assembler Error", "Unregistered station id.");
		}
		
		uint station_postion = this->program.stations[patch.second];
		uint current_position = patch.first;
		int relative = (station_postion) - (current_position);

		ctInstrSize packed[4];
		ctProgramImage_packInt32(&relative, packed);

		for (uint i = patch.first; i < patch.first + 4; i++)
		{
			this->program.instrs[i] = packed[i - patch.first];
		}
	}
}



void CuteAssembler::write(std::string outFile)
{
	ctProgramImage img;

	img.header.const_count = 0;

	img.header.func_count = 1;
	img.func_table = new ctFuncMetadata;
	img.func_table->func_id = 0;
	img.func_table->arg_count = 0;
	img.func_table->locals_size = 10;
	img.func_table->instr_address = 0;

	img.header.instr_count = this->program.instrs.size();
	img.instrs = this->program.instrs.data();

	ctImageError err = ctProgramImage_write(&img, outFile.data());

	if (err == ctImageError_Success)
	{
		this->notify(std::format("Program Image successfully written to: {}", outFile));
	}
	else
	{
		this->throwError("Assembler Error", std::format("Image could not be written. Code: {}", (int) err));
	}
}


void CuteAssembler::assemble(std::string srcFile, std::string outFile)
{
	this->tokens = this->tokenizer.tokenize(srcFile);
	this->parse();
	this->emit();
	this->write(outFile);
}