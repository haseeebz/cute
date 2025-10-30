#include "CuteCompiler.hpp"
#include "CuteByte.h"
#include "tokenizer/token.hpp"

#include <string>
#include <vector>


void CuteCompiler::compile(std::string str)
{
	tokenizer.tokenize(str);
	tokenizer.printTokens();

	std::vector<Token> tokens = tokenizer.getTokens();


	CtInstr instr;
	
	ProgramContext ctx;
	ProgramContext_init(&ctx, tokens.size()+2);

	for (Token tok: tokens)
	{
		if (tok.type == TokenType::tokenInt)
		{
			ctx.instrs[ctx.instr_count] = instrPushConstI;
			ctx.instr_count++;

			ctx.instrs[ctx.instr_count] = std::stoi(tok.str);
			ctx.instr_count++;
		}

		if (tok.type == TokenType::tokenSymbol)
		{
			switch (tok.str[0]) 
			{
				case '+' : instr = instrAddI; break;
				case '-' : instr = instrSubI; break;
				case '*' : instr = instrMulI; break;
				case '/' : instr = instrDivI; break;
			}

			ctx.instrs[ctx.instr_count] = instr;
			ctx.instr_count++;
		}
	}

	ctx.instrs[ctx.instr_count] = instrOutI;
	ctx.instr_count++;

	ctx.instrs[ctx.instr_count] = instrHalt;
	ctx.instr_count++;

	ProgramContext_write(&ctx, (char*) "file.bin");

	ProgramContext_end(&ctx);
}