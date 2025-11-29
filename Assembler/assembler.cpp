#include "CuteByte.h"
#include "CuteToken.hpp"
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CuteAsm.hpp"


std::map<std::string, AsmConstruct::InstrDetails>& CuteAssembler::instrMap()
{
	static std::map<std::string, AsmConstruct::InstrDetails> instrMap = 
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


void CuteAssembler::parseFile()
{
}
	
void CuteAssembler::emitInstrs()
{
	Token tok;
	
	while (true)
	{
		tok = this->tokStream.next();
		
		if (tok.type == tokenEOF)
		{
			break;
		}

		if (tok.type == TokenType::tokenWord)
		{
			std::string word = this->tokStream.viewToken(&tok);

			if (!this->instrMap().contains(word))
			{
				std::cout << "Invalid Instruction\n";
			}

			ctInstr instr = this->instrMap()[word];
			this->instrs.push_back(instr);
		}	

		if (tok.type == TokenType::tokenInt)
		{
			int64_t integar = std::stoll(this->tokStream.viewToken(&tok));

			ctInstrSize instrs[8];
			ctProgramImage_packInt64(integar, instrs);

			for (uint i = 0; i < 8; i++)
			{
				this->instrs.push_back(instrs[i]);
			}
		}
	}
}


void CuteAssembler::write(std::string outFile)
{
	ctProgramImage img;
	img.header.func_count = 1;
	img.header.instr_count = this->instrs.size();

	img.header.const_count = 0;

	img.func_table = new ctFuncMetadata;
	img.func_table[0].func_id = 0;
	img.func_table[0].locals_size = 10;
	img.func_table[0].arg_count = 0;
	img.func_table[0].instr_address = 0;

	img.instrs = this->instrs.data();

	ctImageError err = ctProgramImage_write(&img, outFile.data());

	if (err == ctImageError_Success)
	{
		std::cout << "Program Image written to: " << outFile << std::endl;
	}
	else 
	{
		std::cout << "Image write failure. Code: " << err << std::endl;	
	}

}


void CuteAssembler::assemble(std::string srcFile, std::string outFile)
{
	this->tokStream = this->tokenizer.tokenize(srcFile);

	this->parseFile();
	this->emitInstrs();
	this->write(outFile);
}