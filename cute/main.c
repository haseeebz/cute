#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include "atoms/atoms.h"
#include "parser/parser.h"
#include <stdio.h>

int main()
{
	LexerContext* lexer = LexerContext_new();
	LexerContext_init(lexer, "12 + 12 * 12");
	TokenArray* tokens = LexerContext_tokenize(lexer);

	ParserContext* parser = ParserContext_new();
	ParserContext_init(parser, tokens);
	CuteAtomStack* stack = ParserContext_parse(parser);

	CuteAtomStack_print(stack);
	return 0;
}