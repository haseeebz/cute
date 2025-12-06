#include "include/CuteByte.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
Read Write sequence is as follows:

Header
Const Table
Func Table
Instr Blob
*/

ctImageError ctProgramImage_read(ctProgramImage *img, char *filepath)
{
	FILE *fp = fopen(filepath, "rb");
	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_read;

	items_read = fread(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_read != 1) {return ctImageError_ReadWriteFailure;}

	if (img->header.magic != ctMagicId)
	{
		return ctImageError_InvalidImage;
	}


	//img->const_pool = malloc(sizeof(ctProgramConstant) * img->header.const_count);
	img->const_pool = NULL;
	// Constant reading not implemented yet!

	img->func_table = malloc(sizeof(ctFuncMetadata) * img->header.func_count);
	items_read = fread(img->func_table, sizeof(ctFuncMetadata), img->header.func_count, fp);
	if (items_read != img->header.func_count) {return ctImageError_ReadWriteFailure;}

	img->instrs = malloc(sizeof(ctInstrSize) * img->header.instr_count);
	items_read = fread(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_read != img->header.instr_count) {return ctImageError_ReadWriteFailure;}

	return ctImageError_Success;
}


ctImageError ctProgramImage_write(ctProgramImage *img, char *filepath)
{
	FILE *fp = fopen(filepath, "wb");

	if (!fp) {return ctImageError_FileNotFound;}

	u_int32_t items_written;

	img->header.magic = ctMagicId;

	items_written = fwrite(&img->header, sizeof(ctProgramHeader), 1, fp);
	if (items_written != 1) {return ctImageError_ReadWriteFailure;}

	//items_written = fwrite(img->const_table, sizeof(ctProgramConst), img->header.const_count, fp);
	//if (items_written != img->header.const_count) {return ctImageError_ByteReadWriteFailure;}

	items_written = fwrite(img->func_table, sizeof(ctFuncMetadata), img->header.func_count, fp);
	if (items_written != img->header.func_count) {return ctImageError_ReadWriteFailure;}

	items_written = fwrite(img->instrs, sizeof(ctInstrSize), img->header.instr_count, fp);
	if (items_written != img->header.instr_count) {return ctImageError_ReadWriteFailure;}

	return ctImageError_Success;
}




void ctProgramImage_freeImage(ctProgramImage *img)
{
	if (img->instrs != NULL)
	{
		free(img->instrs);
	}

	if (img->const_pool != NULL)
	{
		free(img->const_pool);
	}

	if (img->func_table != NULL)
	{
		free(img->func_table);
	}
}


inline void ctProgramImage_packInt32(int32_t *i, ctInstrSize *instr4)
{
	memcpy(instr4, i, sizeof(*i));
}

inline void ctProgramImage_packInt64(int64_t *i, ctInstrSize *instr8)
{
	memcpy(instr8, i, sizeof(*i));
}

inline void ctProgramImage_packFloat32(float *i, ctInstrSize *instr4)
{
	memcpy(instr4, i, sizeof(*i));
}

inline void ctProgramImage_packFloat64(double *i, ctInstrSize *instr8)
{
	memcpy(instr8, i, sizeof(*i));
}
