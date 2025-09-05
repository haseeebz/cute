#include "./include/containers.h"
#include <stdbool.h>

int main()
{
	ContainerStack* stack = newContainerStack(10);

	ContainerStack_push(stack, newIntContainer(10));
	ContainerStack_push(stack, newIntContainer(8));
	ContainerStack_push(stack, newBinaryOpContainer(Add));

	printContainerStack(stack);
	return 0;
}