#include "decls.h"
extern unsigned char DAT_05ab4225;
extern unsigned char DAT_05ab4226;

// FUNCTION: SADX 0x0041a7d0
void FUN_0041a7d0(int param_1)
{
	*(int *)((char *)DAT_05ab39ac + 0x2798) = param_1;
}

// FUNCTION: SADX 0x0041a7f0
void FUN_0041a7f0(void)
{
	DAT_05ab4225 = 1;
	DAT_05ab4226 = 1;
}

// FUNCTION: SADX 0x0041a870
void __fastcall FUN_0041a870(int param_1)
{
	delete *(void **)(param_1 + 4);
}
