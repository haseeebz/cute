#include "container.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "eval.hpp"


class Interpreter
{

	Evaluator evaluator;
	Tokenizer tokenizer;
	Parser parser;
	
	void interpretString(std::string expr);
	void interpretFile();
	void interpretREPL();
	void printResult();
	
	public:

	void run(int argc, char* args[]);
};