#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/eval.h"


EvaluatorContext* newEvaluatorContext()
{
	EvaluatorContext* evaluator = malloc(sizeof(EvaluatorContext));
	evaluator->result_stack = newContainerStack(10);
	return evaluator;
}


void initEvaluatorContext(EvaluatorContext* evaluator, ContainerStack* parsed_cons)
{
	evaluator->parsed_cons = parsed_cons;
}


void delEvaluatorContext(EvaluatorContext* evaluator)
{
	delContainerStack(evaluator->parsed_cons);

	delContainerStack(evaluator->result_stack);
	free(evaluator);
}

