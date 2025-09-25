#include "eval.h"
#include "../atoms/atoms.h"
#include <stdbool.h>
#include <stdlib.h>


EvaluatorContext* EvaluatorContext_new()
{
	EvaluatorContext* evaluator = malloc(sizeof(EvaluatorContext));
	evaluator->result_stack = *(CuteAtomStack_new(10));
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

	while (evaluator->index <= evaluator->parsed_stack->size) 
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
		default: break;
		}

		evaluator->index++;
	}

	return CuteAtomStack_pop(&evaluator->result_stack);
}


CuteAtom EvaluatorContext_evalExpr(CuteAtom* op, CuteAtom* a, CuteAtom* b)
{

	CuteAtom atom;

	switch ( op->val.op ) 
	{
	case opAdd: atom = EvaluatorContext_add(a, b); break;
	case opSub: atom = EvaluatorContext_sub(a, b); break;
	case opMul: atom = EvaluatorContext_mul(a, b); break;
	case opDiv: atom = EvaluatorContext_div(a, b); break;
	default: atom.type = atomVoid; return atom;
	}

	return atom;
}


CuteAtom EvaluatorContext_add(CuteAtom* a, CuteAtom* b)
{
	if (a->type == atomFloat || b->type == atomFloat)
	{
		return CuteAtom_makeFloat(a->val.f + b->val.f);
	}
	return CuteAtom_makeInt(a->val.i + b->val.i);
}

CuteAtom EvaluatorContext_sub(CuteAtom* a, CuteAtom* b)
{
	if (a->type == atomFloat || b->type == atomFloat)
	{
		return CuteAtom_makeFloat(a->val.f - b->val.f);
	}
	return CuteAtom_makeInt(a->val.i - b->val.i);
}


CuteAtom EvaluatorContext_mul(CuteAtom* a, CuteAtom* b)
{
	if (a->type == atomFloat || b->type == atomFloat)
	{
		return CuteAtom_makeFloat(a->val.f * b->val.f);
	}
	return CuteAtom_makeInt(a->val.i / b->val.i);
}


CuteAtom EvaluatorContext_div(CuteAtom* a, CuteAtom* b)
{
	if (a->type == atomFloat || b->type == atomFloat)
	{
		return CuteAtom_makeFloat(a->val.f * b->val.f);
	}
	return CuteAtom_makeFloat(a->val.i / (double) b->val.i);
}