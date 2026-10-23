#include "decls.h"
extern int DAT_009c2d58[];
extern int DAT_060ee558;

// FUNCTION: SADX 0x00908fb0
void FUN_00908fb0(void)
{
	DAT_060ee558 ^= 1;
}

// FUNCTION: SADX 0x009090a0
int __stdcall FUN_009090a0(int param_1)
{
	return DAT_009c2d58[param_1];
}
