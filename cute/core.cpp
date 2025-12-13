#include "CuteEngine.h"

#include "CuteCompiler.hpp"


#include "include/CuteCore.hpp"
#include <iostream>
#include <string>


CuteCore::CuteCore()
{
	ctEngine_init();
}


CuteCore::~CuteCore()
{
}


void CuteCore::run(int argc, char *argv[])
{
	this->parseArgs(argc, argv);

	if (this->compileFlag)
	{
		compiler.compile(this->filepath, this->outfile);
		return;
	}

	if (this->engineFlag)
	{
		ctEngine_loadImage(this->filepath.data());
		ctEngine_run();
		return;
	}
}


void CuteCore::parseArgs(int argc, char *argv[])
{
	std::string arg;
	for (int i = 1; i < argc; i++)
	{
		arg = std::string(argv[i]);

		if (arg == "-c")
		{
			this->filepath = argv[++i];
			this->outfile = std::string(this->filepath).append(".out");
			compileFlag = true;
			engineFlag = false;
			return;
		}

		if (arg == "-r")
		{
			this->filepath = argv[++i];
			
			compileFlag = false;
			engineFlag = true;
			return;
		}
		
	}
}