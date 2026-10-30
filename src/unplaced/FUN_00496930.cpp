#include "decls.h"

// FUNCTION: SADX 0x00496930
int FUN_00496930(float *param_1)
{
	unsigned int var1;

	var1 = (unsigned char)(param_1[0] * 255.0) << 8;
	var1 |= (unsigned char)(param_1[1] * 255.0);
	var1 <<= 8;
	var1 |= (unsigned char)(param_1[2] * 255.0);
	var1 <<= 8;
	var1 |= (unsigned char)(param_1[3] * 255.0);
	return var1;
}
