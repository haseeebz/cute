#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include <stdio.h>

int main()
{
	LexerContext* lexer = LexerContext_new();
	LexerContext_init(lexer, "10 + 12 - 090");
	TokenArray* tokens = LexerContext_tokenize(lexer);
	TokenArray_print(tokens);
	return 0;
}