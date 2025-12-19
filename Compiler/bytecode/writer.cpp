#include "CuteByte.h"
#include <string>
#include <vector>
#include <map>

#include "../spec/error.hpp"
#include "gen.hpp"




void CtBytecodeWriter::writeFunction(CtCodeGen::Function* func)
{
	this->current_function = func;

	for (CtCodeGen::Unit* unit: func->units)
	{
		unit->emit(this);
	}

	func->instrs.push_back(instrExit);
	int code = 0;
	ctInstrSize packed[4];
	ctProgramImage_packInt32(&code, packed);
	this->writebackMultipleInstr(packed, 4);

	this->patchFunction(func);
	func->address = this->program->instrs.size();
	this->program->instrs.insert(this->program->instrs.end(), func->instrs.begin(), func->instrs.end());
}


void CtBytecodeWriter::patchFunction(CtCodeGen::Function* func)
{
	for (auto patch: func->patches)
	{
		uint patch_address = patch.first;
		uint patch_station = patch.second;

		if (!func->stations.contains(patch_station))
		{
			CtError::raise(CtError::ErrorType::CompilerError, "Critical! Station to jump to does'nt exist!");
		}

		uint station_address = func->stations[patch_station];

		int offset = int(station_address) - int(patch_address);
		
		ctInstrSize packed[4];
		ctProgramImage_packInt32(&offset, packed);

		for (int i = 0; i < 4; i++)
		{
			func->instrs[patch_address + i] = packed[i];
		}
	}
}


void CtBytecodeWriter::makeImage(std::string outfile)
{
	img.header.func_count = this->program->functions.size();
	img.header.const_count = 0;
	img.header.instr_count = this->program->instrs.size();

	std::vector<ctFuncMetadata> func_table;

	for (auto func: this->program->functions)
	{
		ctFuncMetadata meta;
		meta.func_id = func.second->id;
		meta.args_count = func.second->arg_count;
		meta.locals_count = func.second->locals_count;
		meta.instr_address = func.second->address;
		func_table.push_back(meta);
	}

	img.func_table = func_table.data();

	img.instrs = this->program->instrs.data();

	ctImageError code = ctProgramImage_write(&this->img, outfile.data());
	std::cout << "Image should be written" << code << "\n";
}



void CtBytecodeWriter::writebackInstr(ctInstrSize instr)
{
	this->current_function->instrs.push_back(instr);
}


void CtBytecodeWriter::writebackMultipleInstr(ctInstrSize* instrs, uint count)
{
	for (uint i = 0; i < count; i++)
	{
		this->current_function->instrs.push_back(instrs[i]);
	}
}


void CtBytecodeWriter::registerStation(uint id)
{
	this->current_function->stations[id] = this->current_function->instrs.size();
}


void CtBytecodeWriter::registerPatch(uint station)
{
	this->current_function->patches[this->current_function->instrs.size()] = station;

	ctInstrSize placeholder[4] = {instrNull};
	this->writebackMultipleInstr(placeholder, 4);
}


void CtBytecodeWriter::write(CtCodeGen::Program* program, std::string outfile)
{
	this->program = program;
	
	for (auto func: program->functions)
	{
		this->writeFunction(func.second);
	}

	this->makeImage(outfile);
}


