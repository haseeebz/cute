#include "../atoms/atoms.h"


#pragma once

typedef struct
{
	CuteAtomStack* parsed_stack;
	CuteAtomStack result_stack;
	int index;
} EvaluatorContext;


EvaluatorContext* EvaluatorContext_new();
void EvaluatorContext_del(EvaluatorContext* evaluator);
void EvaluatorContext_init(EvaluatorContext* evaluator, CuteAtomStack* stack);

CuteAtom EvaluatorContext_evaluate(EvaluatorContext* evaluator);
CuteAtom EvaluatorContext_evalExpr(CuteAtom* op, CuteAtom* a, CuteAtom* b);

CuteAtom EvaluatorContext_add(CuteAtom* a, CuteAtom* b);
CuteAtom EvaluatorContext_sub(CuteAtom* a, CuteAtom* b);
CuteAtom EvaluatorContext_mul(CuteAtom* a, CuteAtom* b);
CuteAtom EvaluatorContext_div(CuteAtom* a, CuteAtom* b);
