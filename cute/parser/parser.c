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


CuteAtom ParserContext_tokenToAtom(Token* token)
{
	if (token->type == tokenInt)
	{
		return CuteAtom_makeInt(token->val.i);
	}
	else if (token->type == tokenFloat)
	{
		return CuteAtom_makeFloat(token->val.d);
	} 
	else if (token->type == tokenSymbol)
	{
		CuteOperator op = ParserContext_detectOperator(token->val.c);
		return CuteAtom_makeOperator(op);
	}

	return CuteAtom_makeVoid();
}


CuteOperator ParserContext_detectOperator(char c)
{
	switch (c) 
	{
		case '+' : return opAdd;
		case '-' : return opSub;
		case '*' : return opMul;
		case '/' : return opDiv;
	}
	return -1;
}


CuteAtomStack* ParserContext_parse(ParserContext* parser)
{
	while (parser->index < parser->token_array->size)
	{
		Token token = parser->token_array->tokens[parser->index];
		CuteAtom atom = ParserContext_tokenToAtom(&token);

		if (atom.type == atomInt)
		{
			CuteAtomStack_push(parser->parsed_stack, atom);
			parser->index++;
			continue;
		}

		if (atom.type == atomOp)
		{
			while (!CuteAtomStack_isEmpty(parser->op_stack))
			{
				CuteAtom op_atom = CuteAtomStack_peek(parser->op_stack);

				if (op_atom.val.op > precedence(token.val.c))
				{
					CuteAtomStack_pop(parser->op_stack);
					CuteAtomStack_push(parser->parsed_stack, op_atom);
					continue;
				}
				
				break;
			}

			CuteAtomStack_push(parser->op_stack, atom);
			parser->index++;
			continue;
		}

		parser->index++;
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