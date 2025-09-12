#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/parser.h"



ParserContext* ParserContext_new()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	return parser;
}


void ParserContext_init(ParserContext* parser, ContainerStack* tokenized_cons)
{
	parser->tokenized_cons = tokenized_cons;
	parser->parsed_cons = ContainerStack_new(tokenized_cons->size);
	parser->operator_stack = ContainerStack_new(tokenized_cons->size);
	parser->index = 0;
}


void ParserContext_del(ParserContext* parser)
{
	ContainerStack_del(parser->operator_stack);
	free(parser);
}


ContainerStack* ParserContext_parse(ParserContext* parser, ContainerStack* tokenized_cons)
{
	ParserContext_init(parser, tokenized_cons);
	Container current;

	for (parser->index = 0; parser->index <= tokenized_cons->size; parser->index++)
	{
		current = parser->tokenized_cons->cons[parser->index];

		if (current.type == Int || current.type == Float)
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
		ContainerStack_push(parser->parsed_cons, con);
	}

	return parser->parsed_cons;
}	


bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op1 > op2) {return true;}
	return false;
}