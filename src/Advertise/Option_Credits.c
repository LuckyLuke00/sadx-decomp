#include "decls.h"
static void option_menu_sub_exec(struct TitleMenuWk *wkp);
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
extern struct task *DAT_05edd77c;
void FUN_005e8f10(float);

// FUNCTION: SADX 0x005e8780
struct task *SetAdvaOpCreditsTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd77c = local_8g;
	if (DAT_05edd77c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005e87f0
static void title_menu_exec(struct task *tp)
{
	struct TitleMenuWk *local_8 = (struct TitleMenuWk *)tp->awp;

	if (DAT_05cda18c->awp->work.sl[1] == 0x14 && local_8->Stat == ADVA_STAT_REQWAIT)
	{
		FUN_005e89b0(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEIN;
	}
	if (DAT_05cda18c->awp->work.sl[2] == 0x14 && local_8->Stat == ADVA_STAT_KEEP)
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

// STUB: SADX 0x005e89b0
void FUN_005e89b0(void *param_1)
{
}

// STUB: SADX 0x005e8a70
static void option_menu_sub_exec(struct TitleMenuWk *wkp)
{
}

// STUB: SADX 0x005e8d80
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005e8ef0
void FUN_005e8ef0(struct task *param_1)
{
	FUN_005e8f10(*(float *)((char *)param_1 + 0x10));
}

// STUB: SADX 0x005e9290
void FreeAdvaOpCreditsTask()
{
}
