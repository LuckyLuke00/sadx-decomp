#include "decls.h"

// FUNCTION: SADX 0x0090ad90
void __fastcall FUN_0090ad90(int param_1)
{
	if (*(int *)(param_1 + 0x28) != 0)
	{
		FUN_0090bd00(*(int *)(param_1 + 0x40));
		*(int *)(param_1 + 0x28) = 0;
	}
}
