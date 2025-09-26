#include "parser/node.h"
#include "parser/parser.h"

int main()
{
	ParserContext* parser = ParserContext_new();
	ParserContext_init(parser, "110 + 10");
	CuteNode* root = ParserContext_parse(parser);
	CuteNode_printRecursive(root);
	return 0;
}