#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/parser.h"



ParserContext* newParserContext()
{
	ParserContext* parser = malloc(sizeof(ParserContext));
	return parser;
}


void initParserContext(ParserContext* parser, ContainerStack* tokenized_cons)
{
	parser->tokenized_cons = tokenized_cons;
	parser->parsed_cons = newContainerStack(tokenized_cons->size);
	parser->operator_stack = newContainerStack(tokenized_cons->size);
	parser->index = 0;
}


void delParserContext(ParserContext* parser)
{
	delContainerStack(parser->operator_stack);
	// These two will be freed by the interpreter, but just in case.
	delContainerStack(parser->parsed_cons);
	delContainerStack(parser->tokenized_cons);

	free(parser);
}

