#include "decls.h"
extern int DAT_0629c518;
extern int DAT_0629c4ac;
float njSqrt(float param_1);

// FUNCTION: SADX 0x004309b0
void njCalcVector(float *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3)
{
	float var1;
	float var2;
	float var3;
	float var4;
	float *var5;

	var1 = param_2->x;
	var2 = param_2->y;
	var3 = param_2->z;
	if (param_1 == 0)
	{
		var5 = (float *)DAT_0629c518;
	}
	else
	{
		var5 = param_1;
	}
	param_3->x = var1 * var5[0] + var2 * var5[4] + var3 * var5[8];
	param_3->y = var1 * var5[1] + var2 * var5[5] + var3 * var5[9];
	param_3->z = var1 * var5[2] + var2 * var5[6] + var3 * var5[10];
	if (DAT_0629c4ac != 0)
	{
		var1 = param_3->x;
		var2 = param_3->y;
		var3 = param_3->z;
		var4 = 1.0 / njSqrt(var1 * var1 + var2 * var2 + var3 * var3);
		param_3->x = var1 * var4;
		param_3->y = var2 * var4;
		param_3->z = var3 * var4;
	}
}
