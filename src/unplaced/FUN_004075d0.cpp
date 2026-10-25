#include "decls.h"

// FUNCTION: SADX 0x00407770
void FUN_00407770(void *param_1, int param_2)
{
	if (*(unsigned int *)((char *)param_2 + 0x44) >= 0x10)
	{
		delete *(void **)((char *)param_2 + 0x30);
	}
	*(int *)((char *)param_2 + 0x44) = 0xf;
	*(int *)((char *)param_2 + 0x40) = 0;
	*(char *)((char *)param_2 + 0x30) = 0;
}

// STUB: SADX 0x00407850
void __fastcall FUN_00407850(void *param_1, int param_2)
{
}

// STUB: SADX 0x00407880
void __fastcall FUN_00407880(void *param_1, int param_2)
{
}
