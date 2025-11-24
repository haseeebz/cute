#include "CuteByte.h"
#include "CuteToken.hpp"
#include "CuteAsm.hpp"

#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>




std::map<std::string, ctInstr> CuteAssembler::getInstrMap()
{
	static std::map<std::string, ctInstr> instr_map =
		{
		{"Halt", instrHalt},

		{"DupAtom", instrDupAtom},
		{"PopAtom", instrPopAtom},

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

		{"OutI32", instrOutI32},
		{"OutF32", instrOutF32},
		{"OutI64", instrOutI64},
		{"OutF64", instrOutF64},
	};

	return instr_map;
}


void CuteAssembler::assemble(std::string filepath, std::string outfile)
{
	this->tokStream = this->tokenizer.tokenize(filepath);

	this->startAssembling();

	ctProgramImage* img = this->makeProgramImage();

	for (uint32_t i = 0; i < img->header.func_count; i++)
	{
	printf("Function#%u, Args:%u, Locals:%u, Address:%u\n", i, img->func_table[i].arg_count, img->func_table[i].locals_size, img->func_table[0].address);
	}

	ctImageError code = ctProgramImage_write(img, outfile.data());

	if (code == ctImageError_Success)
	{
		std::cout << "Bytecode written to: " << outfile << std::endl;
	}
	else 
	{
		std::cout << "Bytecode assembly failed. Error: " << code << std::endl;
	}

}


void CuteAssembler::startAssembling()
{
	Token token;

	while (true)
	{
		token = this->tokStream.next();

		if (token.type == TokenType::tokenEOF) {break;}

		if (token.type == TokenType::tokenSymbol)
		{
			char sym = this->tokStream.viewSymToken(&token);

			if (sym == '#') 
			{
				this->handleConst();
				continue;
			}
			
			if (sym == '/')
			{
				while (true)
				{
				token = this->tokStream.next();
				char sym = this->tokStream.viewSymToken(&token);
				if (sym == '/') {break;}
				}
				continue;
			}

			this->raiseError("Invalid Symbol");
		}


		if (token.type == TokenType::tokenWord)
		{
			if (this->tokStream.viewToken(&token) == "func")
			{
				this->handleFunc();
			}

		}

	}

}

void CuteAssembler::handleFunc()
{
	Token token;
	std::string word;
	int32_t id;
	Function func;

	token = this->tokStream.next();
	id = std::stoi(this->tokStream.viewToken(&token));
	
	token = this->tokStream.next();
	func.locals_size = std::stoi(this->tokStream.viewToken(&token));

	token = this->tokStream.next();
	func.arg_count = std::stoi(this->tokStream.viewToken(&token));

	while (true)
	{
		token = this->tokStream.next();

		if (token.type == TokenType::tokenWord)
		{
			std::string word = this->tokStream.viewToken(&token);

			if (word == "end") {break;}

			if (!this->getInstrMap().contains(word)) {this->raiseError("Invalid Instruction");}
			ctInstrSize instr = this->getInstrMap()[word];
			func.currInstrs.push_back(instr);
			continue;
		}

		if (token.type == TokenType::tokenInt)
		{
			ctInstrSize instr = std::stoi(this->tokStream.viewToken(&token));
			func.currInstrs.push_back(instr);
			continue;
		}

	}

	
	this->defined_funcs[id] = func;
}


void CuteAssembler::handleConst()
{
	Token token;
	token = this->tokStream.next();

	if (token.type != TokenType::tokenWord) {this->raiseError("Expected type specifier after #");}

	std::string type = this->tokStream.viewToken(&token);

	Token num = this->tokStream.next();
	std::string nums = this->tokStream.viewToken(&num);

	if (type == "i32")
	{
		int i = std::stoi(nums);
		this->defined_consts.push_back((ctProgramConstant) {.i32 = i});
	} 
	else if (type == "i64")
	{
		long i = std::stol(nums);
		this->defined_consts.push_back((ctProgramConstant) {.i64 = i});
	}
	else if (type == "f32")
	{
		float f = std::stof(nums);
		this->defined_consts.push_back( (ctProgramConstant) {.f32 = f});
	}
	else if (type == "f64")
	{
		double f = std::stod(nums);
		this->defined_consts.push_back((ctProgramConstant) {.f64 = f});
	}
	else 
	{
		this->raiseError("Invalid type specifier after #");
	}

}


ctProgramImage* CuteAssembler::makeProgramImage()
{
	ctProgramImage* img = new ctProgramImage;

	img->header.const_count = this->defined_consts.size();
	img->consts = this->defined_consts.data();

	
	

	img->header.func_count = this->defined_funcs.size();

	funcs.resize(img->header.func_count);

	for (auto func: this->defined_funcs)
	{
		ctFuncMetadata meta;

		meta.func_id = func.first;
		meta.address = instrs.size();
		meta.locals_size = func.second.locals_size;
		meta.arg_count = func.second.arg_count;

		for (auto instr: func.second.currInstrs)
		{
			instrs.push_back(instr);
		}

		funcs[meta.func_id] = meta;

		std::cout << "Registerd Func# " << meta.func_id << '\n';
		std::cout << "Arguments# " << meta.arg_count << '\n';
		std::cout << "Locals Size# " << meta.locals_size << '\n';
		std::cout << "Address# " << meta.address << '\n';
	}

	img->header.instr_count = instrs.size();
	img->instrs = instrs.data();
	img->func_table = funcs.data();


	for (uint32_t i = 0; i < img->header.func_count; i++)
	{
	printf("Function#%u, Args:%u, Locals:%u, Address:%u\n", img->func_table[i].func_id, img->func_table[i].arg_count, img->func_table[i].locals_size, img->func_table[i].address);
	}

	return img;
}


void CuteAssembler::raiseError(std::string msg)
{
	std::cout << "Assembler Error: " << msg << '\n';
	std::cout << "Token: " << this->tokStream.viewToken(&this->tokStream.tokens[this->tokStream.curr_token-1]) << std::endl;
	std::cout << "Token number: " << this->tokStream.curr_token-1 << std::endl;
	std::exit(1);
}