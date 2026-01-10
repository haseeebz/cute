#include "CuteLib.h"

CUTE_DYARRAY_DEF(ArrayInt, int)

void program_main()
{
	ArrayInt array;
	ArrayInt_init(&array, 3);

	ArrayInt_push(&array, 1);
	ArrayInt_push(&array, 2);
	ArrayInt_push(&array, 3);
	ArrayInt_push(&array, 4);
	ArrayInt_push(&array, 3);
	ArrayInt_push(&array, 4);
	ArrayInt_push(&array, 3);
	ArrayInt_push(&array, 4);
	ArrayInt_push(&array, 3);
	ArrayInt_push(&array, 4);
	ArrayInt_push(&array, 3);
	ArrayInt_push(&array, 1000);

	for (size_t i = 0; i < array.size; i++) {printf("%d\n", array.items[i]);} printf("\n");

	ArrayInt_set(&array, 1, 10);

	for (size_t i = 0; i < array.size; i++) {printf("%d\n", array.items[i]);} printf("\n");
}

int main()
{
	cute_Core_run(program_main);
};