#include "decls.h"

// FUNCTION: SADX 0x0067d150
double njScalor(struct NJS_POINT3 *param_1)
{
	float local_8;
	float var1;
	float local_c;
	local_8 = param_1->x * param_1->x;
	var1 = param_1->y * param_1->y;
	local_c = param_1->z * param_1->z;
	return njSqrt(var1 + local_8 + local_c);
}
