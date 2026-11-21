#include "decls.h"
static void title_menu_sub_exec(struct TitleMenuWk *wkp);
void FUN_005fcd40(struct task *param_1);
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp);
extern int DAT_05cd265c;
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);

// FUNCTION: SADX 0x005fbb50
struct task *SetAdvaTitleMenuTask2(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd990 = local_8g;
	if (DAT_05edd990 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005fbbc0
static void title_menu_exec(struct task *tp)
{
	struct TitleMenuWk *local_8 = (struct TitleMenuWk *)tp->awp;

	if (DAT_05cda18c->awp->work.sl[1] == 0xe && local_8->Stat == ADVA_STAT_REQWAIT)
	{
		TitleMenuWakeProcedure(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEIN;
	}
	if (DAT_05cda18c->awp->work.sl[2] == 0xe && local_8->Stat == ADVA_STAT_KEEP)
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
		title_menu_sub_exec(local_8);
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

// STUB: SADX 0x005fbd80
void TitleMenuWakeProcedure(struct TitleMenuWk *wkp)
{
}

// STUB: SADX 0x005fbe70
static void title_menu_sub_exec(struct TitleMenuWk *wkp)
{
}

// FUNCTION: SADX 0x005fca60
static void title_menu_disp(struct task *tp)
{
	struct TitleMenuWk *local_8;

	local_8 = (struct TitleMenuWk *)tp->awp;
	if (local_8->BaseCol == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	FUN_005fcd40((struct task *)local_8);
	DisplayTitleMenuCsr(local_8);
	DAT_05cd265c = 1;
}

// STUB: SADX 0x005fcac0
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp)
{
}
