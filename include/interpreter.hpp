#include "container.hpp"
#include "tokenizer.hpp"
#include "eval.hpp"


class Interpreter
{

	Evaluator evaluator;
	Tokenizer tokenizer;

	public:

	void run();
};