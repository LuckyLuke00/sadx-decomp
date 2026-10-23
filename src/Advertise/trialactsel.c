#include "decls.h"
extern unsigned char DAT_05cd14ed;
void FUN_006077f0(struct TrialActSelWk *param_1);
void FUN_00606810(struct AvaStgActPrmT *param_1);
extern struct task *DAT_05edd9c0;

// STUB: SADX 0x00606730
struct task *SetAdvaTrialActSelTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// STUB: SADX 0x006067b0
void ChgSubModeToStay(struct TrialActSelWk *wkp)
{
}

// FUNCTION: SADX 0x00606810
void FUN_00606810(struct AvaStgActPrmT *param_1)
{
	GetTrialActNowAvaStgActPrm((struct AvaStgActPrmT *)((char *)param_1 + 0x30));
	FUN_00600fc0(param_1);
	*(int *)((char *)param_1 + 0x18) = 0;
	*(int *)((char *)param_1 + 0xc8) = 0;
	*(float *)((char *)param_1 + 0xc4) = 1.0f;
	*(char *)((char *)param_1 + 0xcc) = -1;
}

// FUNCTION: SADX 0x00606a00
void FUN_00606a00(struct AvaStgActPrmT *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_TRIALACT_SEL);
	SetAdvaModeBGM((enum AvaBgmEnum)4);
	SetAdvaSerifu((enum AvaSerifuModeEnum)3);
	DAT_05cd14e1 = 0;
	FUN_00606810(param_1);
	*(unsigned char *)((char *)param_1 + 0xcd) = 0;
	*(unsigned char *)((char *)param_1 + 0xce) = 0;
}

// STUB: SADX 0x00606a50
void FUN_00606a50(struct task *task)
{
}

// FUNCTION: SADX 0x00607130
void trial_act_sel_disp(struct task *tp)
{
	struct TrialActSelWk *local_8;

	local_8 = (struct TrialActSelWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -2.0);
	DrawTrialActSelBg(local_8);
	FUN_006074c0(local_8);
	DrawBCharName((enum AvaCharEnum)DAT_05cd14ed, -1, 158.0f, 90.0f, local_8->BaseZ + -14.0);
	DrawTrialActSelStage(local_8);
}

// FUNCTION: SADX 0x006074c0
void FUN_006074c0(struct TrialActSelWk *param_1)
{
	DrawTrialActSelEmblem(param_1);
	DrawTrialActSelRank(param_1);
	DrawTrialActSelTimeOrWeight(param_1);
	FUN_006077f0(param_1);
}

// STUB: SADX 0x00607500
void DrawTrialActSelEmblem(struct TrialActSelWk *wkp)
{
}

// FUNCTION: SADX 0x006075f0
void DrawTrialActSelRank(struct TrialActSelWk *wkp)
{
	long local_8;
	local_8 = AvaGetTrialBestScore((enum AvaCharEnum)DAT_05cd14ed, wkp->NowStgActPrm.StgActPtr[wkp->SelStg].Stg);
	DrawValTrialS(local_8, 6, 0, 463.0f, 260.0f, wkp->BaseZ + -12.0, 0.5f, 0.5f);
}

// FUNCTION: SADX 0x006077f0
void FUN_006077f0(struct TrialActSelWk *param_1)
{
	short local_8;
	local_8 = AvaGetTrialBestRing((enum AvaCharEnum)DAT_05cd14ed, param_1->NowStgActPrm.StgActPtr[param_1->SelStg].Stg);
	DrawValTrialS(local_8, 6, 0, 463.0f, 390.0f, param_1->BaseZ + -12.0f, 0.5f, 0.5f);
}

// FUNCTION: SADX 0x00607bc0
void FreeAdvaTrialActSelTask()
{
	if (DAT_05edd9c0)
	{
		DestroyTask(DAT_05edd9c0);
	}
}
