#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	ContainerStack* tokenized_cons;
	ContainerStack* parsed_cons;
	ContainerStack* operator_stack;
	int index;
} ParserContext;

ParserContext* ParserContext_new();
void ParserContext_init(ParserContext* parser, ContainerStack* tokenized_cons);
void ParserContext_del(ParserContext* parser);

ContainerStack* ParserContext_parse(ParserContext* parser, ContainerStack* tokenized_cons);
bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2);