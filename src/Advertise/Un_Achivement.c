#include "decls.h"
#include "../advertise.h"
extern int DAT_05b3e384;
extern void *DAT_05edd874;
static void title_menu_disp(struct task *tp);
extern struct task *DAT_05edd870;
void FUN_005f2090(float);

// FUNCTION: SADX 0x005f1030
struct task *SetAdvaAchivementTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, trial_game_exec);
	DAT_05edd870 = local_8g;
	if (DAT_05edd870 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = trial_game_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005f1260
void FUN_005f1260(void *param_1)
{
}

// FUNCTION: SADX 0x005f1320
void achivement_exec(struct TitleMenuWk *wkp)
{
	signed char local_5i = 0;
	signed char local_14[5];
	local_14[local_5i] = -1;
	switch (wkp->SubMode)
	{
	case 0:
		wkp->SubMode = (TitleMenuSbMdEnum)1;
	case 1:
	{
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431d10((SOCController::ControllerButton)FUN_00405f00()->FUN_00424a70()))
			DAT_05b3e384 = 1;
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431d10((SOCController::ControllerButton)7))
		{
		}
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431d10((SOCController::ControllerButton)FUN_00405f00()->FUN_00424a80()))
		{
			CmnAdvaModeProcedure(wkp->PrevMode);
			wkp->SubMode = (TitleMenuSbMdEnum)6;
			break;
		}
		if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
				wkp->SubMode = (TitleMenuSbMdEnum)3;
		}
		else
			SetDialogNoKeyTime(0);
		break;
	}
	break;
	case 2:
	{
		signed char local_15 = GetDialogStat();
		if (local_15 >= 0)
		{
			switch (local_15)
			{
			case 0:
				CharSelAdvaModeProcedure((AdvaModeEnum)3);
				DAT_05cd14e1 = 0;
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 1:
				CharSelAdvaModeProcedure((AdvaModeEnum)9);
				DAT_05cd14e1 = 1;
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 2:
				CmnAdvaModeProcedure(wkp->NextModeSub);
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			default:
				wkp->SubMode = (TitleMenuSbMdEnum)5;
				break;
			}
		}
		else if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
				wkp->SubMode = (TitleMenuSbMdEnum)3;
		}
		else
			SetDialogNoKeyTime(0);
		break;
	}
	case 3:
		if (CloseDialog())
		{
			wkp->Cnt = 0;
			wkp->SubMode = (TitleMenuSbMdEnum)4;
		}
		break;
	case 4:
		if (wkp->Cnt++ >= 20)
		{
			*(int *)((char *)DAT_05cda18c->awp + 0x10) = 107;
			CmnAdvaModeProcedure((AdvaModeEnum)0);
			wkp->SubMode = (TitleMenuSbMdEnum)6;
		}
		break;
	case 5:
		if (AvaGetPutiEnable())
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)wkp->SelMenu, local_14);
		else
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)wkp->SelMenu, local_14);
		wkp->SubMode = (TitleMenuSbMdEnum)1;
		break;
	}
}

// STUB: SADX 0x005f1600
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005f2070
void FUN_005f2070(struct task *param_1)
{
	FUN_005f2090(*(float *)((char *)param_1 + 0x10));
}

// FUNCTION: SADX 0x005f2090
void FUN_005f2090(float param_1)
{
	float local_cg;
	float local_8g;
	___njSetTexture(&texlist_ava_new_menu);
	ghSetPvrTexMaterial(0xffffffff);
	local_cg = 0.0f;
	local_8g = -18.0f;
	DrawTexture(0, 0, 0x280, 0x1e0, 0.99f, (struct Magic::RenderCore::Texture *)DAT_05edd874, 0.0f, 0.0f, 1.0f, 1.0f, -1);
	___njSetTexture(&texlist_ava_new_menu);
}

// STUB: SADX 0x005f2110
void FreeAdvaAchivementTask()
{
}
