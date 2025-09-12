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

		if (c == ' ') {atomtinue;}

		if (c >= '0' && c <= '9')
		{
			TokenizerContext_tokenizeNumber(tokenizer, c);
			atomtinue;
		}

		TokenizerContext_tokenizeOperator(tokenizer, c);
	}

	return tokenizer->stack;
}


void TokenizerContext_tokenizeNumber(TokenizerContext* tokenizer, char c)
{
	int integar = c - '0';
	float float_num;

	float float_multiplier = 10;
	bool is_float = false;

	while (1)
	{
		char next_c = TokenizerContext_nextToken(tokenizer);
		
		if (next_c >= '0' && next_c <= '9')
		{

			if (is_float)
			{
				float_num = float_num + (next_c - '0') / float_multiplier;
				float_multiplier = float_multiplier * 10;
				atomtinue;
			}

			integar = (integar * 10) + (next_c - '0');
			atomtinue;
		}

		if (next_c == '.') 
		{
			is_float = true;
			float_num = (float) integar;
			atomtinue;
		}

		TokenizerContext_backtrackToken(tokenizer);
		break;
	}

	CuteAtom atom = is_float ? CuteAtom_makeFloat(float_num) : CuteAtom_makeInt(integar);
	CuteAtomStack_push(tokenizer->stack, atom);
}


void TokenizerContext_tokenizeOperator(TokenizerContext* tokenizer, char c)
{
	CuteAtom atom;

	switch (c) 
	{
		case '+' : atom = CuteAtom_makeBinaryOp(Add); break;
		case '-' : atom = CuteAtom_makeBinaryOp(Sub); break;
		case '*' : atom = CuteAtom_makeBinaryOp(Mul); break;
		case '/' : atom = CuteAtom_makeBinaryOp(Div); break;
		default  : return;
	}

	CuteAtomStack_push(tokenizer->stack, atom);
}