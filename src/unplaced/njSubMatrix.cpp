#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067daf0
void njSubMatrix(float *md, float *ms)
{
	if (md == NULL)
	{
		md = (float *)DAT_0629c518;
	}
	md[0] -= ms[0];
	md[1] -= ms[1];
	md[2] -= ms[2];
	md[3] -= ms[3];
	md[4] -= ms[4];
	md[5] -= ms[5];
	md[6] -= ms[6];
	md[7] -= ms[7];
	md[8] -= ms[8];
	md[9] -= ms[9];
	md[10] -= ms[10];
	md[11] -= ms[11];
	md[12] -= ms[12];
	md[13] -= ms[13];
	md[14] -= ms[14];
	md[15] -= ms[15];
}
