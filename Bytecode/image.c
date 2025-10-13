#include "cuteInstr.h"
#include "cuteProgImg.h"
#include <stdlib.h>


ProgramImage* ProgramImage_new()
{
	ProgramImage* program = malloc(sizeof(ProgramImage));
	program->const_count = 0;
	program->instr_count = 0;
	return program;
}

void ProgramImage_del(ProgramImage* program)
{
	free(program->instrs);
	free(program->constants);
	free(program);
}


void ProgramImage_appendInstruction(ProgramImage* program, Instruction instr)
{
	if (program->instr_count >= program->_instr_cap)
	{
		Instruction* instrs = malloc(sizeof(InstrByte) * (program->_instr_cap + 1) * 2);
		
		for (int i = 0; i < program->instr_count; i++)
		{
			instrs[i] = program->instrs[i];
		}

		free(program->instrs);
		program->instrs = instrs;
		program->_instr_cap = program->_instr_cap+1 * 2;
	}

	program->instrs[program->instr_count] = instr;
	program->instr_count++;
}


int ProgramImage_addConstant(ProgramImage* program, ProgramConst constant)
{

	if (program->const_count >= program->_const_cap)
	{
		program->_const_cap = (program->_const_cap) + 1 * 2;

		ProgramConst* constants = malloc(sizeof(ProgramConst) * program->_const_cap);
		
		for (int i = 0; i < program->instr_count; i++)
		{
			constants[i] = program->constants[i];
		}

		free(program->constants);
		program->constants = constants;
	}

	program->constants[program->const_count] = constant;
	program->const_count++;

	return program->const_count - 1;
}



int ProgramImage_addConstInt(ProgramImage* program, int32_t i)
{
	ProgramConst constant = {constInt, {.i = i}};
	return ProgramImage_addConstant(program, constant);
}


int ProgramImage_addConstFloat(ProgramImage* program, float f)
{
	ProgramConst constant = {constInt, {.f = f}};
	return ProgramImage_addConstant(program, constant);
}
