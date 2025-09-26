#include "node.h"
#include <stdio.h>
#include <stdlib.h>


CuteNode* CuteNode_makeInt(int i)
{
	CuteNode* node = malloc(sizeof(CuteNode));
	node->type = nodeAtom;
	node->val.atom.type = atomInt;
	node->val.atom.val.i = i;
	return node;
}

CuteNode* CuteNode_makeFloat(double d)
{
	CuteNode* node = malloc(sizeof(CuteNode));
	node->type = nodeAtom;
	node->val.atom.type = atomFloat;
	node->val.atom.val.d = d;
	return node;
}

CuteNode* CuteNode_makeBinaryOp(CuteBinaryOp op, CuteNode* lc, CuteNode* rc)
{
	CuteNode* node = malloc(sizeof(CuteNode));
	node->type = nodeBinaryOp;
	node->val.biop.op = op;
	node->val.biop.lc = lc;
	node->val.biop.rc = rc;
	return node;
}


void CuteNode_printRecursive(CuteNode* node)
{

	if (node->type == nodeAtom)
	{

		switch (node->val.atom.type) 
		{
		case atomInt  : printf(" %d ", node->val.atom.val.i); break;
		case atomFloat: printf(" %lf ", node->val.atom.val.d); break;
		}

	}
	else if (node->type == nodeBinaryOp)
	{
		printf("( Op%d ", node->val.biop.op);
		CuteNode_printRecursive(node->val.biop.lc);
		CuteNode_printRecursive(node->val.biop.rc);
		printf(")");
	}

}

