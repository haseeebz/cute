#include <stdbool.h>
#include "atom.h"

#pragma once

typedef struct {
	CuteAtomStack* tokenized_atoms;
	CuteAtomStack* parsed_atoms;
	CuteAtomStack* operator_stack;
	int index;
} ParserContext;

ParserContext* ParserContext_new();
void ParserContext_init(ParserContext* parser, CuteAtomStack* tokenized_atoms);
void ParserContext_del(ParserContext* parser);

CuteAtomStack* ParserContext_parse(ParserContext* parser, CuteAtomStack* tokenized_atoms);
bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2);