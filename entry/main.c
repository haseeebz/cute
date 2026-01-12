#include "CuteContainer.h"
#include "CuteIO.h"
#include "CuteLib.h"

CUTE_DYARRAY_DEF(ArrayInt, int)

void program_main()
{
	cute_ContainerManager_newBucket();

	ArrayInt* array = NULL;

	cute_ContainerManager_assign(cute_ContainerManager_new(sizeof(ArrayInt)), (cute_Container**)&array);
	ArrayInt_init(array, 10);
	ArrayInt_push(array, 10);

	cute_ContainerManager_throwBucket();
}

int main()
{
	cute_Core_run(program_main);
};