#include "decls.h"
extern unsigned char DAT_00982ec0[];
extern unsigned char DAT_05cd14ed;
extern struct task *DAT_05edd9b0;

// FUNCTION: SADX 0x00600e90
struct task *SetAdvaMiniGameSelTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, minigame_sel_exec);
	DAT_05edd9b0 = local_8g;
	if (DAT_05edd9b0)
	{
		local_cg = CAlloc(1, 0xd0);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_00600f10(local_8g, prmp);
		local_8g->exec = minigame_sel_exec;
		local_8g->disp = minigame_sel_disp;
	}
	return local_8g;
}

// STUB: SADX 0x00600f10
void FUN_00600f10(struct task *param_1, struct ModeSelPrmType *param_2)
{
}

// STUB: SADX 0x00600fc0
void FUN_00600fc0(void *param_1)
{
}

// FUNCTION: SADX 0x006011c0
void FUN_006011c0(void *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_MINIGAME_SEL);
	SetAdvaModeBGM((enum AvaBgmEnum)4);
	SetAdvaSerifu((enum AvaSerifuModeEnum)4);
	DAT_05cd14e1 = 1;
	FUN_00600f70(param_1);
	*(char *)((char *)param_1 + 0xcd) = 0;
	*(char *)((char *)param_1 + 0xce) = 0;
}

// FUNCTION: SADX 0x00601890
void minigame_sel_disp(struct task *tp)
{
	struct MiniGameSelWk *local_8;

	local_8 = (struct MiniGameSelWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -2.0);
	DrawMiniGameSelBg(local_8);
	FUN_00601cf0(local_8);
	DrawBCharName((enum AvaCharEnum)DAT_05cd14ed, 0xffffffff, 158.0f, 90.0f, local_8->BaseZ + -14.0);
	DrawMiniGameSelStage(local_8);
}

// FUNCTION: SADX 0x00601950
void DrawMiniGameSelBg(struct MiniGameSelWk *wkp)
{
	ghSetPvrTexMaterial(-1);
	___njSetTexture(&texlist_ava_trialactsel);
	DrawTitleBack(0.0f * ScreenRaitoX, ScreenRaitoY * 32.0f, wkp->BaseZ + -8.0f, ScreenRaitoX * 565.0f, ScreenRaitoY * 42.0f);
	ghDrawPvrTextureS(0xe, ScreenRaitoX * 32.0f, ScreenRaitoY * 42.0f, wkp->BaseZ + -14.0f, ScreenRaitoX, ScreenRaitoY);
	DrawMiniGameSelRankBg(wkp);
}

// FUNCTION: SADX 0x00601c90
int now_emblem_stg(struct MiniGameSelWk *wkp)
{
	if (DAT_05cd14ed == 6)
	{
		return 0;
	}
	if (DAT_00982ec0[(int)wkp->Stg[wkp->SelStg]] == 0x20 || DAT_00982ec0[(int)wkp->Stg[wkp->SelStg]] == 6)
	{
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x00601cf0
void FUN_00601cf0(struct MiniGameSelWk *param_1)
{
	DrawMiniGameSelEmblem(param_1);
	DrawMiniGameSelRank123(param_1);
}

// FUNCTION: SADX 0x00601d10
void DrawMiniGameSelEmblem(struct MiniGameSelWk *wkp)
{
	int local_8;

	if (now_emblem_stg(wkp) == 0)
	{
		return;
	}
	for (local_8 = 0; local_8 <= 1; local_8++)
	{
		if (AvaGetTrialEmblem((enum AvaCharEnum)DAT_05cd14ed, wkp->NowStgActPrm.StgActPtr[wkp->SelStg].Stg, local_8) != 0)
		{
			DrawEbmlem((float)(local_8 * 77.0 + 480.0), 194.0f, wkp->BaseZ + -12.0);
		}
	}
}

// FUNCTION: SADX 0x00602340
void FreeAdvaMiniGameSelTask()
{
	if (DAT_05edd9b0)
	{
		DestroyTask(DAT_05edd9b0);
	}
}
