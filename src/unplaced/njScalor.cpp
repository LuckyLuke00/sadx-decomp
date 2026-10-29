#include "decls.h"

// FUNCTION: SADX 0x0067d150
double njScalor(struct NJS_POINT3 *v)
{
	float local_8;
	float var1;
	float local_c;
	local_8 = v->x * v->x;
	var1 = v->y * v->y;
	local_c = v->z * v->z;
	return njSqrt(var1 + local_8 + local_c);
}
