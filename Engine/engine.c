#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "cuteEngine.h"

#include "atom.h"
#include "context.h"




void CuteEngine_init(CuteEngine* engine);
void CuteEngine_end(CuteEngine* engine);

void CuteEngine_exec(CuteEngine* engine, ProgramImage* program)
{
	ExecutionContext* ctx = ExecutionContext_init(program);

	Instruction instr = program->instrs[ctx->pc++];


	switch (instr) 
	{
	case instrEXIT: 
	case instrLOADi: 
	case instrSTORi: 
	case instrLCONi: 
	case instrADDi: 
	case instrSUBi: 
	case instrMULi: 
	case instrDIVi: 
	case instrOUT: 
	break;
    }
}
