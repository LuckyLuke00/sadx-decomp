#include "decls.h"
extern int DAT_05b067a8;

// STUB: SADX 0x0043ffa0
long AL_GetLocalChaoCount(long garden)
{
	return (long)0;
}

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

// STUB: SADX 0x00440060
struct chao_save_info *AL_GetNewChaoSaveInfo()
{
	return (struct chao_save_info *)0;
}

// STUB: SADX 0x004400d0
struct chao_save_info *AL_SetHoldingEggBM(long EggColor)
{
	return (struct chao_save_info *)0;
}

// STUB: SADX 0x00440540
void AL_SetHoldingChaoInfo(struct task *pChaoTask)
{
}
