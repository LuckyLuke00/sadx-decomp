#include "decls.h"
extern struct NJS_TEXLIST *DAT_05b37300;
extern float DAT_05b372e8;
extern float DAT_05b372ec;
extern float DAT_05b372f4;
extern float DAT_05b372f8;
extern struct NJS_TEXLIST texlist_mis_p;
extern struct NJS_TEXLIST texlist_timeover;
void late_ReleaseTexture(struct NJS_TEXLIST *tl);
extern int DAT_05b372e4;
extern int DAT_05b42a80;
extern struct NJS_TEXLIST texlist_mis_c;
extern int DAT_05b37308;

// FUNCTION: SADX 0x00497340
int IsDisplayMiClearStatus()
{
	return DAT_05b37308 == 2;
}

// FUNCTION: SADX 0x00497350
void DispMiClearStatusOn()
{
	if (DAT_05b37308 == 0)
	{
		DAT_05b37308 = 1;
	}
}

// FUNCTION: SADX 0x00497370
long GetMiClearStatus()
{
	return DAT_05b37308 != 0;
}

// FUNCTION: SADX 0x00497380
void ReleaseMiClearStatus()
{
	int var1;
	var1 = DAT_05b372e4;
	DAT_05b42a80 = var1;
	___njSetPerspective(var1);
	ReleaseMiMessage();
	late_ReleaseTexture(&texlist_mis_c);
	DAT_05b37308 = 0;
}

// FUNCTION: SADX 0x00498030
void DrawSprite_Signal(unsigned char index, float x, float y, float scale, float alpha)
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	FUN_007d21b0(0);
	___njSetTexture(DAT_05b37300);
	DAT_05b372f4 = scale;
	DAT_05b372f8 = scale;
	DAT_05b372e8 = x;
	DAT_05b372ec = y;
	SetMaterial(alpha, 1.0f, 1.0f, 1.0f);
	late_DrawSprite2D((struct NJS_SPRITE *)&DAT_05b372e8, index, 22046.998f, 0x22, 4);
	ResetMaterial();
}

// FUNCTION: SADX 0x004980c0
void DestructorMissionTimeOver(struct task *tp)
{
	late_ReleaseTexture(&texlist_timeover);
}

// FUNCTION: SADX 0x004982c0
void DestructorMissionSignal(struct task *tp)
{
	late_ReleaseTexture(&texlist_mis_p);
}
