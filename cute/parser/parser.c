#include "parser.h"
#include "../atoms/atoms.h"
#include "../lexer/tokens.h"
#include "../atoms/atoms.h"
#include <stdio.h>
#include <stdlib.h>



ParserContext* ParserContext_new()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	parser->op_stack = CuteAtomStack_new(10);
	return parser;
}

void ParserContext_del(ParserContext* parser)
{
	free(parser->token_array);
	free(parser->op_stack);
	free(parser);
}

void ParserContext_init(ParserContext* parser, TokenArray* tokens)
{
	free(parser->token_array);

	parser->token_array = tokens;
	parser->index = 0;
	parser->parsed_stack = CuteAtomStack_new(tokens->size);
}


CuteAtomStack* ParserContext_parse(ParserContext* parser)
{
	while (parser->index < parser->token_array->size)
	{
		CuteAtomStack_print(parser->parsed_stack);
		CuteAtomStack_print(parser->op_stack);
		Token token = parser->token_array->tokens[parser->index];
		
		if (token.type == tokenInt)
		{
			CuteAtom atom = CuteAtom_makeInt(token.val.i);
			CuteAtomStack_push(parser->parsed_stack, atom);
			parser->index++;
			continue;
		}

		if (token.type == tokenSymbol)
		{
			while (!CuteAtomStack_isEmpty(parser->op_stack))
			{
				CuteAtom op_atom = CuteAtomStack_peek(parser->op_stack);

				if (*(CuteBinaryOp*)op_atom.val > precedence(token.val.c))
				{
					CuteAtomStack_pop(parser->op_stack);
					CuteAtomStack_push(parser->parsed_stack, op_atom);
					continue;
				}
				
				break;
			}

			CuteAtom atom = CuteAtom_makeBinaryOp(precedence(token.val.c));
			CuteAtomStack_push(parser->op_stack, atom);
			parser->index++;
			continue;
		}
	}


	while (!CuteAtomStack_isEmpty(parser->op_stack))
	{
		CuteAtom op_atom = CuteAtomStack_pop(parser->op_stack);
		CuteAtomStack_push(parser->parsed_stack, op_atom);
	}
	
	return parser->parsed_stack;
}



int precedence(char op)
{
	switch (op) 
	{
		case '+' : return 0;
		case '-' : return 1;
		case '*' : return 2;
		case '/' : return 3;
	}
	return -1;
}