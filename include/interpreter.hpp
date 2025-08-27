#include "container.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "eval.hpp"


class Interpreter
{

	Evaluator evaluator;
	Tokenizer tokenizer;
	Parser parser;

	public:

	void run();
};