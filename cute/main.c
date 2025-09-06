#include "./include/containers.h"
#include "./include/tokenizer.h"
#include "./include/parser.h"

#include <stdbool.h>

int main()
{
	TokenizerContext* tokenizer = newTokenizerContext();
	ParserContext* parser = newParserContext();
	ContainerStack* stack = tokenize(tokenizer, "2 + 2 * 3");
	printContainerStack(stack);
	ContainerStack* parsed_stack = parse(parser, stack);
	printContainerStack(parsed_stack);
	return 0;
}