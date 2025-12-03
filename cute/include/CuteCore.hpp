#include "CuteEngine.h"

#include "CuteAsm.hpp"
#include "CuteCompiler.hpp"


class CuteCore
{
	CuteCompiler compiler;
	CuteEngine engine;
	CuteAssembler assembler;

	void parseArgs(int argc, char *argv[]);

	bool compileFlag;
	bool assembleFlag;
	bool engineFlag;

	std::string filepath;
	std::string outfile;
	
	public:

	CuteCore();
	~CuteCore();

	void run(int argc, char *argv[]);
};