#include "decls.h"
extern char DAT_05cda0c6;
extern char character_name[6][10];
static unsigned char stageact_tbl[76][2];
extern float DAT_05cda0f0[6];
extern struct NJS_TEXANIM anim_hint2[6];
extern struct NJS_TEXLIST *hinttexlist[6];
extern struct NJS_TEXANIM anim_hint1[6];
extern float DAT_05cda0e0;

// GLOBAL: SADX 0x026093e8
static struct NJS_TEXANIM anim_title[6];


extern int DAT_05cd14d4;
extern int DAT_05cda0d8;
extern int DAT_05cda0dc;
extern int DAT_05cda0e8;
extern int DAT_05cda108;
extern int DAT_05cda10c;
extern int DAT_05cda110;
extern int DAT_05cda170;
extern unsigned char DAT_05cda0c5;
extern unsigned char DAT_05cda0c7;
extern float _nj_unit_matrix_[16];
extern struct NJS_TEXLIST texlist_title;
extern struct NJS_POINT3 DAT_05cda0cc;
void dsInitTitle();
void InitMemory();
void InitTask();
void ADX_Close();
void dsSetFade(int fade_lev);
void ___njSetBackColor(unsigned long c0, unsigned long c1, unsigned long c2);
void texLoadTexturePvmFile(char *fname, struct NJS_TEXLIST *ptlo);
void dsLoadStageSound();
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern int DAT_05b92eb8;
extern int DAT_05cda0ec;
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern unsigned char DAT_05cda0c4;
extern int DAT_05cda0c8;
extern int DAT_05cda0e4;

// FUNCTION: SADX 0x00599aa0
void InitTitle()
{
	struct NJS_POINT3 u;

	dsInitTitle();
	DAT_05cda10c = 0;
	DAT_05cd14d4 = 1;
	DAT_05cda0e8 = 1;
	InitMemory();
	InitTask();
	ADX_Close();
	DAT_05cda0dc = 0;
	DAT_05cda110 = 0;
	DAT_05cda108 = 1;
	DAT_05cda0d8 = 0;
	dsSetFade(0);
	___njSetBackColor(0xff000000, 0xff000000, 0xff000000);
	texLoadTexturePvmFile("TITLE", &texlist_title);
	DAT_05cda0c5 = 0;
	DAT_05cda0c4 = 0;
	DAT_05cda0c7 = 0;
	DAT_05cda0ec = 0;
	DAT_05cda170 = 0;
	dsLoadStageSound();
	u.x = -6613.86f;
	u.y = -10572.42f;
	u.z = -1697.97f;
	njPushMatrix(&_nj_unit_matrix_);
	FUN_0067d830(0, -1482.63f, -4582.89f, 5921.56f);
	UNKNOWN_ROTATE_Y_MACRO(0, 0xce75);
	njCalcPoint(0, &u, &DAT_05cda0cc);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0059a560
void DisplayTitle()
{
	struct NJS_SPRITE Sprite;
	int local_8g;
	Sprite.tlist = &texlist_title;
	Sprite.tanim = (struct NJS_TEXANIM *)&anim_title;
	___njSetTexture(Sprite.tlist);
	Sprite.sx = 1.0;
	Sprite.sy = 1.0;
	Sprite.p.x = 320.0;
	Sprite.p.y = 0.0;
	for (local_8g = 0; local_8g < 6; local_8g++)
	{
		float local_30;
		local_30 = -1.0;
		if (local_30 >= -3.0)
		{
			if (local_30 < 12048.0)
			{
				local_30 += 22048.0;
			}
		}
		late_DrawSprite2D(&Sprite, local_8g, local_30, 0, 4);
	}
}

// FUNCTION: SADX 0x0059a620
void DisplaySelectingCharacter()
{
	struct NJS_SPRITE Sprite;
	int local_cg;
	int local_8g;
	float local_34t;

	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	for (local_cg = 0; local_cg < 6; local_cg = local_cg + 1)
	{
		if ((char)DAT_05cda0c4 == local_cg)
		{
			DAT_05cda0f0[local_cg] = 1.0f;
		}
		else
		{
			DAT_05cda0f0[local_cg] = DAT_05cda0f0[local_cg] - 0.2f;
			if (DAT_05cda0f0[local_cg] < 0.0f)
			{
				DAT_05cda0f0[local_cg] = 0.0f;
			}
		}
		if (local_cg == 0 || local_cg == 1 || local_cg == 5)
		{
			Sprite.tlist = &texlist_c_select1;
		}
		else
		{
			Sprite.tlist = &texlist_c_select2;
		}
		Sprite.tanim = anim_c_select;
		___njSetTexture(Sprite.tlist);
		SetMaterial(DAT_05cda0f0[local_cg], 1.0f, 1.0f, 1.0f);
		for (local_8g = 0; local_8g < 4; local_8g = local_8g + 1)
		{
			Sprite.sx = 1.25f;
			Sprite.sy = 1.0f;
			Sprite.p.x = 320.0f;
			Sprite.p.y = 0.0f;
			local_34t = -10.0f - DAT_05cda0f0[local_cg];
			if (local_34t >= -3.0f && local_34t < 12048.0f)
			{
				local_34t = local_34t + 22048.0f;
			}
			late_DrawSprite2D(&Sprite, local_cg * 4 + local_8g, local_34t, 0x22, 4);
		}
	}
	ResetMaterial();
}

// FUNCTION: SADX 0x0059a7d0
void DisplayHint1()
{
	struct NJS_SPRITE Sprite;
	int local_8g;
	Sprite.tlist = hinttexlist[(int)(char)DAT_05cda0c4];
	Sprite.tanim = (struct NJS_TEXANIM *)&anim_hint1;
	___njSetTexture(Sprite.tlist);
	Sprite.sx = 1.0;
	Sprite.sy = 1.0;
	Sprite.p.x = 320.0;
	Sprite.p.y = 0.0;
	for (local_8g = 0; local_8g < 6; local_8g++)
	{
		float local_30;
		local_30 = -1.0;
		if (local_30 >= -3.0)
		{
			if (local_30 < 12048.0)
			{
				local_30 += 22048.0;
			}
		}
		late_DrawSprite2D(&Sprite, local_8g, local_30, 0, 4);
	}
}

// FUNCTION: SADX 0x0059a8a0
void DisplayHint2()
{
	struct NJS_SPRITE Sprite;
	int local_8g;
	Sprite.tlist = hinttexlist[(int)(char)DAT_05cda0c4];
	Sprite.tanim = anim_hint2;
	___njSetTexture(Sprite.tlist);
	Sprite.sx = 1.0;
	Sprite.sy = 1.0;
	Sprite.p.x = 320.0;
	Sprite.p.y = 0.0;
	for (local_8g = 0; local_8g < 6; local_8g++)
	{
		float local_30;
		local_30 = -1.0;
		if (local_30 >= -3.0)
		{
			if (local_30 < 12048.0)
			{
				local_30 += 22048.0;
			}
		}
		late_DrawSprite2D(&Sprite, local_8g, local_30, 0, 4);
	}
}

// FUNCTION: SADX 0x0059abe0
void EndDisplayPress(struct task *tp)
{
	late_ReleaseTexture(&texlist_pressstart);
}

// FUNCTION: SADX 0x0059ac00
void dsChrCursorMove()
{
	int local_8;

	local_8 = 0;
	if ((DAT_05b92eb8 & 0x20040) != 0)
	{
		local_8 = -1;
		dsPlay_oneshot(1, 0, 0, 0);
		DAT_05cda0ec = 0;
	}
	if ((DAT_05b92eb8 & 0x10080) != 0)
	{
		local_8 = 1;
		dsPlay_oneshot(1, 0, 0, 0);
		DAT_05cda0ec = 0;
	}
	DAT_05cda0c4 = (unsigned char)((char)DAT_05cda0c4 + local_8);
	if ((char)DAT_05cda0c4 >= 6)
	{
		DAT_05cda0c4 = 0;
	}
	else if ((char)DAT_05cda0c4 < 0)
	{
		DAT_05cda0c4 = 5;
	}
}

// FUNCTION: SADX 0x0059acb0
void TitleSetStageNumber()
{
	unsigned char local_5i;
	unsigned char local_6g;

	if ((char)DAT_05cda0c4 == 4)
	{
		local_6g = 1;
		local_5i = 2;
	}
	else if ((char)DAT_05cda0c4 == 2)
	{
		local_6g = 0xc;
		local_5i = 0;
	}
	else if ((char)DAT_05cda0c4 == 3)
	{
		local_6g = 2;
		local_5i = 0;
	}
	else if ((char)DAT_05cda0c4 == 5)
	{
		local_6g = 5;
		local_5i = 2;
	}
	else if ((char)DAT_05cda0c4 == 1)
	{
		local_6g = 8;
		local_5i = 2;
	}
	else
	{
		local_6g = 4;
		local_5i = 0;
	}
	SetStageNumber(local_6g, local_5i);
	if (((*(unsigned int *)((char *)DAT_05b93264 + 8)) & 4) != 0)
	{
		DAT_05cda170 = 2;
	}
	if (((*(unsigned int *)((char *)DAT_05b93264 + 8)) & 2) != 0)
	{
		DAT_05cda170 = 1;
	}
	DAT_05cd0f28 = -1;
	DAT_05cd0f24 = 1;
	InitScore();
	SeqInit();
	FUN_00573740();
}

// FUNCTION: SADX 0x0059b280
void DisplayTitle_ss()
{
	struct NJS_SPRITE Sprite;
	int local_cg;
	float local_8g;
	float local_34t;

	local_8g = DAT_05cda0e0;
	Sprite.tlist = &texlist_title;
	Sprite.tanim = anim_title;
	___njSetTexture(Sprite.tlist);
	SetMaterial(0.0f, local_8g, local_8g, local_8g);
	Sprite.sx = 1.0f;
	Sprite.sy = 1.0f;
	Sprite.p.x = 320.0f;
	Sprite.p.y = 0.0f;
	for (local_cg = 0; local_cg < 6; local_cg = local_cg + 1)
	{
		local_34t = -1.0f;
		if (local_34t >= -3.0f && local_34t < 12048.0f)
		{
			local_34t = local_34t + 22048.0f;
		}
		late_DrawSprite2D(&Sprite, local_cg, local_34t, 2, 4);
	}
	ResetMaterial();
}

// STUB: SADX 0x0059b370
void DisplaySelectingCharacter_ss()
{
}

// FUNCTION: SADX 0x0059b440
void DisplaySelectingStage_ss()
{
	int local_8g;
	int local_cj;
	int local_10m;
	int local_18;
	int local_14;
	int local_1ci;
	int local_20;

	if (DAT_05cda0e8 == 0xa)
	{
		local_1ci = 0xff00ff00;
		local_20 = 0xffdfdfdf;
	}
	else
	{
		local_1ci = 0xff00bf00;
		local_20 = 0xff7f7f7f;
	}
	njPrintColor((unsigned long)local_20);
	njPrintC(0x100008, "STAGE SELECT");
	local_10m = (char)DAT_05cda0c5 + 0x47;
	local_8g = 0xa;
	for (local_cj = 0; local_cj < 0xd; local_cj = local_cj + 1)
	{
		local_10m = local_10m % 0x4c;
		if (local_10m == (char)DAT_05cda0c5)
		{
			njPrintColor((unsigned long)local_1ci);
		}
		else
		{
			njPrintColor((unsigned long)local_20);
		}
		local_18 = stageact_tbl[local_10m][0];
		local_14 = stageact_tbl[local_10m][1];
		FUN_005b5aa0(local_8g | 0x100000, (local_18 << 8) | local_14);
		local_10m = local_10m + 1;
		local_8g = local_8g + 1;
	}
	njPrintColor(0xffffffff);
}

// FUNCTION: SADX 0x0059b550
void DisplaySelectingSequence()
{
	int local_8g;
	int local_cj;
	int local_10;
	int local_14i;

	if (DAT_05cda0e8 == 0xb)
	{
		local_10 = 0xff00ff00;
		local_14i = 0xffdfdfdf;
	}
	else
	{
		local_10 = 0xff00bf00;
		local_14i = 0xff7f7f7f;
	}
	njPrintColor((unsigned long)local_14i);
	njPrintC(0x60008, "ADV SEQUENCE");
	local_8g = 0xa;
	for (local_cj = 0; local_cj < 6; local_cj = local_cj + 1)
	{
		if (local_cj == (char)DAT_05cda0c6)
		{
			njPrintColor((unsigned long)local_10);
		}
		else
		{
			njPrintColor((unsigned long)local_14i);
		}
		njPrintC(local_8g | 0x60000, &character_name[local_cj][0]);
		njPrintC(local_8g | 0xe0000, "STORY");
		local_8g = local_8g + 1;
	}
	njPrintColor(0xffffffff);
}

// FUNCTION: SADX 0x0059b630
void FUN_0059b630(void)
{
	if ((DAT_05cda0c8 & 0x10) == 0)
	{
		njPrintColor(0xffff0000);
		njPrintC(0x20010, "<<");
		njPrintColor(-1);
	}
}

// FUNCTION: SADX 0x0059b670
void FUN_0059b670(void)
{
	if ((DAT_05cda0c8 & 0x10) == 0)
	{
		njPrintColor(0xffff0000);
		njPrintC(0x220010, ">>");
		njPrintColor(0xffffffff);
	}
}

// FUNCTION: SADX 0x0059b6b0
void dsSetFade(int fade_lev)
{
	DAT_05cda0e4 = fade_lev;
}

// FUNCTION: SADX 0x0059b6c0
int FUN_0059b6c0(int param_1)
{
	DAT_05cda0e4 += param_1;

	if (param_1 < 0)
	{
		if (DAT_05cda0e4 < 1)
		{
			DAT_05cda0e4 = 1;
			return -1;
		}
	}
	else
	{
		if (DAT_05cda0e4 >= 0xff)
		{
			DAT_05cda0e4 = 0xff;
			return 1;
		}
	}

	return 0;
}

// FUNCTION: SADX 0x0059b720
void dsDispFadeBlack()
{
	int local_8g;
	float local_10;
	float local_cj;
	local_8g = DAT_05cda0e4;
	if (local_8g < 0)
		local_8g = 0;
	if (local_8g > 0xff)
		local_8g = 0xff;
	local_8g <<= 0x18;
	local_10 = ScreenRaitoX * 320.0f + 320.0f;
	local_cj = ScreenRaitoY * 240.0f + 240.0f;
	late_DrawBoxFill2D(0.0f, 0.0f, local_10, local_cj, -1.0f, (unsigned long)local_8g, 1);
}

// STUB: SADX 0x0059b7c0
void dsDispFadeWhite()
{
}

// STUB: SADX 0x0059b9c0
void dsDispFadeLoading()
{
}
