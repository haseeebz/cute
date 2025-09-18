#include "lexer/tokens.h"
#include <stdio.h>

int main()
{
	Token token1 = {tokenInt, 12};
	Token token2 = {tokenSymbol, '+'};
	Token token3 = {tokenInt, 10};

	TokenArray* array = TokenArray_new(10);
	
	TokenArray_push(array, token1);
	TokenArray_push(array, token2);
	TokenArray_push(array, token3);

	TokenArray_print(array);
	
	return 0;
}