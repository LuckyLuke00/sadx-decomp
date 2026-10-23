#include "decls.h"

// FUNCTION: SADX 0x0067e460
void njScaleV(float *param_1, struct NJS_POINT3 *param_2)
{
	float fVar1;
	float fVar2;
	float fVar3;

	fVar1 = param_2->x;
	fVar2 = param_2->y;
	fVar3 = param_2->z;
	if (param_1 == NULL)
	{
		param_1 = (float *)DAT_0629c518;
	}
	param_1[0] *= fVar1;
	param_1[1] *= fVar1;
	param_1[2] *= fVar1;
	param_1[3] *= fVar1;
	param_1[4] *= fVar2;
	param_1[5] *= fVar2;
	param_1[6] *= fVar2;
	param_1[7] *= fVar2;
	param_1[8] *= fVar3;
	param_1[9] *= fVar3;
	param_1[10] *= fVar3;
	param_1[11] *= fVar3;
}
