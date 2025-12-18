#include "CuteByte.h"
#include <string>
#include <vector>
#include <map>

#pragma once

class CtBytecodeWriter;

namespace CtIRepr
{
	struct Unit;

	struct Function
	{
		uint id;
		uint arg_count;
		uint locals_count;
		uint address;

		std::vector<Unit> units;

		std::map<uint, uint> stations; // id, address.  
		std::vector<ctInstrSize> instrs;
	};

	struct Program
	{
		std::map<uint, Function*> functions;

		std::vector<ctInstrSize> instrs;
	};


    enum class OpType         {i32, i64, u32, u64, f32, f64};

	enum class LogicOpType    {And, Or, Not, Xor};
	enum class BitwiseOpType  {And, Or, Not, Xor, LShift, RShift};
	enum class CmpType        {Eq, Ue, Gt, Ge, Lt, Le};

	enum class JumpOpType       {Norm, Eq, Ue};


    enum class UnitType
    {
        AddOp,
        SubOp,
        MulOp,
        DivOp,
        ModOp,
        LogicOp,
        BitWiseOp,
        CmpOp,

        LoadOp,
        StoreOp,
        CopyOp,

        TypeCastOp,

        JumpOp,
        StationOp
    };


	struct Unit
    {
        UnitType ut;
        virtual ~Unit() = default;

		virtual void emit(CtBytecodeWriter& writer) = 0;
    };


	struct AddOp : Unit
    {
        OpType op_type;
        AddOp(OpType t) : op_type(t) {ut = UnitType::AddOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct SubOp : Unit
    {
        OpType op_type;
		SubOp(OpType t) : op_type(t) {ut = UnitType::SubOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct MulOp : Unit
    {
        OpType op_type;
		MulOp(OpType t) : op_type(t) {ut = UnitType::MulOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct DivOp : Unit
    {
        OpType op_type;
        DivOp(OpType t) : op_type(t) {ut = UnitType::DivOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct ModOp : Unit
    {
        OpType op_type;
        ModOp(OpType t) : op_type(t) {ut = UnitType::ModOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct LogicOp : Unit
    {
        OpType op_type;
		LogicOpType logic_type;
        LogicOp(OpType t, LogicOpType l) : op_type(t), logic_type(l) {ut = UnitType::LogicOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct BitWiseOp : Unit
    {
        OpType op_type;
		BitwiseOpType bitwise_type;
        BitWiseOp(OpType t, BitwiseOpType b) : op_type(t), bitwise_type(b) {ut = UnitType::BitWiseOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct CmpOp : Unit
    {
        OpType op_type;
		CmpType cmp_type;
        CmpOp(OpType t, CmpType c) : op_type(t), cmp_type(c) {ut = UnitType::CmpOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct LoadOp : Unit
    {
        OpType op_type;
		uint index;
		LoadOp(OpType t, uint i) : op_type(t), index(i) {ut = UnitType::LoadOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct StoreOp : Unit
    {
        OpType op_type;
		uint index;
		StoreOp(OpType t, uint i) : op_type(t), index(i) {ut = UnitType::StoreOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct CopyOp : Unit
    {
        OpType op_type;
		uint src;
		uint dest;
		CopyOp(OpType t, uint src, uint dest) : op_type(t), src(src), dest(dest) {ut = UnitType::CopyOp;}
		void emit(CtBytecodeWriter& writer);
    };


	struct TypeCastOp : Unit
    {
		OpType from_type;
		OpType to_type;
		TypeCastOp(OpType from, OpType to) : from_type(from), to_type(to) {ut = UnitType::TypeCastOp;}
		void emit(CtBytecodeWriter& writer);
    };


	struct JumpOp : Unit
    {
        uint offset;
		JumpOpType jump_type;
		JumpOp(uint o, JumpOpType j) : offset(o), jump_type(j) {ut = UnitType::JumpOp;}
		void emit(CtBytecodeWriter& writer);
    };


    struct StationOp : Unit
    {
        uint id;
		StationOp(uint id) : id(id) {ut = UnitType::StationOp;}
		void emit(CtBytecodeWriter& writer);
    };

}



class CtBytecodeWriter
{
	ctProgramImage img;
	CtIRepr::Program* program;

	void writeFunction(CtIRepr::Function* func);
	void patchFunction(CtIRepr::Function* func);

	void makeImage();

	public:

	void write(CtIRepr::Program* program, std::string outfile);
};
