#include "decls.h"

// FUNCTION: SADX 0x00902f40
void njLinear(float *idata, float *odata, float attr, float frame)
{
	float fVar1;

	fVar1 = 1.0 - frame;
	*odata = idata[3] * frame + fVar1 * *idata;
	odata[1] = idata[4] * frame + idata[1] * fVar1;
	odata[2] = fVar1 * idata[2] + idata[5] * frame;
	return;
}
