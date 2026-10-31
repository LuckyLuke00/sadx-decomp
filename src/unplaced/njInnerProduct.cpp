#include "decls.h"

// FUNCTION: SADX 0x0067d290
float njInnerProduct(NJS_VECTOR *v1, NJS_VECTOR *v2)
{
	float var1;
	float var2;
	float var3;

	var1 = v1->y * v2->y;
	var2 = v1->x * v2->x;
	var3 = v1->z * v2->z;
	return var1 + var2 + var3;
}
