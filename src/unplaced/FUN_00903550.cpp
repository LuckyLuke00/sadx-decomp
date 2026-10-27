#include "decls.h"

// FUNCTION: SADX 0x00903550
int __fastcall FUN_00903550(void *param_1)
{
	struct taskwk *var1 = *(struct taskwk **)((char *)param_1 + 0x6c);
	float var2 = *(float *)((char *)param_1 + 0x7c) + *(float *)((char *)param_1 + 0x78);
	*(float *)((char *)param_1 + 0x78) = var2;
	int var3 = *(int *)((char *)var1 + 4) - 1;
	float var4 = (float)(unsigned int)var3;
	if (var4 <= var2)
	{
		*(float *)((char *)param_1 + 0x78) = var4;
		return 1;
	}
	return 0;
}
