#include "decls.h"
static void option_menu_sub_exec(struct TitleMenuWk *wkp);
static void DisplayTitleNew(float basez);
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp);
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
void FUN_005eaa00(struct task *);
extern struct task *DAT_05edd784;

// FUNCTION: SADX 0x005e9320
void DrawHow2PlayDlgSub(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_how2play);
	ghSetPvrTexMaterial(0xffffffff);
}

// FUNCTION: SADX 0x005e9340
struct task *SetAdvaHow2PlayTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd784 = local_8g;
	if (DAT_05edd784 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = FUN_005eaa00;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005e93b0
static void title_menu_exec(struct task *tp)
{
	struct TitleMenuWk *local_8 = (struct TitleMenuWk *)tp->awp;

	if (DAT_05cda18c->awp->work.sl[1] == 0x15 && local_8->Stat == ADVA_STAT_REQWAIT)
	{
		FUN_005e9570(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEIN;
	}
	if (DAT_05cda18c->awp->work.sl[2] == 0x15 && local_8->Stat == ADVA_STAT_KEEP)
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
		option_menu_sub_exec(local_8);
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

// STUB: SADX 0x005e9570
void FUN_005e9570(void *param_1)
{
}

// STUB: SADX 0x005e9630
static void option_menu_sub_exec(struct TitleMenuWk *wkp)
{
}

// FUNCTION: SADX 0x005eaa00
void FUN_005eaa00(struct task *param_1)
{
	struct TitleMenuWk *local_8;

	local_8 = (struct TitleMenuWk *)param_1->awp;
	if (local_8->BaseCol == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	title_menu_disp((struct task *)local_8);
	DisplayTitleMenuCsr(local_8);
	DAT_05cd265c = 1;
}

// STUB: SADX 0x005eaa60
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp)
{
}

// FUNCTION: SADX 0x005eae90
static void title_menu_disp(struct task *tp)
{
	DisplayTitleNew(*(float *)((char *)tp + 0x10));
}

// STUB: SADX 0x005eaeb0
static void DisplayTitleNew(float basez)
{
}

// FUNCTION: SADX 0x005eb250
void FreeAdvaHow2PlayTask()
{
	if (DAT_05edd784)
	{
		DestroyTask(DAT_05edd784);
	}
}
