#include "decls.h"
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

// STUB: SADX 0x005e93b0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005e9570
void FUN_005e9570(void *param_1)
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

#pragma optimize("", off)
// STUB: SADX 0x005eaa60
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005eae90
static void title_menu_disp(struct task *tp)
{
	DisplayTitleNew(*(float *)((char *)tp + 0x10));
}

#pragma optimize("", off)
// STUB: SADX 0x005eaeb0
static void DisplayTitleNew(float basez)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005eb250
void FreeAdvaHow2PlayTask()
{
	if (DAT_05edd784)
	{
		DestroyTask(DAT_05edd784);
	}
}
