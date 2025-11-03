#include "CuteEngine.h"

#include "CuteCompiler.hpp"

#include "include/CuteCore.hpp"
#include <iostream>
#include <string>


CuteCore::CuteCore()
{
	CuteEngine_init(&this->engine);
}


CuteCore::~CuteCore()
{
	CuteEngine_end(&this->engine);
}


void CuteCore::run(int argc, char* argv[])
{
	this->parseArgs(argc, argv);

	if (this->compileFlag)
	{
		compiler.compile(this->filepath, this->outfile);
		std::cout << "Code successfully compiled to " << this->outfile << std::endl;
		return;
	}

	if (this->engineFlag)
	{
		std::cout << "Running file: " << this->filepath << "\nOutput:\n";
		CuteEngine_run(&this->engine, this->filepath.data());
		return;
	}
}


void CuteCore::parseArgs(int argc, char* argv[])
{
	std::string arg;
	for (int i = 1; i < argc; i++)
	{
		arg = std::string(argv[i]);

		if (arg == "--compile")
		{
			this->filepath = argv[++i];
			std::cout << "Source: " << this->filepath << std::endl;
			this->outfile = std::string(this->filepath).append(".out");
			std::cout << "Output: " << this->outfile << std::endl;
			compileFlag = true;
			return;
		}

		if (arg == "--run")
		{
			this->filepath = argv[++i];
			
			engineFlag = true;
			return;
		}
		
	}
}