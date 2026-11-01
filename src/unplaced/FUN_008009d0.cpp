#include "decls.h"
extern int DAT_060ceaa4;

// FUNCTION: SADX 0x008009d0
void FUN_008009d0(int param_1)
{
	int var1 = *(int *)(param_1 + 0x20);
	int var2 = *(int *)(var1 + 0x2c);
	int var3 = *(int *)(var2 + 0x18);
	if (var3 != 0)
	{
		DAT_060ceaa4--;
		Free((void *)(var3 - 0x48));
		*(int *)(*(int *)(var1 + 0x2c) + 0x18) = 0;
		*(int *)(*(int *)(var1 + 0x2c) + 0x1c) = 0;
	}
	Free(*(void **)(var1 + 0x2c));
}
