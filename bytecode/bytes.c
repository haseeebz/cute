#include "include/CuteByte.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>



void ctProgramImage_free(ctProgramImage* img)
{
	if (img->instrs != NULL)
	{
		free(img->instrs);
	}
	if (img->consts != NULL)
	{
		free(img->consts);
	}
	if (img->func_table != NULL)
	{
		free(img->func_table);
	}
	img->header.instr_count = 0;
	img->header.const_count = 0;
}


ctImageError ctProgramImage_read(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "rb");
	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_read;

	items_read = fread(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_read != 1) {return ctImageError_ByteReadWriteFailure;}

	if (img->header.magic != _ctMagic)
	{
		return ctImageError_InvalidImage;
	}


	img->consts = malloc(sizeof(ctProgramConstant) * img->header.const_count);
	items_read = fread(img->consts, sizeof(ctProgramConstant), img->header.const_count, fp);
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

	items_written = fwrite(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_written != 1) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->consts, sizeof(ctProgramConstant), img->header.const_count, fp);
	if (items_written != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->func_table, sizeof(ctFuncMetadata), img->header.func_count, fp);
	if (items_written != img->header.func_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_written != img->header.instr_count) {return ctImageError_ByteReadWriteFailure;}

	return ctImageError_Success;
}