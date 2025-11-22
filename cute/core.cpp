#include "CuteEngine.h"

#include "CuteCompiler.hpp"

#include "CuteAsm.hpp"

#include "include/CuteCore.hpp"
#include <string>


CuteCore::CuteCore()
{
	CuteEngine_init();
}


CuteCore::~CuteCore()
{
}


void CuteCore::run(int argc, char* argv[])
{
	this->parseArgs(argc, argv);

	if (this->assembleFlag)
	{
		assembler.assemble(this->filepath, this->outfile);
		return;
	}

	if (this->compileFlag)
	{
		compiler.compile(this->filepath, this->outfile);
		return;
	}

	if (this->engineFlag)
	{
		CuteEngine_loadImage(this->filepath.data());
		CuteEngine_runMain();
		return;
	}
}


void CuteCore::parseArgs(int argc, char* argv[])
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
			return;
		}

		if (arg == "-a")
		{
			this->filepath = argv[++i];
			this->outfile = std::string(this->filepath).append(".out");
			assembleFlag = true;
			return;
		}

		if (arg == "-r")
		{
			this->filepath = argv[++i];
			
			engineFlag = true;
			return;
		}
		
	}
}