#include "../lexer/tokens.h"
#include "../lexer/lexer.h"
#include "node.h"

#pragma once

typedef struct
{
	LexerContext* lexer;
	CuteNode* root;
} ParserContext;

ParserContext* ParserContext_new();
void ParserContext_del(ParserContext* parser);
void ParserContext_init(ParserContext* parser, char* string);


CuteNode* ParserContext_parse(ParserContext* parser);

CuteNode* ParserContext_parseExpr(ParserContext* parser, float precedence);

CuteBinaryOp ParserContext_detectOperator(char c);
float ParserContext_getPrecedence(CuteBinaryOp op);

CuteNode* ParserContext_tokenToAtom(Token* token);

int ParserContext_strToInt(char* str, int len);
double ParserContext_strToFloat(char* str, int len);


