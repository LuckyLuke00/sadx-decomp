#include "decls.h"
float njSqrt(float param_1);

// FUNCTION: SADX 0x00477b80
float ghUnitVector(const struct NJS_POINT3 *r4, struct NJS_POINT3 *r5)
{
	float var1;
	float local_10;
	float local_c;
	float local_8;

	var1 = r4->x;
	local_10 = r4->y;
	local_c = r4->z;
	local_8 = 1.0f / njSqrt(var1 * var1 + local_10 * local_10 + local_c * local_c);
	r5->x = var1 * local_8;
	r5->y = local_10 * local_8;
	r5->z = local_c * local_8;
	return local_8;
}

// STUB: SADX 0x00477c00
float FUN_00477c00(float *param_1, float *param_2)
{
	return (float)0;
}
