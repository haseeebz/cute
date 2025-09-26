#include "parser.h"
#include "../lexer/tokens.h"
#include "node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



ParserContext* ParserContext_new()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	parser->lexer = LexerContext_new();
	parser->root = NULL;
	return parser;
}


void ParserContext_del(ParserContext* parser)
{
	LexerContext_del(parser->lexer);
	free(parser);
}


void ParserContext_init(ParserContext* parser, char* string)
{
	LexerContext_init(parser->lexer, string);
}


CuteNode* ParserContext_parse(ParserContext* parser)
{
	parser->root = ParserContext_parseExpr(parser, 0);
	return parser->root;
}

CuteNode* ParserContext_parseExpr(ParserContext* parser, float precedence)
{
	Token token;
	token = LexerContext_nextToken(parser->lexer);
	Token_print(&token, true);

	CuteNode* lhs;
	CuteNode* rhs;

	if (token.type == tokenEOF)
	{
		return NULL;
	}

	if (token.type == tokenInt)
	{
		lhs = CuteNode_makeInt(ParserContext_strToInt(token.str, token.len));
	}


	while (true)
	{
		CuteBinaryOp op;
		token = LexerContext_nextToken(parser->lexer);
		Token_print(&token, true);

		if (token.type == tokenEOF)
		{
			break;
		}

		if (token.type == tokenSymbol)
		{
			op = ParserContext_detectOperator(*token.str);
		}

		if (ParserContext_getPrecedence(op) < precedence) {break;}

		rhs = ParserContext_parseExpr(parser, ParserContext_getPrecedence(op));
		lhs = CuteNode_makeBinaryOp(op, lhs, rhs);
	}

	return lhs;
}


float ParserContext_getPrecedence(CuteBinaryOp op)
{
	switch (op) 
	{
		case binaryAdd : return 1;
		case binarySub : return 2;
		case binaryMul : return 3;
		case binaryDiv : return 4;
		default  : return 0; 
	}
}

CuteBinaryOp ParserContext_detectOperator(char c)
{
	switch (c) 
	{
		case '+' : return binaryAdd;
		case '-' : return binarySub;
		case '*' : return binaryMul;
		case '/' : return binaryDiv;
		default  : return -1; 
	}
}


// These functions work assuming the lexer did its job properly

int ParserContext_strToInt(char* str, int len)
{
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		num = num + (str[i] - '0');
	}
	return num;
}

double ParserContext_strToFloat(char* str, int len)
{
	double num;
	double multiplier = 10;
	bool afterPoint = false;

	for (int i = 0; i < len; i++)
	{
		if (afterPoint)
		{
			num = num + ((str[i] - '0') / multiplier);
			multiplier = multiplier * 10;
			continue;
		}

		if (str[i] == '.')
		{
			afterPoint = true;
			continue;
		}

		num = num + (str[i] - '0');
	}
	return num;
}