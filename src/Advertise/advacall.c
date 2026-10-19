#include "decls.h"

extern unsigned char DAT_05ad95e1;
extern unsigned char DAT_05cd14e2;
extern unsigned char DAT_05cd14eb;
extern int DAT_05b9d848;
extern struct NJS_CAMERA DAT_06298c48;

void FUN_004bac60();
void FUN_004a0520(float param_1, float param_2);
void FUN_005b5aa0();

// FUNCTION: SADX 0x004bab70
long Title2Init(void *Param)
{
	unsigned char *local_8g;
	long local_cg;

	DAT_05ad95e1 = 1;
	FUN_004bac60();
	SetViewAngle(0x31c7);
	FUN_004a0520(-1.0f, -65535.0f);
	njSetCamera(&DAT_06298c48);
	LoadTextureForEachGameMode(0);
	LoadPlayerMotionData(0);
	DAT_05cda18c = 0;
	local_8g = (unsigned char *)Param;
	switch (*local_8g)
	{
	case 1:
		local_cg = 1;
		break;
	case 2:
		local_cg = 2;
		break;
	case 3:
		local_cg = 3;
		break;
	default:
		DAT_05cd14e2 = 0;
		DAT_05cd14eb = 0;
		local_cg = 0;
		DAT_05b9d848 = 0;
		break;
	}
	SetAdvaSequenceTask((struct SeqPrmType *)&local_cg);
	if (local_8g[1] != 0)
	{
		FUN_005b5aa0();
	}
	DAT_05ad95e1 = 0;
	return 0;
}

// FUNCTION: SADX 0x004bacf0
long Title2Exit(void *Param)
{
	npSetZCompareMode(1);
	ReleaseTextureForEachGameMode();
	FreeAdvaSequenceTask();
	GenocideTask();
	FUN_005b5aa0();
	return 0;
}

// FUNCTION: SADX 0x004bad20
long Title2Loop(void *Param)
{
	long local_8;

	npSetZCompareMode(3);
	local_8 = FUN_004bad70();
	if (local_8 == 0)
	{
		if (*(int *)((char *)DAT_05cda18c + 0x2c) == 0)
		{
			local_8 = -2;
		}
		else
		{
			local_8 = *(int *)(*(int *)((char *)DAT_05cda18c + 0x2c) + 0x14);
		}
	}
	FUN_005b5aa0();
	return local_8;
}
