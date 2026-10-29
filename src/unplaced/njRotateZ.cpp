#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x00430aa0
void njRotateZ(NJS_MATRIX *m, Angle ang)
{
	float local_10;
	float local_c;
	float local_8;
	float local_14;
	float local_18;
	float var1;
	float *var2;

	local_10 = njSin(ang);
	local_c = njCos(ang);
	if (m == 0)
	{
		var2 = (float *)DAT_0629c518;
	}
	else
	{
		var2 = *m;
	}
	local_8 = var2[0];
	local_14 = var2[1];
	local_18 = var2[2];
	var1 = var2[3];
	var2[0] = local_10 * var2[4] + local_c * local_8;
	var2[1] = local_14 * local_c + var2[5] * local_10;
	var2[2] = local_10 * var2[6] + local_18 * local_c;
	var2[3] = var1 * local_c + var2[7] * local_10;
	var2[4] = local_c * var2[4] - local_10 * local_8;
	var2[5] = var2[5] * local_c - local_10 * local_14;
	var2[6] = local_c * var2[6] - local_10 * local_18;
	var2[7] = var2[7] * local_c - local_10 * var1;
}
