#include "decls.h"
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
static void DisplayTitleNew(float basez);

// FUNCTION: SADX 0x005eb290
void DrawOptionMenuSubDlgSub(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_help_options);
	ghSetPvrTexMaterial(0xffffffff);
}

// FUNCTION: SADX 0x005ee430
struct task *SetAdvaOptionMenuTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd7bc = local_8g;
	if (DAT_05edd7bc != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005ee4a0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005effc0
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005f0b00
void FUN_005f0b00(struct task *param_1)
{
	DisplayTitleNew(*(float *)((char *)param_1 + 0x10));
}

// STUB: SADX 0x005f0b20
static void DisplayTitleNew(float basez)
{
}
