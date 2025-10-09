#include "tokens.h"
#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Lexer* Lexer_new()
{
	Lexer* lexer = malloc(sizeof(Lexer));
	lexer->buffer = NULL;
	return lexer;
}


void Lexer_del(Lexer* lexer)
{
	free(lexer->buffer);
	free(lexer);
}


void Lexer_init(Lexer* lexer, char* string)
{
	lexer->length = strlen(string);

	if (lexer->buffer != NULL) {free(lexer->buffer);}

	lexer->buffer = malloc(sizeof(char)*lexer->length);
	strncpy(lexer->buffer, string, lexer->length);

	lexer->index = 0;
}


Token Lexer_nextToken(Lexer* lexer)
{
	Token token;
	char* c;

	while (lexer->index < lexer->length)
	{
		c = &lexer->buffer[lexer->index++];

		if (*c == ' ' || *c == '\n') {continue;}

		if (isdigit(*c)) 
		{
			token = Lexer_tokenizeNumber(lexer, c);
		}
		else if (isalpha(*c))
		{
			token = Lexer_tokenizeWord(lexer, c);
		}
		else 
		{
			token = Token_make(tokenSymbol, c, 1);
		}

		return token;
	}

	return Token_make(tokenEOF, NULL, 0);
}

void Lexer_backtrack(Lexer* lexer)
{
	if (lexer->index > 0) 
	{
		lexer->index--;
	}
}



Token Lexer_tokenizeNumber(Lexer* lexer, char* c)
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



Token Lexer_tokenizeWord(Lexer* lexer, char* c)
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