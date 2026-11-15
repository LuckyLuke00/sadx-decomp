#include "decls.h"
static void DisplayTitleNew(float basez);
static void title_menu_exec(struct task *tp);
static void title_menu_sub_exec(struct TitleMenuWk *wkp);

extern struct task *DAT_05b42a8c;
extern int DAT_05cd265c;
extern int DAT_00987278[6];
extern unsigned char DAT_05b42a94;

void FUN_005f22c0(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_004c0e10(void *param_1);
static void title_menu_disp(struct task *tp);

// FUNCTION: SADX 0x004c0680
struct task *SetAdvaTitleMenuTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05b42a8c = local_8g;
	if (DAT_05b42a8c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = FUN_004c0db0;
	}
	return local_8g;
}

// FUNCTION: SADX 0x004c06f0
static void title_menu_exec(struct task *tp)
{
	struct TitleMenuWk *local_8 = (struct TitleMenuWk *)tp->awp;

	if (*(int *)((char *)DAT_05cda18c->awp + 4) == 6 && local_8->Stat == 0)
	{
		FUN_004c08b0(local_8);
		local_8->T = 0.0f;
		local_8->Stat = (AdvaStatEnum)1;
	}
	if (*(int *)((char *)DAT_05cda18c->awp + 8) == 6 && local_8->Stat == 2)
	{
		FUN_005b5aa0(local_8);
		local_8->T = 0.0f;
		local_8->Stat = (AdvaStatEnum)3;
	}
	switch (local_8->Stat)
	{
	case 0:
		local_8->BaseCol = 0;
		break;
	case 1:
		local_8->BaseCol = GetFadeInColFromT(local_8->T);
		local_8->T = (float)DAT_05b9d848 * 0.1f + local_8->T;
		if (local_8->T >= 1.0f)
			local_8->Stat = (AdvaStatEnum)2;
		break;
	case 2:
		local_8->WakeFlg = 0;
		*((char *)DAT_05cda18c->awp + 0x20) = 0;
		local_8->BaseCol = 0xffffffff;
		*(int *)((char *)DAT_05cda18c->awp + 0xc) = 6;
		title_menu_sub_exec(local_8);
		break;
	case 3:
		local_8->BaseCol = GetFadeOutColFromT(local_8->T);
		local_8->T = (float)DAT_05b9d848 * 0.1f + local_8->T;
		if (local_8->T >= 1.0f)
		{
			*((char *)DAT_05cda18c->awp + 0x20) = 1;
			AvaReleaseTexForEachMode((AdvaModeEnum)6);
			*((char *)DAT_05cda18c->awp + 0x1f) = 1;
			local_8->Stat = (AdvaStatEnum)0;
		}
		break;
	}
}

// STUB: SADX 0x004c08b0
void FUN_004c08b0(void *param_1)
{
}

// FUNCTION: SADX 0x004c0970
static void title_menu_sub_exec(struct TitleMenuWk *wkp)
{
	signed char local_5gu = 0;
	signed char css[3];
	signed char cs[5];

	if (!AvaGetTrialEnable())
		cs[local_5gu++] = 1;
	if (!AvaGetMissionEnable() && FUN_0040ae00())
		cs[local_5gu++] = 2;
	cs[local_5gu] = -1;
	switch (wkp->SubMode)
	{
	case 0:
		if (AvaGetPutiEnable())
			AdvaOpenDialogQuick((DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
		else
			AdvaOpenDialogQuick((DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
		wkp->SubMode = (TitleMenuSbMdEnum)1;
	case 1:
		___njSetTexture(&texlist_ava_title);
		ghSetPvrTexMaterial(0xffffffff);
		if (GetDialogStat() >= 0 && DAT_05b40a48 == 1)
		{
			wkp->SelMenu = (TitleMenuEnum)GetDialogStat();
			AvaGetPutiEnable();
			DAT_05cd14ea = DAT_00987278[wkp->SelMenu];
			switch (wkp->SelMenu)
			{
			case 0:
				CharSelAdvaModeProcedure((AdvaModeEnum)8);
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 1:
				local_5gu = 0;
				DAT_05b42a94 = 0;
				if (!GetEnableTrialActNumAll())
					css[local_5gu++] = 0;
				if (!GetEnableMiniGameNumAll())
					css[local_5gu++] = 1;
				css[local_5gu] = -1;
				AdvaOpenDialogCsrLet((DiaTypeEnum)4, 0, css);
				wkp->SubMode = (TitleMenuSbMdEnum)2;
				break;
			case 2:
				if (!FUN_0040ae00())
				{
					CmnAdvaModeProcedure((AdvaModeEnum)14);
					wkp->SubMode = (TitleMenuSbMdEnum)6;
					break;
				}
				CmnAdvaModeProcedure((AdvaModeEnum)1);
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 3:
				CmnAdvaModeProcedure((AdvaModeEnum)14);
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 4:
				CmnAdvaModeProcedure(wkp->PrevMode);
				DAT_05ccca18.lastPlayer = 0;
				AvaExtractFile();
				DAT_05cd0f30 = DAT_05ccca18;
				wkp->SubMode = (TitleMenuSbMdEnum)6;
				break;
			}
		}
		else if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
			{
				DAT_05ccca18.lastPlayer = 0;
				AvaExtractFile();
				DAT_05cd0f30 = DAT_05ccca18;
				wkp->SubMode = (TitleMenuSbMdEnum)3;
			}
		}
		else
			SetDialogNoKeyTime(0);
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
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
		else
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
		wkp->SubMode = (TitleMenuSbMdEnum)1;
		break;
	}
}

// FUNCTION: SADX 0x004c0db0
void FUN_004c0db0(struct task *param_1)
{
	char *local_8;

	local_8 = (char *)param_1->awp;
	if (*(int *)(local_8 + 0x18) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)(local_8 + 0x18));
	title_menu_disp((struct task *)local_8);
	FUN_004c0e10(local_8);
	DAT_05cd265c = 1;
}

// FUNCTION: SADX 0x004c12c0
static void title_menu_disp(struct task *tp)
{
	DisplayTitleNew(*(float *)((char *)tp + 0x10));
}

// STUB: SADX 0x004c12e0
static void DisplayTitleNew(float basez)
{
}

// FUNCTION: SADX 0x004c1680
void FUN_004c1680(void)
{
	if (DAT_05b42a8c != 0)
	{
		DestroyTask(DAT_05b42a8c);
	}
}

// FUNCTION: SADX 0x004c16a0
void ChgSeqTitleMenu()
{
	DAT_05b42a8c->awp->work.sl[1] = 0xe;
}
