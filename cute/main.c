#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include "parser/atoms.h"
#include <stdio.h>

int main()
{
	CuteAtomStack* stack = CuteAtomStack_new(10);
	CuteAtom atom = {Int, {10}};
	CuteAtomStack_push(stack, atom);
	CuteAtom atom2 = {BinaryOp, {'+'}};
	CuteAtomStack_push(stack, atom2);
	CuteAtomStack_print(stack);
	return 0;
}