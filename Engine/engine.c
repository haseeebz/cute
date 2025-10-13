#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "cuteEngine.h"

#include "atom.h"
#include "context.h"
#include <stdint.h>




void CuteEngine_init(CuteEngine* engine)
{
	engine->program = ProgramImage_new();


	ProgramImage_addConstInt(engine->program, 10);
	ProgramImage_addConstInt(engine->program, 20);

	Instruction instrs[] =
	{
		instrLCONi,
		0,
		instrLCONi,
		1,
		instrADDi,
		instrOUT,
		instrEXIT
	};

	for (int i = 0; i < sizeof(instrs)/sizeof(instrs[0]); i++)
	{
		ProgramImage_appendInstr(engine->program, instrs[i]);
	}
}


void CuteEngine_end(CuteEngine* engine)
{
	ProgramImage_del(engine->program);
}


void CuteEngine_exec(CuteEngine* engine)
{
	ExecutionContext ctx;
	ExecutionContext_init(&ctx);

	ProgramImage* program = engine->program;

	while (true)
	{

	Instruction instr = program->instrs[ctx.pc++];
	int32_t p;
	int32_t i;
	int32_t i1;
	int32_t i2;
	


	switch (instr) 
	{

	case instrEXIT: 
		ExecutionContext_end(&ctx);
		return;
		
	case instrLOADi: 
	case instrSTORi: 
	case instrLCONi: 
		p = program->instrs[ctx.pc++];
		i = program->constants[p].val.i;
		ExecutionStack_pushAtom(&ctx.exestack, (Atom) {atomInt, {.i = i}});
		break;
	
	case instrADDi:
		i = ExecutionStack_popAtom(&ctx.exestack).val.i;
		i = i + ExecutionStack_popAtom(&ctx.exestack).val.i;
		ExecutionStack_pushAtom(&ctx.exestack, (Atom) {atomInt, {.i = i}});
		break;
	case instrSUBi: 
	case instrMULi: 
	case instrDIVi: 
	case instrOUT: 
		i = ExecutionStack_popAtom(&ctx.exestack).val.i;
		printf("%d\n", i);
		break;
    }

	}
}
