#include "./include/containers.h"
#include "./include/tokenizer.h"
#include "./include/parser.h"
#include "include/eval.h"

#include <stdbool.h>

int main()
{
	TokenizerContext* tokenizer = newTokenizerContext();
	ParserContext* parser = newParserContext();
	EvaluatorContext* evaluator = newEvaluatorContext();

	ContainerStack* tokenized_cons = TokenizerContext_tokenize(tokenizer, "12 + 8 - 90 * 78 * 45");
	printContainerStack(tokenized_cons);
	ContainerStack* parsed_cons = ParserContext_parse(parser, tokenized_cons);
	printContainerStack(parsed_cons);
	
	EvaluatorContext_evaluate(evaluator, parsed_cons);

	Container result = EvaluatorContext_yield(evaluator);
	printContainer(&result, true);
	return 0;
}