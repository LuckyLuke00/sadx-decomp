#include "decls.h"
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

// STUB: SADX 0x005fbbc0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005fbd80
void TitleMenuWakeProcedure(struct TitleMenuWk *wkp)
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
