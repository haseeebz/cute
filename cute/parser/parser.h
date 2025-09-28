#include "./lexer/tokens.h"
#include "./lexer/lexer.h"
#include "node.h"

#pragma once

typedef struct
{
	Lexer* lexer;
	CuteNode* root;
} Parser;

Parser* Parser_new();
void Parser_del(Parser* parser);
void Parser_init(Parser* parser, char* string);


CuteNode* Parser_parse(Parser* parser);

CuteNode* Parser_parseExpr(Parser* parser, float precedence);

CuteBinaryOp Parser_detectOperator(char c);
float Parser_getPrecedence(CuteBinaryOp op);

CuteNode* Parser_tokenToAtom(Token* token);

int Parser_strToInt(char* str, int len);
double Parser_strToFloat(char* str, int len);


