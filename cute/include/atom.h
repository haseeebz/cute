
#pragma once

typedef enum {
	binaryOpAdd,
	binaryOpSub,
	binaryOpMul,
	binaryOpDiv
} BinaryOpType;


typedef enum {
	atomVoid,
	atomEOL,
	atomEOF,
	atomBinaryOp,
	atomUnaryOp,
	atomInt,
	atomDouble
} AtomType;

typedef union {
	int i;
	double d;
	BinaryOpType bop;
} AtomValue;

typedef struct {
	AtomType type;
	AtomValue value;
} CuteAtom;


void CuteAtom_print(CuteAtom* atom, bool endline);

CuteAtom CuteAtom_makeVoid();
CuteAtom CuteAtom_makeInt(int i);
CuteAtom CuteAtom_makeFloat(float f);
CuteAtom CuteAtom_makeBinaryOp(BinaryOpType op);


typedef struct {
	CuteAtom* atoms;
	int size;
	int capacity;
} CuteAtomStack;

CuteAtomStack* CuteAtomStack_new(int capacity);
void CuteAtomStack_resize(CuteAtomStack* stack, int capacity);
void CuteAtomStack_push(CuteAtomStack* stack, CuteAtom atom);
CuteAtom CuteAtomStack_pop(CuteAtomStack* stack);
CuteAtom CuteAtomStack_peek(CuteAtomStack* stack);
void CuteAtomStack_del(CuteAtomStack* stack);
void CuteAtomStack_print(CuteAtomStack* stack);
