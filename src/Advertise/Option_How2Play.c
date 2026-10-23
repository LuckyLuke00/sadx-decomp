#include "decls.h"
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

// FUNCTION: SADX 0x005eb250
void FreeAdvaHow2PlayTask()
{
	if (DAT_05edd784)
	{
		DestroyTask(DAT_05edd784);
	}
}
