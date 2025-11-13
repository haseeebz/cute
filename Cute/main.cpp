#include "include/CuteCore.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
	int counter = 0;
	
	while (true)
	{
		counter++;
		if (counter > 1000000000) {return 0;}
	}

	CuteCore core;
	core.run(argc, argv);
}