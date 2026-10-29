#include "decls.h"
extern int DAT_0629c518;
extern int DAT_0629c4ac;

// FUNCTION: SADX 0x004309b0
void njCalcVector(float *m, struct NJS_POINT3 *vs, struct NJS_POINT3 *vd)
{
	float var1;
	float var2;
	float var3;
	float var4;
	float *var5;

	var1 = vs->x;
	var2 = vs->y;
	var3 = vs->z;
	if (m == 0)
	{
		var5 = (float *)DAT_0629c518;
	}
	else
	{
		var5 = m;
	}
	vd->x = var1 * var5[0] + var2 * var5[4] + var3 * var5[8];
	vd->y = var1 * var5[1] + var2 * var5[5] + var3 * var5[9];
	vd->z = var1 * var5[2] + var2 * var5[6] + var3 * var5[10];
	if (DAT_0629c4ac != 0)
	{
		var1 = vd->x;
		var2 = vd->y;
		var3 = vd->z;
		var4 = 1.0 / njSqrt(var1 * var1 + var2 * var2 + var3 * var3);
		vd->x = var1 * var4;
		vd->y = var2 * var4;
		vd->z = var3 * var4;
	}
}
