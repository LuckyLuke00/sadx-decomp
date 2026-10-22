#include "decls.h"

extern int DAT_05b935cc;

// FUNCTION: SADX 0x004c3310
void FUN_004c3310(int *param_1)
{
	FUN_004c1b70((char *)param_1);
	*(int *)((char *)param_1 + 0x28) = 0;
}

// FUNCTION: SADX 0x004c3330
void FUN_004c3330(int param_1)
{
	DAT_05b935cc = param_1;
}
