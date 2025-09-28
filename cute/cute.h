#include "eval/eval.h"
#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include "parser/parser.h"

#pragma once

typedef struct
{
	Lexer* lexer;
	Parser* parser;
	EvaluatorContext* evaluator;
} CuteCore;

CuteCore* CuteCore_Init();
void CuteCore_Run(CuteCore* core);
void CuteCore_End(CuteCore* core);

void CuteCore_InvokeREPL(CuteCore* core);
