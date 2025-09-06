#include "./include/containers.h"
#include "./include/tokenizer.h"
#include <stdbool.h>

int main()
{
	TokenizerContext* tokenizer = newTokenizerContext();
	ContainerStack* stack = tokenize(tokenizer, "12+14/900");
	printContainerStack(stack);
	return 0;
}