#include <stdbool.h>
#include "atom.h"

#pragma once

typedef struct {
	CuteAtomStack* parsed_atoms;
	CuteAtomStack* result_stack;
} EvaluatorContext;

EvaluatorContext* EvaluatorContext_new();
void EvaluatorContext_init(EvaluatorContext* evaluator, CuteAtomStack* parsed_atoms);
void EvaluatorContext_del(EvaluatorContext* evaluator);

void EvaluatorContext_evaluate(EvaluatorContext* evaluator, CuteAtomStack* parsed_atoms);
void EvaluatorContext_evalExpr(EvaluatorContext* evaluator, CuteAtom op, CuteAtom c1, CuteAtom c2);
CuteAtom EvaluatorContext_yield(EvaluatorContext* evaluator);

CuteAtom addAtoms(CuteAtom* a, CuteAtom* b);
CuteAtom subAtoms(CuteAtom* a, CuteAtom* b);
CuteAtom mulAtoms(CuteAtom* a, CuteAtom* b);
CuteAtom divAtoms(CuteAtom* a, CuteAtom* b);
