#include "decls.h"
extern "C" double sqrt(double param_1);
void FUN_00434c70(void *param_1, float param_2, float param_3, float param_4, float param_5);

// STUB: SADX 0x00434c70
void FUN_00434c70(void *param_1, float param_2, float param_3, float param_4, float param_5)
{
}

// FUNCTION: SADX 0x00434cc0
float __fastcall FUN_00434cc0(float *param_1)
{
	float var1;
	float var2;

	var1 = param_1[0];
	var2 = var1 * var1;
	var2 = var2 + 0.0;
	var1 = param_1[1];
	var1 = var1 * var1;
	var2 = var1 + var2;
	var1 = param_1[2];
	var1 = var1 * var1;
	var2 = var1 + var2;
	return sqrt(var2);
}

// STUB: SADX 0x00434d50
double __stdcall FUN_00434d50(float *param_1)
{
	return (double)0;
}
