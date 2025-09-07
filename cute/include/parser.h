#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	ContainerStack* tokenized_cons;
	ContainerStack* parsed_cons;
	ContainerStack* operator_stack;
	int index;
} ParserContext;

ParserContext* newParserContext();
void initParserContext(ParserContext* parser, ContainerStack* tokenized_cons);
void delParserContext(ParserContext* parser);

ContainerStack* ParserContext_parse(ParserContext* parser, ContainerStack* tokenized_cons);
bool binaryOpPrecedence(BinaryOpType op1, BinaryOpType op2);