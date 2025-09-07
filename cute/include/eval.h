#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	ContainerStack* parsed_cons;
	ContainerStack* result_stack;
} EvaluatorContext;

EvaluatorContext* newEvaluatorContext();
void initEvaluatorContext(EvaluatorContext* evaluator, ContainerStack* parsed_cons);
void delEvaluatorContext(EvaluatorContext* evaluator);

void EvaluatorContext_evaluate(EvaluatorContext* evaluator, ContainerStack* parsed_cons);
void EvaluatorContext_evalExpr(EvaluatorContext* evaluator, Container op, Container c1, Container c2);
Container EvaluatorContext_yield(EvaluatorContext* evaluator);