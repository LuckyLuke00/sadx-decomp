#include "decls.h"
void FUN_007f25b0();
void MainBGM_Stop();
extern int DAT_060e3d64;
void FUN_007f2240();

// FUNCTION: SADX 0x009041e0
void FUN_009041e0()
{
	if (DAT_060e3d64 == 0)
	{
		FUN_007f2240();
		DAT_060e3d64 = 1;
	}
}

// FUNCTION: SADX 0x00904200
void FUN_00904200()
{
	MainBGM_Stop();
	DAT_060e3d64 = 0;
}

// FUNCTION: SADX 0x00904210
void FUN_00904210()
{
	FUN_007f25b0();
	SetGameLoop(1);
}

// FUNCTION: SADX 0x00904220
void __fastcall FUN_00904220(int param_1, int param_2, int param_3)
{
	*(int *)(param_1 + 0x28) = param_3;
}
