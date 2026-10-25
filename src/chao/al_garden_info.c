#include "decls.h"
void FUN_0043ede0();
void FUN_0043ee00();
int syTmrGetCount();
unsigned long chRandomU32(void);
void FUN_0043eea0();
void FUN_0043f5a0(int param_1);
extern int FUN_0043ed90();
extern int DAT_05aeb698;
extern char DAT_05aeb6a0;
extern int DAT_05aeb694;
int FUN_0043ed90();
extern int DAT_05aeb690;

// FUNCTION: SADX 0x0043edb0
struct CHAO_GARDEN_INFO *AL_GetAnotherGardenInfo()
{
	return (struct CHAO_GARDEN_INFO *)((char *)&DAT_05aeb6a0 + (~ALMC_GetSystemSlot() & 1) * 0xc820);
}

// FUNCTION: SADX 0x0043edd0
char *FUN_0043edd0(int param_1)
{
	return &DAT_05aeb6a0 + param_1 * 0xc820;
}

// FUNCTION: SADX 0x0043ede0
void FUN_0043ede0()
{
	int *var1 = (int *)FUN_0043ed90();
	*var1 = syTmrGetCount();
	var1[1] = chRandomU32();
}

// STUB: SADX 0x0043ee00
void FUN_0043ee00()
{
}

// STUB: SADX 0x0043eea0
void FUN_0043eea0()
{
}

// FUNCTION: SADX 0x0043ef60
void AL_SetAnotherGardenLoaded()
{
	DAT_05aeb698 = 1;
}

// STUB: SADX 0x0043f000
void FUN_0043f000()
{
}

// STUB: SADX 0x0043f060
void AL_ExtractKinderSaveInfo()
{
}

// STUB: SADX 0x0043f0a0
void FUN_0043f0a0()
{
}

// STUB: SADX 0x0043f0e0
void FUN_0043f0e0(int param_1, int param_2)
{
}

// STUB: SADX 0x0043f300
void FUN_0043f300()
{
}

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

// FUNCTION: SADX 0x0043f330
int FUN_0043f330()
{
	return 0x18;
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

// FUNCTION: SADX 0x0043f3a0
void *AL_GetHoldingItemSaveInfo()
{
	return (void *)DAT_05aeb694;
}

// FUNCTION: SADX 0x0043f3b0
int FUN_0043f3b0(void)
{
	if (DAT_05aeb694 != 0)
	{
		return *(short *)((char *)DAT_05aeb694 + 0x0);
	}
	return -1;
}

// FUNCTION: SADX 0x0043f3d0
long AL_GetCurrGardenFruitNum()
{
	int var1;
	int var2;
	AL_GetStageNumber();
	for (var1 = 5; var1 != 0; var1--)
	{
		for (var2 = 3; var2 != 0; var2--)
		{
			FUN_0043ed90();
		}
	}
	return ALW_CountEntry(3);
}

// FUNCTION: SADX 0x0043f510
int FUN_0043f510(int param_1)
{
	if (param_1 != 3)
	{
		int var1 = param_1 != 9;
		return ((var1 - 1) & 0x18);
	}
	return 0x28;
}

// FUNCTION: SADX 0x0043f530
void AL_ClearItemSaveInfo(struct ITEM_SAVE_INFO *pSaveInfo)
{
	pSaveInfo->kind = -1;
	pSaveInfo->place = -1;
	pSaveInfo->status = 0;
	pSaveInfo->nbVisit = 0;
	pSaveInfo->pos.x = 0.0f;
	pSaveInfo->pos.y = 0.0f;
	pSaveInfo->pos.z = 0.0f;
}

// FUNCTION: SADX 0x0043f560
struct ITEM_SAVE_INFO *AL_GetItemSaveInfo(struct task *pItemTask)
{
	struct task *var1;
	var1 = (struct task *)pItemTask->fwp;
	if (var1 != NULL)
	{
		return (struct ITEM_SAVE_INFO *)*(void **)((char *)var1 + 8);
	}
	return NULL;
}

// FUNCTION: SADX 0x0043f580
void AL_ClearItemSaveInfoPtr(struct task *pItemTask)
{
	if (pItemTask->fwp != NULL)
	{
		*(int *)((char *)pItemTask->fwp + 8) = 0;
	}
}

// FUNCTION: SADX 0x0043f5a0
void FUN_0043f5a0(int param_1)
{
	int var1;
	int var2;
	struct ITEM_SAVE_INFO *var3;
	var1 = FUN_0043ed90();
	switch (param_1)
	{
		case 9:
			for (var2 = 0; var2 < 0x18; var2++)
			{
				var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x3b4 + var2 * 0x14);
				AL_ClearItemSaveInfo(var3);
			}
			return;
		case 3:
			for (var2 = 0; var2 < 0x28; var2++)
			{
				var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x94 + var2 * 0x14);
				AL_ClearItemSaveInfo(var3);
			}
			return;
		case 2:
			for (var2 = 0; var2 < 0xa; var2++)
			{
				var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x594 + var2 * 0x14);
				AL_ClearItemSaveInfo(var3);
			}
			return;
	}
}

// FUNCTION: SADX 0x0043f620
struct ITEM_SAVE_INFO *AL_GetNewItemSaveInfo(long category)
{
	int var1;
	int var2;
	struct ITEM_SAVE_INFO *var3;
	var1 = FUN_0043ed90();
	switch (category)
	{
		case 9:
			for (var2 = 0; var2 < 0x18; var2++)
			{
				if (*(short *)((char *)var1 + 0x3b4 + var2 * 0x14) == -1)
				{
					var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x3b4 + var2 * 0x14);
					return var3;
				}
			}
			return 0;
		case 3:
			for (var2 = 0; var2 < 0x28; var2++)
			{
				if (*(short *)((char *)var1 + 0x94 + var2 * 0x14) == -1)
				{
					var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x94 + var2 * 0x14);
					return var3;
				}
			}
			return 0;
		case 2:
			for (var2 = 0; var2 < 0xa; var2++)
			{
				if (*(short *)((char *)var1 + 0x594 + var2 * 0x14) == -1)
				{
					var3 = (struct ITEM_SAVE_INFO *)((char *)var1 + 0x594 + var2 * 0x14);
					return var3;
				}
			}
			return 0;
	}
	return 0;
}

// FUNCTION: SADX 0x0043f8e0
void FUN_0043f8e0()
{
	AL_PackageItemSaveInfo(2);
	AL_PackageItemSaveInfo(3);
	AL_PackageItemSaveInfo(9);
}

// STUB: SADX 0x0043fae0
void FUN_0043fae0()
{
}

// STUB: SADX 0x0043fb50
void FUN_0043fb50()
{
}

// STUB: SADX 0x0043fb80
void FUN_0043fb80()
{
}
