#include "decls.h"

// FUNCTION: SADX 0x007d1c90
void FUN_007d1c90(int param_1, int param_2, float param_3, int param_4)
{
	int *var1 = (int *)DAT_060cbfdc[param_1];
	int *var2 = *(int **)((char *)var1 + 0x20);
	int *var3 = *(int **)((char *)var2 + 0x10);
	*(float *)((char *)var3 + 0x34) = param_3;
	*(int *)((char *)var3 + 0x3c) = param_2;
	*(float *)((char *)var2 + 8) = 0.0f;
	*(int *)((char *)var2 + 0xc) = param_4;
	*(char *)var2 = 1;
}
