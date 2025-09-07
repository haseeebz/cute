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


void EvaluatorContext_evaluate(EvaluatorContext* evaluator, ContainerStack* parsed_cons)
{
	initEvaluatorContext(evaluator, parsed_cons);
	Container current;

	for (int i = 0; i < evaluator->parsed_cons->size; i++)
	{
		current = evaluator->parsed_cons->cons[i];

		if (current.type == Int)
		{
			ContainerStack_push(evaluator->result_stack, current);
		}

		if (current.type == BinaryOp)
		{
			Container c2 = ContainerStack_pop(evaluator->result_stack);
			Container c1 = ContainerStack_pop(evaluator->result_stack);
			EvaluatorContext_evalExpr(evaluator, current, c1, c2);
		}
	}
}


void EvaluatorContext_evalExpr(EvaluatorContext* evaluator, Container op, Container c1, Container c2)
{
	Container result;

	switch (op.value.bop) 
	{
		case Add: result = newIntContainer(c1.value.i + c1.value.i); break;
		case Sub: result = newIntContainer(c1.value.i - c1.value.i); break;
		case Mul: result = newIntContainer(c1.value.i * c1.value.i); break;
		case Div: result = newIntContainer(c1.value.i / c1.value.i); break;
		default : return;
	}

	ContainerStack_push(evaluator->result_stack, result);
}

Container EvaluatorContext_yield(EvaluatorContext* evaluator)
{
	return ContainerStack_pop(evaluator->result_stack);
}
