#include "decls.h"

// FUNCTION: SADX 0x0067ebe0
float njScalor2(float *v)
{
	float var1;
	float var2;
	float var3;

	var1 = v[0] * v[0];
	var2 = v[1] * v[1];
	var3 = v[2] * v[2];
	return var1 + var2 + var3;
}
