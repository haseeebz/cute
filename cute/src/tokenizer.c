#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/atom.h"
#include "../include/tokenizer.h"



TokenizerContext* TokenizerContext_new()
{
	TokenizerContext* tokenizer = malloc(sizeof(TokenizerContext));
	return tokenizer;
}


void TokenizerContext_init(TokenizerContext* tokenizer, char* string)
{	
	tokenizer->index = 0;
	tokenizer->string_size = strlen(string);

	tokenizer->current_string = malloc(sizeof(char) * tokenizer->string_size);
	strcpy(tokenizer->current_string, string);

	tokenizer->stack = CuteAtomStack_new(tokenizer->string_size);
}


void TokenizerContext_del(TokenizerContext* tokenizer)
{
	free(tokenizer->current_string);
	free(tokenizer);
}


char TokenizerContext_nextToken(TokenizerContext* tokenizer)
{
	char c = tokenizer->current_string[tokenizer->index];
	tokenizer->index++;
	return c;
}


void TokenizerContext_backtrackToken(TokenizerContext* tokenizer)
{
	if (tokenizer->index > 0) {tokenizer->index--;}
}


CuteAtomStack* TokenizerContext_tokenize(TokenizerContext* tokenizer, char* string)
{
	TokenizerContext_init(tokenizer, string);
	
	while (tokenizer->index <= tokenizer->string_size) {

		char c = TokenizerContext_nextToken(tokenizer);

		if (c == ' ') {continue;}

		if (c >= '0' && c <= '9')
		{
			TokenizerContext_tokenizeNumber(tokenizer, c);
			continue;
		}

		TokenizerContext_tokenizeOperator(tokenizer, c);
	}

	return tokenizer->stack;
}


void TokenizerContext_tokenizeNumber(TokenizerContext* tokenizer, char c)
{
	int integar = c - '0';
	double double_num;

	double double_multiplier = 10;
	bool is_double = false;

	while (1)
	{
		char next_c = TokenizerContext_nextToken(tokenizer);
		
		if (next_c >= '0' && next_c <= '9')
		{

			if (is_double)
			{
				double_num = double_num + (next_c - '0') / double_multiplier;
				double_multiplier = double_multiplier * 10;
				continue;
			}

			integar = (integar * 10) + (next_c - '0');
			continue;
		}

		if (next_c == '.') 
		{
			is_double = true;
			double_num = (float) integar;
			continue;
		}

		TokenizerContext_backtrackToken(tokenizer);
		break;
	}

	CuteAtom atom = is_double ? CuteAtom_makeDouble(double_num) : CuteAtom_makeInt(integar);
	CuteAtomStack_push(tokenizer->stack, atom);
}


void TokenizerContext_tokenizeOperator(TokenizerContext* tokenizer, char c)
{
	CuteAtom atom;

	switch (c) 
	{
		case '+' : atom = CuteAtom_makeBinaryOp(binaryOpAdd); break;
		case '-' : atom = CuteAtom_makeBinaryOp(binaryOpSub); break;
		case '*' : atom = CuteAtom_makeBinaryOp(binaryOpMul); break;
		case '/' : atom = CuteAtom_makeBinaryOp(binaryOpDiv); break;
		default  : return;
	}

	CuteAtomStack_push(tokenizer->stack, atom);
}