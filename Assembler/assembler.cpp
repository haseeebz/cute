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

	{"ExitEngine",       {instrExitEngine, 1, 4}},
	{"Exit",             {instrExit, 1, 4}},
	{"Out",              {instrOut, 1, 4}},
	{"Dump",             {instrDump, 1, 4}},
	{"PopAtom",          {instrPopAtom, 0, 0}},
	{"DupAtom",          {instrDupAtom, 0, 0}},
	{"Null",             {instrNull, 0, 0}},
	{"ModCall",          {instrModCall, 0, 0}},

	{"LoadCoI32",        {instrLoadCoI32, 1, 4}},
	{"LoadCoI64",        {instrLoadCoI64, 1, 8}},
	{"LoadCoF32",        {instrLoadCoF32, 1, 4}},
	{"LoadCoF64",        {instrLoadCoF64, 1, 8}},
	{"LoadConst",        {instrLoadConst, 0, 0}},

	{"LoadI32",          {instrLoadI32, 1, 4}},
	{"LoadI64",          {instrLoadI64, 1, 4}},
	{"LoadF32",          {instrLoadF32, 1, 4}},
	{"LoadF64",          {instrLoadF64, 1, 4}},

	{"GLoadI32",         {instrGLoadI32, 1, 4}},
	{"GLoadI64",         {instrGLoadI64, 1, 4}},
	{"GLoadF32",         {instrGLoadF32, 1, 4}},
	{"GLoadF64",         {instrGLoadF64, 1, 4}},

	{"StoreI32",         {instrStoreI32, 1, 4}},
	{"StoreI64",         {instrStoreI64, 1, 4}},
	{"StoreF32",         {instrStoreF32, 1, 4}},
	{"StoreF64",         {instrStoreF64, 1, 4}},

	{"GStoreI32",        {instrGStoreI32, 1, 4}},
	{"GStoreI64",        {instrGStoreI64, 1, 4}},
	{"GStoreF32",        {instrGStoreF32, 1, 4}},
	{"GStoreF64",        {instrGStoreF64, 1, 4}},

	{"CopyI32",          {instrCopyI32, 2, 4}},
	{"CopyI64",          {instrCopyI64, 2, 4}},
	{"CopyF32",          {instrCopyF32, 2, 4}},
	{"CopyF64",          {instrCopyF64, 2, 4}},

	{"AddI32",           {instrAddI32, 0, 0}},
	{"AddI64",           {instrAddI64, 0, 0}},
	{"AddF32",           {instrAddF32, 0, 0}},
	{"AddF64",           {instrAddF64, 0, 0}},

	{"SubI32",           {instrSubI32, 0, 0}},
	{"SubI64",           {instrSubI64, 0, 0}},
	{"SubF32",           {instrSubF32, 0, 0}},
	{"SubF64",           {instrSubF64, 0, 0}},

	{"MulI32",           {instrMulI32, 0, 0}},
	{"MulI64",           {instrMulI64, 0, 0}},
	{"MulF32",           {instrMulF32, 0, 0}},
	{"MulF64",           {instrMulF64, 0, 0}},

	{"DivI32",           {instrDivI32, 0, 0}},
	{"DivI64",           {instrDivI64, 0, 0}},
	{"DivF32",           {instrDivF32, 0, 0}},
	{"DivF64",           {instrDivF64, 0, 0}},
	{"DivU32",           {instrDivU32, 0, 0}},
	{"DivU64",           {instrDivU64, 0, 0}},

	{"ModI32",           {instrModI32, 0, 0}},
	{"ModU32",           {instrModU32, 0, 0}},
	{"ModI64",           {instrModI64, 0, 0}},
	{"ModU64",           {instrModU64, 0, 0}},

	{"LogicAnd",         {instrLogicAnd, 0, 0}},
	{"LogicOr",          {instrLogicOr, 0, 0}},
	{"LogicNot",         {instrLogicNot, 0, 0}},
	{"LogicXor",         {instrLogicXor, 0, 0}},

	{"BitAnd",           {instrBitAnd, 0, 0}},
	{"BitOr",            {instrBitOr, 0, 0}},
	{"BitNot",           {instrBitNot, 0, 0}},
	{"BitXor",           {instrBitXor, 0, 0}},

	{"BitLShift",        {instrBitLShift, 0, 0}},
	{"BitRShift",        {instrBitRShift, 0, 0}},
	{"BitRaShift",       {instrBitRaShift, 0, 0}},
	{"BitRShift32",      {instrBitRShift32, 0, 0}},
	{"BitRaShift32",     {instrBitRaShift32, 0, 0}},

	{"CmpI32",           {instrCmpI32, 0, 0}},
	{"CmpI64",           {instrCmpI64, 0, 0}},
	{"CmpF32",           {instrCmpF32, 0, 0}},
	{"CmpF64",           {instrCmpF64, 0, 0}},

	{"Cmp2BoolEq",       {instrCmp2BoolEq, 0, 0}},
	{"Cmp2BoolNe",       {instrCmp2BoolNe, 0, 0}},
	{"Cmp2BoolLt",       {instrCmp2BoolLt, 0, 0}},
	{"Cmp2BoolLe",       {instrCmp2BoolLe, 0, 0}},
	{"Cmp2BoolGt",       {instrCmp2BoolGt, 0, 0}},
	{"Cmp2BoolGe",       {instrCmp2BoolGe, 0, 0}},

	{"F32I32",           {instrF32I32, 0, 0}},
	{"I32F32",           {instrI32F32, 0, 0}},
	{"I64F64",           {instrI64F64, 0, 0}},
	{"F64I64",           {instrF64I64, 0, 0}},
	{"F32F64",           {instrF32F64, 0, 0}},
	{"F64F32",           {instrF64F32, 0, 0}},
	{"I32I64",           {instrI32I64, 0, 0}},
	{"I64I32",           {instrI64I32, 0, 0}},

	{"Jmp",              {instrJmp, 1, 4}},
	{"JmpTrue",          {instrJmpTrue, 1, 4}},
	{"JmpFalse",         {instrJmpFalse, 1, 4}},

	{"FuncCall",         {instrFuncCall, 1, 4}},
	{"Return",           {instrReturn, 0, 0}},

	{"ConNew",           {instrConNew, 0, 0}},
	{"ConDel",           {instrConDel, 0, 0}},
	{"ConStore",         {instrConStore, 0, 0}},
	{"ConGStore",        {instrConGStore, 0, 0}},
	{"ConLoad",          {instrConLoad, 0, 0}},
	{"ConGLoad",         {instrConGLoad, 0, 0}},
	{"ConCopy",          {instrConCopy, 0, 0}},
	{"ConClone",         {instrConClone, 0, 0}},  
	{"ConAccLoad",       {instrConAccLoad, 0, 0}},
	{"ConAccStore",      {instrConAccStore, 0, 0}},
	{"ConInc",           {instrConInc, 0, 0}},
	{"ConDec",           {instrConDec, 0, 0}},

	};


	return instrMap;
}


void CuteAssembler::notify(std::string msg)
{
	std::cout << msg << std::endl;
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

		if (this->tokens.getKeyword("func"))
		{
			this->parseFunction();
		}
	}

}


void CuteAssembler::parseFunction()
{
	AsmDef::Function func;

	std::string int_str;

	this->tokens.getInt(&int_str);
	func.id = std::stoi(int_str);

	this->tokens.getInt(&int_str);
	func.args = std::stoi(int_str);

	this->tokens.getInt(&int_str);
	func.locals = std::stoi(int_str);

	if (func.args > func.locals)
	{
		this->throwError("Assembler Error", "Local memory space is less than required arguments.");
	}

	this->tokens.getKeySym('[');
	this->parseInstrBlock(func);

	this->program.functions[func.id] = func;
}


void CuteAssembler::parseInstrBlock(AsmDef::Function& func)
{
	std::string word;

	while (true)
	{	

		if (this->tokens.getKeySym(']'))
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
			func.addUnit(AsmDef::Unit(AsmDef::UnitType::Station, word));
			func.addStation(i, 0);
			continue;
		}

		else if (this->tokens.getWord(&word))
		{	
			if (!this->instrMap().contains(word))
			{
				this->throwError("Assembler Error", std::format("Unknown Instruction: {}", word));
			}
			func.addUnit(AsmDef::Unit(AsmDef::UnitType::Instr, word));
			continue;
		}

		else if (this->tokens.getInt(&word))
		{
			func.addUnit(AsmDef::Unit(AsmDef::UnitType::Int, word));
			continue;
		}

		else if (this->tokens.getKeySym('-'))
		{
			if (this->tokens.getInt(&word))
			{
				func.addUnit(AsmDef::Unit(AsmDef::UnitType::Int, std::format("-{}", word)));
			}
		}
		
		else if (this->tokens.getFloat(&word))
		{
			func.addUnit(AsmDef::Unit(AsmDef::UnitType::Float, word));
			continue;
		}
	}
}

void CuteAssembler::emit()
{
	for (auto pair: this->program.functions)
	{
		AsmDef::Function func = pair.second;
		this->emitFunction(func);
		this->program.instrs.insert(this->program.instrs.end(), func.instrs.begin(), func.instrs.end());
	}

	this->program.img.header.const_count = 0;
	this->program.img.header.instr_count = this->program.instrs.size();
	this->program.img.header.func_count = this->program.func_table.size();
	this->program.img.func_table = this->program.func_table.data();
	this->program.img.instrs = this->program.instrs.data();
}


void CuteAssembler::emitFunction(AsmDef::Function& func)
{
	ctFuncMetadata meta;
	meta.func_id = func.id;
	meta.args_count = func.args;
	meta.locals_count = func.locals;
	meta.instr_address = this->program.instrs.size();

	ctAsmDebug(
		"Registered Function %d. Args:%d Locals:%d Instr Address:%lu\n", 
		meta.func_id, 
		meta.args_count, 
		meta.locals_count, 
		meta.instr_address
	);

	this->program.func_table.push_back(meta);
	this->emitInstrBlock(func);
	this->patchJumps(func);
}


void CuteAssembler::emitInstrBlock(AsmDef::Function& func)
{
	AsmDef::Unit unit;
	for (uint i = 0; i < func.units.size(); i++)
	{
		unit = func.units[i];

		if (unit.type == AsmDef::UnitType::Station)
		{
			uint id = std::stoi(unit.content);
			func.stations[id] = func.instrs.size();
			continue;
		}

		AsmDef::InstrDetails instr = this->instrMap()[unit.content];
		func.instrs.push_back(instr.code);

		int64_t i64 = 0;
		int32_t i32 = 0;
		float f32 = 0;
		double f64 = 0;

		if ((instr.code == instrJmp) | (instr.code == instrJmpTrue) | (instr.code == instrJmpFalse))
		{
			ctInstrSize packed[4];
			uint station_id;

			unit = func.units[++i];

			if (unit.type != AsmDef::UnitType::Int)
			{
				this->throwError("Assembler Error", "Expected station id (int) after jump");
			}

			station_id = std::stoi(unit.content);

			func.patches[func.instrs.size()] = station_id;
			ctProgramImage_packInt32(&i32, packed); //placeholder
			addMultipleInstrs(func.instrs, packed, 4);
			continue;
		}

		// below code writes the operands of instructions
		// operand size and count defined in the instrMap function

		uint temp = i + 1;
		i += instr.op_count;
		

		for (uint j = temp; j < temp + instr.op_count; j++)
		{

			unit = func.units[j];
			ctInstrSize packed4[4];
			ctInstrSize packed8[8];

			if (unit.type == AsmDef::UnitType::Int)
			{
				
				if (instr.op_size == 4)
				{
					i32 = std::stoi(unit.content);
					ctProgramImage_packInt32(&i32, packed4);
					addMultipleInstrs(func.instrs, packed4, 4);
				}
				else if (instr.op_size == 8)
				{
					i64 = std::stoll(unit.content);
					ctProgramImage_packInt64(&i64, packed8);
					addMultipleInstrs(func.instrs, packed8, 8);
				}
			}
			else if (unit.type == AsmDef::UnitType::Float)
			{
				if (instr.op_size == 4)
				{
					f32 = std::stof(unit.content);
					ctProgramImage_packFloat32(&f32, packed4);
					addMultipleInstrs(func.instrs, packed4, 4);
				}
				else if (instr.op_size == 8)
				{
					f64 = std::stod(unit.content);
					ctProgramImage_packFloat64(&f64, packed8);
					addMultipleInstrs(func.instrs, packed8, 8);
				}
			}
			else 
			{
				this->throwError("Assembler Error", std::format("Expected int or float as instruction operands: {}", unit.content));
			}

		}

	}


}


void CuteAssembler::patchJumps(AsmDef::Function& func)
{
	for (auto patch: func.patches)
	{
		if (!func.stations.contains(patch.second))
		{
			this->throwError("Assembler Error", "Unregistered station id.");
		}
		
		uint station_postion = func.stations[patch.second];
		uint current_position = patch.first;
		int relative = int(station_postion) - int(current_position);
		ctInstrSize packed[4];
		ctProgramImage_packInt32(&relative, packed);

		for (uint i = patch.first; i < patch.first + 4; i++)
		{
			func.instrs[i] = packed[i - patch.first];
		}
	}	
}


void CuteAssembler::write(std::string outFile)
{
	ctImageError err = ctProgramImage_write(&this->program.img, outFile.data());

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