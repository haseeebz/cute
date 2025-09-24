#include "eval.h"
#include "../atoms/atoms.h"
#include <stdlib.h>


EvaluatorContext* EvaluatorContext_new()
{
	EvaluatorContext* evaluator = malloc(sizeof(EvaluatorContext));
	return evaluator;
}


void EvaluatorContext_del(EvaluatorContext* evaluator)
{
	free(evaluator->parsed_stack);
	free(evaluator);
}

void EvaluatorContext_init(EvaluatorContext* evaluator, CuteAtomStack* stack)
{
	free(evaluator->parsed_stack);

	evaluator->index = 0;
	evaluator->parsed_stack = stack;
}

CuteAtom EvaluatorContext_evaluate(EvaluatorContext* evaluator)
{
	CuteAtom current_atom;
	CuteAtom result_atom;	
	CuteAtom a;
	CuteAtom b;

	while (evaluator->index < evaluator->parsed_stack->size) 
	{
		current_atom = evaluator->parsed_stack->atoms[evaluator->index];
		
		switch (current_atom.type) 
		{
		case atomInt:
		case atomFloat: 
			CuteAtomStack_push(&evaluator->result_stack, current_atom);
			break;
		case atomOp:
			b = CuteAtomStack_pop(&evaluator->result_stack);
			a = CuteAtomStack_pop(&evaluator->result_stack);
			result_atom = EvaluatorContext_evalExpr(&current_atom, &a, &b);
			CuteAtomStack_push(&evaluator->result_stack, result_atom);
			break;
		default: continue;
		}
	}

	return CuteAtomStack_pop(&evaluator->result_stack);
}


CuteAtom EvaluatorContext_evalExpr(CuteAtom* op, CuteAtom* a, CuteAtom* b)
{
	int num1 = *(CuteInt*) a->val;
	int num2 = *(CuteInt*) b->val;
	int result;
	CuteAtom atom;

	switch ( *(CuteOperator*) op->val ) 
	{
	case opAdd: result = num1 + num2; break;
	case opSub: result = num1 - num2; break;
	case opMul: result = num1 * num2; break;
	case opDiv: result = num1 / num2; break;
	default: atom.type = atomVoid; return atom;
	}

	atom.type = atomInt;
	*(CuteInt*) atom.val = result;

	return atom;
}