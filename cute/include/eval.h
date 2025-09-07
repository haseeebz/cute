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