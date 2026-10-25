#include "decls.h"
#include <new>
extern "C" double sqrt(double param_1);

// STUB: SADX 0x0041a8d0
void * __stdcall FUN_0041a8d0(int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0041a930
void * __stdcall FUN_0041a930(int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0041a990
void * __stdcall FUN_0041a990(int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0041a9f0
void __fastcall FUN_0041a9f0(int param_1, int param_2)
{
}

// STUB: SADX 0x0041aa50
void __fastcall FUN_0041aa50(int param_1, int param_2)
{
}

// STUB: SADX 0x0041aab0
void __fastcall FUN_0041aab0(int param_1, int param_2)
{
}

// STUB: SADX 0x0041ab10
void __fastcall FUN_0041ab10(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x0041ab70
float __fastcall FUN_0041ab70(float *param_1)
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
	var1 = param_1[3];
	var1 = var1 * var1;
	var2 = var1 + var2;
	return sqrt(var2);
}
