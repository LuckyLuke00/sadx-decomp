#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d350
void njTranslateV(float *param_1, struct NJS_POINT3 *param_2)
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
	param_1[12] += fVar1 * param_1[0] + fVar2 * param_1[4] + fVar3 * param_1[8];
	param_1[13] += fVar1 * param_1[1] + fVar2 * param_1[5] + fVar3 * param_1[9];
	param_1[14] += fVar1 * param_1[2] + fVar2 * param_1[6] + fVar3 * param_1[10];
	param_1[15] += fVar1 * param_1[3] + fVar2 * param_1[7] + fVar3 * param_1[11];
}
