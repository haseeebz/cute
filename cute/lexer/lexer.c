#include "tokens.h"
#include "lexer.h"
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
			int i;
			
		}
	}
}

