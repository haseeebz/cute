#include "./include/containers.h"
#include "./include/tokenizer.h"
#include <stdbool.h>

int main()
{
	ContainerStack* stack = tokenize("12 14 900");
	printContainerStack(stack);
	return 0;
}