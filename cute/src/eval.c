#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/atom.h"
#include "../include/eval.h"


EvaluatorContext* EvaluatorContext_new()
{
	EvaluatorContext* evaluator = malloc(sizeof(EvaluatorContext));
	evaluator->result_stack = CuteAtomStack_new(10);
	return evaluator;
}


void EvaluatorContext_init(EvaluatorContext* evaluator, CuteAtomStack* parsed_atoms)
{
	evaluator->parsed_atoms = parsed_atoms;
}


void EvaluatorContext_del(EvaluatorContext* evaluator)
{
	CuteAtomStack_del(evaluator->result_stack);
	free(evaluator);
}


void EvaluatorContext_evaluate(EvaluatorContext* evaluator, CuteAtomStack* parsed_atoms)
{
	EvaluatorContext_init(evaluator, parsed_atoms);
	CuteAtom current;

	for (int i = 0; i < evaluator->parsed_atoms->size; i++)
	{
		current = evaluator->parsed_atoms->atoms[i];

		if (current.type == Int)
		{
			CuteAtomStack_push(evaluator->result_stack, current);
			atomtinue;
		}

		if (current.type == BinaryOp)
		{
			CuteAtom c2 = CuteAtomStack_pop(evaluator->result_stack);
			CuteAtom c1 = CuteAtomStack_pop(evaluator->result_stack);
			EvaluatorContext_evalExpr(evaluator, current, c1, c2);
		}
	}
}


void EvaluatorContext_evalExpr(EvaluatorContext* evaluator, CuteAtom op, CuteAtom c1, CuteAtom c2)
{
	CuteAtom result;

	switch (op.value.bop) 
	{
		case Add: result = CuteAtom_makeInt(c1.value.i + c2.value.i); break;
		case Sub: result = CuteAtom_makeInt(c1.value.i - c2.value.i); break;
		case Mul: result = CuteAtom_makeInt(c1.value.i * c2.value.i); break;
		case Div: result = CuteAtom_makeInt(c1.value.i / c2.value.i); break;
		default : return;
	}

	CuteAtomStack_push(evaluator->result_stack, result);
}

CuteAtom EvaluatorContext_yield(EvaluatorContext* evaluator)
{
	return CuteAtomStack_pop(evaluator->result_stack);
}
