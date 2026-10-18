#include "decls.h"

extern int DAT_05cd14d4;
extern struct task *DAT_05cda18c;

void FUN_0049f780();
void FUN_007d21b0(void *param_1);
int FUN_004c39c0(int param_1);

// FUNCTION: SADX 0x004bad70
int FUN_004bad70()
{
	int result;

	GetSwitchData();
	PadReadOn();
	FUN_0049f780();
	LoopTask();
	FUN_007d21b0((void *)1);
	___njFogDisable();
	DisplayTask();
	DAT_05cd14d4 = 0;
	if (FUN_004c39c0(0))
	{
		result = *(int *)(*(int *)((char *)DAT_05cda18c + 0x2c) + 0xc) == 5 ? 0x6c : -2;
		GenocideTask();
		return result;
	}
	return 0;
}
