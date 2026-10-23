#include "decls.h"
extern int DAT_060ccb24;

// FUNCTION: SADX 0x007db7c0
void FUN_007db7c0(int param_1, int param_2, int param_3)
{
	int *var1 = (int *)*(int *)((char *)DAT_060ccb24 + 0x20);
	*(int *)((char *)var1 + 0x14) = param_1;
	*(int *)((char *)var1 + 0x18) = param_2;
	*(int *)((char *)var1 + 0x1c) = param_3;
}

// FUNCTION: SADX 0x007db7e0
void FUN_007db7e0(void)
{
	char *var1 = (char *)DAT_060ccb24 + 0x20;
	char *var2 = *(char **)(var1);
	char *var3 = *(char **)(var2 + 0x10);
	*(float *)(var3 + 0x28) = -25.0f;
	*(float *)(var3 + 0x48) = 1.0f;
	*(float *)(var3 + 0x4c) = 1.0f;
	*(float *)(var3 + 0x50) = 1.0f;
	*(float *)(var3 + 0x54) = 0.6f;
	*(char *)var2 = 3;
}
