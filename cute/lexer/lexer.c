#include "tokens.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


LexerContext* LexerContext_new()
{
	LexerContext* lexer = malloc(sizeof(LexerContext));
	lexer->curr_str = NULL;
	return lexer;
}


void LexerContext_del(LexerContext* lexer)
{
	free(lexer->curr_str);
	free(lexer);
}

void LexerContext_init(LexerContext* lexer, char* string)
{
	lexer->len_str = strlen(string);

	if (lexer->curr_str != NULL) {free(lexer->curr_str);}

	lexer->curr_str = malloc(sizeof(char)*lexer->len_str);
	strncpy(lexer->curr_str, string, lexer->len_str);

	lexer->index = 0;
	lexer->token_array = TokenArray_new(lexer->len_str);
}



char LexerContext_nextChar(LexerContext* lexer)
{
	if (lexer->index > lexer->len_str) {return '\0';}
	char c = lexer->curr_str[lexer->index];
	lexer->index++;
	return c;
}

void LexerContext_backtrack(LexerContext* lexer)
{
	lexer->index--;
}


TokenArray* LexerContext_tokenize(LexerContext* lexer)
{
	char c;
	while (lexer->index < lexer->len_str)
	{
		c = LexerContext_nextChar(lexer);

		if (c == ' ') {continue;}

		if (c >= '0' && c <= '9') 
		{
			LexerContext_tokenizeNumber(lexer, c);
			continue;
		}

		Token token = {tokenSymbol, {c}};
		TokenArray_push(lexer->token_array, token);
	}

	return lexer->token_array;
}


void LexerContext_tokenizeNumber(LexerContext* lexer, char c)
{
	int i = c - '0';
			
	while (true) 
	{
		c = LexerContext_nextChar(lexer);
		if (c >= '0' && c <= '9') 
		{
			i = (i*10) + (c - '0');
			continue;
		}

		LexerContext_backtrack(lexer);
		break;
	} 

	Token token = {tokenInt, {i}};
	TokenArray_push(lexer->token_array, token);
}