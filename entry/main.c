#include "CuteContainer.h"
#include "CuteLib.h"

CUTE_DYARRAY_DEF(ArrayInt, int)

void program_main()
{
	cute_ContainerManager_newBucket();

	cute_Container* container = cute_ContainerManager_new(sizeof(cute_Container));

	if (1)
	{
		cute_ContainerManager_newBucket();
		
		container = cute_ContainerManager_new(sizeof(cute_Container));

		cute_ContainerManager_throwBucket();
	}
	
	cute_ContainerManager_throwBucket();
}

int main()
{
	cute_Core_run(program_main);
};