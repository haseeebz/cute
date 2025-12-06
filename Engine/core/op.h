
#pragma once

#define mCtBinaryOp(type, atom1, atom2, op, ctx) \
atom2 = ctx_popExeAtom(ctx); \
atom1 = ctx_popExeAtom(ctx); \
atom1.type = atom1.type op atom2.type; \
ctx_pushExeAtom(ctx,atom1);

#define mCtCmpOp(type, atom1, atom2, ctx) \
atom2 = ctx_popExeAtom(ctx); \
atom1 = ctx_popExeAtom(ctx); \
if (atom1.type > atom2.type) {atom1.i64 = 1;} \
else if (atom1.type < atom2.type) {atom1.i64 = -1;} \
else {atom1.i64 = 0;} \
ctx_pushExeAtom(ctx, atom1);


