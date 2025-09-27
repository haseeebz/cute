#include "tokens.h"
#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


LexerContext* LexerContext_new()
{
	LexerContext* lexer = malloc(sizeof(LexerContext));
	lexer->buffer = NULL;
	return lexer;
}


void LexerContext_del(LexerContext* lexer)
{
	free(lexer->buffer);
	free(lexer);
}


void LexerContext_init(LexerContext* lexer, char* string)
{
	lexer->length = strlen(string);

	if (lexer->buffer != NULL) {free(lexer->buffer);}

	lexer->buffer = malloc(sizeof(char)*lexer->length);
	strncpy(lexer->buffer, string, lexer->length);

	lexer->index = 0;
}


Token LexerContext_nextToken(LexerContext* lexer)
{
	Token token;
	char* c;

	while (lexer->index < lexer->length)
	{
		c = &lexer->buffer[lexer->index++];

		if (*c == ' ' || *c == '\n') {continue;}

		if (isdigit(*c)) 
		{
			token = LexerContext_tokenizeNumber(lexer, c);
		}
		else if (isalpha(*c))
		{
			token = LexerContext_tokenizeWord(lexer, c);
		}
		else 
		{
			token = Token_make(tokenSymbol, c, 1);
		}

		return token;
	}

	return Token_make(tokenEOF, NULL, 0);
}

void LexerContext_backtrack(LexerContext* lexer)
{
	if (lexer->index > 0) 
	{
		lexer->index--;
	}
}



Token LexerContext_tokenizeNumber(LexerContext* lexer, char* c)
{
	int token_length = 1;
	bool isFloat = false;			
	char* nc;
	while (lexer->index < lexer->length) 
	{
		nc = &lexer->buffer[lexer->index++];

		if (isdigit(*nc)) 
		{
			token_length++;
			continue;
		}

		if (*nc == '.')
		{
			token_length++;
			isFloat = true;
			continue;
		}
		
		lexer->index--;
		break;
	} 
	
	if (isFloat)
	{
		return Token_make(tokenFloat, c, token_length);
	}
	else
	{
		return Token_make(tokenInt, c, token_length);
	}
}



Token LexerContext_tokenizeWord(LexerContext* lexer, char* c)
{
	int token_length = 1;
	char* nc;
	while (lexer->index < lexer->length) 
	{
		nc = &lexer->buffer[lexer->index++];

		if (isalpha(*nc) || isdigit(*nc)) 
		{
			token_length++;
			continue;
		}

		lexer->index--;
		break;
	} 

	return Token_make(tokenWord, c, token_length);
}