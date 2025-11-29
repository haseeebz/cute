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


void CuteAssembler::parse();
void CuteAssembler::emit();
void CuteAssembler::write(std::string outFile);


void CuteAssembler::assemble(std::string srcFile, std::string outFile)
{
	this->tokens = this->tokenizer.tokenize(srcFile);

	this->parse();
	this->emit();
	this->write(outFile);
}