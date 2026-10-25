#include "decls.h"

// FUNCTION: SADX 0x0067ebe0
float njScalor2(float *param_1)
{
	float var1;
	float var2;
	float var3;

	var1 = param_1[0] * param_1[0];
	var2 = param_1[1] * param_1[1];
	var3 = param_1[2] * param_1[2];
	return var1 + var2 + var3;
}
