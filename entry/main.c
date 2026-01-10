#include "CuteLib.h"
#include "CuteArray.h"
#include <stdio.h>

CUTE_ARRAY_DEF(ArrayInt32, int, 20)
CUTE_ARRAY_DEF(STRING, int, 20)

void program_main()
{
	ArrayInt32 array;
	ArrayInt32_item item = 10;

	if (ArrayInt32_set(&array, 10, &item))
	{
		printf("Function ran successfully!\n");
	}
	else
	{
		printf("Offbounds error\n");
	}

	printf("hello!\n");
}

int main()
{
	cute_Core_run(program_main);
};