
#pragma once

typedef enum
{
	atomInt,
	atomFloat,
} CuteAtomType;


typedef struct
{
	CuteAtomType type;
	union
	{
		int i;
		double d;
	} val;
} CuteAtom;



typedef enum 
{
	binaryAdd,
	binarySub,
	binaryMul,
	binaryDiv
} CuteBinaryOp;



typedef enum
{
	nodeAtom,
	nodeBinaryOp,
} CuteNodeType;


struct CuteNode
{
	CuteNodeType type;
	union 
	{
		CuteAtom atom;
		struct {
			CuteBinaryOp op;
			struct CuteNode* lc;
			struct CuteNode* rc;
		} biop;
	} val;
};

typedef struct CuteNode CuteNode;


CuteNode* CuteNode_makeInt(int i);
CuteNode* CuteNode_makeFloat(double d);
CuteNode* CuteNode_makeBinaryOp(CuteBinaryOp op, CuteNode* lc, CuteNode* rc);

void CuteNode_printRecursive(CuteNode* node);
void CuteNode_delRecursive(CuteNode* root);