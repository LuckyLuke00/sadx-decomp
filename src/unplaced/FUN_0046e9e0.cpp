#include "decls.h"
void FUN_00711140();

// FUNCTION: SADX 0x0046ea30
void FUN_0046ea30(void *param_1)
{
	ALO_RingWinDelete();
}

// FUNCTION: SADX 0x0046ea60
unsigned long GetTotalRing()
{
	return FUN_00554a80();
}

// FUNCTION: SADX 0x0046ea70
void FUN_0046ea70()
{
	__asm
	{
		push eax
		call FUN_00711140
		pop ecx
	}
}
