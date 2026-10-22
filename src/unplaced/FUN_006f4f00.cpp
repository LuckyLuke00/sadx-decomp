#include "decls.h"

// FUNCTION: SADX 0x006f4f00
float FUN_006f4f00(float *param_1, float *param_2)
{
	float local_4;
	float local_8;

	local_4 = *param_1 - *param_2;
	local_8 = param_1[2] - param_2[2];
	return njSqrt(local_8 * local_8 + local_4 * local_4);
}
