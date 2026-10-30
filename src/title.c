#include "decls.h"



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

// STUB: SADX 0x00599aa0
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
	u.x = -6613.85986328125f;
	u.y = -10572.419921875f;
	u.z = -1697.969970703125f;
	njPushMatrix(&_nj_unit_matrix_);
	FUN_0067d830(0, -1482.6300048828125f, -4582.89013671875f, 5921.56005859375f);
	if (1)
	{
		njRotateY(0, 0xce75);
	}
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

// STUB: SADX 0x0059a620
void DisplaySelectingCharacter()
{
}

// STUB: SADX 0x0059a7d0
void DisplayHint1()
{
}

// STUB: SADX 0x0059a8a0
void DisplayHint2()
{
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

// STUB: SADX 0x0059b280
void DisplayTitle_ss()
{
}

// STUB: SADX 0x0059b370
void DisplaySelectingCharacter_ss()
{
}

// STUB: SADX 0x0059b440
void DisplaySelectingStage_ss()
{
}

// STUB: SADX 0x0059b550
void DisplaySelectingSequence()
{
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
