#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/atom.h"
#include "../include/parser.h"



ParserContext* ParserContext_new()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	return parser;
}


void ParserContext_init(ParserContext* parser, CuteAtomStack* tokenized_atoms)
{
	parser->tokenized_atoms = tokenized_atoms;
	parser->parsed_atoms = CuteAtomStack_new(tokenized_atoms->size);
	parser->operator_stack = CuteAtomStack_new(tokenized_atoms->size);
	parser->index = 0;
}


void ParserContext_del(ParserContext* parser)
{
	CuteAtomStack_del(parser->operator_stack);
	free(parser);
}


CuteAtomStack* ParserContext_parse(ParserContext* parser, CuteAtomStack* tokenized_atoms)
{
	ParserContext_init(parser, tokenized_atoms);
	CuteAtom current;

	for (parser->index = 0; parser->index <= tokenized_atoms->size; parser->index++)
	{
		current = parser->tokenized_atoms->atoms[parser->index];

		if (current.type == atomInt || current.type == atomDouble)
		{
			CuteAtomStack_push(parser->parsed_atoms, current);
			continue;
		}

		if (current.type == atomBinaryOp)
		{
			while (true)
			{
				CuteAtom prev_op = CuteAtomStack_peek(parser->operator_stack);
				if (prev_op.type == atomBinaryOp && binaryOpPrecedence(prev_op.value.bop, current.value.bop))
				{
					CuteAtomStack_push(parser->parsed_atoms, CuteAtomStack_pop(parser->operator_stack));
					continue;
				}

				break;
			}

			CuteAtomStack_push(parser->operator_stack, current);
			continue;
		}
	}

	while (parser->operator_stack->size > 0) 
	{
		CuteAtom atom = CuteAtomStack_pop(parser->operator_stack);
		CuteAtomStack_push(parser->parsed_atoms, atom);
	}

	return parser->parsed_atoms;
}	


bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op1 > op2) {return true;}
	return false;
}