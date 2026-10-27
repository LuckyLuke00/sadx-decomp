#include "decls.h"
extern unsigned char DAT_04c2e568[7];
extern int DAT_04c2e570[8];
extern int DAT_05b3ea10;
extern int DAT_05b3e350;
extern int DAT_05cd14d4;
extern struct task *DAT_060dd870;
extern int DAT_060dd88c;
extern struct GH_FONT_INFO StaffRollFontInfo[];
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern int DAT_060dd888;
void late_DrawBoxFill2D(float x, float y, float x2, float y2, float pri, unsigned long argb, int flgs);

// FUNCTION: SADX 0x008b7850
void StaffRollBgmTask(struct task *tp)
{
	int var1;

	var1 = GetAdvertisePlayerNumber(GetPlayerNumber());
	if (var1 != -1)
	{
		BGM_Play(DAT_04c2e568[var1]);
	}
	FreeTask(tp);
}

// STUB: SADX 0x008b7ad0
struct task *CreateStaffTask(struct task *staffroll_tp)
{
	return (struct task *)0;
}

// STUB: SADX 0x008b7bd0
unsigned long GetNextStaffInterval(struct STAFFROLL_DATA *data, unsigned long staffno)
{
	return (unsigned long)0;
}

// STUB: SADX 0x008b7c70
unsigned long GetAllStaffInterval(struct STAFFROLL_DATA *data)
{
	return (unsigned long)0;
}

// STUB: SADX 0x008b7d40
unsigned long GetStaffIntervalFotLogoStaff(struct STAFFROLL_DATA *data)
{
	return (unsigned long)0;
}

// STUB: SADX 0x008b8040
int FUN_008b8040(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x008b80b0
void LoadSnapShotTexture(struct SNAPSHOT_DATA *data)
{
	int var1;

	var1 = 0;
	while (var1 < data->nbTexlist)
	{
		texLoadTexturePvmFile(data->pvmfile[var1], data->texlist[var1]);
		var1++;
	}
	if (data->lastpvmfile != 0 && data->lasttexlist != 0)
	{
		texLoadTexturePvmFile(data->lastpvmfile, data->lasttexlist);
	}
}

// FUNCTION: SADX 0x008b8100
void ReleaseSnapShotTexture(struct SNAPSHOT_DATA *data)
{
	int var1;

	var1 = 0;
	while (var1 < data->nbTexlist)
	{
		if (data->texlist[var1] != 0)
		{
			late_ReleaseTexture(data->texlist[var1]);
		}
		var1++;
	}
	if (data->lasttexlist != 0)
	{
		late_ReleaseTexture(data->lasttexlist);
	}
}

// FUNCTION: SADX 0x008b8140
void FUN_008b8140(void)
{
	int var1;
	float var2;
	float var3;

	var2 = ScreenRaitoX * 640.0f;
	var3 = ScreenRaitoY * 480.0f;
	var1 = (int)((float)DAT_060dd888 / 300.0f * 255.0f);
	late_DrawBoxFill2D(0.0f, 0.0f, var2, var3, 22047.0f, (unsigned long)((unsigned char)var1) << 0x18, 1);
}

// FUNCTION: SADX 0x008b81d0
long StaffRollExit(void *Param)
{
	int var1;

	DAT_05cd14d4 = 1;
	var1 = GetAdvertisePlayerNumber((unsigned char)GetPlayerNumber());
	ADX_Close();
	if (DAT_060dd870 != 0)
	{
		FreeTask(DAT_060dd870);
		DAT_060dd870 = 0;
	}
	GenocideTask();
	LoopTask();
	ReleaseSnapShotTexture(&SnapShotDataTbl[var1]);
	if (DAT_060dd88c == 0)
	{
		late_ReleaseTexture(&texlist_endbg_logo);
	}
	ghReleaseFontTexture(&StaffRollFontInfo[0]);
	___njReleaseTextureAll();
	FUN_007d21b0((void *)1);
	DAT_05b3e350 = 0;
	DAT_05cd14d4 = 0;
	return 0;
}

// STUB: SADX 0x008b8530
void StaffRollTask(struct task *tp)
{
}

// FUNCTION: SADX 0x008b8630
struct task *CreateStaffRollTask(struct STAFFROLL_DATA *data, int plno)
{
	struct task *var1;
	void *var2;
	int local_10;
	int local_c;
	float local_8;

	var1 = CreateElementalTask(2, 5, StaffRollTask);
	if (var1 != 0)
	{
		var2 = CAlloc(1, 0x38);
		*(void **)((char *)var1 + 0x2c) = var2;
		*(void **)((char *)var2 + 0x2c) = data;
		local_10 = plno;
		*(char *)((char *)var2 + 2) = (char)local_10;
		if (DAT_05b3ea10 == 1)
		{
			local_c = (DAT_04c2e570[local_10] * 0x32) / 0x3c;
		}
		else
		{
			local_c = DAT_04c2e570[local_10];
		}
		*(int *)((char *)var2 + 0xc) = local_c;
		*(int *)((char *)var2 + 0x10) = 0x20;
		local_8 = (float)GetAllStaffInterval(data);
		local_8 /= (float)local_c;
		*(float *)((char *)var2 + 0x24) = local_8;
		*(struct NJS_TEXLIST **)((char *)var2 + 0x34) = &texlist_endbg_logo;
		*(float *)((char *)var2 + 0x14) = 30.0;
	}
	return var1;
}
