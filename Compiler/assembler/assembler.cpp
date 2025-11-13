#include "CuteByte.h"
#include "../tokenizer/tokenizer.hpp"
#include "../tokenizer/token.hpp"
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include "assembler.hpp"



std::map<std::string, ctInstr> CuteAssembler::getInstrMap()
{
	static std::map<std::string, ctInstr> instr_map =
		{
		{"Halt", instrHalt},

		{"DupAtom", instrDupAtom},
		{"PopAtom", instrPopAtom},

		{"LoadCoI8", instrLoadCoI8},
		{"LoadCoI32", instrLoadCoI32},
		{"LoadCoI64", instrLoadCoI64},
		{"LoadCoF32", instrLoadCoF32},
		{"LoadCoF64", instrLoadCoF64},

		{"LoadI32", instrLoadI32},
		{"LoadI64", instrLoadI64},
		{"LoadF32", instrLoadF32},
		{"LoadF64", instrLoadF64},

		{"StoreI32", instrStoreI32},
		{"StoreI64", instrStoreI64},
		{"StoreF32", instrStoreF32},
		{"StoreF64", instrStoreF64},

		{"AddI32", instrAddI32},
		{"AddI64", instrAddI64},
		{"AddF32", instrAddF32},
		{"AddF64", instrAddF64},

		{"SubI32", instrSubI32},
		{"SubI64", instrSubI64},
		{"SubF32", instrSubF32},
		{"SubF64", instrSubF64},

		{"MulI32", instrMulI32},
		{"MulI64", instrMulI64},
		{"MulF32", instrMulF32},
		{"MulF64", instrMulF64},

		{"DivI32", instrDivI32},
		{"DivI64", instrDivI64},
		{"DivF32", instrDivF32},
		{"DivF64", instrDivF64},

		{"And", instrAnd},
		{"Or", instrOr},
		{"Not", instrNot},
		{"Xor", instrXor},

		{"CmpI32", instrCmpI32},
		{"CmpI64", instrCmpI64},
		{"CmpF32", instrCmpF32},
		{"CmpF64", instrCmpF64},

		{"Cmp2BoolEq", instrCmp2BoolEq},
		{"Cmp2BoolNe", instrCmp2BoolNe},
		{"Cmp2BoolLt", instrCmp2BoolLt},
		{"Cmp2BoolLe", instrCmp2BoolLe},
		{"Cmp2BoolGt", instrCmp2BoolGt},
		{"Cmp2BoolGe", instrCmp2BoolGe},

		{"Jmp", instrJmp},
		{"JmpTrue", instrJmpTrue},
		{"JmpFalse", instrJmpFalse},

		{"Call", instrCall},
		{"CallVirtual", instrCallVirtual},
		{"Return", instrReturn},

		{"NewCon", instrNewCon},
		{"AccessCon", instrAccessCon},
		{"DelCon", instrDelCon},

		{"Out", instrOut},
	};

	return instr_map;
}


void CuteAssembler::assemble(TokenStream* tokens, std::string outfile)
{
	this->tokStream = tokens;

	Token token;

	while (true)
	{
		token = this->tokStream->next();

		if (token.type == TokenType::tokenEOF) {break;}

		if (token.type == TokenType::tokenSymbol)
		{
			if (this->tokStream->viewSymToken(&token) != '#') 
			{
				goto Error;
			}
			
			token = this->tokStream->next();


			if (token.type == TokenType::tokenInt)
			{
				int i = std::stoi(this->tokStream->viewToken(&token));
				this->currConstants.push_back((Constant) {.i32 = i});
				continue;
			}


			if (token.type == TokenType::tokenInt)
			{
				float f = std::stof(this->tokStream->viewToken(&token));
				this->currConstants.push_back((Constant) {.f32 = f});
				continue;
			}

			continue;
		}

		if (token.type == TokenType::tokenWord)
		{
			ctInstrSize instr = this->getInstrMap()[this->tokStream->viewToken(&token)];
			this->currInstrs.push_back(instr);
			continue;
		}

		if (token.type == TokenType::tokenInt)
		{
			ctInstrSize instr = std::stoi(this->tokStream->viewToken(&token));
			this->currInstrs.push_back(instr);
			continue;
		}

		Error:
		std::cout << "Bad Bytecode: " << this->tokStream->viewToken(&token) << std::endl;
		std::cout << "Token number: " << this->tokStream->curr_token << std::endl;
		return;
	}


	ctProgramImage img;

	img.header.instr_count = this->currInstrs.size();
	img.instrs = this->currInstrs.data();

	img.header.const_count = this->currConstants.size();
	img.consts = this->currConstants.data();

	ctImageError code = ctProgramImage_write(&img, outfile.data());
}
