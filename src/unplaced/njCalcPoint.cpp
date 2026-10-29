#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x00430bb0
void njCalcPoint(NJS_MATRIX *m, NJS_POINT3 *ps, NJS_POINT3 *pd)
{
	float local_8;
	float var1;
	float local_c;
	float *var2;

	local_8 = ps->x;
	var1 = ps->y;
	local_c = ps->z;
	var2 = *m;
	if (var2 == 0)
	{
		var2 = (float *)DAT_0629c518;
	}
	pd->x = var1 * var2[4] + local_8 * var2[0] + local_c * var2[8] + var2[12];
	pd->y = var2[5] * var1 + var2[1] * local_8 + var2[9] * local_c + var2[13];
	pd->z = var2[6] * var1 + var2[2] * local_8 + var2[10] * local_c + var2[14];
}
