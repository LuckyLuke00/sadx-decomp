#include "decls.h"
void FUN_00440050(void);
extern struct chao_save_info *DAT_05b067b0[4];
extern int DAT_05b067ac;
extern int DAT_05b067a8;

// STUB: SADX 0x0043fd60
void AL_InitChaoSaveInfo()
{
}

#pragma optimize("", off)
// STUB: SADX 0x0043ffa0
long AL_GetLocalChaoCount(long garden)
{
	return (long)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0043fff0
long AL_GetCurrGardenChaoCount()
{
	return AL_GetLocalChaoCount(AL_GetStageNumber());
}

// STUB: SADX 0x00440000
long AL_GetAllChaoCount()
{
	return (long)0;
}

// FUNCTION: SADX 0x00440040
int FUN_00440040()
{
	return DAT_05b067a8;
}

// FUNCTION: SADX 0x00440050
void FUN_00440050(void)
{
	DAT_05b067a8 = 0;
}

#pragma optimize("", off)
// STUB: SADX 0x00440060
struct chao_save_info *AL_GetNewChaoSaveInfo()
{
	return (struct chao_save_info *)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004400d0
struct chao_save_info *AL_SetHoldingEggBM(long EggColor)
{
	if (FUN_00440040() != 0)
	{
		return NULL;
	}
	struct chao_save_info *var1 = AL_GetNewChaoSaveInfo();
	if (var1 != NULL)
	{
		AL_GeneCreate((struct AL_GENE *)((char *)var1 + 0x438));
		*(char *)((char *)var1 + 0x439) = (char)EggColor;
		*(char *)((char *)var1 + 0x80) = 1;
	}
	DAT_05b067a8 = (int)var1;
	return var1;
}

// STUB: SADX 0x00440450
struct task *AL_CreateHoldingChao()
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x00440540
void AL_SetHoldingChaoInfo(struct task *pChaoTask)
{
	if (pChaoTask != NULL)
	{
		DAT_05b067a8 = *(int *)((char *)pChaoTask->twp + 0x6c);
		DAT_05b067ac = 1;
		return;
	}
	FUN_00440050();
}

// FUNCTION: SADX 0x00440570
void AL_SetHoldingEggInfo(struct task *pEggTask)
{
	if (pEggTask != NULL)
	{
		DAT_05b067a8 = *(int *)((char *)pEggTask->twp + 0x6c);
		return;
	}
	FUN_00440050();
}

// FUNCTION: SADX 0x00440590
void AL_SetSelectedChaoSaveInfo(unsigned long PlayerNum, struct chao_save_info *pSaveInfo)
{
	DAT_05b067b0[PlayerNum] = pSaveInfo;
}

// FUNCTION: SADX 0x004405a0
struct chao_save_info *AL_GetSelectedChaoSaveInfo(unsigned long PlayerNum)
{
	return DAT_05b067b0[PlayerNum];
}
