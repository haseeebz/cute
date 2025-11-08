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

	int bytes_read;

	bytes_read = fread(&img->header, sizeof(ctProgramHeader), 1, fp);
	bytes_read = fread(&img->main, sizeof(ctProgramHeader), 1, fp);

	img->instrs = malloc(sizeof(ctInstrSize) * img->header.instr_count);
	bytes_read = fread(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);

	return ctImageError_Success;
}


ctImageError ctProgramImage_write(ctProgramImage* img, char* filepath)
{
	FILE* fp = fopen(filepath, "wb");

	if (!fp) {return ctImageError_FileNotFound;}

	fwrite(&img->header, sizeof(ctProgramHeader), 1, fp);
	fwrite(&img->main, sizeof(ctProgramHeader), 1, fp);
	fwrite(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);

	return ctImageError_Success;
}