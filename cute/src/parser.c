#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/parser.h"



ParserContext* newParserContext()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	return parser;
}


void initParserContext(ParserContext* parser, ContainerStack* tokenized_cons)
{
	parser->tokenized_cons = tokenized_cons;
	parser->parsed_cons = newContainerStack(tokenized_cons->size);
	parser->operator_stack = newContainerStack(tokenized_cons->size);
	parser->index = 0;
}


void delParserContext(ParserContext* parser)
{
	delContainerStack(parser->operator_stack);
	// These two will be freed by the interpreter, but just in case.
	delContainerStack(parser->parsed_cons);
	delContainerStack(parser->tokenized_cons);

	free(parser);
}


ContainerStack* parse(ParserContext* parser, ContainerStack* tokenized_cons)
{
	initParserContext(parser, tokenized_cons);
	Container current;

	for (parser->index = 0; parser->index <= tokenized_cons->size; parser->index++)
	{
		current = parser->tokenized_cons->cons[parser->index];

		if (current.type == Int)
		{
			ContainerStack_push(parser->parsed_cons, current);
			continue;
		}

		if (current.type == BinaryOp)
		{
			while (true)
			{
				Container prev_op = ContainerStack_peek(parser->operator_stack);
				if (prev_op.type == BinaryOp && binaryOpPrecedence(prev_op.value.bop, current.value.bop))
				{
					ContainerStack_push(parser->parsed_cons, ContainerStack_pop(parser->operator_stack));
					continue;
				}

				break;
			}

			ContainerStack_push(parser->operator_stack, current);
			continue;
		}
	}

	while (parser->operator_stack->size > 0) 
	{
		Container con = ContainerStack_pop(parser->operator_stack);
		printContainer(&con, true);
		ContainerStack_push(parser->parsed_cons, con);
	}

	return parser->parsed_cons;
}	


bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op1 > op2) {return true;}
	return false;
}