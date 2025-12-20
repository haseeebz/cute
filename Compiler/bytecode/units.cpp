#include "CuteByte.h"
#include <cstdint>
#include <map>

#include "gen.hpp"




void CtCodeGen::AddOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrAddI32; break;
        case CtCodeGen::OpType::i64: instr = instrAddI64; break;
        case CtCodeGen::OpType::u32: instr = instrAddI32; break; // unsigned treated same
        case CtCodeGen::OpType::u64: instr = instrAddI64; break;
        case CtCodeGen::OpType::f32: instr = instrAddF32; break;
        case CtCodeGen::OpType::f64: instr = instrAddF64; break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::SubOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrSubI32; break;
        case CtCodeGen::OpType::i64: instr = instrSubI64; break;
        case CtCodeGen::OpType::u32: instr = instrSubI32; break;
        case CtCodeGen::OpType::u64: instr = instrSubI64; break;
        case CtCodeGen::OpType::f32: instr = instrSubF32; break;
        case CtCodeGen::OpType::f64: instr = instrSubF64; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::MulOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrMulI32; break;
        case CtCodeGen::OpType::i64: instr = instrMulI64; break;
        case CtCodeGen::OpType::u32: instr = instrMulI32; break;
        case CtCodeGen::OpType::u64: instr = instrMulI64; break;
        case CtCodeGen::OpType::f32: instr = instrMulF32; break;
        case CtCodeGen::OpType::f64: instr = instrMulF64; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::DivOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrDivI32; break;
        case CtCodeGen::OpType::i64: instr = instrDivI64; break;
        case CtCodeGen::OpType::u32: instr = instrDivU32; break;
        case CtCodeGen::OpType::u64: instr = instrDivU64; break;
        case CtCodeGen::OpType::f32: instr = instrDivF32; break;
        case CtCodeGen::OpType::f64: instr = instrDivF64; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::ModOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrModI32; break;
        case CtCodeGen::OpType::u32: instr = instrModU32; break;
        case CtCodeGen::OpType::i64: instr = instrModI64; break;
        case CtCodeGen::OpType::u64: instr = instrModU64; break;
        default: return;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::LogicOp::emit(CtBytecodeWriter* writer)
{
	ctInstr instr;

	switch (this->logic_type)
	{
        case LogicOpType::And:  instr = instrLogicAnd; break;
        case LogicOpType::Or:   instr = instrLogicOr; break;
        case LogicOpType::Not:  instr = instrLogicNot; break;
        case LogicOpType::Xor:  instr = instrLogicXor; break;
		break;
	}

	writer->writebackInstr(instr);
}


void CtCodeGen::BitWiseOp::emit(CtBytecodeWriter* writer)
{
	ctInstr instr;

	switch (this->bitwise_type)
	{
        case BitwiseOpType::And:         instr = instrBitAnd; break;
        case BitwiseOpType::Or:			 instr = instrBitOr; break;
        case BitwiseOpType::Not:		 instr = instrBitNot; break;
        case BitwiseOpType::Xor:   		 instr = instrBitXor; break;
        case BitwiseOpType::LShift:      instr = instrBitLShift; break;
        case BitwiseOpType::RShift:      instr = instrBitRShift; break;
        case BitwiseOpType::RaShift:     instr = instrBitRaShift; break;
        case BitwiseOpType::RShift32:    instr = instrBitRShift32; break;
        case BitwiseOpType::RaShift32:   instr = instrBitRaShift32; break;
		break;
	}

	writer->writebackInstr(instr);
}


void CtCodeGen::CmpOp::emit(CtBytecodeWriter* writer)
{
	ctInstr instr;

	switch (this->op_type)
	{
        case OpType::i32:	instr = instrCmpI32; break;
        case OpType::i64:   instr = instrCmpI64; break;
        case OpType::u32:   instr = instrCmpI32; break; // FIX, we need CmpU32
        case OpType::u64:   instr = instrCmpI64; break;
        case OpType::f32:   instr = instrCmpF32; break;
        case OpType::f64:   instr = instrCmpF64; break;
	}

	writer->writebackInstr(instr);

	switch (this->cmp_type)
	{
        case CmpType::Eq:	instr = instrCmp2BoolEq; break;
        case CmpType::Ue:	instr = instrCmp2BoolNe; break;
        case CmpType::Gt:	instr = instrCmp2BoolGt; break;
        case CmpType::Ge:	instr = instrCmp2BoolGe; break;
        case CmpType::Lt:	instr = instrCmp2BoolLt; break;
        case CmpType::Le:	instr = instrCmp2BoolLe; break;
	}

	writer->writebackInstr(instr);
}


void CtCodeGen::LoadConstOp::emit(CtBytecodeWriter* writer)
{
	ctInstrSize packed[4];


	switch (this->op_type)
	{
        case OpType::i32:	
        case OpType::u32:	
		writer->writebackInstr(instrLoadCoI32);
		break;
        case OpType::f32:
		writer->writebackInstr(instrLoadCoF32);
		break;
		
		case OpType::i64:
		case OpType::u64:
		writer->writebackInstr(instrLoadCoI64);
		break;
        case OpType::f64:
		writer->writebackInstr(instrLoadCoF64);
		break;
	}

	switch (this->op_type)
	{
        case OpType::i32:	
        case OpType::u32:	
        case OpType::f32:
		ctProgramImage_packInt32((int32_t*) &this->i32, packed);
		break;
		
		case OpType::i64:
		case OpType::u64:
        case OpType::f64:
		ctProgramImage_packInt64((int64_t*) &this->i64, packed);
		break;
	}

	writer->writebackMultipleInstr(packed, 4);
}


void CtCodeGen::LoadOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrLoadI32; break;
        case CtCodeGen::OpType::i64: instr = instrLoadI64; break;
        case CtCodeGen::OpType::f32: instr = instrLoadF32; break;
        case CtCodeGen::OpType::f64: instr = instrLoadF64; break;
		default:                     instr = instrLoadI64; break;
    }

    writer->writebackInstr(instr);

	ctInstrSize packed[4];
	ctProgramImage_packInt32( (int32_t*) &this->index, packed);
	writer->writebackMultipleInstr(packed, 4);
	
}


void CtCodeGen::StoreOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrStoreI32; break;
        case CtCodeGen::OpType::i64: instr = instrStoreI64; break;
        case CtCodeGen::OpType::f32: instr = instrStoreF32; break;
        case CtCodeGen::OpType::f64: instr = instrStoreF64; break;
		default:                     instr = instrStoreI64; break;
    }

    writer->writebackInstr(instr);

	ctInstrSize packed[4];
	ctProgramImage_packInt32( (int32_t*) &this->index, packed);
	writer->writebackMultipleInstr(packed, 4);
}


void CtCodeGen::CopyOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::i32: instr = instrCopyI32; break;
        case CtCodeGen::OpType::i64: instr = instrCopyI64; break;
        case CtCodeGen::OpType::f32: instr = instrCopyF32; break;
        case CtCodeGen::OpType::f64: instr = instrCopyF64; break;
		default:                     instr = instrCopyI64; break;
    }

    writer->writebackInstr(instr);


	ctInstrSize packed[4];
	ctProgramImage_packInt32( (int32_t*) &this->src, packed);
	writer->writebackMultipleInstr(packed, 4);

	ctProgramImage_packInt32( (int32_t*) &this->dest, packed);
	writer->writebackMultipleInstr(packed, 4);
}


void CtCodeGen::TypeCastOp::emit(CtBytecodeWriter* writer)
{
	static const std::map<std::pair<CtCodeGen::OpType, CtCodeGen::OpType>, ctInstr> instr_map
	{
		{{CtCodeGen::OpType::f32, CtCodeGen::OpType::i32}, instrF32I32},
		{{CtCodeGen::OpType::i32, CtCodeGen::OpType::f32}, instrI32F32},

		{{CtCodeGen::OpType::f64, CtCodeGen::OpType::i64}, instrF64I64},
		{{CtCodeGen::OpType::i64, CtCodeGen::OpType::f64}, instrI64F64},

		{{CtCodeGen::OpType::f32, CtCodeGen::OpType::f64}, instrF32F64},
		{{CtCodeGen::OpType::f64, CtCodeGen::OpType::f32}, instrF64F32},

		{{CtCodeGen::OpType::i32, CtCodeGen::OpType::i64}, instrI32I64},
		{{CtCodeGen::OpType::i64, CtCodeGen::OpType::i32}, instrI64I32},
	};

	ctInstr instr = instr_map.at({this->from_type, this->to_type});
	writer->writebackInstr(instr);
}


void CtCodeGen::JumpOp::emit(CtBytecodeWriter* writer)
{
	ctInstr instr;

	switch (this->jump_type)
	{
	case JumpOpType::Norm:     instr = instrJmp; break;
	case JumpOpType::True:     instr = instrJmpTrue; break;
	case JumpOpType::False:    instr = instrJmpFalse; break;
	}

	writer->writebackInstr(instr);

	writer->registerPatch(this->station);
}


void CtCodeGen::StationOp::emit(CtBytecodeWriter* writer)
{
	writer->registerStation(this->id);
}


void CtCodeGen::Out::emit(CtBytecodeWriter* writer)
{
	writer->writebackInstr(instrOut);
	ctInstrSize packed[4];
	ctProgramImage_packInt32( (int32_t*) &this->fmt, packed);
	writer->writebackMultipleInstr(packed, 4);
}
