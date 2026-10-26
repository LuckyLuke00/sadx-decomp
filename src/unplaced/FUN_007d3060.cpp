#include "decls.h"

// FUNCTION: SADX 0x007d3060
void FUN_007d3060(void)
{
	char *var1 = (char *)DAT_060cc140 + 0x20;
	char *var2 = *(char **)(var1);
	char *var3 = *(char **)(var2 + 0x10);
	*(float *)(var3 + 0x44) = -25.0f;
	*(float *)(var3 + 0x64) = 1.0f;
	*(float *)(var3 + 0x68) = 1.0f;
	*(float *)(var3 + 0x6c) = 1.0f;
	*(float *)(var3 + 0x70) = 0.5f;
	*(char *)var2 = 5;
}
