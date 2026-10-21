#include "decls.h"
extern int DAT_05aeb694;
int FUN_0043ed90();
extern int DAT_05aeb690;

// FUNCTION: SADX 0x0043f310
int FUN_0043f310()
{
	return FUN_0043ed90() + 0x65c;
}

// FUNCTION: SADX 0x0043f320
int FUN_0043f320()
{
	return FUN_0043ed90();
}

// FUNCTION: SADX 0x0043f340
void FUN_0043f340(int param_1)
{
	*(int *)((char *)FUN_0043ed90() + 8) |= param_1;
}

// FUNCTION: SADX 0x0043f350
void AL_ClearHoldingItemInfo()
{
	DAT_05aeb690 = -1;
	DAT_05aeb694 = 0;
}

// FUNCTION: SADX 0x0043f370
void AL_SetHoldingItemInfo(long category, struct ITEM_SAVE_INFO *pSaveInfo)
{
	DAT_05aeb690 = category;
	DAT_05aeb694 = (int)pSaveInfo;
}

// FUNCTION: SADX 0x0043f390
int FUN_0043f390()
{
	return DAT_05aeb690;
}
