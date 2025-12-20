#include "CuteByte.h"
#include <format>
#include <map>

#include "gen.hpp"

#include "../spec/error.hpp"




void CtCodeGen::AddOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:   instr = instrAddI; break;
        case CtCodeGen::OpType::UInt:  instr = instrAddI; break; // unsigned treated same
        case CtCodeGen::OpType::Float: instr = instrAddF; break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::SubOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:   instr = instrSubI; break;
        case CtCodeGen::OpType::UInt:  instr = instrSubI; break;
        case CtCodeGen::OpType::Float: instr = instrSubF; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::MulOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:   instr = instrMulI; break;
        case CtCodeGen::OpType::UInt:  instr = instrMulI; break;
        case CtCodeGen::OpType::Float: instr = instrMulF; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::DivOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:   instr = instrDivI; break;
        case CtCodeGen::OpType::UInt:  instr = instrDivU; break;
        case CtCodeGen::OpType::Float: instr = instrDivF; break;
        default: break;
    }

    writer->writebackInstr(instr);
}


void CtCodeGen::ModOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:  instr = instrModI; break;
        case CtCodeGen::OpType::UInt: instr = instrModU; break;
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
		break;
	}

	writer->writebackInstr(instr);
}


void CtCodeGen::CmpOp::emit(CtBytecodeWriter* writer)
{
	ctInstr instr;

	switch (this->op_type)
	{
        case OpType::Int:     instr = instrCmpI; break;
        case OpType::UInt:    instr = instrCmpU; break;
        case OpType::Float:   instr = instrCmpF; break; 
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
	ctInstr instr;
	ctInstrSize packed[8];


	switch (this->op_type)
	{
        case OpType::Int:	
        case OpType::UInt:	

		writer->writebackInstr(instrLoadCoI64);
		break;
        case OpType::Float:
		writer->writebackInstr(instrLoadCoF64);
		break;
	}

	switch (this->op_type)
	{
        case OpType::Int:
		ctProgramImage_packInt64((int64_t*) &this->i64, packed);
		break;

		case OpType::UInt:
		ctProgramImage_packInt64((int64_t*) &this->u64, packed);
		break;
		
		case OpType::Float:
		ctProgramImage_packInt64((int64_t*) &this->f64, packed);
		break;
	}

	writer->writebackMultipleInstr(packed, 8);
}


void CtCodeGen::LoadOp::emit(CtBytecodeWriter* writer)
{
    ctInstr instr;

    switch (this->op_type)
    {
        case CtCodeGen::OpType::Int:   instr = instrLoadI; break;
        case CtCodeGen::OpType::UInt:  instr = instrLoadI; break;
        case CtCodeGen::OpType::Float: instr = instrLoadF; break;
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
        case CtCodeGen::OpType::Int:   instr = instrStoreI; break;
        case CtCodeGen::OpType::UInt:  instr = instrStoreI; break;
        case CtCodeGen::OpType::Float: instr = instrStoreF; break;
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
        case CtCodeGen::OpType::Int:   instr = instrCopyI; break;
        case CtCodeGen::OpType::UInt:  instr = instrCopyI; break;
        case CtCodeGen::OpType::Float: instr = instrCopyF; break;
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
		// float - int
		{{CtCodeGen::OpType::Int, CtCodeGen::OpType::Float}, instrItoF}, 
		{{CtCodeGen::OpType::Float, CtCodeGen::OpType::Int}, instrFtoI},
		
		// int - uint
		{{CtCodeGen::OpType::Int, CtCodeGen::OpType::UInt}, instrNull}, 
		{{CtCodeGen::OpType::UInt, CtCodeGen::OpType::Int}, instrNull},

		{{CtCodeGen::OpType::UInt, CtCodeGen::OpType::Float}, instrItoF}, 
		{{CtCodeGen::OpType::Float, CtCodeGen::OpType::UInt}, instrFtoI},
	};

	if (instr_map.contains({this->from_type, this->to_type}))
	{
		ctInstr instr = instr_map.at({this->from_type, this->to_type});

		if (instr != instrNull)
		{
			writer->writebackInstr(instr);
		}

		return;
	}
	
	CtError::raise(
		CtError::ErrorType::CompilerError,
		std::format("Invalid type cast! Cannot convert {} to {}", (int)this->from_type, (int)this->to_type)
	);
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
