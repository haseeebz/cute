#include "parser/node.h"
#include "parser/parser.h"
#include <stdio.h>

int main()
{
	Parser* parser = Parser_new();
	Parser_init(parser, "10 + 20 * 30 / 40 + 50");
	CuteNode* root = Parser_parse(parser);
	CuteNode_printRecursive(root);
	printf("\n");
	return 0;
}