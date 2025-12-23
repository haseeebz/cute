#include "CuteByte.h"
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>
#include <map>

#pragma once



class CtBytecodeWriter;

namespace CtCodeGen
{
	struct Unit;

	struct Function
	{
		uint id;
		uint arg_count;
		uint locals_count;
		uint address;
		uint station_count = 0;

		std::vector<Unit*> units;

		std::map<uint, uint> stations; // id, address.  
		std::vector<ctInstrSize> instrs;
		std::map<uint, uint> patches; // address, station_id

		~Function() {for (auto* unit: units) {delete unit;}}
	};

	struct Program
	{
		std::map<uint, Function*> functions;

		std::vector<ctInstrSize> instrs;

		~Program() {for (auto func: functions) {delete func.second;}}
	};


    enum class OpType         {Int, UInt, Float};

	enum class LogicOpType    {And, Or, Not, Xor};
	enum class BitwiseOpType  {And, Or, Not, Xor, LShift, RShift, RaShift};
	enum class CmpType        {Eq, Ue, Gt, Ge, Lt, Le};

	enum class JumpOpType       {Norm, True, False};


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

		LoadConst,
        LoadOp,
        StoreOp,
        CopyOp,

        TypeCastOp,

        JumpOp,
        StationOp,

		Out
    };


	struct Unit
    {
        UnitType ut;
        ~Unit() = default;

		virtual void emit(CtBytecodeWriter* writer) = 0;
    };


	struct AddOp : Unit
    {
        OpType op_type;
        AddOp(OpType t) : op_type(t) {ut = UnitType::AddOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct SubOp : Unit
    {
        OpType op_type;
		SubOp(OpType t) : op_type(t) {ut = UnitType::SubOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct MulOp : Unit
    {
        OpType op_type;
		MulOp(OpType t) : op_type(t) {ut = UnitType::MulOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct DivOp : Unit
    {
        OpType op_type;
        DivOp(OpType t) : op_type(t) {ut = UnitType::DivOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct ModOp : Unit
    {
        OpType op_type;
        ModOp(OpType t) : op_type(t) {ut = UnitType::ModOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct LogicOp : Unit
    {
		LogicOpType logic_type;
        LogicOp(LogicOpType l) : logic_type(l) {ut = UnitType::LogicOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct BitWiseOp : Unit
    {
		BitwiseOpType bitwise_type;
        BitWiseOp(BitwiseOpType b) : bitwise_type(b) {ut = UnitType::BitWiseOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct CmpOp : Unit
    {
        OpType op_type;
		CmpType cmp_type;
        CmpOp(OpType t, CmpType c) : op_type(t), cmp_type(c) {ut = UnitType::CmpOp;}
		void emit(CtBytecodeWriter* writer);
    };

	struct LoadConstOp : Unit
	{
		OpType op_type;
		union
		{
			int64_t i64;
			uint64_t u64;
			double f64;
		};

		// constructors for each type
		LoadConstOp(int64_t val)   : op_type(OpType::Int),   i64(val)   { ut = UnitType::LoadOp; }
		LoadConstOp(uint64_t val)  : op_type(OpType::UInt),  u64(val)   { ut = UnitType::LoadOp; }
		LoadConstOp(double val)    : op_type(OpType::Float), f64(val)   { ut = UnitType::LoadOp; }
		void emit(CtBytecodeWriter* writer);
	};


    struct LoadOp : Unit
    {
        OpType op_type;
		uint index;
		LoadOp(OpType t, uint i) : op_type(t), index(i) {ut = UnitType::LoadOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct StoreOp : Unit
    {
        OpType op_type;
		uint index;
		StoreOp(OpType t, uint i) : op_type(t), index(i) {ut = UnitType::StoreOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct CopyOp : Unit
    {
        OpType op_type;
		uint src;
		uint dest;
		CopyOp(OpType t, uint src, uint dest) : op_type(t), src(src), dest(dest) {ut = UnitType::CopyOp;}
		void emit(CtBytecodeWriter* writer);
    };


	struct TypeCastOp : Unit
    {
		OpType from_type;
		OpType to_type;
		TypeCastOp(OpType from, OpType to) : from_type(from), to_type(to) {ut = UnitType::TypeCastOp;}
		void emit(CtBytecodeWriter* writer);
    };


	struct JumpOp : Unit
    {
        uint station;
		JumpOpType jump_type;
		JumpOp(uint station, JumpOpType j) : station(station), jump_type(j) {ut = UnitType::JumpOp;}
		void emit(CtBytecodeWriter* writer);
    };


    struct StationOp : Unit
    {
        uint id;
		StationOp(uint id) : id(id) {ut = UnitType::StationOp;}
		void emit(CtBytecodeWriter* writer);
    };

	struct Out : Unit
    {
        uint fmt;
		Out(uint fmt) : fmt(fmt) {ut = UnitType::Out;}
		void emit(CtBytecodeWriter* writer);
    };
}



class CtBytecodeWriter
{
	ctProgramImage img;
	CtCodeGen::Program* program;

	CtCodeGen::Function* current_function;

	void writeFunction(CtCodeGen::Function* func);
	void patchFunction(CtCodeGen::Function* func);

	void makeImage(std::string outfile);

	public:

	// called by units
	void writebackInstr(ctInstrSize instr);
	void writebackMultipleInstr(ctInstrSize* instrs, uint count);
	void registerStation(uint id);
	void registerPatch(uint station);
	

	void write(CtCodeGen::Program* program, std::string outfile);

};


