#include "decls.h"
#include "../advertise.h"
#include <string.h>
extern Magic::RenderCore::Texture *DAT_05edd88c;
extern Magic::RenderCore::Texture *DAT_05edd884;
void FUN_005f24e0(void *param_1);
void FUN_005f34f0(void *param_1);
void FUN_005f3310(float);
void FUN_005f2320(struct task *);
extern struct task *DAT_05edd888;
void FUN_005f2850(struct task *);

// FUNCTION: SADX 0x005f2230
void FUN_005f2230(void)
{
	DAT_05edd870->awp->work.ul[1] = 5;
}

// FUNCTION: SADX 0x005f2250
struct task *FUN_005f2250(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005f2320);
	DAT_05edd888 = local_8g;
	if (DAT_05edd888 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, param_1);
		local_8g->exec = FUN_005f2320;
		local_8g->disp = FUN_005f2850;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005f22c0
void FUN_005f22c0(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	local_8->work.sl[1] = *(int *)param_2;
	local_8->work.sl[2] = *(int *)((char *)param_2 + 4);
	local_8->work.sl[3] = *(int *)((char *)param_2 + 8);
	*(float *)((char *)local_8 + 0x10) = 5300.0f;
	*(int *)local_8 = 0;
	*(char *)((char *)local_8 + 0x26) = 0;
	FUN_005f34f0(local_8);
}

// FUNCTION: SADX 0x005f2320
void FUN_005f2320(struct task *param_1)
{
	struct TitleMenuWk *local_8 = (struct TitleMenuWk *)param_1->awp;

	if (DAT_05cda18c->awp->work.sl[1] == 0x11 && local_8->Stat == ADVA_STAT_REQWAIT)
	{
		FUN_005f24e0(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEIN;
	}
	if (DAT_05cda18c->awp->work.sl[2] == 0x11 && local_8->Stat == ADVA_STAT_KEEP)
	{
		FUN_005b5aa0(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEOUT;
	}
	switch (local_8->Stat)
	{
	case ADVA_STAT_REQWAIT:
		local_8->BaseCol = 0;
		break;
	case ADVA_STAT_FADEIN:
		local_8->BaseCol = GetFadeInColFromT(local_8->T);
		local_8->T = (float)DAT_05b9d848 * 0.1f + local_8->T;
		if (local_8->T >= 1.0f)
			local_8->Stat = ADVA_STAT_KEEP;
		break;
	case ADVA_STAT_KEEP:
		local_8->WakeFlg = 0;
		*((char *)DAT_05cda18c->awp + 0x20) = 0;
		local_8->BaseCol = 0xffffffff;
		DAT_05cda18c->awp->work.sl[3] = 6;
		FUN_005f25a0(local_8);
		break;
	case ADVA_STAT_FADEOUT:
		local_8->BaseCol = GetFadeOutColFromT(local_8->T);
		local_8->T = (float)DAT_05b9d848 * 0.1f + local_8->T;
		if (local_8->T >= 1.0f)
		{
			*((char *)DAT_05cda18c->awp + 0x20) = 1;
			*((char *)DAT_05cda18c->awp + 0x1f) = 1;
			local_8->Stat = ADVA_STAT_REQWAIT;
		}
		break;
	}
}

// STUB: SADX 0x005f24e0
void FUN_005f24e0(void *param_1)
{
}

// FUNCTION: SADX 0x005f25a0
void FUN_005f25a0(struct TitleMenuWk *param_1)
{
	signed char local_18[5];
	signed char local_5i = 0;
	signed char local_cj[3];
	local_18[local_5i] = -1;
	switch (param_1->SubMode)
	{
	case 0:
		param_1->SubMode = (TitleMenuSbMdEnum)1;
	case 1:
	{
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431c60((SOCController::ControllerButton)7))
		{
		}
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431c60((SOCController::ControllerButton)FUN_00405f00()->FUN_00424a80()))
		{
			CmnAdvaModeProcedure((AdvaModeEnum)14);
			param_1->SubMode = (TitleMenuSbMdEnum)6;
			break;
		}
		if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
			{
				DAT_05ccca18.lastPlayer = 0;
				AvaExtractFile();
				DAT_05cd0f30 = DAT_05ccca18;
				param_1->SubMode = (TitleMenuSbMdEnum)3;
			}
		}
		else
			SetDialogNoKeyTime(0);
		break;
	}
	break;
	case 2:
	{
		signed char local_19 = GetDialogStat();
		if (local_19 >= 0)
		{
			switch (local_19)
			{
			case 0:
				CharSelAdvaModeProcedure((AdvaModeEnum)3);
				DAT_05cd14e1 = 0;
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 1:
				CharSelAdvaModeProcedure((AdvaModeEnum)9);
				DAT_05cd14e1 = 1;
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 2:
				CmnAdvaModeProcedure(param_1->NextModeSub);
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			default:
				param_1->SubMode = (TitleMenuSbMdEnum)5;
				break;
			}
		}
		else if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
				param_1->SubMode = (TitleMenuSbMdEnum)3;
		}
		else
			SetDialogNoKeyTime(0);
		break;
	}
	case 3:
		if (CloseDialog())
		{
			param_1->Cnt = 0;
			param_1->SubMode = (TitleMenuSbMdEnum)4;
		}
		break;
	case 4:
		if (param_1->Cnt++ >= 20)
		{
			*(int *)((char *)DAT_05cda18c->awp + 0x10) = 107;
			CmnAdvaModeProcedure((AdvaModeEnum)0);
			param_1->SubMode = (TitleMenuSbMdEnum)6;
		}
		break;
	case 5:
		if (AvaGetPutiEnable())
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)param_1->SelMenu, local_18);
		else
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)param_1->SelMenu, local_18);
		param_1->SubMode = (TitleMenuSbMdEnum)1;
		break;
	}
}


// FUNCTION: SADX 0x005f32f0
void FUN_005f32f0(struct task *param_1)
{
	FUN_005f3310(*(float *)((char *)param_1 + 0x10));
}

// FUNCTION: SADX 0x005f3310
void FUN_005f3310(float param_1)
{
	float local_8g;
	float local_cg;

	___njSetTexture(&texlist_ava_new_menu);
	ghSetPvrTexMaterial(0xffffffff);
	local_cg = 0.0f;
	local_8g = -18.0f;
	DrawTexture(0, 0, 0x280, 0x1e0, 0.99f, DAT_05edd884, 0.0f, 0.0f, 1.0f, 1.0f, -1);
	___njSetTexture(&texlist_ava_new_menu);
}

// FUNCTION: SADX 0x005f3390
void FUN_005f3390()
{
	if (DAT_05edd888)
	{
		DestroyTask(DAT_05edd888);
	}
	if (DAT_05edd884)
	{
		FUN_0041c2d0(DAT_05edd884);
		delete DAT_05edd884;
		DAT_05edd884 = 0;
	}
	if (DAT_05edd88c)
	{
		FUN_0041c2d0(DAT_05edd88c);
		delete DAT_05edd88c;
		DAT_05edd88c = 0;
	}
}

// FUNCTION: SADX 0x005f3460
void FUN_005f3460(void)
{
	DAT_05edd888->awp->work.ul[1] = 5;
}
