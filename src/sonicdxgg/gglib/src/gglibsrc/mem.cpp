#include "decls.h"

// FUNCTION: SADX 0x0091b2d0
void __fastcall FUN_0091b2d0(int param_1)
{
	if (*(int *)(param_1 + 0x20) != 0)
	{
		if (*(int *)(param_1 + 0x30) != 0)
		{
			delete *(void **)(param_1 + 0x30);
			*(int *)(param_1 + 0x30) = 0;
		}
		*(int *)(param_1 + 0x20) = 0;
	}
}

// STUB: SADX 0x0091b5f0
void __fastcall FUN_0091b5f0(void *param_1, char param_2)
{
}
