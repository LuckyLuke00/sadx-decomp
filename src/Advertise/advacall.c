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
long Title2Init(void *param_1)
{
	unsigned char *local_4;
	long local_8;

	DAT_05ad95e1 = 1;
	FUN_004bac60();
	SetViewAngle(0x31c7);
	FUN_004a0520(-1.0f, -65535.0f);
	njSetCamera(&DAT_06298c48);
	LoadTextureForEachGameMode(0);
	LoadPlayerMotionData(0);
	DAT_05cda18c = 0;
	local_4 = (unsigned char *)param_1;
	switch (*local_4)
	{
	case 1:
		local_8 = 1;
		break;
	case 2:
		local_8 = 2;
		break;
	case 3:
		local_8 = 3;
		break;
	default:
		DAT_05cd14e2 = 0;
		DAT_05cd14eb = 0;
		local_8 = 0;
		DAT_05b9d848 = 0;
		break;
	}
	SetAdvaSequenceTask((struct SeqPrmType *)&local_8);
	if (local_4[1] != 0)
	{
		FUN_005b5aa0();
	}
	DAT_05ad95e1 = 0;
	return 0;
}

// FUNCTION: SADX 0x004bacf0
long Title2Exit(void *param_1)
{
	npSetZCompareMode(1);
	ReleaseTextureForEachGameMode();
	FreeAdvaSequenceTask();
	GenocideTask();
	FUN_005b5aa0();
	return 0;
}

// FUNCTION: SADX 0x004bad20
long Title2Loop(void *param_1)
{
	long local_4;

	npSetZCompareMode(3);
	local_4 = FUN_004bad70();
	if (local_4 == 0)
	{
		if (*(int *)((char *)DAT_05cda18c + 0x2c) == 0)
		{
			local_4 = -2;
		}
		else
		{
			local_4 = *(int *)(*(int *)((char *)DAT_05cda18c + 0x2c) + 0x14);
		}
	}
	FUN_005b5aa0();
	return local_4;
}
