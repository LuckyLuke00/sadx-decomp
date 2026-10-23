#include "decls.h"
void njLinear(float *param_1, float *param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00902f40
void njLinear(float *param_1, float *param_2, float param_3, float param_4)
{
	float fVar1;

	fVar1 = 1.0 - param_4;
	*param_2 = param_1[3] * param_4 + fVar1 * *param_1;
	param_2[1] = param_1[4] * param_4 + param_1[1] * fVar1;
	param_2[2] = fVar1 * param_1[2] + param_1[5] * param_4;
	return;
}
