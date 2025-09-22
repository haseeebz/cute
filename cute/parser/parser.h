#include "../atoms/atoms.h"
#include "../lexer/tokens.h"

#pragma once

typedef struct
{
	TokenArray* token_array;
	CuteAtomStack* parsed_stack;
	CuteAtomStack* op_stack;
	int index;
} ParserContext;

ParserContext* ParserContext_new();
void ParserContext_del(ParserContext* parser);
void ParserContext_init(ParserContext* parser, TokenArray* tokens);

CuteAtom ParserContext_tokenToAtom(Token* token);
CuteOperator ParserContext_detectOperator(char c);
CuteAtomStack* ParserContext_parse(ParserContext* parser);
int precedence(char op);