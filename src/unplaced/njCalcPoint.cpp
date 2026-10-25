#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x00430bb0
void njCalcPoint(float *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3)
{
	float local_8;
	float var1;
	float local_c;
	float *var2;

	local_8 = param_2->x;
	var1 = param_2->y;
	local_c = param_2->z;
	var2 = param_1;
	if (var2 == 0)
	{
		var2 = (float *)DAT_0629c518;
	}
	param_3->x = var1 * var2[4] + local_8 * var2[0] + local_c * var2[8] + var2[12];
	param_3->y = var2[5] * var1 + var2[1] * local_8 + var2[9] * local_c + var2[13];
	param_3->z = var2[6] * var1 + var2[2] * local_8 + var2[10] * local_c + var2[14];
}
