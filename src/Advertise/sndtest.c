#include "decls.h"

// FUNCTION: SADX 0x006047e0
void FUN_006047e0(int param_1)
{
	*(int *)(param_1 + 0x18) = 0;
	*(int *)(param_1 + 0x38) = 0;
}

// FUNCTION: SADX 0x006049a0
void FUN_006049a0(int param_1)
{
	AvaLoadTexForEachMode((AdvaModeEnum)4);
	ghLoadFontTexture((struct GH_FONT_INFO *)&Ascii16x16FontInfo);
	ghSelectFont((struct GH_FONT_INFO *)&Ascii16x16FontInfo);
	SetAdvaBGM(-1);
	SetAdvaSerifu((AvaSerifuModeEnum)6);
	*(char *)(param_1 + 0x35) = 0;
	*(char *)(param_1 + 0x36) = 0;
	FUN_006047e0(param_1);
}

// FUNCTION: SADX 0x00605500
void snd_test_disp(struct task *tp)
{
	struct SndTestWk *local_8;

	local_8 = (struct SndTestWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -4.0);
	DrawSndTestBg(local_8);
	if (local_8->SubMode >= 3)
	{
		DrawSndTestSubMenuBg(local_8);
	}
	if (local_8->SubMode >= 3 && local_8->SubMode <= 5)
	{
		DrawSndTestSubMenuList(local_8);
	}
	if (local_8->SubMode >= 6)
	{
		DrawSndTestEffMenuBg(local_8);
		if (local_8->SubMode <= 8)
		{
			DrawSndTestEffMenuList(local_8);
		}
	}
}

// STUB: SADX 0x00605830
void FUN_00605830(unsigned long c0, unsigned long c1, float avg)
{
}

// FUNCTION: SADX 0x00605aa0
void FUN_00605aa0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, float param_5)
{
	param_2 = BetweenCol(((param_2 >> 0x10) & 0xff) << 0x10 | ((param_2 >> 8) & 0xff) << 8 | (param_2 & 0xff), param_2, param_5);
	param_4 = BetweenCol(((param_4 >> 0x10) & 0xff) << 0x10 | ((param_4 >> 8) & 0xff) << 8 | (param_4 & 0xff), param_4, param_5);
	ghSetPvrTexVertexColor(param_1, param_2, param_3, param_4);
}

// STUB: SADX 0x00606240
void DrawSndTestBg(struct SndTestWk *wkp)
{
}
