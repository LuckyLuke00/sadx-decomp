#include "decls.h"

// FUNCTION: SADX 0x0047be10
void FUN_0047be10(void *param_1)
{
	if (*(void **)((char *)param_1 + 0x30) != NULL)
	{
		Free(*(void **)((char *)param_1 + 0x30));
		*(void **)((char *)param_1 + 0x30) = NULL;
	}
}

// FUNCTION: SADX 0x0047c660
int FUN_0047c660(void)
{
	int var1;
	int var2;
	int var3;

	var3 = 0;
	for (var1 = 1; var1 < 4; var1++)
	{
		for (var2 = 3; var2 < 0xb; var2++)
		{
			var3 += AL_GBAManagerIsSelected(var1, var2) != 0;
		}
	}
	return var3;
}
