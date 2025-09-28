#include "parser.h"
#include "../lexer/tokens.h"
#include "../lexer/lexer.h"
#include "node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



Parser* Parser_new()
{
	Parser* parser = malloc(sizeof(Parser));
	parser->lexer = Lexer_new();
	parser->root = NULL;
	return parser;
}


void Parser_del(Parser* parser)
{
	Lexer_del(parser->lexer);
	free(parser);
}


void Parser_init(Parser* parser, char* string)
{
	Lexer_init(parser->lexer, string);
}


CuteNode* Parser_parse(Parser* parser)
{
	parser->root = Parser_parseExpr(parser, 0);
	return parser->root;
}

CuteNode* Parser_parseExpr(Parser* parser, float precedence)
{
	Token token;
	CuteNode* lhs;
	
	token = Lexer_nextToken(parser->lexer);

	lhs = Parser_tokenToAtom(&token);

	while (true)
	{
		CuteNode* rhs;

		token = Lexer_nextToken(parser->lexer);

		if (token.type == tokenEOF) {break;}

		CuteBinaryOp optype = Parser_detectOperator(*token.str);
		float current_precedence = Parser_getPrecedence(optype);

		if (current_precedence < precedence) 
		{
			Lexer_backtrack(parser->lexer);
			break;
		}
		
		rhs = Parser_parseExpr(parser, current_precedence);
		lhs = CuteNode_makeBinaryOp(optype, lhs, rhs);
	}
	return lhs;
}


float Parser_getPrecedence(CuteBinaryOp op)
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

CuteBinaryOp Parser_detectOperator(char c)
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

CuteNode* Parser_tokenToAtom(Token* token)
{
	if (token->type == tokenInt)
	{
		return CuteNode_makeInt(Parser_strToInt(token->str, token->len));
	}
	else if (token->type == tokenFloat) 
	{
		return CuteNode_makeFloat(Parser_strToFloat(token->str, token->len));
	}
	else
	{
		printf("Invalid Syntax: Expected atom");
		exit(1);
	}
}


// These functions work assuming the lexer did its job properly

int Parser_strToInt(char* str, int len)
{
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		num = (num * 10) + (str[i] - '0');
	}
	return num;
}

double Parser_strToFloat(char* str, int len)
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

		num = (num * 10) + (str[i] - '0');
	}
	return num;
}