#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/eval.h"


EvaluatorContext* EvaluatorContext_new()
{
	EvaluatorContext* evaluator = malloc(sizeof(EvaluatorContext));
	evaluator->result_stack = ContainerStack_new(10);
	return evaluator;
}


void EvaluatorContext_init(EvaluatorContext* evaluator, ContainerStack* parsed_cons)
{
	evaluator->parsed_cons = parsed_cons;
}


void EvaluatorContext_del(EvaluatorContext* evaluator)
{
	ContainerStack_del(evaluator->parsed_cons);

	ContainerStack_del(evaluator->result_stack);
	free(evaluator);
}


void EvaluatorContext_evaluate(EvaluatorContext* evaluator, ContainerStack* parsed_cons)
{
	EvaluatorContext_init(evaluator, parsed_cons);
	Container current;

	for (int i = 0; i < evaluator->parsed_cons->size; i++)
	{
		current = evaluator->parsed_cons->cons[i];

		if (current.type == Int)
		{
			ContainerStack_push(evaluator->result_stack, current);
			continue;
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
		case Add: result = Container_makeInt(c1.value.i + c2.value.i); break;
		case Sub: result = Container_makeInt(c1.value.i - c2.value.i); break;
		case Mul: result = Container_makeInt(c1.value.i * c2.value.i); break;
		case Div: result = Container_makeInt(c1.value.i / c2.value.i); break;
		default : return;
	}

	ContainerStack_push(evaluator->result_stack, result);
}

Container EvaluatorContext_yield(EvaluatorContext* evaluator)
{
	return ContainerStack_pop(evaluator->result_stack);
}
