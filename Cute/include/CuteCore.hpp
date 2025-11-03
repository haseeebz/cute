#include "CuteEngine.h"

#include "CuteCompiler.hpp"


class CuteCore
{
	CuteCompiler compiler;
	CuteEngine engine;

	void parseArgs(int argc, char* argv[]);

	bool compileFlag;
	bool engineFlag;

	std::string filepath;
	std::string outfile;
	
	public:

	CuteCore();
	~CuteCore();

	void run(int argc, char* argv[]);
};