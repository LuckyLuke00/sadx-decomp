#include "decls.h"
static void title_menu_exec(struct task *tp);
static void title_menu_disp(struct task *tp);
extern unsigned char DAT_05edd940;
void FUN_005fa3a0(struct DDlgType *param_1);
void FUN_005fa060();
static void DisplayTitleNew(float basez);

// FUNCTION: SADX 0x005f4e40
void DrawMainMenuDlgSub_LB(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_lb_menu);
	ghSetPvrTexMaterial(0xffffffff);
}

// FUNCTION: SADX 0x005f4e60
int FUN_005f4e60()
{
	switch ((unsigned char)DAT_05edd940)
	{
		case 0:
			return 0;
		case 1:
			if (InitLB() == 0)
			{
				DAT_05edd940 = 0;
				return 0;
			}
			DAT_05edd940 = 2;
			break;
		case 2:
			DrawLB();
			break;
		case 3:
			FUN_005fa060();
			DAT_05edd940 = 0;
			return 2;
	}
	return 1;
}

// STUB: SADX 0x005f5940
void FUN_005f5940(void)
{
}

// STUB: SADX 0x005fa060
void FUN_005fa060(void)
{
}

// FUNCTION: SADX 0x005fa160
struct task *SetAdvaTitleMenuTask_LB(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd91c = local_8g;
	if (DAT_05edd91c)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	DAT_05edd940 = 0;
	return local_8g;
}

#pragma optimize("", off)
// STUB: SADX 0x005fa1e0
static void title_menu_exec(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005fa3a0
void FUN_005fa3a0(struct DDlgType *dlgp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x005fac40
static void title_menu_disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005fb390
void FUN_005fb390(struct task *param_1)
{
	DisplayTitleNew(*(float *)((char *)param_1 + 0x10));
}

#pragma optimize("", off)
// STUB: SADX 0x005fb3b0
static void DisplayTitleNew(float basez)
{
}
#pragma optimize("", on)
