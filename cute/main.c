#include "./include/containers.h"
#include <stdbool.h>

int main()
{
	Container con = newBinaryOpContainer(Sub);
	printContainer(&con, true);
	return 0;
}