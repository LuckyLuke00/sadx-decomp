#include "decls.h"
extern int DAT_05b3e350;
extern int DAT_05cd14d4;
extern struct task *DAT_060dd870;
extern int DAT_060dd88c;
extern struct GH_FONT_INFO StaffRollFontInfo[];
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern int DAT_060dd888;
void late_DrawBoxFill2D(float x, float y, float x2, float y2, float pri, unsigned long argb, int flgs);

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

// STUB: SADX 0x008b8630
struct task *CreateStaffRollTask(struct STAFFROLL_DATA *data, int plno)
{
	return (struct task *)0;
}
