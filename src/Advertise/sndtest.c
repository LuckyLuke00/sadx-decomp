#include "decls.h"
extern int DAT_05b3ea18;
extern int DAT_05b3ebbc;
void FUN_006049a0(int param_1);
struct task *FUN_00604760(struct task *param_1, struct ModeSelPrmType *param_2);

// FUNCTION: SADX 0x006046f0
struct task *SetAdvaSndTestTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, snd_test_exec);
	DAT_05edd9bc = local_8g;
	if (DAT_05edd9bc != 0)
	{
		local_cg = CAlloc(1, 0x48);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_00604760(local_8g, prmp);
		local_8g->exec = snd_test_exec;
		local_8g->disp = snd_test_disp;
	}
	return local_8g;
}

#pragma optimize("", off)
// STUB: SADX 0x00604760
struct task *FUN_00604760(struct task *param_1, struct ModeSelPrmType *param_2)
{
	return (struct task *)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006047e0
void FUN_006047e0(int param_1)
{
	*(int *)(param_1 + 0x18) = 0;
	*(int *)(param_1 + 0x38) = 0;
}

// STUB: SADX 0x00604800
void snd_test_exec(struct task *tp)
{
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

// FUNCTION: SADX 0x006052a0
void sndeff_csr_up(struct SndTestWk *wkp)
{
	switch (wkp->SndEffCsrX)
	{
	case 0:
		if (wkp->RowMlt < 0x21)
		{
			IsndStop(0x1f);
			IsndVolume(-0x7f, 0x1f);
			wkp->CsrScale = 1.5f;
			wkp->RowMlt++;
			wkp->RowBnk = 0;
			wkp->RowSe = 0;
			if (DAT_05b3ea18 == 0)
			{
				SetBankDir(EBankNumTbl[wkp->RowMlt]);
			}
			else
			{
				SetBankDir(EBankNumTblE[wkp->RowMlt]);
			}
		}
		break;
	case 1:
		if (wkp->RowBnk < MltTbl[wkp->RowMlt]->nbBank - 1)
		{
			wkp->CsrScale = 1.5f;
			wkp->RowBnk++;
			wkp->RowSe = 0;
		}
		break;
	case 2:
		if (wkp->RowSe < MltTbl[wkp->RowMlt]->SeTbl[wkp->RowBnk].nbSe - 1)
		{
			wkp->CsrScale = 1.5f;
			wkp->RowSe++;
		}
		break;
	}
	wkp->SndEffCsrY = 0;
}

// FUNCTION: SADX 0x006053f0
void sndeff_csr_down(struct SndTestWk *wkp)
{
	switch (wkp->SndEffCsrX)
	{
	case 0:
		if (wkp->RowMlt > 0)
		{
			IsndStop(0x1f);
			IsndVolume(-0x7f, 0x1f);
			wkp->CsrScale = 1.5f;
			wkp->RowMlt--;
			wkp->RowBnk = 0;
			wkp->RowSe = 0;
			if (DAT_05b3ebbc == 0)
			{
				SetBankDir(EBankNumTbl[wkp->RowMlt]);
			}
			else
			{
				SetBankDir(EBankNumTblE[wkp->RowMlt]);
			}
		}
		break;
	case 1:
		if (wkp->RowBnk > 0)
		{
			wkp->CsrScale = 1.5f;
			wkp->RowBnk--;
			wkp->RowSe = 0;
		}
		break;
	case 2:
		if (wkp->RowSe > 0)
		{
			wkp->CsrScale = 1.5f;
			wkp->RowSe--;
		}
		break;
	}
	wkp->SndEffCsrY = 1;
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

#pragma optimize("", off)
// STUB: SADX 0x006058a0
void DrawSndTestSubMenuBg(struct SndTestWk *wkp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00605aa0
void FUN_00605aa0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, float param_5)
{
	param_2 = BetweenCol(((param_2 >> 0x10) & 0xff) << 0x10 | ((param_2 >> 8) & 0xff) << 8 | (param_2 & 0xff), param_2, param_5);
	param_4 = BetweenCol(((param_4 >> 0x10) & 0xff) << 0x10 | ((param_4 >> 8) & 0xff) << 8 | (param_4 & 0xff), param_4, param_5);
	ghSetPvrTexVertexColor(param_1, param_2, param_3, param_4);
}

// FUNCTION: SADX 0x00605db0
void draw_sndeff_arrow(unsigned long colu, unsigned long cold, int udflg, float x, float y, float z, float mag)
{
	int local_8 = (udflg != 0 ? 0x40000000 : 0);
	___njSetTexture(&texlist_ava_sndtest);
	ghSetPvrTexMaterial(0xffffffff);
	ghDrawPvrTextureS(local_8 | 0x4000005, x - 320.0f + ScreenRaitoX * 320.0f, y - 240.0f + ScreenRaitoY * 240.0f, z + -0.30000001192092896, mag, mag);
	ghDrawPvrTextureS(local_8 | 0x4000004, x - 320.0f + ScreenRaitoX * 320.0f, y - 240.0f + ScreenRaitoY * 240.0f, z, mag, mag);
	ghSetPvrTexVertexColor(colu, cold, colu, cold);
	ghDrawPvrTextureS(local_8 | 0x4000003, x - 320.0f + ScreenRaitoX * 320.0f, y - 240.0f + ScreenRaitoY * 240.0f, z + -0.6000000238418579, mag, mag);
}

// FUNCTION: SADX 0x00606240
void DrawSndTestBg(struct SndTestWk *wkp)
{
	___njSetTexture(&texlist_ava_sndtest);
	ghSetPvrTexMaterial(-1);
	DrawTitleBack(0.0f * ScreenRaitoX, ScreenRaitoY * 32.0f, wkp->BaseZ + -8.0f, ScreenRaitoX * 565.0f, ScreenRaitoY * 42.0f);
	ghDrawPvrTextureS(0xc, ScreenRaitoX * 32.0f, ScreenRaitoY * 40.0f, wkp->BaseZ + -14.0f, ScreenRaitoX, ScreenRaitoY);
}
