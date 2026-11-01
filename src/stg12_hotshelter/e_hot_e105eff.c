#include "decls.h"

// GLOBAL: SADX 0x04c2c73c
static struct CRUSHLIGHT_DATA cl_data;

// FUNCTION: SADX 0x008b6cb0
void E105_CrushLight(struct NJS_POINT3 *pPos, float fLength)
{
	cl_data.fLength = fLength;
	CreateCrushLight(pPos, &cl_data);
}
