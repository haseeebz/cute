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
	img->header.instr_count = 0;
}


ctImageError ctProgramImage_read(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "rb");
	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_read;

	items_read = fread(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_read != 1) {return ctImageError_ByteReadFailure;}

	items_read = fread(&img->main, sizeof(ctProgramHeader), 1, fp);
	if (items_read != 1) {return ctImageError_ByteReadFailure;}

	img->instrs = malloc(sizeof(ctInstrSize) * img->header.instr_count);
	items_read = fread(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_read != img->header.instr_count) {return ctImageError_ByteReadFailure;}

	return ctImageError_Success;
}


ctImageError ctProgramImage_write(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "wb");

	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_written;

	items_written = fwrite(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_written != 1) {return ctImageError_ByteWriteFailure;}

	items_written = fwrite(&img->main, sizeof(ctProgramHeader), 1, fp);
	if (items_written != 1) {return ctImageError_ByteWriteFailure;}

	items_written = fwrite(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_written != img->header.instr_count) {return ctImageError_ByteWriteFailure;}

	return ctImageError_Success;
}