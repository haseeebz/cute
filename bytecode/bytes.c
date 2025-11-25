#include "include/CuteByte.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
Read Write sequence is as follows:

Header
Const Type Table
Const Table
Const Table
Func Table
Instr Array
*/

ctImageError ctProgramImage_read(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "rb");
	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_read;

	items_read = fread(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_read != 1) {return ctImageError_ByteReadWriteFailure;}

	if (img->header.magic != ctMagicId)
	{
		return ctImageError_InvalidImage;
	}

	img->const_type_table = malloc(sizeof(ctProgramConstTSize) * img->header.const_count);
	items_read = fread(img->const_type_table, sizeof(ctProgramConstTSize), img->header.const_count, fp);
	if (items_read != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	img->const_table = malloc(sizeof(ctProgramConst) * img->header.const_count);
	items_read = fread(img->const_table, sizeof(ctProgramConst), img->header.const_count, fp);
	if (items_read != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	img->func_table = malloc(sizeof(ctFuncMetadata) * img->header.func_count);
	items_read = fread(img->func_table, sizeof(ctFuncMetadata), img->header.func_count, fp);
	if (items_read != img->header.func_count) {return ctImageError_ByteReadWriteFailure;}

	img->instrs = malloc(sizeof(ctInstrSize) * img->header.instr_count);
	items_read = fread(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_read != img->header.instr_count) {return ctImageError_ByteReadWriteFailure;}

	return ctImageError_Success;
}


ctImageError ctProgramImage_write(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "wb");

	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_written;

	img->header.magic = ctMagicId;

	items_written = fwrite(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_written != 1) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->const_type_table, sizeof(ctProgramConstTSize), img->header.const_count, fp);
	if (items_written != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->const_table, sizeof(ctProgramConst), img->header.const_count, fp);
	if (items_written != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->func_table, sizeof(ctFuncMetadata), img->header.func_count, fp);
	if (items_written != img->header.func_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_written != img->header.instr_count) {return ctImageError_ByteReadWriteFailure;}

	return ctImageError_Success;
}




void ctProgramImage_freeImage(ctProgramImage* img)
{
	if (img->instrs != NULL)
	{
		free(img->instrs);
	}

	if (img->const_table != NULL)
	{
		free(img->const_table);
	}

	if (img->const_type_table != NULL)
	{
		free(img->const_type_table);
	}

	if (img->func_table != NULL)
	{
		free(img->func_table);
	}
}


void ctProgramImage_packInt(int64_t i, ctInstr* eightInstrs)
{
	memcpy(eightInstrs, &i, sizeof(i));
}

void ctProgramImage_extractInt(ctInstr* eightInstrs, int64_t* i)
{
	memcpy(&i, eightInstrs, sizeof(i));
}